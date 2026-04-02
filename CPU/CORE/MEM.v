`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"

module MEM (
    input clk,
    input reset,
    input [`DATA_WIDTH-1:0] execute_result_in,
    input [`DATA_WIDTH-1:0] mem_write_data,
    input reg_write,
    input mem_write,
    input [`ADDRESS_WIDTH-1:0] rdM,
    output [`ADDRESS_WIDTH-1:0] rdW,
    output [`DATA_WIDTH-1:0] execute_result_out
);
    
endmodule