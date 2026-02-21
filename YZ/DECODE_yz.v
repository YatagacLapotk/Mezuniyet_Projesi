`include "E:/RV32IM/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"

// =============================================================================
//  DECODE Stage — RV32IM Pipeline
//
//  Responsibilities:
//    1. Read the register file (rs1, rs2)
//    2. Generate sign-extended / zero-extended immediates
//    3. Decode alu_control, mdu_control, csr_control
//    4. Generate scalar control signals: reg_write, mem_write, branch, jump
//    5. Forward: imm, alu_src, mem_read, mem_to_reg, pc_out, rd_addr_out
//       and csr_addr (for the CSR unit in the execute/WB stage)
//
//  ALU control encoding (matches ALU.v):
//    ADD=0, SUB=1, OR=2,  AND=3,  XOR=4,
//    SLL=5, SRL=6, SRA=7, SLT=8,  SLTU=9,
//    EQ=10, GE=11, LT=12, NE=13,  LTU=14, GEU=15
//
//  MDU control encoding (matches MDU.v ordering):
//    MUL=0, MULH=1, MULHU=2, MULHSU=3,
//    DIV=4, DIVU=5, REM=6,  REMU=7
//
//  CSR control encoding (matches CSR.v):
//    WRITE=2'b00, SET=2'b01, CLEAR=2'b10
// =============================================================================

module DECODE_yz (
    // ---- Pipeline handshake ------------------------------------------------
    input                           clk,
    input                           reset,
    input                           flush,
    input                           stall,
    // ---- Instruction from FETCH/IF-ID register -----------------------------
    input  [`INSTRUCTION_WIDTH-1:0] instruction,
    input  [`DATA_WIDTH-1:0]        pc,
    // ---- Write-back bus (from WB stage) ------------------------------------
    input                           wb_reg_write,
    input  [`ADDRESS_WIDTH-1:0]     wb_rd_addr,
    input  [`DATA_WIDTH-1:0]        wb_rd_data,
    // ---- Register-file outputs ---------------------------------------------
    output [`DATA_WIDTH-1:0]        rd1,
    output [`DATA_WIDTH-1:0]        rd2,
    // ---- ALU / MDU / CSR control -------------------------------------------
    output reg [`ALU_CNTR-1:0]      alu_control,
    output reg [`MDU_CNTRL-1:0]     mdu_control,
    output reg [`CSR_CNTRL-1:0]     csr_control,
    output     [`CSR_ADDR_WIDTH-1:0] csr_addr,
    // ---- Immediate (sign-extended, mux-selected) ---------------------------
    output reg [`DATA_WIDTH-1:0]    imm,
    // ---- Destination register address (forwarded to EX/WB) ----------------
    output     [`ADDRESS_WIDTH-1:0] rd_addr_out,
    // ---- PC pass-through ---------------------------------------------------
    output     [`DATA_WIDTH-1:0]    pc_out,
    // ---- Scalar control signals --------------------------------------------
    output reg                      reg_write,
    output reg                      mem_write,
    output reg                      mem_read,
    output reg                      branch,
    output reg                      jump,
    // ---- Source / result mux selects ---------------------------------------
    //   alu_src  : 0 = rs2,  1 = imm
    //   mem_to_reg: 0 = ALU, 1 = mem, 2 = pc+4, 3 = CSR
    output reg                      alu_src,
    output reg [1:0]                mem_to_reg,
    // ---- MDU / CSR active --------------------------------------------------
    output reg                      mdu_en,
    output reg                      csr_rd,
    output reg                      csr_wr
);

// ---------------------------------------------------------------------------
// Instruction-field extraction
// ---------------------------------------------------------------------------
wire [`OPCODE_WIDTH-1:0]    opcode  = instruction[6:0];
wire [`FUNCT3_WIDTH-1:0]    funct3  = instruction[14:12];
wire [`FUNCT7_WIDTH-1:0]    funct7  = instruction[31:25];
wire [`SHAMT_WIDTH-1:0]     shamt   = instruction[24:20];
wire [`ADDRESS_WIDTH-1:0]   rd_addr = instruction[11:7];
wire [`ADDRESS_WIDTH-1:0]   rs1_addr= instruction[19:15];
wire [`ADDRESS_WIDTH-1:0]   rs2_addr= instruction[24:20];

assign rd_addr_out = rd_addr;
assign csr_addr    = instruction[31:20];   // CSR address lives in imm[11:0]
assign pc_out      = pc;

// ---------------------------------------------------------------------------
// Immediate variants (sign-extended)
// ---------------------------------------------------------------------------
wire [`DATA_WIDTH-1:0] imm_i = {{20{instruction[31]}}, instruction[31:20]};
wire [`DATA_WIDTH-1:0] imm_s = {{20{instruction[31]}}, instruction[31:25], instruction[11:7]};
wire [`DATA_WIDTH-1:0] imm_b = {{19{instruction[31]}}, instruction[7], instruction[30:25], instruction[11:8], 1'b0};
wire [`DATA_WIDTH-1:0] imm_u = {instruction[31:12], 12'b0};
wire [`DATA_WIDTH-1:0] imm_j = {{12{instruction[31]}}, instruction[19:12], instruction[20], instruction[30:21], 1'b0};
// Zero-extended rs1 field used for CSR immediate (CSRRWI / CSRRSI / CSRRCI)
wire [`DATA_WIDTH-1:0] imm_z = {{27{1'b0}}, rs1_addr};  // uimm[4:0]

// ---------------------------------------------------------------------------
// Register File instantiation
// ---------------------------------------------------------------------------
REG_FILE u_reg_file (
    .clk (clk),
    .res (reset),
    .we  (wb_reg_write),
    .A1  (rs1_addr),
    .A2  (rs2_addr),
    .A3  (wb_rd_addr),
    .WD  (wb_rd_data),
    .RD1 (rd1),
    .RD2 (rd2)
);

// ---------------------------------------------------------------------------
// Opcode constants (matching RISC-V ISA)
// ---------------------------------------------------------------------------
localparam OP_LUI    = 7'b0110111;   // U-type
localparam OP_AUIPC  = 7'b0010111;   // U-type
localparam OP_JAL    = 7'b1101111;   // J-type
localparam OP_JALR   = 7'b1100111;   // I-type
localparam OP_BRANCH = 7'b1100011;   // B-type
localparam OP_LOAD   = 7'b0000011;   // I-type
localparam OP_STORE  = 7'b0100011;   // S-type
localparam OP_IMM    = 7'b0010011;   // I-type  (ALU immediate)
localparam OP_REG    = 7'b0110011;   // R-type  (ALU reg-reg / MDU)
localparam OP_SYSTEM = 7'b1110011;   // I-type  (CSR / ECALL / EBREAK)

// ---------------------------------------------------------------------------
// ALU control codes (local aliases for readability)
// ---------------------------------------------------------------------------
localparam ALU_ADD  = 4'd0;
localparam ALU_SUB  = 4'd1;
localparam ALU_OR   = 4'd2;
localparam ALU_AND  = 4'd3;
localparam ALU_XOR  = 4'd4;
localparam ALU_SLL  = 4'd5;
localparam ALU_SRL  = 4'd6;
localparam ALU_SRA  = 4'd7;
localparam ALU_SLT  = 4'd8;
localparam ALU_SLTU = 4'd9;
localparam ALU_EQ   = 4'd10;
localparam ALU_GE   = 4'd11;
localparam ALU_LT   = 4'd12;
localparam ALU_NE   = 4'd13;
localparam ALU_LTU  = 4'd14;
localparam ALU_GEU  = 4'd15;

// MDU control codes
localparam MDU_MUL    = 3'd0;
localparam MDU_MULH   = 3'd1;
localparam MDU_MULHU  = 3'd2;
localparam MDU_MULHSU = 3'd3;
localparam MDU_DIV    = 3'd4;
localparam MDU_DIVU   = 3'd5;
localparam MDU_REM    = 3'd6;
localparam MDU_REMU   = 3'd7;

// CSR control codes
localparam CSR_WRITE = 2'b00;
localparam CSR_SET   = 2'b01;
localparam CSR_CLEAR = 2'b10;

// mem_to_reg mux codes
localparam MEM2REG_ALU  = 2'd0;
localparam MEM2REG_MEM  = 2'd1;
localparam MEM2REG_PC4  = 2'd2;
localparam MEM2REG_CSR  = 2'd3;

// Whether funct7 indicates the M-extension
wire is_mext = (funct7 == 7'b0000001);

// ---------------------------------------------------------------------------
// Combinational decoder
// ---------------------------------------------------------------------------
always @(*) begin
    // Default / NOP values
    alu_control = ALU_ADD;
    mdu_control = MDU_MUL;
    csr_control = CSR_WRITE;
    imm         = 32'd0;
    reg_write   = 1'b0;
    mem_write   = 1'b0;
    mem_read    = 1'b0;
    branch      = 1'b0;
    jump        = 1'b0;
    alu_src     = 1'b0;
    mem_to_reg  = MEM2REG_ALU;
    mdu_en      = 1'b0;
    csr_rd      = 1'b0;
    csr_wr      = 1'b0;

    casez (instruction)
        // ================================================================
        //  LUI — Load Upper Immediate
        // ================================================================
        `LUI: begin
            imm        = imm_u;
            reg_write  = 1'b1;
            alu_src    = 1'b1;                // s2 = imm
            alu_control= ALU_ADD;             // 0 + imm_u  (rs1 forced to x0 externally)
        end

        // ================================================================
        //  AUIPC — Add Upper Immediate to PC
        // ================================================================
        `AUIPC: begin
            imm        = imm_u;
            reg_write  = 1'b1;
            alu_src    = 1'b1;
            alu_control= ALU_ADD;             // pc + imm_u (EX stage muxes pc as s1)
        end

        // ================================================================
        //  JAL — Jump and Link
        // ================================================================
        `JAL: begin
            imm        = imm_j;
            reg_write  = 1'b1;
            jump       = 1'b1;
            alu_src    = 1'b1;
            alu_control= ALU_ADD;             // pc + imm_j -> branch target
            mem_to_reg = MEM2REG_PC4;         // rd = pc + 4
        end

        // ================================================================
        //  JALR — Jump and Link Register
        // ================================================================
        `JALR: begin
            imm        = imm_i;
            reg_write  = 1'b1;
            jump       = 1'b1;
            alu_src    = 1'b1;
            alu_control= ALU_ADD;             // rs1 + imm_i -> target (clear bit 0 in EX)
            mem_to_reg = MEM2REG_PC4;
        end

        // ================================================================
        //  BRANCH instructions
        // ================================================================
        `BEQ: begin
            imm        = imm_b;
            branch     = 1'b1;
            alu_control= ALU_EQ;
        end

        `BNE: begin
            imm        = imm_b;
            branch     = 1'b1;
            alu_control= ALU_NE;
        end

        `BLT: begin
            imm        = imm_b;
            branch     = 1'b1;
            alu_control= ALU_LT;
        end

        `BGE: begin
            imm        = imm_b;
            branch     = 1'b1;
            alu_control= ALU_GE;
        end

        `BLTU: begin
            imm        = imm_b;
            branch     = 1'b1;
            alu_control= ALU_LTU;
        end

        `BGEU: begin
            imm        = imm_b;
            branch     = 1'b1;
            alu_control= ALU_GEU;
        end

        // ================================================================
        //  LOAD instructions
        // ================================================================
        `LB, `LH, `LW, `LBU, `LHU: begin
            imm        = imm_i;
            reg_write  = 1'b1;
            mem_read   = 1'b1;
            alu_src    = 1'b1;
            alu_control= ALU_ADD;             // address = rs1 + imm_i
            mem_to_reg = MEM2REG_MEM;
        end

        // ================================================================
        //  STORE instructions
        // ================================================================
        `SB, `SH, `SW: begin
            imm        = imm_s;
            mem_write  = 1'b1;
            alu_src    = 1'b1;
            alu_control= ALU_ADD;             // address = rs1 + imm_s
        end

        // ================================================================
        //  ALU Immediate instructions  (OP_IMM, funct7[5]=0 unless SRLI/SRAI)
        // ================================================================
        `ADDI: begin
            imm        = imm_i;
            reg_write  = 1'b1;
            alu_src    = 1'b1;
            alu_control= ALU_ADD;
        end

        `SLTI: begin
            imm        = imm_i;
            reg_write  = 1'b1;
            alu_src    = 1'b1;
            alu_control= ALU_SLT;
        end

        `SLTIU: begin
            imm        = imm_i;
            reg_write  = 1'b1;
            alu_src    = 1'b1;
            alu_control= ALU_SLTU;
        end

        `XORI: begin
            imm        = imm_i;
            reg_write  = 1'b1;
            alu_src    = 1'b1;
            alu_control= ALU_XOR;
        end

        `ORI: begin
            imm        = imm_i;
            reg_write  = 1'b1;
            alu_src    = 1'b1;
            alu_control= ALU_OR;
        end

        `ANDI: begin
            imm        = imm_i;
            reg_write  = 1'b1;
            alu_src    = 1'b1;
            alu_control= ALU_AND;
        end

        `SLLI: begin
            imm        = {{27{1'b0}}, shamt};  // zero-extended shamt
            reg_write  = 1'b1;
            alu_src    = 1'b1;
            alu_control= ALU_SLL;
        end

        `SRLI: begin
            imm        = {{27{1'b0}}, shamt};
            reg_write  = 1'b1;
            alu_src    = 1'b1;
            alu_control= ALU_SRL;
        end

        `SRAI: begin
            imm        = {{27{1'b0}}, shamt};
            reg_write  = 1'b1;
            alu_src    = 1'b1;
            alu_control= ALU_SRA;
        end

        // ================================================================
        //  R-type: ALU reg-reg  AND  M-extension (MUL/DIV)
        // ================================================================
        `ADD: begin
            reg_write  = 1'b1;
            alu_control= ALU_ADD;
        end

        `SUB: begin
            reg_write  = 1'b1;
            alu_control= ALU_SUB;
        end

        `SLL: begin
            reg_write  = 1'b1;
            alu_control= ALU_SLL;
        end

        `SLT: begin
            reg_write  = 1'b1;
            alu_control= ALU_SLT;
        end

        `SLTU: begin
            reg_write  = 1'b1;
            alu_control= ALU_SLTU;
        end

        `XOR: begin
            reg_write  = 1'b1;
            alu_control= ALU_XOR;
        end

        `SRL: begin
            reg_write  = 1'b1;
            alu_control= ALU_SRL;
        end

        `SRA: begin
            reg_write  = 1'b1;
            alu_control= ALU_SRA;
        end

        `OR: begin
            reg_write  = 1'b1;
            alu_control= ALU_OR;
        end

        `AND: begin
            reg_write  = 1'b1;
            alu_control= ALU_AND;
        end

        // ---- M-extension ---------------------------------------------------
        `MUL: begin
            reg_write  = 1'b1;
            mdu_en     = 1'b1;
            mdu_control= MDU_MUL;
        end

        `MULH: begin
            reg_write  = 1'b1;
            mdu_en     = 1'b1;
            mdu_control= MDU_MULH;
        end

        `MULHU: begin
            reg_write  = 1'b1;
            mdu_en     = 1'b1;
            mdu_control= MDU_MULHU;
        end

        `MULHSU: begin
            reg_write  = 1'b1;
            mdu_en     = 1'b1;
            mdu_control= MDU_MULHSU;
        end

        `DIV: begin
            reg_write  = 1'b1;
            mdu_en     = 1'b1;
            mdu_control= MDU_DIV;
        end

        `DIVU: begin
            reg_write  = 1'b1;
            mdu_en     = 1'b1;
            mdu_control= MDU_DIVU;
        end

        `REM: begin
            reg_write  = 1'b1;
            mdu_en     = 1'b1;
            mdu_control= MDU_REM;
        end

        `REMU: begin
            reg_write  = 1'b1;
            mdu_en     = 1'b1;
            mdu_control= MDU_REMU;
        end

        // ================================================================
        //  SYSTEM — CSR instructions
        //  funct3 identifies CSR vs ECALL/EBREAK
        //  funct3[2]=0 → register source,  funct3[2]=1 → immediate source
        //
        //  funct3:
        //    3'b001 CSRRW,  3'b010 CSRRS,  3'b011 CSRRC
        //    3'b101 CSRRWI, 3'b110 CSRRSI, 3'b111 CSRRCI
        // ================================================================
        32'b????????????????001?????1110011: begin  // CSRRW
            reg_write  = 1'b1;
            csr_wr     = 1'b1;
            csr_rd     = 1'b1;
            csr_control= CSR_WRITE;
            mem_to_reg = MEM2REG_CSR;
            alu_src    = 1'b0;  // rs1 value written to CSR
        end

        32'b????????????????010?????1110011: begin  // CSRRS
            reg_write  = 1'b1;
            csr_wr     = (rs1_addr != 5'd0) ? 1'b1 : 1'b0;
            csr_rd     = 1'b1;
            csr_control= CSR_SET;
            mem_to_reg = MEM2REG_CSR;
            alu_src    = 1'b0;
        end

        32'b????????????????011?????1110011: begin  // CSRRC
            reg_write  = 1'b1;
            csr_wr     = (rs1_addr != 5'd0) ? 1'b1 : 1'b0;
            csr_rd     = 1'b1;
            csr_control= CSR_CLEAR;
            mem_to_reg = MEM2REG_CSR;
            alu_src    = 1'b0;
        end

        32'b????????????????101?????1110011: begin  // CSRRWI
            imm        = imm_z;
            reg_write  = 1'b1;
            csr_wr     = 1'b1;
            csr_rd     = 1'b1;
            csr_control= CSR_WRITE;
            mem_to_reg = MEM2REG_CSR;
            alu_src    = 1'b1;  // immediate source
        end

        32'b????????????????110?????1110011: begin  // CSRRSI
            imm        = imm_z;
            reg_write  = 1'b1;
            csr_wr     = (rs1_addr != 5'd0) ? 1'b1 : 1'b0;
            csr_rd     = 1'b1;
            csr_control= CSR_SET;
            mem_to_reg = MEM2REG_CSR;
            alu_src    = 1'b1;
        end

        32'b????????????????111?????1110011: begin  // CSRRCI
            imm        = imm_z;
            reg_write  = 1'b1;
            csr_wr     = (rs1_addr != 5'd0) ? 1'b1 : 1'b0;
            csr_rd     = 1'b1;
            csr_control= CSR_CLEAR;
            mem_to_reg = MEM2REG_CSR;
            alu_src    = 1'b1;
        end

        // ECALL / EBREAK — not decoded here; handled by exception logic
        // default NOP — all signals already set to safe defaults above
        default: begin
        end
    endcase

    // ---- Flush / stall override -------------------------------------------
    // On a flush all control signals that could cause side-effects are killed.
    if (flush) begin
        reg_write  = 1'b0;
        mem_write  = 1'b0;
        mem_read   = 1'b0;
        branch     = 1'b0;
        jump       = 1'b0;
        mdu_en     = 1'b0;
        csr_wr     = 1'b0;
        csr_rd     = 1'b0;
    end
end

endmodule
