`include "Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module MDU (
    input[`DATA_WIDTH-1:0] s1,
    input[`DATA_WIDTH-1:0] s2,
    input[`FUNCT3_WIDTH-1:0] funct3,
    output [`DATA_WIDTH-1:0] d3
);

localparam [31:0] MUL = `MUL;
localparam [31:0] MULH = `MULH;
localparam [31:0] MULHSU = `MULHSU;
localparam [31:0] MULHU = `MULHU;
localparam [31:0] DIV = `DIV;
localparam [31:0] DIVU = `DIVU;
localparam [31:0] REM = `REM;
localparam [31:0] REMU = `REMU;


wire [`MUL_WIDTH-1:0] mul_result;
wire [`MUL_WIDTH-1:0] mulhu_result;
wire [`MUL_WIDTH-1:0] mulhsu_result;

assign mul_result = $signed(s1) * $signed(s2);
assign mulhu_result = $unsigned(s1) * $unsigned(s2);
assign mulhsu_result = $unsigned(s1) * $signed(s2);


assign d3 = funct3 == MUL[14:12] ? mul_result[31:0] :
            funct3 == MULH[14:12] ? mul_result[63:32] :
            funct3 == MULHSU[14:12] ? mulhsu_result[63:32] :
            funct3 == MULHU[14:12] ? mulhu_result[63:32] :
            funct3 == DIV[14:12] ? (s2 == 32'b0 ? 32'hFFFFFFFF : $signed(s1) / $signed(s2)) :
            funct3 == DIVU[14:12] ? (s2 == 32'b0 ? 32'hFFFFFFFE : $unsigned(s1) / $unsigned(s2)) :
            funct3 == REM[14:12] ? (s2 == 32'b0 ? s1 : $signed(s1) % $signed(s2)):
            funct3 == REMU[14:12] ? (s2 == 32'b0 ? s1 : $unsigned(s1) % $unsigned(s2)):
            32'b0;
endmodule