`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module DECODE (
    input clk,
    input reset,
    input [`INSTRUCTION_WIDTH-1:0] instruction,
    input [`DATA_WIDTH-1:0] pc,
    input flush,
    input stall,
    output [`DATA_WIDTH-1:0] rd1,
    output [`DATA_WIDTH-1:0] rd2,
    output [`ALU_CNTR-1:0] alu_control,
    output [`MDU_CNTRL-1:0] mdu_control,
    output [`CSR_CNTRL-1:0] csr_control,
    output [`CSR_ADDR_WIDTH-1:0] csr_addr,
    output reg_write,
    output mem_write,
    output branch,
    output jump
);

wire [`OPCODE_WIDTH-1:0] opcode;
wire  [`FUNCT3_WIDTH-1:0] funct3;
wire [`FUNCT7_WIDTH-1:0] funct7;
wire [`SHAMT_WIDTH-1:0] shamt;
wire [`ADDRESS_WIDTH-1:0] rd_addr;
wire [`ADDRESS_WIDTH-1:0] rs1_addr;
wire [`ADDRESS_WIDTH-1:0] rs2_addr;
wire [`DATA_WIDTH-1:0] imm_i;
wire [`DATA_WIDTH-1:0] imm_s;
wire [`DATA_WIDTH-1:0] imm_b;
wire [`DATA_WIDTH-1:0] imm_u;
wire [`DATA_WIDTH-1:0] imm_j;

assign opcode = instruction[6:0];
assign funct3 = instruction[14:12];
assign funct7 = instruction[31:25];
assign shamt = instruction[24:20];
assign rd_addr = instruction[11:7];
assign rs1_addr = instruction[19:15];
assign rs2_addr = instruction[24:20];
assign imm_i = {{20{instruction[31]}}, instruction[31:20]};
assign imm_s = {{20{instruction[31]}}, instruction[31:25], instruction[11:7]};
assign imm_b = {{19{instruction[31]}}, instruction[7], instruction[30:25], instruction[11:8], 1'b0};
assign imm_u = {instruction[31:12], 12'b0};
assign imm_j = {{12{instruction[31]}}, instruction[19:12], instruction[20], instruction[30:21], 1'b0};









    
endmodule