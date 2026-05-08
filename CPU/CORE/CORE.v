`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"

module CORE (
    input clk,
    input reset,
    input [`DATA_WIDTH-1:0] comm_data_in,
    output [`DATA_WIDTH-1:0] comm_data_out
);

//FETCH wiring
wire stallF;
wire stallD;
wire flushD;
wire pc_src;
wire [`DATA_WIDTH-1:0] exception_handler_Address;
//comm_data_in kullanılabilir.
wire [`DATA_WIDTH-1:0] branch_target;
//-----output------
wire [`DATA_WIDTH-1:0] instruction_out;
wire [`DATA_WIDTH-1:0] pc_4_out_fetch;
wire [`DATA_WIDTH-1:0] pc_out_fetch;

//DECODE wiring
wire flushE;
wire we;
wire [`ADDRESS_WIDTH-1:0] w_addr;
wire [`DATA_WIDTH-1:0] wd;
//-----output------
wire [`DATA_WIDTH-1:0] pc_out_decode;
wire [`DATA_WIDTH-1:0] pc_4_out_decode;
wire [`DATA_WIDTH-1:0] rd1;
wire [`DATA_WIDTH-1:0] rd2;
wire [`DATA_WIDTH-1:0] rs1_addr_out;
wire [`DATA_WIDTH-1:0] rs2_addr_out;
wire [`DATA_WIDTH-1:0] rd_addr_d;
wire [`ALU_CNTR-1:0] alu_control;
wire alu_imm_en;
wire [`MDU_CNTRL-1:0] mdu_control;
wire [`CSR_CNTRL-1:0] csr_control;
wire [`CSR_ADDR_WIDTH-1:0] csr_addr;
wire [`DATA_WIDTH-1:0] csr_data;
wire [`DATA_WIDTH-1:0] imm;
wire [`WB_CNTRL-1:0] wb_cntrl;
wire isa_slct;
wire exception_type;
wire reg_write;
wire mem_write;
wire exception;
wire branch;
wire jump;


HAZARD_UNIT HAZARD_UNIT(
    .rs1D(rs1_addr_out),
    .rs2D(rs2_addr_out),
    .rs1E(),
    .rs2E(),
    .rdE(),
    .rdM(),
    .rdW(),
    .reg_writeM(),
    .reg_writeW(),
    .result_srcE_zer(),
    .forwardA(),
    .forwardB(),
    .pc_src(pc_src),
    .stallF(stallF),
    .stallD(stallD),
    .flushD(flushD),
    .flushE(flushE)
);

FETCH FETCH(
    .clk(clk),
    .reset(reset),
    .stallF(stallF),
    .stallD(stallD),
    .flushD(flushD),
    .exception(exception),
    .pc_src(pc_src),
    .exception_handler_address(exception_handler_Address),
    .cache_input(comm_data_in),
    .branch_target(branch_target),
    .instruction_out(instruction_out),
    .pc_4_out(pc_4_out_fetch),
    .pc_out(pc_out_fetch)
);

DECODE DECODE(
   .clk(clk),
   .reset(reset),
   .flushE(flushE),
   .we(we),
   .w_addr(w_addr),
   .instruction(instruction_out),
   .pc(pc_out_fetch),
   .pc4(pc_4_out_fetch),
   .wd(wd),
   .pc_out(pc_out_decode),
   .pc_4_out(pc_4_out_decode),
   .rd1(rd1),
   .rd2(rd2),
   .rs1_addr_out(rs1_addr_out),
   .rs2_addr_out(rs2_addr_out),
   .rd_addr_d(rd_addr_d),
   .alu_control(alu_control),
   .alu_imm_en(alu_imm_en),
   .mdu_control(mdu_control),
   .csr_control(csr_control),
   .csr_addr(csr_addr),
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

EXECUTE EXECUTE(
    .clk(clk),
    .reset(reset),
    .rd1(rd1),
    .rd2(rd2),
    .pc(pc_out_decode),
    .pc_4(pc_4_out_decode),
    .imm_ext(imm),
    .exe_result_in(),
    .wb_result_in(),
    .imm(),
    .rs1_addr_in(),
    .rs2_addr_in(),
    .rd_addr_d(),
    .alu_control(),
    .alu_imm_en(),
    .mdu_control(),
    .wb_controlD(),
    .isa_slct(),
    .reg_writeD(),
    .mem_writeD(),
    .branch(),
    .jump(),
    .forwardA(),
    .forwardB(),
    .pc_4_out(),
    .mem_write_data(),
    .rs1_addr_outE(),
    .rs2_addr_outE(), 
    .rdE(),
    .rdM(),
    .pc_target_out(),
    .pc_src(),
    .reg_writeM(),
    .mem_writeM(),
    .wb_controlM(),
    .wb_contorlZ(), 
    .result_out()
);

MEM MEM(
    .clk(clk),
    .reset(reset),
    .execute_result_in(),
    .mem_write_data(),
    .wb_controlM(),
    .reg_write(),
    .mem_write(),
    .pc_4(),
    .rdM(),
    .rdM_hazard_out(),
    .reg_write_hazard(),
    .reg_write_out(),
    .wb_control_out(),
    .rdW(),
    .execute_result_out(),
    .mem_result_out(),
    .wb_result_out(),
    .pc_4_out()
);

CSR CSR(
    .clk(clk),
    .reset(reset),
    .pc(),
    .instr(),
    .csr_addr(),
    .exception(),
    .interrupt(),
    .exception_code(),
    .csr_data_in(),
    .csr_cntrl(),
    .csr_rd(),
    .csr_wr(),
    .csr_data_out(),
    .csr_mtvec(),
    .csr_mepc()
);
    
endmodule