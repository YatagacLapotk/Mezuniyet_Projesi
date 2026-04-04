`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module I_CACHE(
input clk,
input reset,

// comm interface
input we,
input [`INSTRUCTION_WIDTH-1:0] inst_in,
input [`CACHE_ADDRESS-1:0] w_addr,

//FETCH inst request
input instruction_req,
input [`CACHE_ADDRESS-1:0] r_addr,
output reg [`INSTRUCTION_WIDTH-1:0] inst_out,
output hit,

// Memory miss request 
output mem_req,
output reg [`INSTRUCTION_WIDTH-1:0] mem_address,         
input wire [`INSTRUCTION_WIDTH-1:0] mem_data_in,         
input wire mem_ready 
);

reg [`INSTRUCTION_WIDTH-1:0] i_cache [0:`CACHE_SIZE]; // cache boyutunu 8kb olara ayarladım sonrasında konuşur değişiriz.

always @(posedge clk) begin
    if (reset)begin
        for(integer i = 0; i<`INSTRUCTION_WIDTH-1;i+=1)begin
        
        end
    end 
    if (we)begin
        i_cache[w_addr] = inst_in;
    end
    else if (instruction_req)begin
        inst_out <= i_cache[r_addr];
    end


end



    
endmodule