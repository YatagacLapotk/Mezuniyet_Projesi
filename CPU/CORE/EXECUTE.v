`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"

module EXECUTE (
    input clk,
    input [`DATA_WIDTH-1:0] rd1,
    input [`DATA_WIDTH-1:0] rd2,
    input [`DATA_WIDTH-1:0] pc,
    input [`DATA_WIDTH-1:0] imm_ext,
    input [`DATA_WIDTH-1:0] exe_result_in,
    input [`DATA_WIDTH-1:0] wb_result_in,
    input [`DATA_WIDTH-1:0] wb_in,
    input [`ADDRESS_WIDTH-1:0] rs1_addr_in,
    input [`ADDRESS_WIDTH-1:0] rs2_addr_in,
    input [`ALU_CNTR-1:0] alu_control,
    input alu_imm_en,
    input [`MDU_CNTRL-1:0] mdu_control,
    input [`WB_CNTRL-1:0] wb_control,
    input [`ISA_SLCT-1:0] isa_slct,
    input reg_write,
    input mem_write,
    input branch,
    input jump,
    input [2:0] forwardA,
    input [2:0] forwardB,
    output [`DATA_WIDTH-1:0] mem_write_data,
    output [`ADDRESS_WIDTH-1:0] rs1_addr_outE,
    output [`ADDRESS_WIDTH-1:0] rs2_addr_outE,
    output [`ADDRESS_WIDTH-1:0] rdE,
    output [`ADDRESS_WIDTH-1:0] rdM,
    output [`DATA_WIDTH-1:0] pc_target_out,
    output pc_src,
    output [`DATA_WIDTH-1:0]result_out
);

//Biraz daha devam ettirdim. küçük küçk devam ettiriyorum.

wire [`DATA_WIDTH-1:0] alu_src_A;
wire [`DATA_WIDTH-1:0] alu_src_B;
wire [`DATA_WIDTH-1:0] mdu_src_A;
wire [`DATA_WIDTH-1:0] mdu_src_B;
wire [`DATA_WIDTH-1:0] alu_result_out;
wire [`DATA_WIDTH-1:0] mdu_result_out;


ALU alu(
    .s1(alu_src_A),
    .s2(alu_src_B),
    .ALU_CNTR(alu_control),
    .ALU_OUT(alu_result_out)
);

MDU mdu(
    .s1(mdu_src_A),
    .s2(mdu_src_B),
    .funct3(mdu_control),
    .d3(mdu_result_out)
);

//ALU A src selector



    
endmodule