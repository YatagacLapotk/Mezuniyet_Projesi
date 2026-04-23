`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"

module EXECUTE (
    input clk,
    input reset,
    input [`DATA_WIDTH-1:0] rd1,
    input [`DATA_WIDTH-1:0] rd2,
    input [`DATA_WIDTH-1:0] pc,
    input [`DATA_WIDTH-1:0] pc_4,
    input [`DATA_WIDTH-1:0] imm_ext,
    input [`DATA_WIDTH-1:0] exe_result_in,
    input [`DATA_WIDTH-1:0] wb_result_in,
    input [`DATA_WIDTH-1:0] imm,
    input [`ADDRESS_WIDTH-1:0] rs1_addr_in,
    input [`ADDRESS_WIDTH-1:0] rs2_addr_in,
    input [`ADDRESS_WIDTH-1:0] rd_addr_d,
    input [`ALU_CNTR-1:0] alu_control,
    input alu_imm_en,
    input [`MDU_CNTRL-1:0] mdu_control,
    input [`WB_CNTRL-1:0] wb_controlD,
    input isa_slct,
    input reg_writeD,
    input mem_writeD,
    input branch,
    input jump,
    input [1:0] forwardA,
    input [1:0] forwardB,
    output reg [`DATA_WIDTH-1:0] pc_4_out,
    output reg [`DATA_WIDTH-1:0] mem_write_data,
    output [`ADDRESS_WIDTH-1:0] rs1_addr_outE, // Bu çıkışlara atama yapılmamış teset yaparken hata verdi oradan gördüm. rs1 ve rs2'leri atadım kotrol edersin.
    output [`ADDRESS_WIDTH-1:0] rs2_addr_outE, // Bu çıkışlara atama yapılmamış
    output [`ADDRESS_WIDTH-1:0] rdE,
    output reg [`ADDRESS_WIDTH-1:0] rdM,
    output [`DATA_WIDTH-1:0] pc_target_out,
    output pc_src,
    output reg reg_writeM,
    output reg mem_writeM,
    output reg [`WB_CNTRL-1:0] wb_controlM,
    output wb_contorlZ,
    output reg [`DATA_WIDTH-1:0]result_out
);

wire [`DATA_WIDTH-1:0] alu_src_A;
wire [`DATA_WIDTH-1:0] alu_src_B;
wire [`DATA_WIDTH-1:0] alu_src_B_imm;
wire [`DATA_WIDTH-1:0] mdu_src_A;
wire [`DATA_WIDTH-1:0] mdu_src_B;
wire [`DATA_WIDTH-1:0] alu_result_out;
wire [`DATA_WIDTH-1:0] mdu_result_out;
wire zero;

reg [`DATA_WIDTH-1:0] result_out_reg;

ALU alu(
    .s1(alu_src_A),
    .s2(alu_src_B_imm),
    .ALU_CNTR(alu_control),
    .ALU_OUT(alu_result_out)
);

MDU mdu(
    .s1(mdu_src_A),
    .s2(mdu_src_B),
    .funct3(mdu_control),
    .d3(mdu_result_out)
);

assign pc_target_out = pc + imm; //Branch ve jump işlemleri için hedef adres ataması.

assign rs1_addr_outE = rs1_addr_in; //rs1 adresini çıkışa atama
assign rs2_addr_outE = rs2_addr_in; //rs2 adresini çıkışa atama

//Forward işlemleri için atama harris'ten bakarak yaptım burayı
assign alu_src_A = (forwardA==2'b00) ? (rd1):
                   (forwardA==2'b01) ? (exe_result_in):
                   (forwardA==2'b10) ? (wb_result_in) :
                    rd1;
assign alu_src_B = (forwardB==2'b00) ? (rd2):
                   (forwardB==2'b01) ? (exe_result_in):
                   (forwardB==2'b10) ? (wb_result_in) :
                    rd2;
assign mdu_src_A = (forwardA==2'b00) ? (rd1):
                   (forwardA==2'b01) ? (exe_result_in):
                   (forwardA==2'b10) ? (wb_result_in) :
                    rd1;
assign mdu_src_B = (forwardB==2'b00) ? (rd2):
                   (forwardB==2'b01) ? (exe_result_in):
                   (forwardB==2'b10) ? (wb_result_in) :
                    rd2;


//Immidiate işlemleri için kaynak atama.
assign alu_src_B_imm = (alu_imm_en==1'b1) ? (imm) : (alu_src_B);

assign zero = ~(|alu_result_out);//zero bitinin ataması
assign pc_src = (jump|(zero&branch));//pc giriş değeri ataması
assign rdE = rd_addr_d;

//isa selector aslında tek bit olması gerekiyor ben neden 2 bit koymuşum bilmiyorum.
//jal ve jalr kendi içerisinde çalışıryor zaten bu buyruklarda belleğe bir şey yazılmadığı için direkt atlanması gerekiyor.
always @ (*) begin
    if (isa_slct == 1'b0) 
        result_out_reg = alu_result_out;
    else  
        result_out_reg = mdu_result_out;
end

assign wb_contorlZ = wb_contorlD[0]; //harris kitabından aldım. Hazard unit için bir sinyal.

always @(posedge clk) begin
    if(reset)begin
        result_out <= 0;
        mem_write_data <= 0;
        rdM <= 0;
        reg_writeM <= 0;
        mem_writeM <= 0;
        wb_controlM <= 0;
        pc_4_out<= 0;
    end
    else begin
        result_out <= result_out_reg; 
        mem_write_data <= alu_src_B;
        rdM <= rd_addr_d;
        reg_writeM <= reg_writeD;
        mem_writeM <= mem_writeD;
        wb_controlM <= wb_controlD;
        pc_4_out <= pc_4;
    end
end


endmodule