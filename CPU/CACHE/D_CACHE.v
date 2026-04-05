`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module D_CACHE (
    input clk,
    input reset,

    // comm interface
    input we,
    input [`DATA_WIDTH-1:0] data_in,
    input [`CACHE_ADDRESS-1:0] w_addr,

    //FETCH inst
    input [`CACHE_ADDRESS-1:0] r_addr,
    output [`DATA_WIDTH-1:0] data_out
);

reg [`DATA_WIDTH-1:0] d_cache [0:`CACHE_SIZE];

always @(posedge clk) begin
    if (reset)begin
        for(integer i = 0; i<`CACHE_SIZE;i+=1)begin
            d_cache[i]<= 0;
        end
    end 
    else if (we)begin
        d_cache[w_addr] = data_in;
    end
end

assign data_out = d_cache[r_addr];

    
endmodule