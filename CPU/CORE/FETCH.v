`include "Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"

module FETCH (
    input clk,
    input reset,
    input stall,
    input [`DATA_WIDTH-1:0] MEMORY_IN,
    input [`DATA_WIDTH-1:0] BRANCH_TARGET,
    input BRANCH,
    output [`DATA_WIDTH-1:0] PC_OUT,
    output [`DATA_WIDTH-1:0] INSTRUCTION_OUT
);
    
endmodule
