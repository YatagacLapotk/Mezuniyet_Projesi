`include "sabit_veriler.vh"
`timescale 1ns / 1ps

module DECODE_TB;

    // -------------------------------------------------------
    // Clock & Period
    // -------------------------------------------------------
    localparam CLK_PERIOD = 10;
    reg clk;
    always #(CLK_PERIOD/2) clk = ~clk;

    // -------------------------------------------------------
    // DUT Inputs
    // -------------------------------------------------------
    reg                             reset;
    reg                             flushE;
    reg                             we;
    reg  [`ADDRESS_WIDTH-1:0]       w_addr;
    reg  [`INSTRUCTION_WIDTH-1:0]   instruction;
    reg  [`DATA_WIDTH-1:0]          pc;
    reg  [`DATA_WIDTH-1:0]          wd;

    // -------------------------------------------------------
    // DUT Outputs
    // -------------------------------------------------------
    wire [`DATA_WIDTH-1:0]          pc_out;
    wire [`DATA_WIDTH-1:0]          rd1;
    wire [`DATA_WIDTH-1:0]          rd2;
    wire [`ADDRESS_WIDTH-1:0]       rd_addr_d;
    wire [`ALU_CNTR-1:0]            alu_control;
    wire                            alu_imm_en;
    wire [`MDU_CNTRL-1:0]           mdu_control;
    wire [`CSR_CNTRL-1:0]           csr_control;
    wire [`CSR_ADDR_WIDTH-1:0]      csr_addr;
    wire [`DATA_WIDTH-1:0]          csr_data;
    wire [`DATA_WIDTH-1:0]          imm;
    wire [`WB_CNTRL-1:0]            wb_cntrl;
    wire [`ISA_SLCT-1:0]            isa_slct;
    wire                            exception_type;
    wire                            reg_write;
    wire                            mem_write;
    wire                            exception;
    wire                            branch;
    wire                            jump;

    // -------------------------------------------------------
    // DUT Instantiation
    // -------------------------------------------------------
    DECODE uut (
        .clk(clk),
        .reset(reset),
        .flushE(flushE),
        .we(we),
        .w_addr(w_addr),
        .instruction(instruction),
        .pc(pc),
        .wd(wd),
        .pc_out(pc_out),
        .rd1(rd1),
        .rd2(rd2),
        .rd_addr_d(rd_addr_d),
        .alu_control(alu_control),
        .alu_imm_en(alu_imm_en),
        .mdu_control(mdu_control),
        .csr_control(csr_control),
        .csr_addr(csr_addr),
        .csr_data(csr_data),
        .imm(imm),
        .wb_cntrl(wb_cntrl),
        .isa_slct(isa_slct),
        .exception_type(exception_type),
        .reg_write(reg_write),
        .mem_write(mem_write),
        .exception(exception),
        .branch(branch),
        .jump(jump)
    );

    // -------------------------------------------------------
    // Test Counters
    // -------------------------------------------------------
    integer pass_count = 0;
    integer fail_count = 0;
    integer test_count = 0;

    // -------------------------------------------------------
    // Instruction Builder Tasks
    // -------------------------------------------------------
    // R-type: funct7[6:0] | rs2[4:0] | rs1[4:0] | funct3[2:0] | rd[4:0] | opcode[6:0]
    function [31:0] r_type_instr;
        input [6:0] funct7;
        input [4:0] rs2;
        input [4:0] rs1;
        input [2:0] funct3;
        input [4:0] rd;
        input [6:0] opcode;
        r_type_instr = {funct7, rs2, rs1, funct3, rd, opcode};
    endfunction

    // I-type: imm[11:0] | rs1[4:0] | funct3[2:0] | rd[4:0] | opcode[6:0]
    function [31:0] i_type_instr;
        input [11:0] imm_val;
        input [4:0]  rs1;
        input [2:0]  funct3;
        input [4:0]  rd;
        input [6:0]  opcode;
        i_type_instr = {imm_val, rs1, funct3, rd, opcode};
    endfunction

    // S-type: imm[11:5] | rs2[4:0] | rs1[4:0] | funct3[2:0] | imm[4:0] | opcode[6:0]
    function [31:0] s_type_instr;
        input [11:0] imm_val;
        input [4:0]  rs2;
        input [4:0]  rs1;
        input [2:0]  funct3;
        input [6:0]  opcode;
        s_type_instr = {imm_val[11:5], rs2, rs1, funct3, imm_val[4:0], opcode};
    endfunction

    // B-type: imm[12|10:5] | rs2[4:0] | rs1[4:0] | funct3[2:0] | imm[4:1|11] | opcode[6:0]
    function [31:0] b_type_instr;
        input [12:0] imm_val; // 13-bit immediate (bit 0 is always 0)
        input [4:0]  rs2;
        input [4:0]  rs1;
        input [2:0]  funct3;
        input [6:0]  opcode;
        b_type_instr = {imm_val[12], imm_val[10:5], rs2, rs1, funct3, imm_val[4:1], imm_val[11], opcode};
    endfunction

    // U-type: imm[31:12] | rd[4:0] | opcode[6:0]
    function [31:0] u_type_instr;
        input [19:0] imm_val;
        input [4:0]  rd;
        input [6:0]  opcode;
        u_type_instr = {imm_val, rd, opcode};
    endfunction

    // J-type: imm[20|10:1|11|19:12] | rd[4:0] | opcode[6:0]
    function [31:0] j_type_instr;
        input [20:0] imm_val; // 21-bit immediate (bit 0 is always 0)
        input [4:0]  rd;
        input [6:0]  opcode;
        j_type_instr = {imm_val[20], imm_val[10:1], imm_val[11], imm_val[19:12], rd, opcode};
    endfunction

    // -------------------------------------------------------
    // Check Tasks
    // -------------------------------------------------------
    task check_alu_control;
        input [`ALU_CNTR-1:0] expected;
        input [127:0] test_name;
        begin
            test_count = test_count + 1;
            if (alu_control !== expected) begin
                $display("[FAIL] %0s | alu_control: Got=%b  Expected=%b", test_name, alu_control, expected);
                fail_count = fail_count + 1;
            end else begin
                $display("[PASS] %0s | alu_control=%b", test_name, alu_control);
                pass_count = pass_count + 1;
            end
        end
    endtask

    task check_imm;
        input [`DATA_WIDTH-1:0] expected;
        input [127:0] test_name;
        begin
            test_count = test_count + 1;
            if (imm !== expected) begin
                $display("[FAIL] %0s | imm: Got=%h  Expected=%h", test_name, imm, expected);
                fail_count = fail_count + 1;
            end else begin
                $display("[PASS] %0s | imm=%h", test_name, imm);
                pass_count = pass_count + 1;
            end
        end
    endtask

    task check_signal;
        input expected;
        input actual;
        input [127:0] test_name;
        begin
            test_count = test_count + 1;
            if (actual !== expected) begin
                $display("[FAIL] %0s | Got=%b  Expected=%b", test_name, actual, expected);
                fail_count = fail_count + 1;
            end else begin
                $display("[PASS] %0s | Value=%b", test_name, actual);
                pass_count = pass_count + 1;
            end
        end
    endtask

    task check_multi_signal;
        input [31:0] expected;
        input [31:0] actual;
        input [127:0] test_name;
        begin
            test_count = test_count + 1;
            if (actual !== expected) begin
                $display("[FAIL] %0s | Got=%h  Expected=%h", test_name, actual, expected);
                fail_count = fail_count + 1;
            end else begin
                $display("[PASS] %0s | Value=%h", test_name, actual);
                pass_count = pass_count + 1;
            end
        end
    endtask

    // Wait for one clock cycle and let outputs settle
    task tick;
        begin
            @(posedge clk);
            #1; // small delay for outputs to settle
        end
    endtask

    // -------------------------------------------------------
    // Helper: write a value to a register via the reg file
    // -------------------------------------------------------
    task write_reg;
        input [4:0]  addr;
        input [31:0] data;
        begin
            we     = 1'b1;
            w_addr = addr;
            wd     = data;
            tick();
            we     = 1'b0;
        end
    endtask

    // -------------------------------------------------------
    // Main Stimulus
    // -------------------------------------------------------
    initial begin
        $dumpfile("DECODE_TB.vcd");
        $dumpvars(0, DECODE_TB);

        $display("============================================================");
        $display("         DECODE Unit Test Bench - RV32IM_Zicsr");
        $display("============================================================");

        // -------------------------------------------------------
        // Initialization
        // -------------------------------------------------------
        clk         = 0;
        reset       = 1;
        flushE      = 0;
        we          = 0;
        w_addr      = 5'b0;
        instruction = `NOP;
        pc          = 32'h00000000;
        wd          = 32'b0;

        // Apply reset
        tick();
        tick();
        reset = 0;
        tick();

        // -------------------------------------------------------
        // Pre-load some registers for read verification
        // x1 = 0x0000_000A, x2 = 0x0000_0014
        // x3 = 0xFFFF_FFF0, x5 = 0x0000_0005
        // -------------------------------------------------------
        write_reg(5'd1,  32'h0000000A);
        write_reg(5'd2,  32'h00000014);
        write_reg(5'd3,  32'hFFFFFFF0);
        write_reg(5'd5,  32'h00000005);

        $display("------------------------------------------------------------");
        $display("  Registers pre-loaded: x1=0x0A, x2=0x14, x3=0xFFF0, x5=0x05");
        $display("------------------------------------------------------------");

        // ===================================================
        //  1) R-TYPE INSTRUCTIONS (opcode = 0110011)
        // ===================================================
        $display("\n>>> R-TYPE Instructions <<<");

        // ADD x4, x1, x2  => funct7=0000000, rs2=2, rs1=1, funct3=000, rd=4
        instruction = r_type_instr(7'b0000000, 5'd2, 5'd1, 3'b000, 5'd4, 7'b0110011);
        tick();
        check_alu_control(4'b0000, "ADD  x4,x1,x2    ");
        check_signal(1'b0, alu_imm_en, "ADD  alu_imm_en   ");
        check_signal(1'b0, mem_write,  "ADD  mem_write    ");
        check_signal(1'b0, branch,     "ADD  branch       ");
        check_signal(1'b0, jump,       "ADD  jump         ");

        // SUB x4, x1, x2  => funct7=0100000, rs2=2, rs1=1, funct3=000, rd=4
        instruction = r_type_instr(7'b0100000, 5'd2, 5'd1, 3'b000, 5'd4, 7'b0110011);
        tick();
        check_alu_control(4'b0001, "SUB  x4,x1,x2    ");

        // SLL x4, x1, x2  => funct7=0000000, funct3=001
        instruction = r_type_instr(7'b0000000, 5'd2, 5'd1, 3'b001, 5'd4, 7'b0110011);
        tick();
        check_alu_control(4'b0101, "SLL  x4,x1,x2    ");

        // SLT x4, x1, x2  => funct7=0000000, funct3=010
        instruction = r_type_instr(7'b0000000, 5'd2, 5'd1, 3'b010, 5'd4, 7'b0110011);
        tick();
        check_alu_control(4'b1000, "SLT  x4,x1,x2    ");

        // SLTU x4, x1, x2 => funct7=0000000, funct3=011
        instruction = r_type_instr(7'b0000000, 5'd2, 5'd1, 3'b011, 5'd4, 7'b0110011);
        tick();
        check_alu_control(4'b1001, "SLTU x4,x1,x2    ");

        // XOR x4, x1, x2  => funct7=0000000, funct3=100
        instruction = r_type_instr(7'b0000000, 5'd2, 5'd1, 3'b100, 5'd4, 7'b0110011);
        tick();
        check_alu_control(4'b0100, "XOR  x4,x1,x2    ");

        // SRL x4, x1, x2  => funct7=0000000, funct3=101
        instruction = r_type_instr(7'b0000000, 5'd2, 5'd1, 3'b101, 5'd4, 7'b0110011);
        tick();
        check_alu_control(4'b0110, "SRL  x4,x1,x2    ");

        // SRA x4, x1, x2  => funct7=0100000, funct3=101
        instruction = r_type_instr(7'b0100000, 5'd2, 5'd1, 3'b101, 5'd4, 7'b0110011);
        tick();
        check_alu_control(4'b0111, "SRA  x4,x1,x2    ");

        // OR x4, x1, x2   => funct7=0000000, funct3=110
        instruction = r_type_instr(7'b0000000, 5'd2, 5'd1, 3'b110, 5'd4, 7'b0110011);
        tick();
        check_alu_control(4'b0010, "OR   x4,x1,x2    ");

        // AND x4, x1, x2  => funct7=0000000, funct3=111
        instruction = r_type_instr(7'b0000000, 5'd2, 5'd1, 3'b111, 5'd4, 7'b0110011);
        tick();
        check_alu_control(4'b0011, "AND  x4,x1,x2    ");

        // ===================================================
        //  2) I-TYPE ALU INSTRUCTIONS (opcode = 0010011)
        // ===================================================
        $display("\n>>> I-TYPE ALU Instructions <<<");

        // ADDI x4, x1, 100  => imm=0x064, rs1=1, funct3=000, rd=4
        instruction = i_type_instr(12'h064, 5'd1, 3'b000, 5'd4, 7'b0010011);
        tick();
        check_alu_control(4'b0000, "ADDI x4,x1,100   ");
        check_signal(1'b1, alu_imm_en, "ADDI alu_imm_en   ");
        check_imm(32'h00000064, "ADDI imm=100      ");

        // ADDI x4, x1, -1  => imm=0xFFF (sign-extended)
        instruction = i_type_instr(12'hFFF, 5'd1, 3'b000, 5'd4, 7'b0010011);
        tick();
        check_imm(32'hFFFFFFFF, "ADDI imm=-1 (sext)");

        // SLTI x4, x1, 5   => imm=0x005, funct3=010
        instruction = i_type_instr(12'h005, 5'd1, 3'b010, 5'd4, 7'b0010011);
        tick();
        check_alu_control(4'b1000, "SLTI x4,x1,5     ");

        // XORI x4, x1, 0xFF => funct3=100
        instruction = i_type_instr(12'h0FF, 5'd1, 3'b100, 5'd4, 7'b0010011);
        tick();
        check_alu_control(4'b0100, "XORI x4,x1,0xFF  ");

        // ORI x4, x1, 0xAB  => funct3=110
        instruction = i_type_instr(12'h0AB, 5'd1, 3'b110, 5'd4, 7'b0010011);
        tick();
        check_alu_control(4'b0010, "ORI  x4,x1,0xAB  ");

        // ANDI x4, x1, 0xF  => funct3=111
        instruction = i_type_instr(12'h00F, 5'd1, 3'b111, 5'd4, 7'b0010011);
        tick();
        check_alu_control(4'b0011, "ANDI x4,x1,0xF   ");

        // SLLI x4, x1, 4   => funct7=0000000, shamt=4 => imm[11:0]=0x004, funct3=001
        instruction = i_type_instr(12'h004, 5'd1, 3'b001, 5'd4, 7'b0010011);
        tick();
        check_alu_control(4'b0101, "SLLI x4,x1,4     ");

        // SRLI x4, x1, 4   => funct7=0000000, shamt=4 => imm[11:0]=0x004, funct3=101
        instruction = i_type_instr(12'h004, 5'd1, 3'b101, 5'd4, 7'b0010011);
        tick();
        check_alu_control(4'b0110, "SRLI x4,x1,4     ");

        // SRAI x4, x1, 4   => funct7=0100000, shamt=4 => imm[11:0]=0x404, funct3=101
        instruction = i_type_instr(12'h404, 5'd1, 3'b101, 5'd4, 7'b0010011);
        tick();
        check_alu_control(4'b0111, "SRAI x4,x1,4     ");

        // ===================================================
        //  3) LOAD INSTRUCTIONS (opcode = 0000011)
        // ===================================================
        $display("\n>>> LOAD Instructions <<<");

        // LW x4, 8(x1)  => imm=0x008, rs1=1, funct3=010, rd=4
        instruction = i_type_instr(12'h008, 5'd1, 3'b010, 5'd4, 7'b0000011);
        tick();
        check_alu_control(4'b0000, "LW   x4,8(x1)    ");
        check_signal(1'b1, reg_write,  "LW   reg_write    ");
        check_signal(1'b0, mem_write,  "LW   mem_write    ");

        // LH x4, 4(x1) => funct3=001
        instruction = i_type_instr(12'h004, 5'd1, 3'b001, 5'd4, 7'b0000011);
        tick();
        check_alu_control(4'b0000, "LH   x4,4(x1)    ");

        // LB x4, 2(x1) => funct3=000
        instruction = i_type_instr(12'h002, 5'd1, 3'b000, 5'd4, 7'b0000011);
        tick();
        check_alu_control(4'b0000, "LB   x4,2(x1)    ");

        // ===================================================
        //  4) STORE INSTRUCTIONS (opcode = 0100011)
        // ===================================================
        $display("\n>>> STORE Instructions <<<");

        // SW x2, 16(x1)  => imm=0x010, rs2=2, rs1=1, funct3=010
        instruction = s_type_instr(12'h010, 5'd2, 5'd1, 3'b010, 7'b0100011);
        tick();
        check_alu_control(4'b0000, "SW   x2,16(x1)   ");
        check_signal(1'b1, mem_write,  "SW   mem_write    ");
        check_signal(1'b0, reg_write,  "SW   reg_write    ");
        check_signal(1'b1, alu_imm_en, "SW   alu_imm_en   ");

        // SH x2, 8(x1) => funct3=001
        instruction = s_type_instr(12'h008, 5'd2, 5'd1, 3'b001, 7'b0100011);
        tick();
        check_signal(1'b1, mem_write, "SH   mem_write    ");

        // SB x2, 4(x1) => funct3=000
        instruction = s_type_instr(12'h004, 5'd2, 5'd1, 3'b000, 7'b0100011);
        tick();
        check_signal(1'b1, mem_write, "SB   mem_write    ");

        // ===================================================
        //  5) BRANCH INSTRUCTIONS (opcode = 1100011)
        // ===================================================
        $display("\n>>> BRANCH Instructions <<<");

        // BEQ x1, x2, offset=16  => imm=16 (13'h010), funct3=000
        instruction = b_type_instr(13'h010, 5'd2, 5'd1, 3'b000, 7'b1100011);
        tick();
        check_alu_control(4'b1010, "BEQ  x1,x2,16    ");
        check_signal(1'b1, branch,     "BEQ  branch       ");
        check_signal(1'b0, jump,       "BEQ  jump         ");
        check_signal(1'b1, alu_imm_en, "BEQ  alu_imm_en   ");

        // BNE x1, x2, offset=8 => funct3=001
        instruction = b_type_instr(13'h008, 5'd2, 5'd1, 3'b001, 7'b1100011);
        tick();
        check_alu_control(4'b1101, "BNE  x1,x2,8     ");

        // BLT x1, x2, offset=4 => funct3=100
        instruction = b_type_instr(13'h004, 5'd2, 5'd1, 3'b100, 7'b1100011);
        tick();
        check_alu_control(4'b1100, "BLT  x1,x2,4     ");

        // BGE x1, x2, offset=4 => funct3=101
        instruction = b_type_instr(13'h004, 5'd2, 5'd1, 3'b101, 7'b1100011);
        tick();
        check_alu_control(4'b1011, "BGE  x1,x2,4     ");

        // BLTU x1, x2, offset=4 => funct3=110
        instruction = b_type_instr(13'h004, 5'd2, 5'd1, 3'b110, 7'b1100011);
        tick();
        check_alu_control(4'b1110, "BLTU x1,x2,4     ");

        // BGEU x1, x2, offset=4 => funct3=111
        instruction = b_type_instr(13'h004, 5'd2, 5'd1, 3'b111, 7'b1100011);
        tick();
        check_alu_control(4'b1111, "BGEU x1,x2,4     ");

        // ===================================================
        //  6) U-TYPE INSTRUCTIONS
        // ===================================================
        $display("\n>>> U-TYPE Instructions <<<");

        // LUI x4, 0xDEADB  => opcode=0110111
        instruction = u_type_instr(20'hDEADB, 5'd4, 7'b0110111);
        tick();
        check_imm(32'hDEADB000, "LUI  x4,0xDEADB   ");
        check_signal(1'b1, alu_imm_en, "LUI  alu_imm_en   ");
        check_signal(1'b0, branch,     "LUI  branch       ");
        check_signal(1'b0, mem_write,  "LUI  mem_write    ");

        // AUIPC x4, 0x12345 => opcode=0010111
        instruction = u_type_instr(20'h12345, 5'd4, 7'b0010111);
        pc = 32'h00001000;
        tick();
        check_imm(32'h12345000, "AUIPC x4,0x12345  ");
        check_signal(1'b1, alu_imm_en, "AUIPC alu_imm_en  ");

        // ===================================================
        //  7) JAL / JALR
        // ===================================================
        $display("\n>>> JAL / JALR Instructions <<<");

        // JAL x1, offset=256 => opcode=1101111
        // imm = 21'h100 = 256
        instruction = j_type_instr(21'h100, 5'd1, 7'b1101111);
        tick();
        check_signal(1'b1, jump,       "JAL  jump         ");
        check_signal(1'b0, branch,     "JAL  branch       ");
        check_signal(1'b1, alu_imm_en, "JAL  alu_imm_en   ");

        // JALR x1, x2, 0  => opcode=1100111, funct3=000
        instruction = i_type_instr(12'h000, 5'd2, 3'b000, 5'd1, 7'b1100111);
        tick();
        check_signal(1'b1, jump,       "JALR jump         ");
        check_signal(1'b1, alu_imm_en, "JALR alu_imm_en   ");

        // ===================================================
        //  8) M-EXTENSION (funct7=0000001, opcode=0110011)
        // ===================================================
        $display("\n>>> M-Extension Instructions <<<");

        // MUL x4, x1, x2 => funct7=0000001, funct3=000
        instruction = r_type_instr(7'b0000001, 5'd2, 5'd1, 3'b000, 5'd4, 7'b0110011);
        tick();
        check_multi_signal({29'b0, 3'b000}, {29'b0, mdu_control}, "MUL  mdu_ctrl=000 ");
        check_signal(1'b1, isa_slct[0], "MUL  isa_slct     ");

        // MULH x4, x1, x2 => funct7=0000001, funct3=001
        instruction = r_type_instr(7'b0000001, 5'd2, 5'd1, 3'b001, 5'd4, 7'b0110011);
        tick();
        check_multi_signal({29'b0, 3'b001}, {29'b0, mdu_control}, "MULH mdu_ctrl=001 ");

        // DIV x4, x1, x2  => funct7=0000001, funct3=100
        instruction = r_type_instr(7'b0000001, 5'd2, 5'd1, 3'b100, 5'd4, 7'b0110011);
        tick();
        check_multi_signal({29'b0, 3'b100}, {29'b0, mdu_control}, "DIV  mdu_ctrl=100 ");

        // DIVU x4, x1, x2 => funct7=0000001, funct3=101
        instruction = r_type_instr(7'b0000001, 5'd2, 5'd1, 3'b101, 5'd4, 7'b0110011);
        tick();
        check_multi_signal({29'b0, 3'b101}, {29'b0, mdu_control}, "DIVU mdu_ctrl=101 ");

        // REM x4, x1, x2  => funct7=0000001, funct3=110
        instruction = r_type_instr(7'b0000001, 5'd2, 5'd1, 3'b110, 5'd4, 7'b0110011);
        tick();
        check_multi_signal({29'b0, 3'b110}, {29'b0, mdu_control}, "REM  mdu_ctrl=110 ");

        // REMU x4, x1, x2 => funct7=0000001, funct3=111
        instruction = r_type_instr(7'b0000001, 5'd2, 5'd1, 3'b111, 5'd4, 7'b0110011);
        tick();
        check_multi_signal({29'b0, 3'b111}, {29'b0, mdu_control}, "REMU mdu_ctrl=111 ");

        // ===================================================
        //  9) Zicsr INSTRUCTIONS (opcode = 1110011)
        // ===================================================
        $display("\n>>> Zicsr Instructions <<<");

        // CSRRW x1, mstatus, x2 => funct3=001, csr_addr=0x300
        instruction = i_type_instr(12'h300, 5'd2, 3'b001, 5'd1, 7'b1110011);
        tick();
        check_multi_signal({30'b0, 2'b01}, {30'b0, csr_control}, "CSRRW csr_ctrl=01 ");
        check_multi_signal({20'b0, 12'h300}, {20'b0, csr_addr},  "CSRRW csr_addr    ");

        // CSRRS x1, mie, x2 => funct3=010, csr_addr=0x304
        instruction = i_type_instr(12'h304, 5'd2, 3'b010, 5'd1, 7'b1110011);
        tick();
        check_multi_signal({30'b0, 2'b10}, {30'b0, csr_control}, "CSRRS csr_ctrl=10 ");

        // CSRRC x1, mtvec, x2 => funct3=011, csr_addr=0x305
        instruction = i_type_instr(12'h305, 5'd2, 3'b011, 5'd1, 7'b1110011);
        tick();
        check_multi_signal({30'b0, 2'b11}, {30'b0, csr_control}, "CSRRC csr_ctrl=11 ");

        // CSRRWI x1, mstatus, uimm=5 => funct3=101, rs1=5 (used as uimm), csr_addr=0x300
        instruction = i_type_instr(12'h300, 5'd5, 3'b101, 5'd1, 7'b1110011);
        tick();
        check_multi_signal({30'b0, 2'b01}, {30'b0, csr_control}, "CSRRWI csr_ctrl=01");
        check_multi_signal(32'h00000005, csr_data,                "CSRRWI csr_data=5 ");

        // CSRRSI x1, mstatus, uimm=3 => funct3=110, rs1=3 (uimm)
        instruction = i_type_instr(12'h300, 5'd3, 3'b110, 5'd1, 7'b1110011);
        tick();
        check_multi_signal({30'b0, 2'b10}, {30'b0, csr_control}, "CSRRSI csr_ctrl=10");
        check_multi_signal(32'h00000003, csr_data,                "CSRRSI csr_data=3 ");

        // CSRRCI x1, mstatus, uimm=7 => funct3=111, rs1=7 (uimm)
        instruction = i_type_instr(12'h300, 5'd7, 3'b111, 5'd1, 7'b1110011);
        tick();
        check_multi_signal({30'b0, 2'b11}, {30'b0, csr_control}, "CSRRCI csr_ctrl=11");
        check_multi_signal(32'h00000007, csr_data,                "CSRRCI csr_data=7 ");

        // ===================================================
        //  10) EXCEPTIONS: ECALL / EBREAK
        // ===================================================
        $display("\n>>> Exception Instructions <<<");

        // ECALL  => 32'h00000073
        instruction = 32'h00000073;
        tick();
        check_signal(1'b1, exception,      "ECALL exception   ");
        check_signal(1'b0, exception_type, "ECALL type=0      ");

        // EBREAK => 32'h00100073
        instruction = 32'h00100073;
        tick();
        check_signal(1'b1, exception,      "EBREAK exception  ");
        check_signal(1'b1, exception_type, "EBREAK type=1     ");

        // ===================================================
        //  11) REGISTER READ VERIFICATION
        //      After clock edge, rd1/rd2 should reflect
        //      register file values from previous cycle.
        // ===================================================
        $display("\n>>> Register Read Verification <<<");

        // ADD x4, x1, x2 => reads x1 and x2
        instruction = r_type_instr(7'b0000000, 5'd2, 5'd1, 3'b000, 5'd4, 7'b0110011);
        tick(); // combinational decode happens, registered on next edge
        tick(); // outputs now available
        check_multi_signal(32'h0000000A, rd1, "RegRead  rd1=x1   ");
        check_multi_signal(32'h00000014, rd2, "RegRead  rd2=x2   ");

        // ADD x6, x3, x5 => reads x3 and x5
        instruction = r_type_instr(7'b0000000, 5'd5, 5'd3, 3'b000, 5'd6, 7'b0110011);
        tick();
        tick();
        check_multi_signal(32'hFFFFFFF0, rd1, "RegRead  rd1=x3   ");
        check_multi_signal(32'h00000005, rd2, "RegRead  rd2=x5   ");

        // ===================================================
        //  12) PC PASSTHROUGH
        // ===================================================
        $display("\n>>> PC Passthrough <<<");

        pc = 32'h0000_1234;
        instruction = `NOP;
        tick();
        check_multi_signal(32'h00001234, pc_out, "PC passthrough    ");

        // ===================================================
        //  13) FLUSH (flushE)
        // ===================================================
        $display("\n>>> FlushE Test <<<");

        // Load a real instruction first
        instruction = r_type_instr(7'b0000000, 5'd2, 5'd1, 3'b000, 5'd4, 7'b0110011);
        tick();

        // Now assert flushE
        flushE = 1;
        tick();

        // Check that outputs are zeroed after flush
        check_multi_signal(32'b0, rd1,         "Flush rd1=0       ");
        check_multi_signal(32'b0, rd2,         "Flush rd2=0       ");
        check_alu_control(4'b0000,             "Flush alu_ctrl=0  ");
        check_signal(1'b0, alu_imm_en,         "Flush alu_imm_en  ");
        check_signal(1'b0, reg_write,          "Flush reg_write   ");
        check_signal(1'b0, mem_write,          "Flush mem_write   ");
        check_signal(1'b0, branch,             "Flush branch      ");
        check_signal(1'b0, jump,               "Flush jump        ");

        flushE = 0;

        // ===================================================
        //  14) NOP INSTRUCTION
        // ===================================================
        $display("\n>>> NOP Test <<<");

        instruction = `NOP; // ADDI x0, x0, 0
        tick();
        check_alu_control(4'b0000, "NOP  alu_ctrl=ADD ");
        check_signal(1'b1, alu_imm_en, "NOP  alu_imm_en   ");

        // ===================================================
        //  Summary
        // ===================================================
        $display("\n============================================================");
        $display("         DECODE Test Bench Finished");
        $display("============================================================");
        $display("  Total : %0d", test_count);
        $display("  PASS  : %0d", pass_count);
        $display("  FAIL  : %0d", fail_count);
        $display("============================================================");

        if (fail_count == 0)
            $display(">>> ALL TESTS PASSED <<<");
        else
            $display(">>> SOME TESTS FAILED <<<");

        $finish;
    end

endmodule
