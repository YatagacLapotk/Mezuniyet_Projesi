`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"

module CORE (
    input clk,
    input reset,
    input interrupt,
    input [`DATA_WIDTH-1:0] comm_data_in,
    output [`DATA_WIDTH-1:0] comm_data_out
);

//FETCH wiring
wire stallF;
wire stallD;
wire flushD;
wire pc_src;
//comm_data_in kullanılabilir.
wire [`DATA_WIDTH-1:0] branch_target;
//-----output------
wire [`DATA_WIDTH-1:0] instruction_out;
wire [`DATA_WIDTH-1:0] pc_4_out_fetch;
wire [`DATA_WIDTH-1:0] pc_out_fetch;

//DECODE wiring
wire flushE;
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
wire csr_rd;
wire csr_wr;
wire [`DATA_WIDTH-1:0] csr_data_out;
wire [`DATA_WIDTH-1:0] csr_mtvec;
wire [`DATA_WIDTH-1:0] csr_mepc;
wire [`DATA_WIDTH-1:0] imm;
wire [`WB_CNTRL-1:0] wb_cntrl;
wire [`FUNCT3_WIDTH-1:0] funct3_out_decode;
wire isa_slct;
wire exception_type;
wire reg_writeD;
wire mem_writeD;
wire exception;
wire branch;
wire jump;

//EXECUTE wiring
wire [`DATA_WIDTH-1:0] pc_4_outE;
wire [`DATA_WIDTH-1:0] mem_write_data;
wire [`ADDRESS_WIDTH-1:0] rs1_addr_outE;
wire [`ADDRESS_WIDTH-1:0] rs2_addr_outE;
wire [`ADDRESS_WIDTH-1:0] rdE;
wire [`ADDRESS_WIDTH-1:0] rdM;
wire  reg_writeM;
wire mem_writeM;
wire [`WB_CNTRL-1:0] wb_cntrlM;
wire wb_controlZ;
wire [`DATA_WIDTH-1:0] result_out;
wire [`FUNCT3_WIDTH-1:0] funct3_out_execute;

//MEM wiring
wire [`ADDRESS_WIDTH-1:0] rdM_hazard_out;
wire reg_write_hazard;
wire reg_write_en;
wire [`WB_CNTRL-1:0] wb_control_out;
wire [`ADDRESS_WIDTH-1:0] rdW;
wire [`DATA_WIDTH-1:0] execute_result_out;
wire [`DATA_WIDTH-1:0] mem_result_out;
wire [`DATA_WIDTH-1:0] wb_result_out;
wire [`DATA_WIDTH-1:0] pc_4_outM;

//WB wiring
wire [`DATA_WIDTH-1:0] wb_out;

//HAZARD UNIT
wire [1:0] forwardA;
wire [1:0] forwardB;

HAZARD_UNIT HAZARD_UNIT(
    .rs1D(rs1_addr_out),
    .rs2D(rs2_addr_out),
    .rs1E(rs1_addr_outE),
    .rs2E(rs2_addr_outE),
    .rdE(rdE),
    .rdM(rdM),
    .rdW(rdW),
    .reg_writeM(reg_writeM),
    .reg_writeW(reg_write_hazard),
    .result_srcE_zer(wb_controlZ),
    .forwardA(forwardA),
    .forwardB(forwardB),
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
    .exception_handler_address(csr_mtvec),
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
   .we(reg_write_en),
   .w_addr(rdW),
   .instruction(instruction_out),
   .pc(pc_out_fetch),
   .pc4(pc_4_out_fetch),
   .wd(wb_out),
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
   .funct3_out(funct3_out_decode),
   .exception_type(exception_type),
   .reg_write(reg_writeD),
   .mem_write(mem_writeD),
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
    .exe_result_in(execute_result_out),
    .wb_result_in(wb_out),
    .imm(imm),
    .rs1_addr_in(rs1_addr_out),
    .rs2_addr_in(rs2_addr_out),
    .rd_addr_d(rd_addr_d),
    .alu_control(alu_control),
    .alu_imm_en(alu_imm_en),
    .mdu_control(mdu_control),
    .wb_controlD(wb_cntrl),
    .csr_data_in(csr_data_out),
    .isa_slct(isa_slct),
    .reg_writeD(reg_writeD),
    .mem_writeD(mem_writeD),
    .funct3_in(funct3_out_decode),
    .branch(branch),
    .jump(jump),
    .forwardA(forwardA),
    .forwardB(forwardB),
    .pc_4_out(pc_4_outE),
    .mem_write_data(mem_write_data),
    .rs1_addr_outE(rs1_addr_outE),
    .rs2_addr_outE(rs2_addr_outE), 
    .rdE(rdE),
    .rdM(rdM),
    .pc_target_out(branch_target),
    .pc_src(pc_src),
    .reg_writeM(reg_writeM),
    .mem_writeM(mem_writeM),
    .wb_controlM(wb_cntrlM),
    .wb_contorlZ(wb_controlZ), 
    .result_out(result_out),
    .funct3_out(funct3_out_execute)
);

MEM MEM(
    .clk(clk),
    .reset(reset),
    .execute_result_in(result_out),
    .mem_write_data(mem_write_data),
    .wb_controlM(wb_cntrlM),
    .reg_write(reg_writeM),
    .mem_write(mem_writeM),
    .pc_4(pc_4_outE),
    .rdM(rdM),
    .funct3_in(funct3_out_execute),
    .rdM_hazard_out(rdM_hazard_out),
    .reg_write_hazard(reg_write_hazard),
    .reg_write_en(reg_write_en),
    .wb_control_out(wb_control_out),
    .rdW(rdW),
    .execute_result_out(execute_result_out),
    .mem_result_out(mem_result_out),
    .wb_result_out(wb_result_out),
    .pc_4_out(pc_4_outM)
);

assign wb_out = (wb_cntrlM==2'b00) ? wb_result_out: 
                (wb_cntrlM==2'b01) ? mem_result_out:
                (wb_cntrlM==2'b10) ? pc_4_outM 
                : 32'b0;


CSR CSR(
    .clk(clk),
    .reset(reset),
    .pc(pc_out_decode),
    .instr(instruction_out),
    .csr_addr(csr_addr),
    .exception(exception),
    .interrupt(interrupt),
    .exception_code(exception_type),
    .csr_data_in(csr_data),
    .csr_cntrl(csr_control),
    .csr_rd(csr_rd),
    .csr_wr(csr_wr),
    .csr_data_out(csr_data_out),
    .csr_mtvec(csr_mtvec),
    .csr_mepc(csr_mepc)
);
    
endmodule