`include "sabit_veriler.vh"

// =============================================================================
// CORE Testbench — Pipeline-Aware Version
// =============================================================================
// 5-stage pipeline: FETCH -> DECODE -> EXECUTE -> MEM -> WB
//
// Forwarding paths (from HAZARD_UNIT):
//   - EX-EX:  rdM (result from MEM stage register) -> EX stage srcA/srcB
//   - MEM-EX: rdW (result from WB stage register) -> EX stage srcA/srcB
//
// This means back-to-back instructions CAN depend on each other via forwarding,
// EXCEPT for load-use hazards (stalled 1 cycle by hazard unit).
//
// Register file reads are combinational (DECODE reads), writes are on posedge (WB).
// The register file does NOT have write-before-read bypass, so values are available
// via forwarding, not via direct register reads for close dependencies.
// =============================================================================

module CORE_TB ();

    // -------------------------------------------
    // Signals
    // -------------------------------------------
    reg clk;
    reg reset;
    reg interrupt;
    reg [`DATA_WIDTH-1:0] comm_data_in;
    wire [`DATA_WIDTH-1:0] comm_data_out;

    // Program loader interface
    reg loader_we;
    reg load_done;
    reg [`DATA_WIDTH-1:0] loader_addr;
    reg [`DATA_WIDTH-1:0] loader_data;
    reg cpu_halt;

    // Test tracking
    integer test_pass = 0;
    integer test_fail = 0;
    integer test_num  = 0;

    // -------------------------------------------
    // DUT
    // -------------------------------------------
    CORE uut (
        .clk(clk),
        .reset(reset),
        .interrupt(interrupt),
        .comm_data_in(comm_data_in),
        .comm_data_out(comm_data_out),
        .loader_we(loader_we),
        .load_done(load_done),
        .loader_addr(loader_addr),
        .loader_data(loader_data),
        .cpu_halt(cpu_halt)
    );

    // -------------------------------------------
    // Clock: 100 MHz (10ns period)
    // -------------------------------------------
    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end

    // -------------------------------------------
    // Diagnostic Debug Block
    // -------------------------------------------
    always @(posedge clk) begin
        if ($time >= 13250 && $time <= 13550) begin
            $display("[DBG] Time=%0d PC_fetch=%0h PC_decode=%0h PC_execute=%0h PC_mem=%0h", 
                     $time, uut.FETCH.pc_out_reg, uut.DECODE.pc_out, uut.EXECUTE.pc, uut.MEM.pc_4-4);
            $display("      Decode: instr=%0h, csr_rd=%b, csr_wr=%b, csr_addr=%0h, csr_data_out=%0h, csr_read_en=%b, reg_write=%b, rd_addr_d=%0d", 
                     uut.DECODE.instruction, uut.DECODE.csr_rd, uut.DECODE.csr_wr, uut.DECODE.csr_addr, uut.csr_data_out, uut.DECODE.csr_read_en, uut.DECODE.reg_write, uut.DECODE.rd_addr_d);
            $display("      Execute: csr_read_en=%b, csr_data_in=%0h, result_out_reg=%0h, result_out=%0h, rdE=%0d, reg_writeM=%b", 
                     uut.EXECUTE.csr_read_en, uut.EXECUTE.csr_data_in, uut.EXECUTE.result_out_reg, uut.EXECUTE.result_out, uut.EXECUTE.rdE, uut.EXECUTE.reg_writeM);
            $display("      Mem: execute_result_in=%0h, wb_result_out=%0h, rdW=%0d, reg_write_en=%b, wb_out=%0h", 
                     uut.MEM.execute_result_in, uut.MEM.wb_result_out, uut.MEM.rdW, uut.MEM.reg_write_en, uut.wb_out);
        end
    end

    // -------------------------------------------
    // Hierarchical access helpers
    // -------------------------------------------
    function [31:0] read_reg;
        input [4:0] idx;
        begin
            read_reg = uut.DECODE.REG_FILE.REG32[idx];
        end
    endfunction

    function [31:0] read_icache;
        input [31:0] word_idx;
        begin
            read_icache = uut.FETCH.I_CACHE.i_cache[word_idx];
        end
    endfunction

    function [31:0] read_dcache;
        input [31:0] word_idx;
        begin
            read_dcache = uut.MEM.D_CACHE.d_cache[word_idx];
        end
    endfunction

    // -------------------------------------------
    // Task: Load one instruction into I_CACHE
    // -------------------------------------------
    task load_instruction;
        input [31:0] addr;
        input [31:0] instr;
        begin
            @(negedge clk);
            loader_addr = addr;
            loader_data = instr;
            loader_we   = 1;
            @(negedge clk);
            loader_we   = 0;
        end
    endtask

    // -------------------------------------------
    // Task: Load a program from program_mem array
    // -------------------------------------------
    integer prog_i;
    reg [31:0] program_mem [0:63];
    integer    program_len;

    task load_program;
        begin
            cpu_halt = 1;
            @(posedge clk);
            for (prog_i = 0; prog_i < program_len; prog_i = prog_i + 1) begin
                load_instruction(`UART_ADDR + (prog_i * 4), program_mem[prog_i]);
            end
            @(negedge clk);
            load_done = 1;
            cpu_halt  = 0;
            @(negedge clk);
            load_done = 0;
        end
    endtask

    // -------------------------------------------
    // Task: Wait N clock cycles
    // -------------------------------------------
    task wait_cycles;
        input integer n;
        integer wc;
        begin
            for (wc = 0; wc < n; wc = wc + 1)
                @(posedge clk);
        end
    endtask

    // -------------------------------------------
    // Assertion helpers
    // -------------------------------------------
    task check_reg;
        input [255:0] test_name;
        input [4:0]   reg_idx;
        input [31:0]  expected;
        reg   [31:0]  actual;
        begin
            actual = read_reg(reg_idx);
            test_num = test_num + 1;
            if (actual === expected) begin
                $display("[PASS] Test %0d: %0s | x%0d = 0x%08X", test_num, test_name, reg_idx, actual);
                test_pass = test_pass + 1;
            end else begin
                $display("[FAIL] Test %0d: %0s | x%0d = 0x%08X (expected 0x%08X)", test_num, test_name, reg_idx, actual, expected);
                test_fail = test_fail + 1;
            end
        end
    endtask

    task check_dcache;
        input [255:0] test_name;
        input [31:0]  word_addr;
        input [31:0]  expected;
        reg   [31:0]  actual;
        begin
            actual = read_dcache(word_addr);
            test_num = test_num + 1;
            if (actual === expected) begin
                $display("[PASS] Test %0d: %0s | D_CACHE[0x%0X] = 0x%08X", test_num, test_name, word_addr, actual);
                test_pass = test_pass + 1;
            end else begin
                $display("[FAIL] Test %0d: %0s | D_CACHE[0x%0X] = 0x%08X (expected 0x%08X)", test_num, test_name, word_addr, actual, expected);
                test_fail = test_fail + 1;
            end
        end
    endtask

    task halt_cpu;
        begin
            @(negedge clk);
            cpu_halt = 1;
            @(posedge clk);
        end
    endtask

    task dump_regs;
        integer ri;
        begin
            $display("  --- Register Dump ---");
            for (ri = 0; ri < 32; ri = ri + 1) begin
                if (read_reg(ri) != 0)
                    $display("    x%0d = 0x%08X", ri, read_reg(ri));
            end
        end
    endtask

    task do_reset;
        begin
            @(negedge clk); reset = 1; cpu_halt = 1;
            repeat (5) @(posedge clk);
            @(negedge clk); reset = 0;
            repeat (2) @(posedge clk);
        end
    endtask

    // =========================================================================
    // MAIN TEST SEQUENCE
    // =========================================================================
    initial begin
        // -----------------------------------------------
        // Initialization
        // -----------------------------------------------
        reset       = 1;
        interrupt   = 0;
        comm_data_in = 0;
        loader_we   = 0;
        load_done   = 0;
        loader_addr = 0;
        loader_data = 0;
        cpu_halt    = 1;
        program_len = 0;

        repeat (5) @(posedge clk);
        @(negedge clk);
        reset = 0;
        repeat (2) @(posedge clk);

        // =================================================================
        // TEST GROUP 1: Basic ADDI (independent instructions)
        // =================================================================
        // Each ADDI uses x0 as source, so there are no data dependencies.
        // All instructions can be back-to-back.
        // After the last ADDI, we need 4 NOPs to drain the pipeline.
        $display("\n============================================================");
        $display("  TEST GROUP 1: Basic ADDI (independent, x0 source)");
        $display("============================================================");

        //  [0] ADDI x1, x0, 10    -> x1 = 10
        //  [1] ADDI x2, x0, 20    -> x2 = 20
        //  [2] ADDI x3, x0, -5    -> x3 = 0xFFFFFFFB
        //  [3] ADDI x5, x0, 100   -> x5 = 100  (no dependency!)
        //  [4-7] NOP drain
        program_mem[0] = 32'h00A00093;   // ADDI x1, x0, 10
        program_mem[1] = 32'h01400113;   // ADDI x2, x0, 20
        program_mem[2] = 32'hFFB00193;   // ADDI x3, x0, -5
        program_mem[3] = 32'h06400293;   // ADDI x5, x0, 100
        program_mem[4] = `NOP;
        program_mem[5] = `NOP;
        program_mem[6] = `NOP;
        program_mem[7] = `NOP;
        program_len = 8;

        load_program;
        wait_cycles(20);
        halt_cpu;

        check_reg("ADDI x1,x0,10",   1, 32'd10);
        check_reg("ADDI x2,x0,20",   2, 32'd20);
        check_reg("ADDI x3,x0,-5",   3, 32'hFFFFFFFB);
        check_reg("ADDI x5,x0,100",  5, 32'd100);
        check_reg("x0 still zero",   0, 32'd0);

        dump_regs;
        do_reset;

        // =================================================================
        // TEST GROUP 2: ADDI with dependency (forwarding test)
        // =================================================================
        // Back-to-back dependent ADDI: forwarding should handle this.
        //  [0] ADDI x1, x0, 5     -> x1 = 5
        //  [1] ADDI x2, x1, 3     -> x2 = 8 (EX-EX forward from x1)
        //  [2] ADDI x3, x2, 7     -> x3 = 15 (EX-EX forward from x2)
        //  [3] ADDI x4, x3, 10    -> x4 = 25 (EX-EX forward from x3)
        //  [4-7] NOP drain
        $display("\n============================================================");
        $display("  TEST GROUP 2: ADDI Chain (EX-EX forwarding)");
        $display("============================================================");

        program_mem[0] = 32'h00500093;   // ADDI x1, x0, 5
        program_mem[1] = 32'h00308113;   // ADDI x2, x1, 3
        program_mem[2] = 32'h00710193;   // ADDI x3, x2, 7
        program_mem[3] = 32'h00A18213;   // ADDI x4, x3, 10
        program_mem[4] = `NOP;
        program_mem[5] = `NOP;
        program_mem[6] = `NOP;
        program_mem[7] = `NOP;
        program_len = 8;

        load_program;
        wait_cycles(20);
        halt_cpu;

        check_reg("FWD: x1=5",  1, 32'd5);
        check_reg("FWD: x2=8",  2, 32'd8);
        check_reg("FWD: x3=15", 3, 32'd15);
        check_reg("FWD: x4=25", 4, 32'd25);

        dump_regs;
        do_reset;

        // =================================================================
        // TEST GROUP 3: R-type ALU (ADD, SUB, AND, OR, XOR, SLT)
        // =================================================================
        // Load operands first, wait for them to be in register file,
        // then execute R-type instructions.
        $display("\n============================================================");
        $display("  TEST GROUP 3: R-type ALU Operations");
        $display("============================================================");

        //  [0] ADDI x1, x0, 15
        //  [1] ADDI x2, x0, 7
        //  [2-5] NOP (wait for x1,x2 to reach WB and be in reg file)
        //  [6]  ADD  x3, x1, x2   -> x3 = 22
        //  [7]  SUB  x4, x1, x2   -> x4 = 8
        //  [8]  AND  x5, x1, x2   -> x5 = 15 & 7 = 7
        //  [9]  OR   x6, x1, x2   -> x6 = 15 | 7 = 15
        //  [10] XOR  x7, x1, x2   -> x7 = 15 ^ 7 = 8
        //  [11] SLT  x8, x2, x1   -> x8 = (7 < 15) = 1
        //  [12-15] NOP drain
        program_mem[0]  = 32'h00F00093;  // ADDI x1, x0, 15
        program_mem[1]  = 32'h00700113;  // ADDI x2, x0, 7
        program_mem[2]  = `NOP;
        program_mem[3]  = `NOP;
        program_mem[4]  = `NOP;
        program_mem[5]  = `NOP;
        program_mem[6]  = 32'h002081B3;  // ADD  x3, x1, x2
        program_mem[7]  = 32'h40208233;  // SUB  x4, x1, x2
        program_mem[8]  = 32'h0020F2B3;  // AND  x5, x1, x2
        program_mem[9]  = 32'h0020E333;  // OR   x6, x1, x2
        program_mem[10] = 32'h0020C3B3;  // XOR  x7, x1, x2
        program_mem[11] = 32'h00112433;  // SLT  x8, x2, x1
        program_mem[12] = `NOP;
        program_mem[13] = `NOP;
        program_mem[14] = `NOP;
        program_mem[15] = `NOP;
        program_len = 16;

        load_program;
        wait_cycles(30);
        halt_cpu;

        check_reg("ADD x3=x1+x2=22",  3, 32'd22);
        check_reg("SUB x4=x1-x2=8",   4, 32'd8);
        check_reg("AND x5=x1&x2=7",   5, 32'd7);
        check_reg("OR  x6=x1|x2=15",  6, 32'd15);
        check_reg("XOR x7=x1^x2=8",   7, 32'd8);
        check_reg("SLT x8=(x2<x1)=1", 8, 32'd1);

        dump_regs;
        do_reset;

        // =================================================================
        // TEST GROUP 4: Shift Operations (SLLI, SRLI, SRAI)
        // =================================================================
        $display("\n============================================================");
        $display("  TEST GROUP 4: Shift Operations");
        $display("============================================================");

        //  [0] ADDI  x1, x0, 240 (0xF0)
        //  [1] ADDI  x4, x0, -16 (0xFFFFFFF0)
        //  [2-5] NOP
        //  [6] SLLI  x2, x1, 4   -> x2 = 240 << 4 = 3840
        //  [7] SRLI  x3, x1, 4   -> x3 = 240 >> 4 = 15
        //  [8] SRAI  x5, x4, 4   -> x5 = 0xFFFFFFF0 >>> 4 = 0xFFFFFFFF
        //  [9-12] NOP
        program_mem[0]  = 32'h0F000093;  // ADDI x1, x0, 0xF0
        program_mem[1]  = 32'hFF000213;  // ADDI x4, x0, -16
        program_mem[2]  = `NOP;
        program_mem[3]  = `NOP;
        program_mem[4]  = `NOP;
        program_mem[5]  = `NOP;
        program_mem[6]  = 32'h00409113;  // SLLI x2, x1, 4
        program_mem[7]  = 32'h0040D193;  // SRLI x3, x1, 4
        program_mem[8]  = 32'h40425293;  // SRAI x5, x4, 4
        program_mem[9]  = `NOP;
        program_mem[10] = `NOP;
        program_mem[11] = `NOP;
        program_mem[12] = `NOP;
        program_len = 13;

        load_program;
        wait_cycles(25);
        halt_cpu;

        check_reg("SLLI x2=240<<4=3840",   2, 32'd3840);
        check_reg("SRLI x3=240>>4=15",     3, 32'd15);
        check_reg("SRAI x5=-16>>>4=-1",    5, 32'hFFFFFFFF);

        dump_regs;
        do_reset;

        // =================================================================
        // TEST GROUP 5: LUI
        // =================================================================
        $display("\n============================================================");
        $display("  TEST GROUP 5: LUI");
        $display("============================================================");

        // LUI sets upper 20 bits, lower 12 bits = 0.
        // In your design, LUI uses ALU with alu_imm_en=1, src_A=x0(=0), so result = 0+imm_u.
        //  [0] LUI   x1, 0xDEADB -> x1 = 0xDEADB000
        //  [1] LUI   x2, 0x12345 -> x2 = 0x12345000
        //  [2-5] NOP
        program_mem[0]  = 32'hDEADB0B7;  // LUI x1, 0xDEADB
        program_mem[1]  = 32'h12345137;  // LUI x2, 0x12345
        program_mem[2]  = `NOP;
        program_mem[3]  = `NOP;
        program_mem[4]  = `NOP;
        program_mem[5]  = `NOP;
        program_len = 6;

        load_program;
        wait_cycles(15);
        halt_cpu;

        check_reg("LUI x1=0xDEADB000", 1, 32'hDEADB000);
        check_reg("LUI x2=0x12345000", 2, 32'h12345000);

        dump_regs;
        do_reset;

        // =================================================================
        // TEST GROUP 6: Store Word / Load Word (SW / LW)
        // =================================================================
        $display("\n============================================================");
        $display("  TEST GROUP 6: Store and Load Word (SW / LW)");
        $display("============================================================");

        // Store x1 to memory, then load it back into x3.
        // D_CACHE uses byte addressing with [31:2] for word select.
        //  [0] ADDI x1, x0, 0x42  -> x1 = 0x42
        //  [1] ADDI x2, x0, 0x100 -> x2 = 0x100 (base addr)
        //  [2-5] NOP (let x1, x2 reach register file)
        //  [6] SW   x1, 0(x2)     -> mem[0x100] = 0x42
        //  [7-10] NOP (wait for store to complete in MEM stage)
        //  [11] LW  x3, 0(x2)     -> x3 = mem[0x100] = 0x42
        //  [12-15] NOP
        program_mem[0]  = 32'h04200093;  // ADDI x1, x0, 0x42
        program_mem[1]  = 32'h10000113;  // ADDI x2, x0, 0x100
        program_mem[2]  = `NOP;
        program_mem[3]  = `NOP;
        program_mem[4]  = `NOP;
        program_mem[5]  = `NOP;
        program_mem[6]  = 32'h00112023;  // SW x1, 0(x2)
        program_mem[7]  = `NOP;
        program_mem[8]  = `NOP;
        program_mem[9]  = `NOP;
        program_mem[10] = `NOP;
        program_mem[11] = 32'h00012183;  // LW x3, 0(x2)
        program_mem[12] = `NOP;
        program_mem[13] = `NOP;
        program_mem[14] = `NOP;
        program_mem[15] = `NOP;
        program_len = 16;

        load_program;
        wait_cycles(30);
        halt_cpu;

        // D_CACHE is word-addressed internally: byte addr 0x100 -> word index 0x100>>2 = 0x40
        check_dcache("SW: D_CACHE[0x40]=0x42", 32'h40, 32'h00000042);
        check_reg("LW x3=mem[0x100]=0x42", 3, 32'h00000042);

        dump_regs;
        do_reset;

        // =================================================================
        // TEST GROUP 7: BEQ (Branch Equal — taken)
        // =================================================================
        $display("\n============================================================");
        $display("  TEST GROUP 7: BEQ (Branch Taken)");
        $display("============================================================");

        // BEQ is resolved in EXECUTE stage. When taken, pipeline flushes
        // DECODE (flushD) and EXECUTE (flushE).
        //
        //  [0] ADDI x1, x0, 10
        //  [1] ADDI x2, x0, 10
        //  [2-5] NOP
        //  [6] BEQ  x1, x2, +12   -> taken, jump to [9]
        //  [7] ADDI x3, x0, 0xFF  -> FLUSHED (in pipeline when branch resolves)
        //  [8] ADDI x4, x0, 0xEE  -> FLUSHED
        //  [9] ADDI x5, x0, 0xAA  -> executes, x5 = 0xAA
        //  [10-13] NOP

        // BEQ x1, x2, +12 (offset=12 bytes from BEQ's PC)
        // B-type encoding: imm[12|10:5] rs2 rs1 funct3 imm[4:1|11] opcode
        // offset=12: imm[12]=0, imm[11]=0, imm[10:5]=000000, imm[4:1]=0110
        // 0_000000 00010 00001 000 0110_0 1100011
        // = 0000000_00010_00001_000_01100_1100011
        // = 0x00208663
        program_mem[0]  = 32'h00A00093;  // ADDI x1, x0, 10
        program_mem[1]  = 32'h00A00113;  // ADDI x2, x0, 10
        program_mem[2]  = `NOP;
        program_mem[3]  = `NOP;
        program_mem[4]  = `NOP;
        program_mem[5]  = `NOP;
        program_mem[6]  = 32'h00208663;  // BEQ x1, x2, +12
        program_mem[7]  = 32'h0FF00193;  // ADDI x3, x0, 0xFF (flushed)
        program_mem[8]  = 32'h0EE00213;  // ADDI x4, x0, 0xEE (flushed)
        program_mem[9]  = 32'h0AA00293;  // ADDI x5, x0, 0xAA (target)
        program_mem[10] = `NOP;
        program_mem[11] = `NOP;
        program_mem[12] = `NOP;
        program_mem[13] = `NOP;
        program_len = 14;

        load_program;
        wait_cycles(30);
        halt_cpu;

        check_reg("BEQ flushed: x3=0", 3, 32'h00000000);
        check_reg("BEQ flushed: x4=0", 4, 32'h00000000);
        check_reg("BEQ target: x5=0xAA", 5, 32'h000000AA);

        dump_regs;
        do_reset;

        // =================================================================
        // TEST GROUP 8: BNE (Branch Not Equal — not taken)
        // =================================================================
        $display("\n============================================================");
        $display("  TEST GROUP 8: BNE (Branch Not Taken)");
        $display("============================================================");

        // x1 == x2, so BNE should NOT be taken.
        //  [0] ADDI x1, x0, 10
        //  [1] ADDI x2, x0, 10
        //  [2-5] NOP
        //  [6] BNE  x1, x2, +8   -> NOT taken (equal)
        //  [7] ADDI x3, x0, 0xBB -> executes, x3 = 0xBB
        //  [8-11] NOP
        // BNE x1, x2, +8: funct3=001
        // 0000000_00010_00001_001_01000_1100011 = 0x00209463
        program_mem[0]  = 32'h00A00093;  // ADDI x1, x0, 10
        program_mem[1]  = 32'h00A00113;  // ADDI x2, x0, 10
        program_mem[2]  = `NOP;
        program_mem[3]  = `NOP;
        program_mem[4]  = `NOP;
        program_mem[5]  = `NOP;
        program_mem[6]  = 32'h00209463;  // BNE x1, x2, +8
        program_mem[7]  = 32'h0BB00193;  // ADDI x3, x0, 0xBB
        program_mem[8]  = `NOP;
        program_mem[9]  = `NOP;
        program_mem[10] = `NOP;
        program_mem[11] = `NOP;
        program_len = 12;

        load_program;
        wait_cycles(25);
        halt_cpu;

        check_reg("BNE not taken: x3=0xBB", 3, 32'h000000BB);

        dump_regs;
        do_reset;

        // =================================================================
        // TEST GROUP 9: JAL (Jump and Link)
        // =================================================================
        $display("\n============================================================");
        $display("  TEST GROUP 9: JAL (Jump and Link)");
        $display("============================================================");

        // JAL is computed in EXECUTE: pc_target = pc + imm_j
        // The return address (PC+4) goes to rd via wb_cntrl=2'b10
        //
        // Layout (byte addresses from UART_ADDR):
        //  [0] +0x00: ADDI x1, x0, 1     -> x1 = 1
        //  [1] +0x04: JAL  x10, +12       -> x10 = UART_ADDR+0x08, jump to [4]
        //  [2] +0x08: ADDI x2, x0, 0xDD   -> flushed
        //  [3] +0x0C: ADDI x3, x0, 0xEE   -> flushed
        //  [4] +0x10: ADDI x4, x0, 0x55   -> target, x4 = 0x55
        //  [5-8] NOP

        // JAL x10, +12: imm=12=0x00C
        // J-type: imm[20|10:1|11|19:12] rd opcode
        // 12 decimal = 0b 0000 0000 0000 0000 1100
        // imm[20]=0, imm[19:12]=00000000, imm[11]=0, imm[10:1]=0000000110
        // 0_0000000110_0_00000000_01010_1101111
        // = 00000000110000000000_01010_1101111
        // Hex: Let me compute carefully
        // Bit 31: imm[20] = 0
        // Bits 30:21: imm[10:1] = 00 0000 0110
        // Bit 20: imm[11] = 0
        // Bits 19:12: imm[19:12] = 0000 0000
        // Bits 11:7: rd = 01010
        // Bits 6:0: opcode = 1101111
        // = 0000 0000 1100 0000 0000 0101 0110 1111
        // = 0x00C005EF
        program_mem[0] = 32'h00100093;   // ADDI x1, x0, 1
        program_mem[1] = 32'h00C0056F;   // JAL x10, +12
        program_mem[2] = 32'h0DD00113;   // ADDI x2, x0, 0xDD (flushed)
        program_mem[3] = 32'h0EE00193;   // ADDI x3, x0, 0xEE (flushed)
        program_mem[4] = 32'h05500213;   // ADDI x4, x0, 0x55 (target)
        program_mem[5] = `NOP;
        program_mem[6] = `NOP;
        program_mem[7] = `NOP;
        program_mem[8] = `NOP;
        program_len = 9;

        load_program;
        wait_cycles(25);
        halt_cpu;

        check_reg("JAL: x1=1",          1, 32'h00000001);
        check_reg("JAL: x2=0 (flushed)", 2, 32'h00000000);
        check_reg("JAL: x3=0 (flushed)", 3, 32'h00000000);
        check_reg("JAL: x4=0x55",        4, 32'h00000055);
        // x10 = return addr = PC_of_JAL + 4 = (UART_ADDR + 4) + 4 = UART_ADDR + 8
        check_reg("JAL: x10=ret addr",   10, `UART_ADDR + 32'h8);

        dump_regs;
        do_reset;

        // =================================================================
        // TEST GROUP 10: Immediate Logic (ANDI, ORI, XORI)
        // =================================================================
        $display("\n============================================================");
        $display("  TEST GROUP 10: Immediate Logic (ANDI, ORI, XORI)");
        $display("============================================================");

        //  [0] ADDI  x1, x0, 0xFF
        //  [1-4] NOP
        //  [5] ANDI  x2, x1, 0x0F  -> x2 = 0x0F
        //  [6] ORI   x3, x1, 0x100 -> x3 = 0x1FF
        //  [7] XORI  x4, x1, 0xFF  -> x4 = 0x00
        //  [8-11] NOP
        program_mem[0]  = 32'h0FF00093;  // ADDI x1, x0, 0xFF
        program_mem[1]  = `NOP;
        program_mem[2]  = `NOP;
        program_mem[3]  = `NOP;
        program_mem[4]  = `NOP;
        program_mem[5]  = 32'h00F0F113;  // ANDI x2, x1, 0x0F
        program_mem[6]  = 32'h1000E193;  // ORI  x3, x1, 0x100
        program_mem[7]  = 32'h0FF0C213;  // XORI x4, x1, 0xFF
        program_mem[8]  = `NOP;
        program_mem[9]  = `NOP;
        program_mem[10] = `NOP;
        program_mem[11] = `NOP;
        program_len = 12;

        load_program;
        wait_cycles(25);
        halt_cpu;

        check_reg("ANDI x2=0xFF&0x0F=0x0F",  2, 32'h0000000F);
        check_reg("ORI  x3=0xFF|0x100=0x1FF", 3, 32'h000001FF);
        check_reg("XORI x4=0xFF^0xFF=0x00",   4, 32'h00000000);

        dump_regs;
        do_reset;

        // =================================================================
        // TEST GROUP 11: SLTI / SLTIU
        // =================================================================
        $display("\n============================================================");
        $display("  TEST GROUP 11: SLTI / SLTIU");
        $display("============================================================");

        //  [0] ADDI  x1, x0, -5     -> x1 = 0xFFFFFFFB
        //  [1] ADDI  x2, x0, 10     -> x2 = 10
        //  [2-5] NOP
        //  [6] SLTI  x3, x1, 0      -> x3 = (-5 < 0) = 1
        //  [7] SLTI  x4, x2, 5      -> x4 = (10 < 5) = 0
        //  [8] SLTIU x5, x1, 1      -> x5 = (0xFFFFFFFB < 1 unsigned) = 0
        //  [9-12] NOP
        program_mem[0]  = 32'hFFB00093;  // ADDI x1, x0, -5
        program_mem[1]  = 32'h00A00113;  // ADDI x2, x0, 10
        program_mem[2]  = `NOP;
        program_mem[3]  = `NOP;
        program_mem[4]  = `NOP;
        program_mem[5]  = `NOP;
        program_mem[6]  = 32'h0000A193;  // SLTI  x3, x1, 0
        program_mem[7]  = 32'h00512213;  // SLTI  x4, x2, 5
        program_mem[8]  = 32'h0010B293;  // SLTIU x5, x1, 1
        program_mem[9]  = `NOP;
        program_mem[10] = `NOP;
        program_mem[11] = `NOP;
        program_mem[12] = `NOP;
        program_len = 13;

        load_program;
        wait_cycles(25);
        halt_cpu;

        check_reg("SLTI  x3=(-5<0)=1",       3, 32'd1);
        check_reg("SLTI  x4=(10<5)=0",        4, 32'd0);
        check_reg("SLTIU x5=(0xFFFFFFFB<1)=0", 5, 32'd0);

        dump_regs;
        do_reset;

        // =================================================================
        // TEST GROUP 12: x0 Hardwired Zero
        // =================================================================
        $display("\n============================================================");
        $display("  TEST GROUP 12: x0 Hardwired Zero");
        $display("============================================================");

        program_mem[0] = 32'h06300013;   // ADDI x0, x0, 99
        program_mem[1] = `NOP;
        program_mem[2] = `NOP;
        program_mem[3] = `NOP;
        program_mem[4] = `NOP;
        program_len = 5;

        load_program;
        wait_cycles(12);
        halt_cpu;

        check_reg("x0 stays zero after ADDI x0,x0,99", 0, 32'h00000000);

        do_reset;

        // =================================================================
        // TEST GROUP 13: MEM-EX Forwarding (2-gap dependency)
        // =================================================================
        $display("\n============================================================");
        $display("  TEST GROUP 13: MEM-EX Forwarding (2-gap)");
        $display("============================================================");

        // Instruction N produces a value, instruction N+2 uses it.
        // This tests the MEM->EX forwarding path (rdW -> EX).
        //  [0] ADDI x1, x0, 100
        //  [1] NOP                  (1 cycle gap)
        //  [2] ADDI x2, x1, 50     -> uses x1 via MEM-EX forward
        //  [3-6] NOP
        program_mem[0] = 32'h06400093;   // ADDI x1, x0, 100
        program_mem[1] = `NOP;
        program_mem[2] = 32'h03208113;   // ADDI x2, x1, 50
        program_mem[3] = `NOP;
        program_mem[4] = `NOP;
        program_mem[5] = `NOP;
        program_mem[6] = `NOP;
        program_len = 7;

        load_program;
        wait_cycles(20);
        halt_cpu;

        check_reg("MEM-EX FWD: x1=100", 1, 32'd100);
        check_reg("MEM-EX FWD: x2=150", 2, 32'd150);

        dump_regs;
        do_reset;

        // =================================================================
        // TEST GROUP 14: Basic MUL, DIV, REM
        // =================================================================
        $display("\n============================================================");
        $display("  TEST GROUP 14: Basic MUL, DIV, REM");
        $display("============================================================");
        // x1=7, x2=6, then MUL/DIV/REM/DIVU/REMU
        program_mem[0]  = 32'h00700093;  // ADDI x1, x0, 7
        program_mem[1]  = 32'h00600113;  // ADDI x2, x0, 6
        program_mem[2]  = `NOP;
        program_mem[3]  = `NOP;
        program_mem[4]  = `NOP;
        program_mem[5]  = `NOP;
        program_mem[6]  = 32'h022081B3;  // MUL  x3, x1, x2  -> 42
        program_mem[7]  = 32'h0220C233;  // DIV  x4, x1, x2  -> 1
        program_mem[8]  = 32'h0220E2B3;  // REM  x5, x1, x2  -> 1
        program_mem[9]  = 32'h0220D333;  // DIVU x6, x1, x2  -> 1
        program_mem[10] = 32'h0220F3B3;  // REMU x7, x1, x2  -> 1
        program_mem[11] = `NOP;
        program_mem[12] = `NOP;
        program_mem[13] = `NOP;
        program_mem[14] = `NOP;
        program_len = 15;

        load_program;
        wait_cycles(30);
        halt_cpu;

        check_reg("MUL  x3=7*6=42",   3, 32'd42);
        check_reg("DIV  x4=7/6=1",    4, 32'd1);
        check_reg("REM  x5=7%6=1",    5, 32'd1);
        check_reg("DIVU x6=7/6=1",    6, 32'd1);
        check_reg("REMU x7=7%6=1",    7, 32'd1);

        dump_regs;
        do_reset;

        // =================================================================
        // TEST GROUP 15: MULH — Upper 32 bits
        // =================================================================
        $display("\n============================================================");
        $display("  TEST GROUP 15: MULH (upper 32 bits)");
        $display("============================================================");
        // x1=0x10000, x2=0x10000 -> product=0x1_00000000
        // MUL  -> lower 32 = 0x00000000
        // MULH -> upper 32 = 0x00000001
        program_mem[0]  = 32'h000100B7;  // LUI x1, 0x00010 -> x1=0x10000
        program_mem[1]  = 32'h00010137;  // LUI x2, 0x00010 -> x2=0x10000
        program_mem[2]  = `NOP;
        program_mem[3]  = `NOP;
        program_mem[4]  = `NOP;
        program_mem[5]  = `NOP;
        program_mem[6]  = 32'h022081B3;  // MUL  x3, x1, x2
        program_mem[7]  = 32'h02209233;  // MULH x4, x1, x2
        program_mem[8]  = `NOP;
        program_mem[9]  = `NOP;
        program_mem[10] = `NOP;
        program_mem[11] = `NOP;
        program_len = 12;

        load_program;
        wait_cycles(25);
        halt_cpu;

        check_reg("MUL  lower=0",  3, 32'h00000000);
        check_reg("MULH upper=1",  4, 32'h00000001);

        dump_regs;
        do_reset;

        // =================================================================
        // TEST GROUP 16: Signed MUL/DIV with negatives
        // =================================================================
        $display("\n============================================================");
        $display("  TEST GROUP 16: Signed MUL/DIV with negatives");
        $display("============================================================");
        // x1=-7 (0xFFFFFFF9), x2=6
        // MUL -> (-7)*6 = -42 = 0xFFFFFFD6
        // DIV -> -7/6  = -1  = 0xFFFFFFFF
        // REM -> -7%6  = -1  = 0xFFFFFFFF
        program_mem[0]  = 32'hFF900093;  // ADDI x1, x0, -7
        program_mem[1]  = 32'h00600113;  // ADDI x2, x0, 6
        program_mem[2]  = `NOP;
        program_mem[3]  = `NOP;
        program_mem[4]  = `NOP;
        program_mem[5]  = `NOP;
        program_mem[6]  = 32'h022081B3;  // MUL x3, x1, x2
        program_mem[7]  = 32'h0220C233;  // DIV x4, x1, x2
        program_mem[8]  = 32'h0220E2B3;  // REM x5, x1, x2
        program_mem[9]  = `NOP;
        program_mem[10] = `NOP;
        program_mem[11] = `NOP;
        program_mem[12] = `NOP;
        program_len = 13;

        load_program;
        wait_cycles(25);
        halt_cpu;

        check_reg("MUL (-7)*6=-42", 3, 32'hFFFFFFD6);
        check_reg("DIV -7/6=-1",    4, 32'hFFFFFFFF);
        check_reg("REM -7%6=-1",    5, 32'hFFFFFFFF);

        dump_regs;
        do_reset;

        // =================================================================
        // TEST GROUP 17: Division by zero
        // =================================================================
        $display("\n============================================================");
        $display("  TEST GROUP 17: Division by zero");
        $display("============================================================");
        // x1=42, x0=0 (hardwired)
        // DIV  x3,x1,x0 -> 0xFFFFFFFF (per MDU impl)
        // DIVU x4,x1,x0 -> 0xFFFFFFFE (per MDU impl)
        // REM  x5,x1,x0 -> x1=42
        // REMU x6,x1,x0 -> x1=42
        // Encoding: rs2=x0=00000
        // DIV  x3,x1,x0: 0000001_00000_00001_100_00011_0110011 = 0x0200C1B3
        // DIVU x4,x1,x0: 0000001_00000_00001_101_00100_0110011 = 0x0200D233
        // REM  x5,x1,x0: 0000001_00000_00001_110_00101_0110011 = 0x0200E2B3
        // REMU x6,x1,x0: 0000001_00000_00001_111_00110_0110011 = 0x0200F333
        program_mem[0]  = 32'h02A00093;  // ADDI x1, x0, 42
        program_mem[1]  = `NOP;
        program_mem[2]  = `NOP;
        program_mem[3]  = `NOP;
        program_mem[4]  = `NOP;
        program_mem[5]  = 32'h0200C1B3;  // DIV  x3, x1, x0
        program_mem[6]  = 32'h0200D233;  // DIVU x4, x1, x0
        program_mem[7]  = 32'h0200E2B3;  // REM  x5, x1, x0
        program_mem[8]  = 32'h0200F333;  // REMU x6, x1, x0
        program_mem[9]  = `NOP;
        program_mem[10] = `NOP;
        program_mem[11] = `NOP;
        program_mem[12] = `NOP;
        program_len = 13;

        load_program;
        wait_cycles(25);
        halt_cpu;

        check_reg("DIV/0  -> 0xFFFFFFFF", 3, 32'hFFFFFFFF);
        check_reg("DIVU/0 -> 0xFFFFFFFE", 4, 32'hFFFFFFFE);
        check_reg("REM/0  -> x1=42",      5, 32'd42);
        check_reg("REMU/0 -> x1=42",      6, 32'd42);

        dump_regs;
        do_reset;

        // =================================================================
        // TEST GROUP 18: MUL with EX-EX Forwarding
        // =================================================================
        // Back-to-back: ADDI produces x1, MUL immediately uses x1.
        // Tests that MDU source muxes use forwarding correctly.
        $display("\n============================================================");
        $display("  TEST GROUP 18: MUL with EX-EX Forwarding");
        $display("============================================================");
        // [0] ADDI x1, x0, 7
        // [1] MUL  x2, x1, x1  -> 7*7=49 (EX-EX fwd on both ports)
        // [2-5] NOP
        // MUL x2,x1,x1: 0000001_00001_00001_000_00010_0110011 = 0x02108133
        program_mem[0]  = 32'h00700093;  // ADDI x1, x0, 7
        program_mem[1]  = 32'h02108133;  // MUL  x2, x1, x1
        program_mem[2]  = `NOP;
        program_mem[3]  = `NOP;
        program_mem[4]  = `NOP;
        program_mem[5]  = `NOP;
        program_len = 6;

        load_program;
        wait_cycles(20);
        halt_cpu;

        check_reg("MUL EX-EX fwd: x1=7",   1, 32'd7);
        check_reg("MUL EX-EX fwd: x2=49",  2, 32'd49);

        dump_regs;
        do_reset;

        // =================================================================
        // TEST GROUP 19: Load-Use Hazard Stall
        // =================================================================
        // LW followed immediately by an instruction that uses the loaded
        // register. The hazard unit must insert a 1-cycle stall.
        $display("\n============================================================");
        $display("  TEST GROUP 19: Load-Use Hazard Stall");
        $display("============================================================");
        // [0] ADDI x2, x0, 0x100   -> base addr
        // [1] ADDI x4, x0, 5       -> operand
        // [2] ADDI x5, x0, 0x42    -> store value
        // [3-6] NOP
        // [7] SW   x5, 0(x2)       -> mem[0x100] = 0x42
        // [8-9] NOP
        // [10] LW  x1, 0(x2)       -> x1 = 0x42 (load)
        // [11] ADD x3, x1, x4      -> x3 = 0x42+5 = 0x47 (LOAD-USE!)
        // [12-15] NOP
        program_mem[0]  = 32'h10000113;  // ADDI x2, x0, 0x100
        program_mem[1]  = 32'h00500213;  // ADDI x4, x0, 5
        program_mem[2]  = 32'h04200293;  // ADDI x5, x0, 0x42
        program_mem[3]  = `NOP;
        program_mem[4]  = `NOP;
        program_mem[5]  = `NOP;
        program_mem[6]  = `NOP;
        program_mem[7]  = 32'h00512023;  // SW x5, 0(x2)
        program_mem[8]  = `NOP;
        program_mem[9]  = `NOP;
        program_mem[10] = 32'h00012083;  // LW x1, 0(x2)
        program_mem[11] = 32'h004081B3;  // ADD x3, x1, x4  (load-use)
        program_mem[12] = `NOP;
        program_mem[13] = `NOP;
        program_mem[14] = `NOP;
        program_mem[15] = `NOP;
        program_len = 16;

        load_program;
        wait_cycles(35);
        halt_cpu;

        check_reg("LW-USE: x1=0x42",      1, 32'h00000042);
        check_reg("LW-USE: x3=0x42+5=71", 3, 32'h00000047);

        dump_regs;
        do_reset;

        // =================================================================
        // TEST GROUP 20: Dual Forwarding (both srcA & srcB)
        // =================================================================
        // Two back-to-back ADDIs, then ADD using both results.
        // Tests that forwardA and forwardB both activate simultaneously.
        $display("\n============================================================");
        $display("  TEST GROUP 20: Dual Forwarding (both A & B)");
        $display("============================================================");
        // [0] ADDI x1, x0, 10
        // [1] ADDI x2, x0, 20
        // [2] ADD  x3, x1, x2  -> x1 via MEM-EX, x2 via EX-EX
        // [3-6] NOP
        // ADD x3,x1,x2 = 0x002081B3
        program_mem[0]  = 32'h00A00093;  // ADDI x1, x0, 10
        program_mem[1]  = 32'h01400113;  // ADDI x2, x0, 20
        program_mem[2]  = 32'h002081B3;  // ADD  x3, x1, x2
        program_mem[3]  = `NOP;
        program_mem[4]  = `NOP;
        program_mem[5]  = `NOP;
        program_mem[6]  = `NOP;
        program_len = 7;

        load_program;
        wait_cycles(20);
        halt_cpu;

        check_reg("DUAL FWD: x1=10", 1, 32'd10);
        check_reg("DUAL FWD: x2=20", 2, 32'd20);
        check_reg("DUAL FWD: x3=30", 3, 32'd30);

        dump_regs;
        do_reset;

        // =================================================================
        // TEST GROUP 21: MUL chain with forwarding
        // =================================================================
        // Tests MUL -> MUL dependency chain through forwarding paths.
        $display("\n============================================================");
        $display("  TEST GROUP 21: MUL chain with forwarding");
        $display("============================================================");
        // [0] ADDI x1, x0, 3
        // [1-4] NOP
        // [5] MUL  x2, x1, x1  -> 3*3=9
        // [6] MUL  x3, x2, x1  -> 9*3=27 (EX-EX fwd x2)
        // [7-10] NOP
        // MUL x2,x1,x1 = 0x02108133
        // MUL x3,x2,x1: 0000001_00001_00010_000_00011_0110011 = 0x021101B3
        program_mem[0]  = 32'h00300093;  // ADDI x1, x0, 3
        program_mem[1]  = `NOP;
        program_mem[2]  = `NOP;
        program_mem[3]  = `NOP;
        program_mem[4]  = `NOP;
        program_mem[5]  = 32'h02108133;  // MUL x2, x1, x1 -> 9
        program_mem[6]  = 32'h021101B3;  // MUL x3, x2, x1 -> 27
        program_mem[7]  = `NOP;
        program_mem[8]  = `NOP;
        program_mem[9]  = `NOP;
        program_mem[10] = `NOP;
        program_len = 11;

        load_program;
        wait_cycles(25);
        halt_cpu;

        check_reg("MUL chain: x2=9",  2, 32'd9);
        check_reg("MUL chain: x3=27", 3, 32'd27);

        dump_regs;
        do_reset;

        // =================================================================
        // TEST GROUP 22: CSR Zicsr Instructions
        // =================================================================
        $display("\n============================================================");
        $display("  TEST GROUP 22: CSR Zicsr Instructions");
        $display("============================================================");
        // [0] LUI x1, 1          -> x1 = 0x00001000
        // [1] ADDI x10, x0, 8    -> x10 = 8 (mask for MIE)
        // [2-5] NOP
        // [6] CSRRW x2, mtvec, x1 -> writes x1 to mtvec, reads old mtvec to x2 (x2 = 0)
        // [7] CSRRS x3, mstatus, x10 -> sets MIE bit, reads old mstatus to x3 (x3 = 0)
        // [8] CSRRC x4, mstatus, x10 -> clears MIE bit, reads old mstatus to x4 (x4 = 8)
        // [9] CSRRWI x5, mie, 0x1F  -> writes 0x1F to mie, reads old mie to x5 (x5 = 0)
        // [10] CSRRSI x6, mie, 0x02  -> sets bit 1, reads old mie to x6 (x6 = 0x1F)
        // [11] CSRRCI x7, mie, 0x02  -> clears bit 1, reads old mie to x7 (x7 = 0x1F)
        // [12-15] NOP
        program_mem[0]  = 32'h000010B7;  // LUI x1, 1
        program_mem[1]  = 32'h00800513;  // ADDI x10, x0, 8
        program_mem[2]  = `NOP;
        program_mem[3]  = `NOP;
        program_mem[4]  = `NOP;
        program_mem[5]  = `NOP;
        program_mem[6]  = 32'h30509173;  // CSRRW x2, mtvec, x1
        program_mem[7]  = 32'h300521F3;  // CSRRS x3, mstatus, x10
        program_mem[8]  = 32'h30053273;  // CSRRC x4, mstatus, x10
        program_mem[9]  = 32'h304FD2F3;  // CSRRWI x5, mie, 0x1F
        program_mem[10] = 32'h30416373;  // CSRRSI x6, mie, 0x02
        program_mem[11] = 32'h304173F3;  // CSRRCI x7, mie, 0x02
        program_mem[12] = `NOP;
        program_mem[13] = `NOP;
        program_mem[14] = `NOP;
        program_mem[15] = `NOP;
        program_len = 16;

        load_program;
        wait_cycles(30);
        halt_cpu;

        check_reg("CSRRW mtvec read old",  2, 32'h00000000);
        check_reg("CSRRS mstatus read old",3, 32'h00000000);
        check_reg("CSRRC mstatus read old",4, 32'h00000008);
        check_reg("CSRRWI mie read old",   5, 32'h00000000);
        check_reg("CSRRSI mie read old",   6, 32'h0000001F);
        check_reg("CSRRCI mie read old",   7, 32'h0000001F);

        // Check CSR final values inside CSR module using hierarchical paths
        if (uut.CSR.mtvec === 32'h00001000) begin
            $display("[PASS] mtvec final value = 0x00001000");
            test_pass = test_pass + 1;
        end else begin
            $display("[FAIL] mtvec final value = 0x%08X (expected 0x00001000)", uut.CSR.mtvec);
            test_fail = test_fail + 1;
        end
        test_num = test_num + 1;

        if (uut.CSR.mstatus === 32'h00000000) begin
            $display("[PASS] mstatus final value = 0x00000000");
            test_pass = test_pass + 1;
        end else begin
            $display("[FAIL] mstatus final value = 0x%08X (expected 0x00000000)", uut.CSR.mstatus);
            test_fail = test_fail + 1;
        end
        test_num = test_num + 1;

        if (uut.CSR.mie === 32'h0000001D) begin
            $display("[PASS] mie final value = 0x0000001D");
            test_pass = test_pass + 1;
        end else begin
            $display("[FAIL] mie final value = 0x%08X (expected 0x0000001D)", uut.CSR.mie);
            test_fail = test_fail + 1;
        end
        test_num = test_num + 1;

        dump_regs;
        do_reset;

        // =================================================================
        // TEST GROUP 23: Exception Handling (ECALL)
        // =================================================================
        $display("\n============================================================");
        $display("  TEST GROUP 23: Exception Handling (ECALL)");
        $display("============================================================");
        program_mem[0]  = 32'h000010B7;  // LUI x1, 1 (0x1000)
        program_mem[1]  = 32'h40008093;  // ADDI x1, x1, 1024 (0x1400)
        program_mem[2]  = 32'h40008093;  // ADDI x1, x1, 1024 (0x1800)
        program_mem[3]  = 32'h05408093;  // ADDI x1, x1, 84   (0x1854)
        program_mem[4]  = `NOP;
        program_mem[5]  = `NOP;
        program_mem[6]  = `NOP;
        program_mem[7]  = `NOP;
        program_mem[8]  = 32'h30509073;  // CSRRW x0, mtvec, x1 (writes 0x1854 to mtvec)
        program_mem[9]  = 32'h00800113;  // ADDI x2, x0, 8
        program_mem[10] = `NOP;
        program_mem[11] = `NOP;
        program_mem[12] = `NOP;
        program_mem[13] = `NOP;
        program_mem[14] = 32'h30011073;  // CSRRW x0, mstatus, x2 (writes 8 to mstatus)
        program_mem[15] = `NOP;
        program_mem[16] = `NOP;
        program_mem[17] = `NOP;
        program_mem[18] = 32'h00000073;  // ECALL (at PC = 0x1848)
        program_mem[19] = 32'h0AA00193;  // ADDI x3, x0, 0xAA (should be flushed)
        program_mem[20] = 32'h0BB00213;  // ADDI x4, x0, 0xBB (should be flushed)
        program_mem[21] = 32'h0CC00293;  // ADDI x5, x0, 0xCC (Exception Handler starts here)
        program_mem[22] = 32'h34101373;  // CSRRW x6, mepc, x0
        program_mem[23] = 32'h34201373;  // CSRRW x7, mcause, x0
        program_mem[24] = `NOP;
        program_mem[25] = `NOP;
        program_mem[26] = `NOP;
        program_mem[27] = `NOP;
        program_len = 28;

        load_program;
        wait_cycles(45);
        halt_cpu;

        check_reg("ECALL handler executes (x5=0xCC)", 5, 32'h000000CC);
        check_reg("ECALL flushed instr 1 (x3=0)",     3, 32'h00000000);
        check_reg("ECALL flushed instr 2 (x4=0)",     4, 32'h00000000);
        check_reg("mepc saved correct PC (x6)",        6, `UART_ADDR + 32'd72);
        check_reg("mcause saved correct code (x7)",    7, 32'h00000000);

        dump_regs;
        do_reset;

        // =================================================================
        // SUMMARY
        // =================================================================
        $display("\n============================================================");
        $display("  FINAL RESULTS: %0d passed, %0d failed out of %0d tests", 
                 test_pass, test_fail, test_num);
        $display("============================================================\n");

        if (test_fail == 0)
            $display("  >>> ALL TESTS PASSED <<<\n");
        else
            $display("  >>> SOME TESTS FAILED — Check register dumps above <<<\n");

        #100;
        $finish;
    end

    // -------------------------------------------
    // Timeout watchdog
    // -------------------------------------------
    initial begin
        #5000000;
        $display("\n[TIMEOUT] Simulation exceeded time limit!");
        $finish;
    end

    // -------------------------------------------
    // VCD dump
    // -------------------------------------------
    initial begin
        $dumpfile("CORE_TB.vcd");
        $dumpvars(0, CORE_TB);
    end

endmodule