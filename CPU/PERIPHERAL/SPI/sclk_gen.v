`define CLK 5000000
`define BAUD_RATE 19200

module sclk_gen(
    input wire clk,
    input wire reset,
    input wire sclk_enable, // Enable sinyali HIGH olduğu sürece sclk üretir. haberleşme olmadığında sclk LOW olmalı
    output reg sclk
);


parameter counter_sclk = (`CLK / `BAUD_RATE)/2; // Clock frenkansını SPI frekansına ayarlar. 2'ye bölme sebebi 43 tick LOW 43 tick HIGH olur.
reg [9:0] counter = 0; 

always @ (posedge clk or posedge reset) begin
    if (reset) begin
    counter <= 0;
    sclk <= 0;
    end else if (sclk_enable) begin
        if (counter == counter_sclk-1) begin
            counter <= 0;
            sclk <= ~sclk; // UART'ın aksine bir enable sinyali üretmiyoruz, haberleşmede kullanılacak olan ayrı bir clock sinyali üretiyoruz dolayısıyla her 43 tikte bir tersliyoruz.
        end else 
            counter <= counter + 1;
    end else begin
        sclk <= 0;
        counter <= 0;
    end
end
endmodule