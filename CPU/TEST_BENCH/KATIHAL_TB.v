`include "sabit_veriler.vh"

// =============================================================================
// KATIHAL (Top Module) Testbench - Behavioral Simulation Only
// =============================================================================
// Full hierarchical access to verify all sub-module functionality:
//   - I_CACHE (instruction cache)
//   - D_CACHE (data cache)
//   - REG_FILE (register file x0-x31)
//   - ALU operations
//   - MDU (multiply/divide unit)
//   - CSR registers
//   - HAZARD_UNIT (forwarding, stalling, flushing)
//   - Pipeline stages (FETCH, DECODE, EXECUTE, MEM, WB)
//   - UART, SPI, PROGRAM_LOADER
// =============================================================================

module KATIHAL_TB ();

    // -------------------------------------------
    // Test Parameters
    // -------------------------------------------
    localparam CLK_PERIOD = 200;  // 100 MHz = 10ns period
    localparam BAUD_TICKS = `CLK / `BAUD_RATE;  // Clock cycles per UART bit
    localparam TIMEOUT_CYCLES = 10000000;  // Global simulation timeout

    // -------------------------------------------
    // DUT Signals
    // -------------------------------------------
    reg        clk;
    reg        reset;
    reg        rx_enable;
    reg        uart_in;
    reg        spi_enable;
    reg        sclk_enable;
    reg        miso;
    wire       mosi;
    wire       ss;
    wire       busy;
    wire       uart_output;
    wire       sclk;
    wire [15:0] data_mem_out;

    // Test tracking
    integer test_pass = 0;
    integer test_fail = 0;
    reg loader_done_captured;
    integer cycle_count;

    // -------------------------------------------
    // DUT Connection - Behavioral sim uses direct clock, no clk_wiz
    // -------------------------------------------
    top uut (
        .clk(clk),
        .reset(reset),
        .rx_enable(rx_enable),
        .uart_in(uart_in),
        .spi_enable(spi_enable),
        .sclk_enable(sclk_enable),
        .miso(miso),
        .mosi(mosi),
        .ss(ss),
        .busy(busy),
        .uart_output(uart_output),
        .data_mem_out(data_mem_out),
        .sclk(sclk)
    );

    // -------------------------------------------
    // 100 MHz Clock Generation (10ns period)
    // -------------------------------------------
    initial begin
        clk = 0;
        forever #100 clk = ~clk;
    end

    // -------------------------------------------
    // Loader done capture
    // -------------------------------------------
    always @(posedge clk) begin
        if (reset) begin
            loader_done_captured <= 0;
        end else begin
            if (uut.PROGRAM_LOADER.done) begin
                loader_done_captured <= 1;
            end
        end
    end

    // -------------------------------------------
    // Baud Rate Timing Constants
    // -------------------------------------------
    localparam SCLK_HALF_PERIOD = (`CLK / `BAUD_RATE) / 2;

    // -------------------------------------------
    // Hierarchical Access Functions - Full Sub-module Visibility
    // -------------------------------------------

    // REG_FILE: Read any of 32 registers
    function [31:0] read_reg;
        input [4:0] idx;
        begin
            read_reg = uut.CORE.DECODE.REG_FILE.REG32[idx];
        end
    endfunction

    // I_CACHE: Read instruction cache
    function [31:0] read_icache;
        input [31:0] word_idx;
        begin
            read_icache = uut.CORE.FETCH.I_CACHE.i_cache[word_idx];
        end
    endfunction

    // D_CACHE: Read data cache
    function [31:0] read_dcache;
        input [31:0] idx;
        begin
            read_dcache = uut.CORE.MEM.D_CACHE.d_cache[idx];
        end
    endfunction

    // CSR registers
    function [31:0] read_csr;
        input [11:0] addr;
        begin
            // Access CSR via exported ports. Some internal CSR regs are not exposed
            // so read via csr_data_out when direct signals are not available.
            if (addr == 12'h305)      read_csr = uut.CORE.CSR.csr_mtvec;
            else if (addr == 12'h341) read_csr = uut.CORE.CSR.csr_mepc;
            else if (addr == 12'h300) read_csr = uut.CORE.CSR.csr_data_out; // mstatus via csr_data_out when active
            else if (addr == 12'h342) read_csr = uut.CORE.CSR.csr_data_out; // mcause
            else if (addr == 12'h344) read_csr = uut.CORE.CSR.csr_data_out; // mip (not exported separately)
            else if (addr == 12'h304) read_csr = uut.CORE.CSR.csr_data_out; // mie
            else                      read_csr = 32'h0;
        end
    endfunction

    // Program Counter
    function [31:0] read_pc;
        input dummy;
        begin
            // Use the exported fetch stage PC output (pc_out) instead of internal wire
            read_pc = uut.CORE.FETCH.pc_out;
        end
    endfunction

    // Pipeline instruction registers
    function [31:0] read_if_id_instr;
        input dummy;
        begin read_if_id_instr = uut.CORE.FETCH.instruction_out; end
    endfunction

    function [31:0] read_id_ex_instr;
        input dummy;
        // The design does not export a full "instructionE" signal; show Execute-stage PC instead
        begin read_id_ex_instr = uut.CORE.EXECUTE.pc; end
    endfunction

    // ALU
    function [31:0] read_alu_a;
        input dummy;
        // ALU instance inside EXECUTE is named 'alu'; use the EXECUTE internal alu source wire
        begin read_alu_a = uut.CORE.EXECUTE.alu_src_A; end
    endfunction

    function [31:0] read_alu_b;
        input dummy;
        // ALU second input (after immediate selection) is 'alu_src_B_imm' inside EXECUTE
        begin read_alu_b = uut.CORE.EXECUTE.alu_src_B_imm; end
    endfunction

    function [31:0] read_alu_result;
        input dummy;
        // EXECUTE exposes the ALU result as 'result_out'
        begin read_alu_result = uut.CORE.EXECUTE.result_out; end
    endfunction

    // HAZARD_UNIT
    function [1:0] read_forward_a;
        input dummy;
        begin read_forward_a = uut.CORE.HAZARD_UNIT.forwardA; end
    endfunction

    function [1:0] read_forward_b;
        input dummy;
        begin read_forward_b = uut.CORE.HAZARD_UNIT.forwardB; end
    endfunction

    function read_stall_f;
        input dummy;
        begin read_stall_f = uut.CORE.HAZARD_UNIT.stallF; end
    endfunction

    function read_stall_d;
        input dummy;
        begin read_stall_d = uut.CORE.HAZARD_UNIT.stallD; end
    endfunction

    function read_flush_d;
        input dummy;
        begin read_flush_d = uut.CORE.HAZARD_UNIT.flushD; end
    endfunction

    function read_flush_e;
        input dummy;
        begin read_flush_e = uut.CORE.HAZARD_UNIT.flushE; end
    endfunction

    // MDU
    function read_mdu_busy;
        input dummy;
        // MDU in this design is combinational (no busy signal)
        begin read_mdu_busy = 1'b0; end
    endfunction

    function read_mdu_done;
        input dummy;
        // MDU has no done flag in this implementation
        begin read_mdu_done = 1'b0; end
    endfunction

    function [31:0] read_mdu_result;
        input dummy;
        // MDU instance is inside EXECUTE as 'mdu' and its output port is 'd3'
        begin read_mdu_result = uut.CORE.EXECUTE.mdu.d3; end
    endfunction

    // PROGRAM_LOADER
    function read_loader_done;
        input dummy;
        begin read_loader_done = uut.PROGRAM_LOADER.done; end
    endfunction

    function read_loader_we;
        input dummy;
        begin read_loader_we = uut.PROGRAM_LOADER.we; end
    endfunction

    function [3:0] read_loader_state;
        input dummy;
        begin read_loader_state = uut.PROGRAM_LOADER.state; end
    endfunction

    function [31:0] read_loader_write_ptr;
        input dummy;
        begin read_loader_write_ptr = uut.PROGRAM_LOADER.write_ptr; end
    endfunction

    // CPU control
    function read_cpu_halt;
        input dummy;
        begin read_cpu_halt = uut.cpu_halt; end
    endfunction

    // -------------------------------------------
    // Verification Tasks
    // -------------------------------------------
    task check;
        input [255:0] name;
        input [31:0] actual;
        input [31:0] expected;
        begin
            if (actual === expected) begin
                $display("[PASS] %0s = 0x%08X", name, actual);
                test_pass = test_pass + 1;
            end else begin
                $display("[FAIL] %0s = 0x%08X (expected 0x%08X)", name, actual, expected);
                test_fail = test_fail + 1;
            end
        end
    endtask

    task check_1bit;
        input [255:0] name;
        input actual;
        input expected;
        begin
            if (actual === expected) begin
                $display("[PASS] %0s = %b", name, actual);
                test_pass = test_pass + 1;
            end else begin
                $display("[FAIL] %0s = %b (expected %b)", name, actual, expected);
                test_fail = test_fail + 1;
            end
        end
    endtask

    task check_16bit;
        input [255:0] name;
        input [15:0] actual;
        input [15:0] expected;
        begin
            if (actual === expected) begin
                $display("[PASS] %0s = 0x%04X", name, actual);
                test_pass = test_pass + 1;
            end else begin
                $display("[FAIL] %0s = 0x%04X (expected 0x%04X)", name, actual, expected);
                test_fail = test_fail + 1;
            end
        end
    endtask

    task check_reg;
        input [255:0] test_name;
        input [4:0]   reg_idx;
        input [31:0]  expected;
        reg   [31:0]  actual;
        begin
            // wait one clock to ensure register write-back has settled
            @(posedge clk);
            actual = read_reg(reg_idx);
            if (actual === expected) begin
                $display("[PASS] %0s | x%0d = 0x%08X", test_name, reg_idx, actual);
                test_pass = test_pass + 1;
            end else begin
                $display("[FAIL] %0s | x%0d = 0x%08X (expected 0x%08X)", test_name, reg_idx, actual, expected);
                test_fail = test_fail + 1;
            end
        end
    endtask

    // Pipeline state check
    task check_pipeline;
        begin
            $display("  Pipeline State:");
            $display("    PC = 0x%08X", read_pc(0));
            $display("    IF/ID instr = 0x%08X", read_if_id_instr(0));
            $display("    ID/EX instr = 0x%08X", read_id_ex_instr(0));
            $display("    HAZARD: forwardA=%b, forwardB=%b, stallF=%b, stallD=%b, flushD=%b, flushE=%b",
                     read_forward_a(0), read_forward_b(0), read_stall_f(0), read_stall_d(0),
                     read_flush_d(0), read_flush_e(0));
        end
    endtask

    // -------------------------------------------
    // UART Transmission Tasks
    // -------------------------------------------
    task uart_send_byte;
        input [7:0] byte_val;
        integer bit_i;
        begin
            // Start bit (LOW)
            @(posedge clk);
            uart_in = 1'b0;
            repeat (BAUD_TICKS) @(posedge clk);

            // 8 data bits (LSB first)
            for (bit_i = 0; bit_i < 8; bit_i = bit_i + 1) begin
                uart_in = byte_val[bit_i];
                repeat (BAUD_TICKS) @(posedge clk);
            end

            // Stop bit (HIGH)
            uart_in = 1'b1;
            repeat (BAUD_TICKS) @(posedge clk);
        end
    endtask

    task uart_send_word;
        input [31:0] word_val;
        begin
            uart_send_byte(word_val[7:0]);
            uart_send_byte(word_val[15:8]);
            uart_send_byte(word_val[23:16]);
            uart_send_byte(word_val[31:24]);
        end
    endtask

    // -------------------------------------------
    // SPI Transmission Tasks
    // -------------------------------------------
    task spi_send_byte;
        input [7:0] byte_val;
        integer bit_i;
        begin
            wait (ss == 1'b0);
            miso = byte_val[7];
            for (bit_i = 6; bit_i >= 0; bit_i = bit_i - 1) begin
                @(negedge sclk);
                miso = byte_val[bit_i];
            end
            wait (ss == 1'b1);
        end
    endtask

    task spi_send_word;
        input [31:0] word_val;
        begin
            spi_send_byte(word_val[7:0]);
            spi_send_byte(word_val[15:8]);
            spi_send_byte(word_val[23:16]);
            spi_send_byte(word_val[31:24]);
        end
    endtask

    // -------------------------------------------
    // Wait Tasks
    // -------------------------------------------
    task wait_loader_done;
        begin
            wait (uut.PROGRAM_LOADER.done == 1'b1);
            @(posedge clk);
            @(posedge clk);
        end
    endtask

    task wait_loader_done_timeout;
        input [31:0] max_cycles;
        input [255:0] test_name;
        integer cycle_count;
        begin
            cycle_count = 0;
            while (busy == 1'b1 && cycle_count < max_cycles) begin
                @(posedge clk);
                cycle_count = cycle_count + 1;
            end
            if (cycle_count >= max_cycles) begin
                $display("  [WARN] %0s: Loader DONE timeout", test_name);
            end
        end
    endtask

    task wait_cycles;
        input [31:0] num_cycles;
        begin
            repeat (num_cycles) @(posedge clk);
        end
    endtask

    // -------------------------------------------
    // Reset Task
    // -------------------------------------------
    task do_reset;
        begin
            @(negedge clk);
            reset       = 1;
            rx_enable   = 1;
            uart_in     = 1;
            spi_enable  = 0;
            sclk_enable = 0;
            miso        = 0;
            repeat (10) @(posedge clk);
            @(negedge clk);
            reset = 0;
            repeat (5) @(posedge clk);
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
        rx_enable   = 1;
        uart_in     = 1;
        spi_enable  = 0;
        sclk_enable = 0;
        miso        = 0;

        repeat (10) @(posedge clk);
        @(negedge clk);
        reset = 0;
        // Check PC immediately after deasserting reset (before first rising edge)
        $display("  [DBG] Immediately after reset deassert: FETCH.pc_out=0x%08X FETCH.pc_out_reg=0x%08X",
             uut.CORE.FETCH.pc_out, uut.CORE.FETCH.pc_out_reg);
        @(posedge clk);
        check("PC after reset", read_pc(0), `RESET_PC);
        repeat (5) @(posedge clk);

        // =============================================================
        // TEST 0: Reset Aftermath - Check All Sub-module States
        // =============================================================
        $display("\n============================================================");
        $display("  TEST 0: Reset Aftermath - Sub-module State Check");
        $display("============================================================");

        check_1bit("busy", busy, 1'b0);
        check_1bit("loader done", read_loader_done(0), 1'b0);
        check_1bit("loader we", read_loader_we(0), 1'b0);
        check_1bit("cpu_halt", read_cpu_halt(0), 1'b0);
        $display("  [DBG] FETCH: pc_out=0x%08X, pc_out_reg=0x%08X, stallD=%b, flushD=%b",
             uut.CORE.FETCH.pc_out, uut.CORE.FETCH.pc_out_reg, uut.CORE.HAZARD_UNIT.stallD, uut.CORE.HAZARD_UNIT.flushD);
        check("PC after reset", read_pc(0), `RESET_PC);
        check_reg("x0 always zero", 0, 32'd0);

        // =============================================================
        // TEST 1: I_CACHE Loading via UART
        // =============================================================
        $display("\n============================================================");
        $display("  TEST 1: I_CACHE Loading - UART Single NOP");
        $display("============================================================");

        rx_enable = 0;
        $display("  [%0t] Sending NOP (0x00000013) via UART...", $time);
        uart_send_word(32'h00000013);
        uart_in = 1;
        rx_enable = 1;

        wait_loader_done_timeout(1000000, "TEST 1");
        repeat (5) @(posedge clk);

        check("I_CACHE[UART_ADDR>>2]", read_icache(`UART_ADDR >> 2), 32'h00000013);
        check_1bit("busy after load", busy, 1'b0);

        // =============================================================
        // TEST 2: Register File & ALU Verification
        // =============================================================
        $display("\n============================================================");
        $display("  TEST 2: REG_FILE & ALU Operations");
        $display("============================================================");

        do_reset;

        rx_enable = 0;
        $display("  [%0t] Loading ALU test program...", $time);

        // ADDI x1 = 10, x2 = 20 -> ADD x3 = 30, SUB x4 = -10
        uart_send_word(32'h00A00093);  // ADDI x1, x0, 10
        uart_send_word(32'h01400113);  // ADDI x2, x0, 20
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h002081B3);  // ADD x3, x1, x2
        uart_send_word(32'h40208233);  // SUB x4, x1, x2 (10-20 = -10)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00302023);  // SW x3, 0(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);

        uart_in = 1;
        rx_enable = 1;

        wait_loader_done_timeout(1000000, "TEST 2 Load");

        // Let CPU execute
        cycle_count = 0;
        while (data_mem_out !== 16'd30 && cycle_count < 500) begin
            @(posedge clk);
            cycle_count = cycle_count + 1;
        end

        check_reg("ADDI x1 = 10", 1, 32'd10);
        check_reg("ADDI x2 = 20", 2, 32'd20);
        check_reg("ADD x3 = x1+x2 = 30", 3, 32'd30);
        check_reg("SUB x4 = x1-x2 = -10", 4, 32'hFFFFFFF6);
        @(posedge clk);
        check_16bit("data_mem_out (SW x3)", data_mem_out, 16'd30);

        // =============================================================
        // TEST 3: HAZARD_UNIT - Forwarding Detection
        // =============================================================
        $display("\n============================================================");
        $display("  TEST 3: HAZARD_UNIT Forwarding");
        $display("============================================================");

        do_reset;

        // Load program with data hazards
        rx_enable = 0;
        $display("  [%0t] Loading forwarding test program...", $time);

        uart_send_word(32'h00100093);  // ADDI x1, x0, 1
        uart_send_word(32'h00200113);  // ADDI x2, x0, 2
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        // These create hazards - x1 and x2 just written
        uart_send_word(32'h002081B3);  // ADD x3, x1, x2 (needs forwarding)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00302023);  // SW x3, 0(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);

        uart_in = 1;
        rx_enable = 1;

        wait_loader_done_timeout(1000000, "TEST 3");

        // Wait for store result (SW x3 -> memory) so CPU has executed
        cycle_count = 0;
        while (data_mem_out !== 16'd3 && cycle_count < 500) begin
            @(posedge clk);
            cycle_count = cycle_count + 1;
        end

        // Check forwarding was active (informational) and verify result
        $display("  Forwarding check: forwardA=%b, forwardB=%b",
                 read_forward_a(0), read_forward_b(0));

        check_reg("Forwarding: x3 = 3", 3, 32'd3);

        // =============================================================
        // TEST 4: Branch & Flush
        // =============================================================
        $display("\n============================================================");
        $display("  TEST 4: Branch (BEQ) & Pipeline Flush");
        $display("============================================================");

        do_reset;

        rx_enable = 0;
        $display("  [%0t] Loading branch test program...", $time);

        uart_send_word(32'h00A00093);  // ADDI x1, x0, 10
        uart_send_word(32'h00A00113);  // ADDI x2, x0, 10
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00208863);  // BEQ x1, x2, +16 (-> skip 4 instr)
        uart_send_word(32'h0FF00193);  // ADDI x3, x0, 0xFF (flushed)
        uart_send_word(32'h0EE00213);  // ADDI x4, x0, 0xEE (flushed)
        uart_send_word(`NOP);
        uart_send_word(32'h0AA00293);  // ADDI x5, x0, 0xAA (target)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00502023);  // SW x5, 0(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);

        uart_in = 1;
        rx_enable = 1;

        wait_loader_done_timeout(1000000, "TEST 4 Load");

        cycle_count = 0;
        while (data_mem_out !== 16'hAA && cycle_count < 300) begin
            @(posedge clk);
            cycle_count = cycle_count + 1;
        end

        $display("  [DBG-BRANCH] EXECUTE.mem_writeM=%b mem_write_data=0x%08X EXECUTE.rdM=0x%0h MEM.mem_result_out=0x%08X D_CACHE[0]=0x%08X",
             uut.CORE.EXECUTE.mem_writeM, uut.CORE.EXECUTE.mem_write_data, uut.CORE.EXECUTE.rdM, uut.CORE.MEM.mem_result_out, uut.CORE.MEM.D_CACHE.d_cache[0]);
        $display("  [DBG-BRANCH2] MEM.funct3_in=%b MEM.rdW=%0d MEM.reg_write_en=%b MEM.wb_control_out=%b MEM.wb_result_out=0x%08X CORE.wb_out=0x%08X",
             uut.CORE.MEM.funct3_in, uut.CORE.MEM.rdW, uut.CORE.MEM.reg_write_en, uut.CORE.MEM.wb_control_out, uut.CORE.MEM.wb_result_out, uut.CORE.wb_out);
        $display("  [DBG-BRANCH3] DECODE.funct3_out=%b EXECUTE.funct3_out=%b CORE.wb_controlZ=%b HAZARD.flushE=%b HAZARD.stallD=%b",
             uut.CORE.DECODE.funct3_out, uut.CORE.EXECUTE.funct3_out, uut.CORE.wb_controlZ, uut.CORE.HAZARD_UNIT.flushE, uut.CORE.HAZARD_UNIT.stallD);
        @(posedge clk);
        check_16bit("Branch target stored", data_mem_out, 16'hAA);
        check_reg("x3 flushed", 3, 32'h0);
        check_reg("x4 flushed", 4, 32'h0);
        check_reg("x5 = 0xAA", 5, 32'hAA);

        // =============================================================
        // TEST 5: MDU (Multiply/Divide Unit)
        // =============================================================
        $display("\n============================================================");
        $display("  TEST 5: MDU Operations");
        $display("============================================================");

        do_reset;

        rx_enable = 0;
        $display("  [%0t] Loading MDU test program...", $time);

        uart_send_word(32'h00000093);  // ADDI x1, x0, 0
        uart_send_word(32'h00508093);  // ADDI x1, x1, 5
        uart_send_word(32'h00000113);  // ADDI x2, x0, 0
        uart_send_word(32'h00310113);  // ADDI x2, x2, 3
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h022080B3);  // MUL x1, x1 (x1 = 5*3 = 15)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h02208133);  // DIV x2, x1, x2 (15/3 = 5)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00202023);  // SW x2, 0(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);

        uart_in = 1;
        rx_enable = 1;

        wait_loader_done_timeout(1000000, "TEST 5 Load");

        cycle_count = 0;
        while (data_mem_out !== 16'd5 && cycle_count < 500) begin
            @(posedge clk);
            cycle_count = cycle_count + 1;
        end

        check_reg("MUL result x1 = 15", 1, 32'd15);
        $display("  [DBG-MDU] mdu_control=%b mdu_src_A=0x%08X mdu_src_B=0x%08X mdu.d3=0x%08X result_out=0x%08X",
             uut.CORE.EXECUTE.mdu_control, uut.CORE.EXECUTE.mdu_src_A, uut.CORE.EXECUTE.mdu_src_B, uut.CORE.EXECUTE.mdu.d3, uut.CORE.EXECUTE.result_out);
        $display("  [DBG-MDU2] forwardA=%b forwardB=%b exe_result_in=0x%08X wb_result_in=0x%08X MEM.wb_result_out=0x%08X",
             uut.CORE.HAZARD_UNIT.forwardA, uut.CORE.HAZARD_UNIT.forwardB, uut.CORE.EXECUTE.exe_result_in, uut.CORE.EXECUTE.wb_result_in, uut.CORE.MEM.wb_result_out);
           $display("  [DBG-MDU3] DECODE.funct3_out=%b EXECUTE.funct3_out=%b CORE.wb_controlZ=%b HAZARD.flushE=%b HAZARD.stallD=%b",
                  uut.CORE.DECODE.funct3_out, uut.CORE.EXECUTE.funct3_out, uut.CORE.wb_controlZ, uut.CORE.HAZARD_UNIT.flushE, uut.CORE.HAZARD_UNIT.stallD);
        check_reg("DIV result x2 = 5", 2, 32'd5);

        // =============================================================
        // TEST 6: D_CACHE Operations
        // =============================================================
        $display("\n============================================================");
        $display("  TEST 6: D_CACHE Store/Load Operations");
        $display("============================================================");

        do_reset;

        rx_enable = 0;
        $display("  [%0t] Loading D-cache test program...", $time);

        uart_send_word(32'h123450B7);  // LUI x1, 0x12345
        uart_send_word(32'h67808093);  // ADDI x1, x1, 0x678 (x1 = 0x12345678)
        uart_send_word(32'h10000113);  // ADDI x2, x0, 0x100 (base address)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00112023);  // SW x1, 0(x2)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00012183);  // LW x3, 0(x2)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00302023);  // SW x3, 0(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);

        uart_in = 1;
        rx_enable = 1;

        wait_loader_done_timeout(1000000, "TEST 6");

        cycle_count = 0;
        while (data_mem_out !== 16'h5678 && cycle_count < 300) begin
            @(posedge clk);
            cycle_count = cycle_count + 1;
        end

        @(posedge clk);
        check_16bit("D_CACHE: LW data", data_mem_out, 16'h5678);
        $display("  [DBG-DCACHE] MEM.execute_result_out=0x%08X MEM.mem_result_out=0x%08X D_CACHE[0x%0h]=0x%08X REG32[3]=0x%08X",
             uut.CORE.MEM.execute_result_out, uut.CORE.MEM.mem_result_out, 32'h100>>2, uut.CORE.MEM.D_CACHE.d_cache[32'h100>>2], uut.CORE.DECODE.REG_FILE.REG32[3]);
        $display("  [DBG-DCACHE2] MEM.funct3_in=%b MEM.rdW=%0d MEM.reg_write_en=%b MEM.wb_control_out=%b MEM.wb_result_out=0x%08X",
             uut.CORE.MEM.funct3_in, uut.CORE.MEM.rdW, uut.CORE.MEM.reg_write_en, uut.CORE.MEM.wb_control_out, uut.CORE.MEM.wb_result_out);
           $display("  [DBG-DCACHE3] DECODE.funct3_out=%b EXECUTE.funct3_out=%b CORE.wb_controlZ=%b HAZARD.flushE=%b HAZARD.stallD=%b",
                  uut.CORE.DECODE.funct3_out, uut.CORE.EXECUTE.funct3_out, uut.CORE.wb_controlZ, uut.CORE.HAZARD_UNIT.flushE, uut.CORE.HAZARD_UNIT.stallD);
        check_reg("x3 loaded from memory", 3, 32'h12345678);

        // =============================================================
        // TEST 7: SPI Program Loading
        // =============================================================
        $display("\n============================================================");
        $display("  TEST 7: SPI Program Loading");
        $display("============================================================");

        do_reset;

        spi_enable = 1;
        sclk_enable = 1;

        $display("  [%0t] Loading program via SPI...", $time);

        spi_send_word(32'h09900093);  // ADDI x1, x0, 0x99
        spi_send_word(32'h00102023);  // SW x1, 0(x0)
        spi_send_word(`NOP);
        spi_send_word(`NOP);
        spi_send_word(`NOP);
        spi_send_word(`NOP);

        spi_enable = 0;
        sclk_enable = 0;

        wait_loader_done_timeout(1000000, "TEST 7");

        cycle_count = 0;
        while (data_mem_out !== 16'h99 && cycle_count < 200) begin
            @(posedge clk);
            cycle_count = cycle_count + 1;
        end

        check("I_CACHE[SPI_ADDR>>2]", read_icache(`SPI_ADDR >> 2), 32'h09900093);
        $display("  [DBG-SPI] I_CACHE[SPI_ADDR>>2]=0x%08X MEM.mem_result_out=0x%08X D_CACHE[%0d]=0x%08X",
             uut.CORE.FETCH.I_CACHE.i_cache[`SPI_ADDR>>2], uut.CORE.MEM.mem_result_out, `SPI_ADDR>>2, uut.CORE.MEM.D_CACHE.d_cache[`SPI_ADDR>>2]);
        $display("  [DBG-SPI2] MEM.funct3_in=%b MEM.rdW=%0d MEM.reg_write_en=%b MEM.wb_control_out=%b MEM.wb_result_out=0x%08X",
             uut.CORE.MEM.funct3_in, uut.CORE.MEM.rdW, uut.CORE.MEM.reg_write_en, uut.CORE.MEM.wb_control_out, uut.CORE.MEM.wb_result_out);
           $display("  [DBG-SPI3] DECODE.funct3_out=%b EXECUTE.funct3_out=%b CORE.wb_controlZ=%b HAZARD.flushE=%b HAZARD.stallD=%b",
                  uut.CORE.DECODE.funct3_out, uut.CORE.EXECUTE.funct3_out, uut.CORE.wb_controlZ, uut.CORE.HAZARD_UNIT.flushE, uut.CORE.HAZARD_UNIT.stallD);
        @(posedge clk);
        check_16bit("SPI loaded program result", data_mem_out, 16'h99);

        // =============================================================
        // TEST 8: CSR Register Operations
        // =============================================================
        $display("\n============================================================");
        $display("  TEST 8: CSR Operations");
        $display("============================================================");

        do_reset;

        rx_enable = 0;
        $display("  [%0t] Loading CSR test program...", $time);

        // CSRRWI x1, mscratch, 0x55
        // CSRRW x2, mstatus, x0
        uart_send_word(32'h0F100093);  // CSRRWI x1, mscratch(0x340), 0x1
        uart_send_word(32'h300021F3);  // CSRRS x3, mstatus(0x300), x0
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00302023);  // SW x3, 0(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);

        uart_in = 1;
        rx_enable = 1;

        wait_loader_done_timeout(1000000, "TEST 8");

        // Verify CSR was written
        $display("  CSR mstatus after reset: 0x%08X", read_csr(12'h300));

        // =============================================================
        // TEST 9: Comprehensive Pipeline Test
        // =============================================================
        $display("\n============================================================");
        $display("  TEST 9: Comprehensive Pipeline Test");
        $display("============================================================");

        do_reset;

        rx_enable = 0;
        $display("  [%0t] Loading comprehensive program...", $time);

        // Sequence: LUI, ADDI, ADD, SUB, AND, OR, XOR, SLL, SRL, SRA
        uart_send_word(32'h123450B7);  // LUI x1, 0x12345
        uart_send_word(32'h67808093);  // ADDI x1, x1, 0x678
        uart_send_word(32'hFF600213);  // ADDI x2, x0, -10
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h002081B3);  // ADD x3, x1, x2
        uart_send_word(32'h002091B3);  // SLL x3, x1, x2
        uart_send_word(32'h0020D1B3);  // SRL x3, x1, x2
        uart_send_word(32'h0020D1B3);  // SRA x3, x1, x2 (duplicate)
        uart_send_word(32'h0020E1B3);  // OR x3, x1, x2
        uart_send_word(32'h0020F1B3);  // AND x3, x1, x2
        uart_send_word(32'h0020C1B3);  // XOR x3, x1, x2
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00302023);  // SW x3, 0(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);

        uart_in = 1;
        rx_enable = 1;

        wait_loader_done_timeout(1000000, "TEST 9 Load");

        // Allow CPU time to execute the loaded program
        repeat (200) @(posedge clk);

        // Check final state
        check_reg("LUI+ADDI x1", 1, 32'h12345678);
        $display("  [DBG-IMM] DECODE.instruction=0x%08X DECODE.imm=0x%08X DECODE.imms_i=0x%08X FETCH.pc_out=0x%08X I_CACHE@pc=0x%08X",
             uut.CORE.DECODE.instruction, uut.CORE.DECODE.imm, uut.CORE.DECODE.imms_i, uut.CORE.FETCH.pc_out, uut.CORE.FETCH.I_CACHE.i_cache[uut.CORE.FETCH.pc_out>>2]);
        $display("  [DBG-IMM2] DECODE.funct3_out=%b EXECUTE.funct3_out=%b CORE.wb_controlZ=%b HAZARD.flushE=%b HAZARD.stallD=%b",
             uut.CORE.DECODE.funct3_out, uut.CORE.EXECUTE.funct3_out, uut.CORE.wb_controlZ, uut.CORE.HAZARD_UNIT.flushE, uut.CORE.HAZARD_UNIT.stallD);
        check_reg("ADDI x2", 2, 32'hFFFFFFF6);  // -10 in 2's complement

        // =============================================================
        // TEST 10: Load-Use Hazard (Stall)
        // =============================================================
        $display("\n============================================================");
        $display("  TEST 10: Load-Use Hazard (Stall Detection)");
        $display("============================================================");

        do_reset;

        rx_enable = 0;
        $display("  [%0t] Loading LW-use hazard program...", $time);

        uart_send_word(32'h04200093);  // ADDI x1, x0, 0x42
        uart_send_word(32'h10000113);  // ADDI x2, x0, 0x100
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00112023);  // SW x1, 0(x2)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00012183);  // LW x3, 0(x2) - Load x1 value
        uart_send_word(32'h00318233);  // ADD x4, x3, x3 (use-load hazard!)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00402023);  // SW x4, 0(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);

        uart_in = 1;
        rx_enable = 1;

        wait_loader_done_timeout(1000000, "TEST 10 Load");

        cycle_count = 0;
        while (data_mem_out !== 16'h84 && cycle_count < 300) begin
            @(posedge clk);
            cycle_count = cycle_count + 1;
            // Display hazard unit state during execution
            if (read_stall_d(0)) begin
                $display("    [%0t] Stall detected!", $time);
            end
        end

           $display("  [DBG-LOADUSE] MEM.funct3_in=%b MEM.mem_result_out=0x%08X D_CACHE[%0d]=0x%08X MEM.wb_result_out=0x%08X MEM.rdW=%0d MEM.reg_write_en=%b",
               uut.CORE.MEM.funct3_in, uut.CORE.MEM.mem_result_out, 32'h0>>2, uut.CORE.MEM.D_CACHE.d_cache[32'h0>>2], uut.CORE.MEM.wb_result_out, uut.CORE.MEM.rdW, uut.CORE.MEM.reg_write_en);
           $display("  [DBG-LOADUSE2] DECODE.funct3_out=%b EXECUTE.funct3_out=%b CORE.wb_controlZ=%b HAZARD.flushE=%b HAZARD.stallD=%b",
               uut.CORE.DECODE.funct3_out, uut.CORE.EXECUTE.funct3_out, uut.CORE.wb_controlZ, uut.CORE.HAZARD_UNIT.flushE, uut.CORE.HAZARD_UNIT.stallD);
        @(posedge clk);
        check_16bit("Load-use hazard result (0x42*2=0x84)", data_mem_out, 16'h84);
        check_reg("x3 = loaded value", 3, 32'h42);
        check_reg("x4 = x3+x3", 4, 32'h84);

        // =============================================================
        // FINAL RESULTS
        // =============================================================
        $display("\n========================================");
        $display("  TEST RESULTS: %0d passed, %0d failed", test_pass, test_fail);
        $display("========================================\n");

        #1000;
        $finish;
    end

    // -------------------------------------------
    // Timeout Watchdog
    // -------------------------------------------
    initial begin
        #2000000000;
        $display("[TIMEOUT] Simulation exceeded time limit");
        $display("Results: %0d passed, %0d failed", test_pass, test_fail);
        $finish;
    end

    // -------------------------------------------
    // VCD Dump
    // -------------------------------------------
    initial begin
        $dumpfile("KATIHAL_TB.vcd");
        $dumpvars(0, KATIHAL_TB);
    end

endmodule
