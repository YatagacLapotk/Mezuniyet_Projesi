`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module DECODE (
    input clk,
    input [`INSTRUCTION_WIDTH-1:0] instruction,
    input [`DATA_WIDTH-1:0] pc,
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
    output reg [`DATA_WIDTH-1:0] imm;
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
wire [`DATA_WIDTH-1:0] immu_i;
wire [`DATA_WIDTH-1:0] immu_s;
wire [`DATA_WIDTH-1:0] immu_b;
wire [`DATA_WIDTH-1:0] immu_u;
wire [`DATA_WIDTH-1:0] immu_j;


assign opcode = instruction[6:0];
assign funct3 = instruction[14:12];
assign funct7 = instruction[31:25];
assign shamt = instruction[24:20];
assign rd_addr = instruction[11:7];
assign rs1_addr = instruction[19:15];
assign rs2_addr = instruction[24:20];

//Sign extention for immediate values
assign imm_i = {{20{instruction[31]}}, instruction[31:20]};
assign imm_s = {{20{instruction[31]}}, instruction[31:25], instruction[11:7]};
assign imm_b = {{19{instruction[31]}}, instruction[7], instruction[30:25], instruction[11:8], 1'b0};
assign imm_u = {instruction[31:12], 12'b0};
assign imm_j = {{12{instruction[31]}}, instruction[19:12], instruction[20], instruction[30:21], 1'b0};

assign immu_i = {{20{1'b0}}, instruction[31:20]};
assign immu_s = {{20{1'b0}}, instruction[31:25], instruction[11:7]};
assign immu_b = {{19{1'b0}}, instruction[7], instruction[30:25], instruction[11:8], 1'b0};
assign immu_u = {instruction[31:12], 12'b0};
assign immu_j = {{12{1'b0}}, instruction[19:12], instruction[20], instruction[30:21], 1'b0};

always @ (posedge clk) begin
    if (reset) begin
        imm <= 32'b0;
        alu_control <= 4'b0;
        mdu_control <= 3'b0;
        csr_control <= 3'b0;
        csr_addr <= 12'b0;
        reg_write <= 1'b0;
        mem_write <= 1'b0;
        branch <= 1'b0;
        jump <= 1'b0;
    end
end

//Alu contol signal
//Hepsi R tip buyruk, önce funct7'nin 5. biti kontrol edilir, daha sonra ise funt3 kontrol edilir.
always @  (*) begin
    if (opcode == 7'b0110011) begin
        if (funct7[5] == 1'b1)
            alu_control = (funct3 == 3'b000) ? 4'b0001 :  4'b1000; //SUB ve SRA
        else if begin
            case (funct3)
                3'b000: alu_control = 4'b0000; //ADD
                3'b001: alu_control = 4'b0101; //SLL
                3'b010: alu_control = 4'b1000; //SLT
                3'b011: alu_control = 4'b1001; //SLTU
                3'b100: alu_control = 4'b0100; //XOR
                3'b101: alu_control = 4'b0110; //SRL
                3'b110: alu_control = 4'b0010; //OR
                3'b111: alu_contorl = 4'b0011; //AND
            endcase    
        end
    end
end

//alu_control, mdu_control, csr_control ayrı ayrı hesaplanabilir.
// veya micro code ile bütün kontrol sinyalleri tek bir sinyal olarak hesaplanabilir.

 
    
endmodule