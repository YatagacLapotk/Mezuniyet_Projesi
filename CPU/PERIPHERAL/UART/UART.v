module UART (
    input wire tx_enable, // Harici sinyal
    input wire rx_enable, // Harici sinyal
    input wire clk,
    input wire reset,
    input wire clear,
    output wire tx_out, // UART hattına seri olarak gönderilecek veri
    input wire data_in, // UART hattından seri olarak gelen veri
    input wire [7:0] data_out, // Gönderilecek veriyi tutan 8 bitlik wire
    output wire rx_busy,
    output wire [7:0] rx_in, // UART hattından gelen veriyi tutacak reg
    output wire data_ready 

);

wire baud_enable_tx;
wire baud_enable_rx;


baudrate baudrate (
    .clk(clk),
    .reset(reset),
    .rx_enable(baud_enable_rx),
    .tx_enable(baud_enable_tx)
);

UART_tx UART_tx (
    .clk(clk),
    .reset(reset),
    .txena(tx_enable),
    .tx_baudena(baud_enable_tx),
    .data_out(data_out),
    .tx_out(tx_out)
);

UART_rx UART_rx (
    .clk(clk),
    .reset(reset),
    .rxena(rx_enable),
    .rx_baudena(baud_enable_rx),
    .data_in(data_in),
    .rx_in(rx_in),
    .rx_busy(rx_busy),
    .data_ready(data_ready),
    .clear(clear)
);
endmodule