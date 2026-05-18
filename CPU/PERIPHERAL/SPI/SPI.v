`include "sabit_veriler.vh"

module SPI (
    input wire clk,
    input wire reset,
    input wire [7:0] data_out,
    input wire enable,
    input wire sclk_enable,
    input wire miso,
    input wire clear,
    output wire data_ready,
    output wire busy,
    output wire ss,
    output wire mosi,
    output wire [7:0] data_in
);

wire sclk_w;

sclk_gen sclk_gen (
    .clk(clk),
    .reset(reset),
    .sclk_enable(sclk_enable),
    .sclk(sclk_w)
);


SPI_master SPI_master (
    .clk(clk),
    .reset(reset),
    .miso(miso),
    .data_out(data_out),
    .sclk(sclk_w),
    .enable(enable),
    .mosi(mosi),
    .data_in(data_in),
    .data_ready(data_ready),
    .busy(busy),
    .ss(ss),
    .sclk_enable(sclk_enable),
    .clear(clear) //UART'la aynı program loader'ı kullanmak için ekledim.
);                //UART clear sinyaliyle sıfırladığı için buraya da bir tane ekleyerek ikisiyle de uyumlu olmasını sağladım.                   
endmodule         //Sıkıntı olursa değiştiririz.
