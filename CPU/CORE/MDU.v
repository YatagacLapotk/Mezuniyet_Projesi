`include "Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module MDU (
    input[`DATA_WIDTH-1:0] s1,
    input[`DATA_WIDTH-1:0] s2,
    input[`FUNCT3_WIDTH-1:0] funct3,
    output [`DATA_WIDTH-1:0] d3
);

wire [`MUL_WIDTH-1:0] mul_result;
wire [`MUL_WIDTH-1:0] mulhu_result;
wire [`MUL_WIDTH-1:0] mulhsu_result;

assign mul_result = $signed(s1) * $signed(s2);
assign mulhu_result = $unsigned(s1) * $unsigned(s2);
assign mulhsu_result = $unsigned(s1) * $signed(s2);


assign d3 = funct3 == 3'b000 ? mul_result[31:0] :
            funct3 == 3'b001 ? mul_result[63:32] :
            funct3 == 3'b010 ? mulhsu_result[63:32] :
            funct3 == 3'b011 ? mulhu_result[63:32] :
            funct3 == 3'b100 ? (s2 == 32'b0 ? 32'hFFFFFFFF : $signed(s1) / $signed(s2)) :
            funct3 == 3'b101 ? (s2 == 32'b0 ? 32'hFFFFFFFE : $unsigned(s1) / $unsigned(s2)) :
            funct3 == 3'b110 ? (s2 == 32'b0 ? s1 : $signed(s1) % $signed(s2)):
            funct3 == 3'b111 ? (s2 == 32'b0 ? s1 : $unsigned(s1) % $unsigned(s2)):
            32'b0;
endmodule