
`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module DECODE (
    input clk,
    input reset,
    input flushE,
    input we,
    input [`ADDRESS_WIDTH-1:0] w_addr,
    input [`INSTRUCTION_WIDTH-1:0] instruction,
    input [`DATA_WIDTH-1:0] pc,
    input [`DATA_WIDTH-1:0] wd,
    output reg [`DATA_WIDTH-1:0] pc_out,
    output reg [`DATA_WIDTH-1:0] rd1,
    output reg [`DATA_WIDTH-1:0] rd2,
    output reg [`ADDRESS_WIDTH-1:0] rs1_addr_out,
    output reg [`ADDRESS_WIDTH-1:0] rs2_addr_out,
    output reg [`ADDRESS_WIDTH-1:0] rd_addr_d,
    output reg [`ALU_CNTR-1:0] alu_control,
    output reg alu_imm_en,
    output reg [`MDU_CNTRL-1:0] mdu_control,
    output reg [`CSR_CNTRL-1:0] csr_control,
    output reg [`CSR_ADDR_WIDTH-1:0] csr_addr,
    output reg [`DATA_WIDTH-1:0] csr_data,
    output reg [`DATA_WIDTH-1:0] imm, 
    output reg [`WB_CNTRL-1:0] wb_cntrl,
    output reg [`ISA_SLCT-1:0] isa_slct,
    output reg exception_type, //ecall ve ebreak için ayırılmış bittir. 0 olursa ecall 1 olursa ebreak oluyor. 
    output reg reg_write,
    output reg mem_write,
    output reg exception,
    output reg branch,
    output reg jump
);

localparam [6:0] r_logic   = 7'b0110011;
localparam [6:0] i_logic   = 7'b0010011;
localparam [6:0] s_logic   = 7'b0100011;
localparam [6:0] l_logic   = 7'b0000011;
localparam [6:0] b_logic   = 7'b1100011;
localparam [6:0] sys_logic = 7'b1110011;


wire [`OPCODE_WIDTH-1:0] opcode;
wire [`FUNCT3_WIDTH-1:0] funct3;
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
wire [`DATA_WIDTH-1:0] imms_i;
wire [`DATA_WIDTH-1:0] imms_s;
wire [`DATA_WIDTH-1:0] imms_b;
wire [`DATA_WIDTH-1:0] imms_u;
wire [`DATA_WIDTH-1:0] imms_j;
wire [`DATA_WIDTH-1:0] immu_i;
wire [`DATA_WIDTH-1:0] immu_s;
wire [`DATA_WIDTH-1:0] immu_b;
wire [`DATA_WIDTH-1:0] immu_u;
wire [`DATA_WIDTH-1:0] immu_j;
wire [`DATA_WIDTH-1:0] csr_imm;
wire csr_imm_en;
wire un_sign;


wire [`DATA_WIDTH-1:0] rd1_wire;
wire [`DATA_WIDTH-1:0] rd2_wire;

reg [`ADDRESS_WIDTH-1:0] rd_addr_d_reg;
reg [`ALU_CNTR-1:0] alu_control_reg;
reg alu_imm_en_reg;
reg [`MDU_CNTRL-1:0] mdu_control_reg;
reg [`CSR_CNTRL-1:0] csr_control_reg;
reg [`CSR_ADDR_WIDTH-1:0] csr_addr_reg;
reg [`DATA_WIDTH-1:0] imm_reg; 
reg [`WB_CNTRL-1:0] wb_cntrl_reg;
reg [`ISA_SLCT-1:0] isa_slct_reg;
reg reg_write_reg;
reg mem_write_reg;
reg branch_reg;
reg jump_reg;


assign opcode = instruction[6:0];
assign funct3 = instruction[14:12];
assign funct7 = instruction[31:25];
assign shamt = instruction[24:20];
assign rd_addr = instruction[11:7];
assign rs1_addr = instruction[19:15];
assign rs2_addr = instruction[24:20];

REG_FILE REG_FILE(
    .clk(clk),
    .res(reset),
    .we(we),
    .A1(rs1_addr),
    .A2(rs2_addr),
    .A3(w_addr),
    .WD(wd),
    .RD1(rd1_wire),
    .RD2(rd2_wire)
);

//Sign extention for immediate values
assign imms_i = {{20{instruction[31]}}, instruction[31:20]};
assign imms_s = {{20{instruction[31]}}, instruction[31:25], instruction[11:7]};
assign imms_b = {{19{instruction[31]}}, instruction[7], instruction[30:25], instruction[11:8], 1'b0};
assign imms_u = {instruction[31:12], 12'b0};
assign imms_j = {{12{instruction[31]}}, instruction[19:12], instruction[20], instruction[30:21], 1'b0};

assign immu_i = {{20{1'b0}}, instruction[31:20]};
assign immu_s = {{20{1'b0}}, instruction[31:25], instruction[11:7]};
assign immu_b = {{19{1'b0}}, instruction[7], instruction[30:25], instruction[11:8], 1'b0};
assign immu_u = {instruction[31:12], 12'b0};
assign immu_j = {{12{1'b0}}, instruction[19:12], instruction[20], instruction[30:21], 1'b0};

assign un_sign = (instruction == `SLTIU) 
| (instruction == `LHU)
| (instruction == `LBU)
| (instruction == `BLTU)
| (instruction == `BGEU)
| (instruction == `AUIPC)
| (instruction == `LUI)
| (instruction == `JAL);


assign imm_i = (un_sign==1'b0)?  imms_i : immu_i;
assign imm_s = (un_sign==1'b0)?  imms_s : immu_s;
assign imm_b = (un_sign==1'b0)?  imms_b : immu_b;
assign imm_u = (un_sign==1'b0)?  imms_u : immu_u;
assign imm_j = (un_sign==1'b0)?  imms_j : immu_j;

//CSR imm control
assign csr_imm = {27'b0,instruction[19:15]};
assign csr_imm_en = funct3[2];

//ALU contol signal
/*Opcode kontrol  eidlerek R-tipi olup olmadığı kontrol edilir, daha sonra ise funct7nin 5.biti kontrol edilerek SUB ve SRA işlemleri ayrılır, diğer işlemler ise funct3e göre ayrılır.
Branch işlemleri ise opcode kontrol edilerek ayrılır, daha sonra ise funct3e göre ayrılır.*/
always @  (*) begin
    if (opcode == r_logic) begin
        if (funct7[5] == 1'b1)
            alu_control_reg = (funct3 == 3'b000) ? 4'b0001 :  4'b0111; //SUB ve SRA
        else if(funct7[0])begin
            mdu_control_reg = funct3; 
        end
        else begin
            case (funct3)
                3'b000: alu_control_reg = 4'b0000; //ADD
                3'b001: alu_control_reg = 4'b0101; //SLL
                3'b010: alu_control_reg = 4'b1000; //SLT
                3'b011: alu_control_reg = 4'b1001; //SLTU
                3'b100: alu_control_reg = 4'b0100; //XOR
                3'b101: alu_control_reg = 4'b0110; //SRL
                3'b110: alu_control_reg = 4'b0010; //OR
                3'b111: alu_control_reg = 4'b0011; //AND
            endcase    
        end
    end 
    //buradaki alu control değerleri doğru değildi aluya göre ayarladım.
    else if (opcode == b_logic) begin 
        case (funct3)
            3'b000: alu_control_reg = 4'b1010; //BEQ
            3'b001: alu_control_reg = 4'b1101; //BNE
            3'b100: alu_control_reg = 4'b1100; //BLT
            3'b101: alu_control_reg = 4'b1011; //BGE
            3'b110: alu_control_reg = 4'b1110; //BLTU 
            3'b111: alu_control_reg = 4'b1111; //BGEU 
        endcase
    end
    else if ((opcode == i_logic)) begin
        if(funct7[5]) begin
            alu_control_reg = 4'b0111; 
        end
        else begin
            case (funct3)
                3'b000: alu_control_reg = 4'b0000; //ADDI
                3'b001: alu_control_reg = 4'b0101; //SLLI
                3'b010: alu_control_reg = 4'b1000; //SLTI
                3'b011: alu_control_reg = 4'b1001; //SLTIU
                3'b100: alu_control_reg = 4'b0100; //XORI
                3'b101: alu_control_reg = 4'b0110; //SRLI
                3'b110: alu_control_reg = 4'b0010; //ORI
                3'b111: alu_control_reg = 4'b0011; //ANDI
            endcase  
        end 
    end
    else if((opcode == s_logic)||(opcode==l_logic))begin
        alu_control_reg = 4'b0000; 
    end 
    else if (opcode==sys_logic) begin
       csr_control = funct3[1:0];
    end
    else begin
        alu_control_reg = 4'b0000;
        mdu_control_reg = 3'b000;
        csr_control = 2'b00;
    end
end
/* Burda "cannot be driven by primitives or continuous assignment." hatası geliyordu register oldukları için yapayzeka imm_next diyeb bi değişken tenımlamayı önerdi ama gereksiz gördüm 
direk procedural bloğun içine koydum. Bi de 171 ve 172. satırda da aynı hatayı veriyordu REG_FILE içinde çıkışları wire yaptım o çözdü ama emin değilim.
*/

//Ben açıklamamışım ama tek bitlik işlemleri burada ayptığımız gibi ayrı ayrı hesaplarsak daha az kafa karışır diye düşünüyorum.//
always @ (*) begin
    imm_reg =   (opcode == i_logic)    ? imm_i :
                (opcode == s_logic)    ? imm_s :      
                (opcode == b_logic)    ? imm_b :
                (opcode == 7'b0010111) ? imm_u : //AUIPC
                (opcode == 7'b0110111) ? imm_u : //LUI
                (opcode == 7'b1101111) ? imm_j : //JAL
                (opcode == 7'b1100111) ? imm_i : //JALR
                32'b0;

    alu_imm_en_reg  = (opcode == i_logic)
                    | (opcode == s_logic)
                    | (opcode == b_logic)
                    | (opcode == 7'b0010111) 
                    | (opcode == 7'b0110111)
                    | (opcode == 7'b1101111)
                    | (opcode == 7'b1100111);

    reg_write_reg   = (opcode == l_logic);

    mem_write_reg   = (opcode == s_logic);

    branch_reg      = (opcode == b_logic);

    jump_reg        = (opcode == 7'b1101111) 
                    | (opcode == 7'b1100111);
    
    wb_cntrl_reg    = ((opcode==i_logic)| (opcode==r_logic)) ? 2'b00 // Aklıma sadece default ve alu değeri ne zaman direkt alınır onu yazmak geldi sıralamaların hepsi harris ve harristeki pipeline tasarımından alınma. Devamı yapılabilir.
                    : 2'b11;  
    
    isa_slct_reg    = (opcode==r_logic) & (funct7[0]); //Sadece bir olup olmama durumuna bakılır. 1 ise mdu çıktısı alınır. 0 ise alu çıktısı alınır.
    
    exception       =  (opcode==sys_logic) & (funct3==3'b000);
    
    exception_type  =  (instruction[20]) & (exception);

    csr_data = (csr_imm_en) ? csr_imm : rd1; 

    csr_addr = instruction[31:20];
end

//harris and  harris'in kitabına göre flushE yaptım çünkü çıkışları sadece sıfırlıyoruz. //Tamamdır.
always @ (posedge clk) begin
    if (flushE) begin
        rd1 <= 32'b0;
        rd2 <= 32'b0;
        rd_addr_d_reg <= 0;
        imm_reg <= 32'b0;
        alu_control_reg <= 4'b0;
        alu_imm_en_reg <= 1'b0;
        mdu_control_reg <= 3'b0;
        wb_cntrl_reg <= 0;
        isa_slct_reg <= 0;
        reg_write_reg <= 1'b0;
        mem_write_reg <= 1'b0;
        branch_reg <= 1'b0;
        jump_reg <= 1'b0;
        pc_out <= 0;
        rs1_addr_out <= 0;
        rs2_addr_out <= 0;
    end
    else begin
        rd1 <= rd1_wire;
        rd2 <= rd2_wire;
        rd_addr_d <= rd_addr_d_reg;
        imm <= imm_reg;
        alu_control <= alu_control_reg;
        alu_imm_en <= alu_imm_en_reg;
        mdu_control <= mdu_control_reg;
        wb_cntrl <= wb_cntrl_reg;
        isa_slct <= isa_slct_reg;
        reg_write <= reg_write_reg;
        mem_write <= mem_write_reg;
        branch <= branch_reg;
        jump <= jump_reg; 
        pc_out <= pc;
        rs1_addr_out <= rs1_addr;
        rs2_addr_out <= rs2_addr;
    end
end


endmodule