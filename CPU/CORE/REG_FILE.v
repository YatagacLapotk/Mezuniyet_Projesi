module REG_FILE (
    input           clk,
    input           res,
    input  [4:0]    A1,
    input  [4:0]    A2,
    input  [4:0]    A3,
    input  [31:0]   WD,
    output [31:0]   RD1,
    output [31:0]   RD2
);

reg [31:0] REG32[31:0] ;


always @(posedge clk) begin
    if(res)begin 
        for (integer i=0;i<32;i+=1) begin
            REG32[i] <= 32'b0;
        end
    end
    else begin
        if(A3 != 5'b0)begin
            REG32[A3] <= WD;
        end
    end
end
assign RD1 = REG32[A1];
assign RD2 = REG32[A2];
endmodule