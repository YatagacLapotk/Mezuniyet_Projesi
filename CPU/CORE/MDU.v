`include "sabit_veriler.vh"
module MDU (
    input[`DATA_WIDTH-1:0] s1,
    input[`DATA_WIDTH-1:0] s2,
    input[`FUNCT3_WIDTH-1:0] funct3,
    output [`DATA_WIDTH-1:0] d3
);

wire signed [`DATA_WIDTH-1:0] s1_signed = s1;
wire signed [`DATA_WIDTH-1:0] s2_signed = s2;

wire [`MUL_WIDTH-1:0] mul_result;
wire [`MUL_WIDTH-1:0] mulhu_result;
wire [`MUL_WIDTH-1:0] mulhsu_result;

assign mul_result = s1_signed * s2_signed;
assign mulhu_result = s1 * s2;
assign mulhsu_result = s1_signed * $signed({1'b0, s2});

reg [`DATA_WIDTH-1:0] d3_reg;
always @(*) begin
    case (funct3)
        3'b000: d3_reg = mul_result[31:0];
        3'b001: d3_reg = mul_result[63:32];
        3'b010: d3_reg = mulhsu_result[63:32];
        3'b011: d3_reg = mulhu_result[63:32];
        3'b100: begin
            if (s2 == 32'b0)
                d3_reg = 32'hFFFFFFFF;
            else
                d3_reg = s1_signed / s2_signed;
        end
        3'b101: begin
            if (s2 == 32'b0)
                d3_reg = 32'hFFFFFFFE;
            else
                d3_reg = s1 / s2;
        end
        3'b110: begin
            if (s2 == 32'b0)
                d3_reg = s1;
            else
                d3_reg = s1_signed % s2_signed;
        end
        3'b111: begin
            if (s2 == 32'b0)
                d3_reg = s1;
            else
                d3_reg = s1 % s2;
        end
        default: d3_reg = 32'b0;
    endcase
end
assign d3 = d3_reg;
endmodule