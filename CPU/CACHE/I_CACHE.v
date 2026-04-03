`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module I_CACHE (
input clk,
input [`INSTRUCTION_WIDTH-1:0] inst_in,
input [`INST_ADDRESS-1:2] addr,  //Cacche boyutu ne kadar olması lazım kararlaştırırız tam emin değilim ben de onu ayarlamamız lazım.
input we,
output hit,
output [`INSTRUCTION_WIDTH-1:0] inst_out
);
    
endmodule