module REG_FILE (
    input               clk,
    input               res,
    input      [4:0]    A1,
    input      [4:0]    A2,
    input      [4:0]    A3,
    input      [31:0]   WD,
    output reg [31:0]   RD1,
    output reg [31:0]   RD2
);

reg [31:0] REG32[31:0] ;


always @(posedge clk) begin
    if(res)begin 
        for (integer i=0;i<32;i+=1) begin
            REG32[i] <= 32'b0;
        end
        RD1 <= 32'b0;
        RD2 <= 32'b0;
    end
    else begin
       RD1 <= REG32[A1];
       RD2 <= REG32[A2];
       REG32[A3] <= WD;
    end
end
    
endmodule