`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module I_CACHE(
input clk,
input reset,

// comm interface
input we,
input [`INSTRUCTION_WIDTH-1:0] inst_in,
input [`CACHE_ADDRESS-1:0] w_addr,

//FETCH inst
input [`CACHE_ADDRESS-1:0] r_addr,
output [`INSTRUCTION_WIDTH-1:0] inst_out
);

reg [`INSTRUCTION_WIDTH-1:0] i_cache [0:`CACHE_SIZE]; // cache boyutunu 8kb olara ayarladım sonrasında konuşur değişiriz.

always @(posedge clk) begin
    if (reset)begin
        for(integer i = 0; i<`CACHE_SIZE;i=i+1)begin
            i_cache[i]<= 0;
        end
    end 
    else if (we)begin
        i_cache[w_addr] = inst_in;
    end
end

assign inst_out = i_cache[r_addr];


    
endmodule