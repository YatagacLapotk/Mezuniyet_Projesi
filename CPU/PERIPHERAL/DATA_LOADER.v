`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module DATA_LOADER (
    input clk,
    input reset,
    input [31:0] mem_data,
    input out_selector, //1 ise spi 0 ise uart
    output tx_enable,
    output spi_enable,
    output [7:0] uart_out,
    output [7:0] spi_out
);

localparam STALL = 0, START = 1, DATA = 2,DONE = 3;
    
endmodule