`define sabit_veriler_VH

`define FIRST_ADDR 32'h00000000

`define ADDRESS_WIDTH       5
`define DATA_WIDTH         32
`define REG_FILE_DEPTH     32
`define INSTRUCTION_WIDTH  32
`define MUL_WIDTH          64
`define OPCODE_WIDTH        7
`define FUNCT3_WIDTH        3
`define FUNCT7_WIDTH        7
`define ALU_CNTR            4
`define MDU_CNTRL           3
`define CSR_ADDR_WIDTH     12
`define CSR_CNTRL           2
`define SHAMT_WIDTH         5
`define WB_CNTRL            2

`define NOP 32'h00000013

// CSR Addresses
`define MSTATUS        12'h300
`define MIE            12'h304
`define MTVEC          12'h305
`define MEPC           12'h341
`define MCAUSE         12'h342
`define MTVAL          12'h343

// MUL/DIV Operations
`define MUL            32'b0000001??????????000?????0110011
`define MULH           32'b0000001??????????001?????0110011
`define MULHU          32'b0000001??????????010?????0110011
`define MULHSU         32'b0000001??????????011?????0110011
`define DIV            32'b0000001??????????100?????0110011
`define DIVU           32'b0000001??????????101?????0110011
`define REM            32'b0000001??????????110?????0110011
`define REMU           32'b0000001??????????111?????0110011


// RV32I Operations
`define LUI            32'b?????????????????????????0110111
`define AUIPC          32'b?????????????????????????0010111
`define JAL            32'b?????????????????????????1101111
`define JALR           32'b?????????????????000?????1100111
`define LB             32'b?????????????????000?????0000011
`define LH             32'b?????????????????001?????0000011 
`define LW             32'b?????????????????010?????0000011
`define LBU            32'b?????????????????100?????0000011
`define LHU            32'b?????????????????101?????0000011
`define SB             32'b?????????????????000?????0100011
`define SH             32'b?????????????????001?????0100011
`define SW             32'b?????????????????010?????0100011
`define ADDI           32'b?????????????????000?????0010011
`define SLTI           32'b?????????????????010?????0010011
`define SLTIU          32'b?????????????????011?????0010011
`define XORI           32'b?????????????????100?????0010011
`define ORI            32'b?????????????????110?????0010011
`define ANDI           32'b?????????????????111?????0010011
`define SLLI           32'b0000000??????????001?????0010011
`define SRLI           32'b0000000??????????101?????0010011
`define SRAI           32'b0100000??????????101?????0010011 
// ALU Operations
`define ADD            32'b0000000??????????000?????0110011 
`define SUB            32'b0100000??????????000?????0110011 
`define SLL            32'b0000000??????????001?????0110011 
`define SLT            32'b0000000??????????010?????0110011 
`define SLTU           32'b0000000??????????011?????0110011 
`define XOR            32'b0000000??????????100?????0110011 
`define SRL            32'b0000000??????????101?????0110011 
`define SRA            32'b0100000??????????101?????0110011 
`define OR             32'b0000000??????????110?????0110011 
`define AND            32'b0000000??????????111?????0110011 
// Branch Operations (calculated in ALU)
`define BEQ            32'b?????????????????000?????1100011 
`define BNE            32'b?????????????????001?????1100011 
`define BLT            32'b?????????????????100?????1100011 
`define BGE            32'b?????????????????101?????1100011 
`define BLTU           32'b?????????????????110?????1100011 
`define BGEU           32'b?????????????????111?????1100011 
//Exception 
`define ECALL          32'b00000000000000000000000001110011 
`define EBREAK         32'b00000000000100000000000001110011 

//Zicsr instructions
`define CSRRW          32'b?????????????????001?????1110011
`define CSRRS          32'b?????????????????010?????1110011
`define CSRRC          32'b?????????????????011?????1110011
`define CSRRWI         32'b?????????????????101?????1110011
`define CSRRSI         32'b?????????????????110?????1110011
`define CSRRCI         32'b?????????????????111?????1110011
`timescale 1ns / 1ps

module EXECUTE_TB;

    // -------------------------------------------------------
    // Clock & Period
    // -------------------------------------------------------
    localparam CLK_PERIOD = 10;
    reg clk;
    always #(CLK_PERIOD/2) clk = ~clk;

    // -------------------------------------------------------
    // DUT Inputs
    // -------------------------------------------------------
    reg                          reset;
    reg  [`DATA_WIDTH-1:0]       rd1;
    reg  [`DATA_WIDTH-1:0]       rd2;
    reg  [`DATA_WIDTH-1:0]       pc;
    reg  [`DATA_WIDTH-1:0]       imm_ext;
    reg  [`DATA_WIDTH-1:0]       exe_result_in;
    reg  [`DATA_WIDTH-1:0]       wb_result_in;
    reg  [`DATA_WIDTH-1:0]       imm;
    reg  [`ADDRESS_WIDTH-1:0]    rs1_addr_in;
    reg  [`ADDRESS_WIDTH-1:0]    rs2_addr_in;
    reg  [`ADDRESS_WIDTH-1:0]    rd_addr_d;
    reg  [`ALU_CNTR-1:0]         alu_control;
    reg                          alu_imm_en;
    reg  [`MDU_CNTRL-1:0]        mdu_control;

    reg                          isa_slct;
    reg                          reg_writeD;
    reg                          mem_writeD;
    reg                          branch;
    reg                          jump;
    reg  [1:0]                   forwardA;
    reg  [1:0]                   forwardB;

    // -------------------------------------------------------
    // DUT Outputs
    // -------------------------------------------------------
    wire [`DATA_WIDTH-1:0]       mem_write_data;
    wire [`ADDRESS_WIDTH-1:0]    rs1_addr_outE;
    wire [`ADDRESS_WIDTH-1:0]    rs2_addr_outE;
    wire [`ADDRESS_WIDTH-1:0]    rdE;
    wire [`ADDRESS_WIDTH-1:0]    rdM;
    wire [`DATA_WIDTH-1:0]       pc_target_out;
    wire                         pc_src;
    wire                         reg_writeM;
    wire                         mem_writeM;

    wire [`DATA_WIDTH-1:0]       result_out;

    // -------------------------------------------------------
    // DUT Instantiation
    // -------------------------------------------------------
    EXECUTE uut (
        .clk(clk),
        .reset(reset),
        .rd1(rd1),
        .rd2(rd2),
        .pc(pc),
        .imm_ext(imm_ext),
        .exe_result_in(exe_result_in),
        .wb_result_in(wb_result_in),
        .imm(imm),
        .rs1_addr_in(rs1_addr_in),
        .rs2_addr_in(rs2_addr_in),
        .rd_addr_d(rd_addr_d),
        .alu_control(alu_control),
        .alu_imm_en(alu_imm_en),
        .mdu_control(mdu_control),

        .isa_slct(isa_slct),
        .reg_writeD(reg_writeD),
        .mem_writeD(mem_writeD),
        .branch(branch),
        .jump(jump),
        .forwardA(forwardA),
        .forwardB(forwardB),
        .mem_write_data(mem_write_data),
        .rs1_addr_outE(rs1_addr_outE),
        .rs2_addr_outE(rs2_addr_outE),
        .rdE(rdE),
        .rdM(rdM),
        .pc_target_out(pc_target_out),
        .pc_src(pc_src),
        .reg_writeM(reg_writeM),
        .mem_writeM(mem_writeM),

        .result_out(result_out)
    );

    // -------------------------------------------------------
    // Test Counters
    // -------------------------------------------------------
    integer pass_count = 0;
    integer fail_count = 0;
    integer test_count = 0;

    // -------------------------------------------------------
    // Check Tasks
    // -------------------------------------------------------
    task check_signal;
        input expected;
        input actual;
        input [255:0] test_name;
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

    task check_value;
        input [31:0] expected;
        input [31:0] actual;
        input [255:0] test_name;
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

    task check_addr;
        input [`ADDRESS_WIDTH-1:0] expected;
        input [`ADDRESS_WIDTH-1:0] actual;
        input [255:0] test_name;
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

    // Wait for one clock cycle and let outputs settle
    task tick;
        begin
            @(posedge clk);
            #1;
        end
    endtask

    // Helper: set all inputs to a known default state
    task set_defaults;
        begin
            rd1            = 32'h0;
            rd2            = 32'h0;
            pc             = 32'h0;
            imm_ext        = 32'h0;
            exe_result_in  = 32'h0;
            wb_result_in   = 32'h0;
            imm            = 32'h0;
            rs1_addr_in    = 5'b0;
            rs2_addr_in    = 5'b0;
            rd_addr_d      = 5'b0;
            alu_control    = 4'b0000;
            alu_imm_en     = 1'b0;
            mdu_control    = 3'b000;

            isa_slct       = 1'b0;
            reg_writeD     = 1'b0;
            mem_writeD     = 1'b0;
            branch         = 1'b0;
            jump           = 1'b0;
            forwardA       = 2'b00;
            forwardB       = 2'b00;
        end
    endtask

    // -------------------------------------------------------
    // Main Stimulus
    // -------------------------------------------------------
    initial begin
        $dumpfile("EXECUTE_TB.vcd");
        $dumpvars(0, EXECUTE_TB);

        $display("============================================================");
        $display("        EXECUTE Unit Test Bench - RV32IM");
        $display("============================================================");

        // -------------------------------------------------------
        // Initialization & Reset
        // -------------------------------------------------------
        clk   = 0;
        reset = 1;
        set_defaults();

        tick();
        tick();
        reset = 0;
        tick();

        // ===================================================
        //  1) RESET VERIFICATION
        // ===================================================
        $display("\n>>> Reset Verification <<<");

        // After reset, pipeline regs should be 0
        check_value(32'h0, result_out,     "RST result_out=0    ");
        check_value(32'h0, mem_write_data, "RST mem_write_data=0");
        check_addr(5'b0,   rdM,            "RST rdM=0           ");
        check_signal(1'b0, reg_writeM,     "RST reg_writeM=0    ");
        check_signal(1'b0, mem_writeM,     "RST mem_writeM=0    ");

        // ===================================================
        //  2) ALU OPERATIONS (isa_slct=0, forwardA/B=00)
        // ===================================================
        $display("\n>>> ALU Operations <<<");

        // --- ADD: rd1 + rd2 ---
        set_defaults();
        rd1         = 32'h0000_000A; // 10
        rd2         = 32'h0000_0014; // 20
        alu_control = 4'b0000;       // ADD
        isa_slct    = 1'b0;
        reg_writeD  = 1'b1;
        rd_addr_d   = 5'd4;
        #1;
        // Combinational result: check result_out_reg via next clock
        tick();
        check_value(32'h0000_001E, result_out, "ADD 10+20=30       ");
        check_addr(5'd4, rdM,                  "ADD rdM=4           ");
        check_signal(1'b1, reg_writeM,         "ADD reg_writeM=1    ");

        // --- SUB: rd1 - rd2 ---
        set_defaults();
        rd1         = 32'h0000_0020; // 32
        rd2         = 32'h0000_000A; // 10
        alu_control = 4'b0001;       // SUB
        isa_slct    = 1'b0;
        #1;
        tick();
        check_value(32'h0000_0016, result_out, "SUB 32-10=22       ");

        // --- AND ---
        set_defaults();
        rd1         = 32'hFF00_FF00;
        rd2         = 32'h0F0F_0F0F;
        alu_control = 4'b0011;       // AND
        isa_slct    = 1'b0;
        #1;
        tick();
        check_value(32'h0F00_0F00, result_out, "AND                ");

        // --- OR ---
        set_defaults();
        rd1         = 32'hFF00_0000;
        rd2         = 32'h00FF_0000;
        alu_control = 4'b0010;       // OR
        isa_slct    = 1'b0;
        #1;
        tick();
        check_value(32'hFFFF_0000, result_out, "OR                 ");

        // --- XOR ---
        set_defaults();
        rd1         = 32'hAAAA_AAAA;
        rd2         = 32'h5555_5555;
        alu_control = 4'b0100;       // XOR
        isa_slct    = 1'b0;
        #1;
        tick();
        check_value(32'hFFFF_FFFF, result_out, "XOR                ");

        // --- SLL (shift left logical) ---
        set_defaults();
        rd1         = 32'h0000_0001;
        rd2         = 32'h0000_0004; // shift by 4
        alu_control = 4'b0101;       // SLL
        isa_slct    = 1'b0;
        #1;
        tick();
        check_value(32'h0000_0010, result_out, "SLL 1<<4=16        ");

        // --- SRL (shift right logical) ---
        set_defaults();
        rd1         = 32'h0000_0080;
        rd2         = 32'h0000_0003; // shift by 3
        alu_control = 4'b0110;       // SRL
        isa_slct    = 1'b0;
        #1;
        tick();
        check_value(32'h0000_0010, result_out, "SRL 0x80>>3=0x10   ");

        // --- SRA (shift right arithmetic) ---
        set_defaults();
        rd1         = 32'hFFFF_FF00; // -256
        rd2         = 32'h0000_0004; // shift by 4
        alu_control = 4'b0111;       // SRA
        isa_slct    = 1'b0;
        #1;
        tick();
        check_value(32'hFFFF_FFF0, result_out, "SRA -256>>>4=-16   ");

        // --- SLT (set less than, signed) ---
        set_defaults();
        rd1         = 32'hFFFF_FFFF; // -1 signed
        rd2         = 32'h0000_0001; // 1
        alu_control = 4'b1000;       // SLT
        isa_slct    = 1'b0;
        #1;
        tick();
        check_value(32'h0000_0001, result_out, "SLT -1<1 = 1       ");

        // --- SLTU (set less than, unsigned) ---
        set_defaults();
        rd1         = 32'h0000_0001;
        rd2         = 32'hFFFF_FFFF;
        alu_control = 4'b1001;       // SLTU
        isa_slct    = 1'b0;
        #1;
        tick();
        check_value(32'h0000_0001, result_out, "SLTU 1<0xFFFFFFFF  ");

        // ===================================================
        //  3) ALU WITH IMMEDIATE (alu_imm_en=1)
        // ===================================================
        $display("\n>>> ALU with Immediate <<<");

        // ADDI: rd1 + imm
        set_defaults();
        rd1         = 32'h0000_0010; // 16
        imm         = 32'h0000_0064; // 100
        alu_control = 4'b0000;       // ADD
        alu_imm_en  = 1'b1;
        isa_slct    = 1'b0;
        #1;
        tick();
        check_value(32'h0000_0074, result_out, "ADDI 16+100=116    ");

        // ANDI: rd1 & imm
        set_defaults();
        rd1         = 32'hFFFF_FFFF;
        imm         = 32'h0000_00FF;
        alu_control = 4'b0011;       // AND
        alu_imm_en  = 1'b1;
        isa_slct    = 1'b0;
        #1;
        tick();
        check_value(32'h0000_00FF, result_out, "ANDI 0xFFFF&0xFF   ");

        // ===================================================
        //  4) MDU OPERATIONS (isa_slct=1)
        // ===================================================
        $display("\n>>> MDU Operations <<<");

        // MUL: rd1 * rd2 (low 32 bits)
        set_defaults();
        rd1         = 32'h0000_0005; // 5
        rd2         = 32'h0000_0003; // 3
        mdu_control = 3'b000;        // MUL
        isa_slct    = 1'b1;
        #1;
        tick();
        check_value(32'h0000_000F, result_out, "MUL 5*3=15         ");

        // DIV: rd1 / rd2
        set_defaults();
        rd1         = 32'h0000_0014; // 20
        rd2         = 32'h0000_0004; // 4
        mdu_control = 3'b100;        // DIV
        isa_slct    = 1'b1;
        #1;
        tick();
        check_value(32'h0000_0005, result_out, "DIV 20/4=5         ");

        // REM: rd1 % rd2
        set_defaults();
        rd1         = 32'h0000_0011; // 17
        rd2         = 32'h0000_0005; // 5
        mdu_control = 3'b110;        // REM
        isa_slct    = 1'b1;
        #1;
        tick();
        check_value(32'h0000_0002, result_out, "REM 17%5=2         ");

        // DIV by zero: should return 0xFFFFFFFF
        set_defaults();
        rd1         = 32'h0000_000A;
        rd2         = 32'h0000_0000;
        mdu_control = 3'b100;        // DIV
        isa_slct    = 1'b1;
        #1;
        tick();
        check_value(32'hFFFF_FFFF, result_out, "DIV by 0=0xFFFFFFFF");

        // ===================================================
        //  5) FORWARDING MUXES
        // ===================================================
        $display("\n>>> Forwarding Mux Tests <<<");

        // forwardA=01 => alu_src_A = exe_result_in
        set_defaults();
        rd1            = 32'hDEAD_BEEF;
        exe_result_in  = 32'h0000_0010;
        wb_result_in   = 32'h0000_0020;
        rd2            = 32'h0000_0005;
        alu_control    = 4'b0000; // ADD
        isa_slct       = 1'b0;
        forwardA       = 2'b01;
        forwardB       = 2'b00;
        #1;
        tick();
        check_value(32'h0000_0015, result_out, "FwdA=01 exe+rd2    ");

        // forwardA=10 => alu_src_A = wb_result_in
        set_defaults();
        rd1            = 32'hDEAD_BEEF;
        wb_result_in   = 32'h0000_0030;
        rd2            = 32'h0000_0002;
        alu_control    = 4'b0000; // ADD
        isa_slct       = 1'b0;
        forwardA       = 2'b10;
        forwardB       = 2'b00;
        #1;
        tick();
        check_value(32'h0000_0032, result_out, "FwdA=10 wb+rd2     ");

        // forwardB=01 => alu_src_B = exe_result_in
        set_defaults();
        rd1            = 32'h0000_0003;
        rd2            = 32'hDEAD_BEEF;
        exe_result_in  = 32'h0000_0007;
        alu_control    = 4'b0000; // ADD
        isa_slct       = 1'b0;
        forwardA       = 2'b00;
        forwardB       = 2'b01;
        #1;
        tick();
        check_value(32'h0000_000A, result_out, "FwdB=01 rd1+exe    ");

        // forwardB=10 => alu_src_B = wb_result_in
        set_defaults();
        rd1            = 32'h0000_0003;
        rd2            = 32'hDEAD_BEEF;
        wb_result_in   = 32'h0000_0007;
        alu_control    = 4'b0000; // ADD
        isa_slct       = 1'b0;
        forwardA       = 2'b00;
        forwardB       = 2'b10;
        #1;
        tick();
        check_value(32'h0000_000A, result_out, "FwdB=10 rd1+wb     ");

        // Both forwarded: forwardA=01, forwardB=10
        set_defaults();
        rd1            = 32'hDEAD_BEEF;
        rd2            = 32'hDEAD_BEEF;
        exe_result_in  = 32'h0000_0004;
        wb_result_in   = 32'h0000_0006;
        alu_control    = 4'b0000; // ADD
        isa_slct       = 1'b0;
        forwardA       = 2'b01;
        forwardB       = 2'b10;
        #1;
        tick();
        check_value(32'h0000_000A, result_out, "FwdA=01,B=10 4+6   ");

        // ===================================================
        //  6) PC TARGET CALCULATION
        // ===================================================
        $display("\n>>> PC Target Calculation <<<");

        set_defaults();
        pc  = 32'h0000_1000;
        imm = 32'h0000_0100; // offset 256
        #1;
        check_value(32'h0000_1100, pc_target_out, "pc_target 0x1000+0x100");

        set_defaults();
        pc  = 32'h0000_2000;
        imm = 32'hFFFF_FFF0; // offset -16
        #1;
        check_value(32'h0000_1FF0, pc_target_out, "pc_target 0x2000-16   ");

        // ===================================================
        //  7) PC_SRC (branch & jump logic)
        // ===================================================
        $display("\n>>> PC Source Logic <<<");

        // jump=1 => pc_src=1 regardless
        set_defaults();
        jump   = 1'b1;
        branch = 1'b0;
        rd1    = 32'h0000_0001; // ALU result != 0 => zero=0
        rd2    = 32'h0000_0000;
        alu_control = 4'b0000; // ADD => result=1 => zero=0
        #1;
        check_signal(1'b1, pc_src, "JAL pc_src=1        ");

        // branch=1, ALU result==0 => zero=1 => pc_src=1  (BEQ taken)
        set_defaults();
        jump        = 1'b0;
        branch      = 1'b1;
        rd1         = 32'h0000_0005;
        rd2         = 32'h0000_0005;
        alu_control = 4'b1010; // EQ => result=1? No, EQ gives 1 if equal
        // EQ: ALU_OUT = (s1==s2) ? 1 : 0 => result=1 => zero=0
        // Actually zero = ~(|alu_result_out), so if result=1, zero=0
        // For BEQ to be taken, we need zero=1, i.e. alu_result_out==0
        // With BEQ, the ALU computes EQ, result=1 (they are equal), zero=0
        // So the branch is NOT taken here. Let me use SUB to get zero.
        alu_control = 4'b0001; // SUB: 5-5=0 => zero=1
        #1;
        check_signal(1'b1, pc_src, "BEQ taken pc_src=1  ");

        // branch=1, ALU result!=0 => zero=0 => pc_src=0  (BEQ not taken)
        set_defaults();
        jump        = 1'b0;
        branch      = 1'b1;
        rd1         = 32'h0000_0005;
        rd2         = 32'h0000_0003;
        alu_control = 4'b0001; // SUB: 5-3=2 => zero=0
        #1;
        check_signal(1'b0, pc_src, "BEQ not taken src=0 ");

        // jump=0, branch=0 => pc_src=0
        set_defaults();
        #1;
        check_signal(1'b0, pc_src, "No branch/jump src=0");

        // ===================================================
        //  8) ADDRESS PASSTHROUGH
        // ===================================================
        $display("\n>>> Address Passthrough <<<");

        set_defaults();
        rs1_addr_in = 5'd12;
        rs2_addr_in = 5'd15;
        rd_addr_d   = 5'd7;
        #1;
        check_addr(5'd12, rs1_addr_outE, "rs1_addr passthrough ");
        check_addr(5'd15, rs2_addr_outE, "rs2_addr passthrough ");
        check_addr(5'd7,  rdE,           "rdE passthrough      ");

        // ===================================================
        //  9) PIPELINE REGISTER OUTPUTS
        // ===================================================
        $display("\n>>> Pipeline Register Outputs <<<");

        set_defaults();
        rd1         = 32'h0000_0010;
        rd2         = 32'h0000_0020;
        alu_control = 4'b0000;  // ADD => result = 0x30
        isa_slct    = 1'b0;
        rd_addr_d   = 5'd10;
        reg_writeD  = 1'b1;
        mem_writeD  = 1'b1;

        #1;
        tick();

        check_value(32'h0000_0030, result_out,     "Pipe result=0x30    ");
        check_value(32'h0000_0020, mem_write_data,  "Pipe mem_wr_data    ");
        check_addr(5'd10, rdM,                      "Pipe rdM=10         ");
        check_signal(1'b1, reg_writeM,              "Pipe reg_writeM=1   ");
        check_signal(1'b1, mem_writeM,              "Pipe mem_writeM=1   ");

        // mem_write_data should be alu_src_B (the forwarded B source)
        // With forwardB=01, it should use exe_result_in
        set_defaults();
        rd2            = 32'hDEAD_BEEF;
        exe_result_in  = 32'h0000_CAFE;
        forwardB       = 2'b01;
        alu_control    = 4'b0000;
        isa_slct       = 1'b0;
        #1;
        tick();
        check_value(32'h0000_CAFE, mem_write_data, "Pipe fwdB mem_data  ");

        // ===================================================
        //  10) RESET DURING OPERATION
        // ===================================================
        $display("\n>>> Reset During Operation <<<");

        // First set up a non-zero state
        set_defaults();
        rd1         = 32'h0000_00FF;
        rd2         = 32'h0000_0001;
        alu_control = 4'b0000;
        isa_slct    = 1'b0;
        reg_writeD  = 1'b1;
        mem_writeD  = 1'b1;
        rd_addr_d   = 5'd15;

        #1;
        tick(); // registers latch non-zero values
        // Verify non-zero
        check_value(32'h0000_0100, result_out, "Pre-reset result    ");

        // Now assert reset
        reset = 1;
        tick();

        check_value(32'h0, result_out,     "Reset result_out=0  ");
        check_value(32'h0, mem_write_data, "Reset mem_wr_data=0 ");
        check_addr(5'b0,   rdM,            "Reset rdM=0         ");
        check_signal(1'b0, reg_writeM,     "Reset reg_writeM=0  ");
        check_signal(1'b0, mem_writeM,     "Reset mem_writeM=0  ");

        reset = 0;
        tick();

        // ===================================================
        //  11) ISA SELECT (ALU vs MDU)
        // ===================================================
        $display("\n>>> ISA Select <<<");

        // isa_slct=0 => ALU result
        set_defaults();
        rd1         = 32'h0000_0008;
        rd2         = 32'h0000_0002;
        alu_control = 4'b0000;  // ADD => 10
        mdu_control = 3'b000;   // MUL => 16
        isa_slct    = 1'b0;     // select ALU
        #1;
        tick();
        check_value(32'h0000_000A, result_out, "ISA=0 ALU 8+2=10   ");

        // isa_slct=1 => MDU result
        set_defaults();
        rd1         = 32'h0000_0008;
        rd2         = 32'h0000_0002;
        alu_control = 4'b0000;  // ADD => 10
        mdu_control = 3'b000;   // MUL => 16
        isa_slct    = 1'b1;     // select MDU
        #1;
        tick();
        check_value(32'h0000_0010, result_out, "ISA=1 MDU 8*2=16   ");

        // ===================================================
        //  12) ALU BRANCH OPERATIONS (EQ, NE, LT, GE, LTU, GEU)
        // ===================================================
        $display("\n>>> ALU Branch Operations <<<");

        // EQ: equal values
        set_defaults();
        rd1 = 32'h0000_0005;
        rd2 = 32'h0000_0005;
        alu_control = 4'b1010; // EQ
        isa_slct = 1'b0;
        #1;
        tick();
        check_value(32'h0000_0001, result_out, "EQ 5==5 => 1       ");

        // NE: not equal
        set_defaults();
        rd1 = 32'h0000_0005;
        rd2 = 32'h0000_0003;
        alu_control = 4'b1101; // NE
        isa_slct = 1'b0;
        #1;
        tick();
        check_value(32'h0000_0001, result_out, "NE 5!=3 => 1       ");

        // LT: signed less than
        set_defaults();
        rd1 = 32'hFFFF_FFFF; // -1
        rd2 = 32'h0000_0001; // 1
        alu_control = 4'b1100; // LT
        isa_slct = 1'b0;
        #1;
        tick();
        check_value(32'h0000_0001, result_out, "LT -1<1 => 1       ");

        // GE: signed greater or equal
        set_defaults();
        rd1 = 32'h0000_0005;
        rd2 = 32'h0000_0003;
        alu_control = 4'b1011; // GE
        isa_slct = 1'b0;
        #1;
        tick();
        check_value(32'h0000_0001, result_out, "GE 5>=3 => 1       ");

        // ===================================================
        //  13) FORWARDING WITH IMMEDIATE
        // ===================================================
        $display("\n>>> Forwarding + Immediate <<<");

        // forwardA=01, alu_imm_en=1: exe_result_in + imm
        set_defaults();
        exe_result_in = 32'h0000_0100;
        imm           = 32'h0000_0050;
        alu_control   = 4'b0000; // ADD
        alu_imm_en    = 1'b1;
        isa_slct      = 1'b0;
        forwardA      = 2'b01;
        #1;
        tick();
        check_value(32'h0000_0150, result_out, "FwdA+Imm 0x100+0x50");

        // ===================================================
        //  Summary
        // ===================================================
        $display("\n============================================================");
        $display("        EXECUTE Test Bench Finished");
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
