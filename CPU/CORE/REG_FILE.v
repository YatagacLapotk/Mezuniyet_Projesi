`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module REG_FILE (
    input           clk,
    input           res,
    input           we,
    input  [`ADDRESS_WIDTH-1:0]    A1,
    input  [`ADDRESS_WIDTH-1:0]    A2,
    input  [`ADDRESS_WIDTH-1:0]    A3,
    input  [`DATA_WIDTH-1:0]   WD,
    output [`DATA_WIDTH-1:0]   RD1,
    output [`DATA_WIDTH-1:0]   RD2
);

reg [`DATA_WIDTH-1:0] REG32[`REG_FILE_DEPTH-1:0] ;

always @(posedge clk) begin
    if(res)begin 
        for (integer i=0;i<`REG_FILE_DEPTH;i+=1) begin
            REG32[i] <= {`DATA_WIDTH{1'b0}};
        end
    end
    else begin
        if(we && A3 != {`ADDRESS_WIDTH{1'b0}})begin
            REG32[A3] <= WD;
        end
    end
end
assign RD1 = REG32[A1];
assign RD2 = REG32[A2];
endmodule