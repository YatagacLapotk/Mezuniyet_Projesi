`include "sabit_veriler.vh"

module SPI_master (
    input wire clk,
    input wire reset,
    output reg mosi, // Master out slave in
    input wire miso, // Master in slave out 
    input wire [7:0] data_out, // Gönderilecek data
    output reg [7:0] data_in, // Alınan data
    output reg data_ready,
    output reg busy,
    input wire sclk,  // Haberleşme için kullanılacak sclk. sclk_gen modülünden gelecek.
    output reg ss, // Slave select 
    input wire enable, // Harici enable sinyali
    input wire sclk_enable,
    input wire clear
);


parameter IDLE = 2'b00;
parameter START = 2'b01;
parameter DATA = 2'b10;
parameter STOP = 2'b11;

reg [1:0] state = IDLE;
reg [7:0] miso_buffer; // Mastera gelen verinin geçici tutulacağı 
reg [7:0] mosi_buffer; // Masterdan giden verinin geçini tutlacağı yer
reg [2:0] bit_index = 0;
reg sclk_prev = 0;

always @ (posedge clk or posedge reset) begin
    if (reset) begin
        state <= IDLE;
        data_ready <= 1'b0;
        busy <= 1'b0;
        mosi <= 1'b0;
        ss <= 1'b1; // Default HIGH 
        data_in <= 8'b0;
        miso_buffer <= 8'b0;
        mosi_buffer <= 8'b0;
        bit_index <= 3'd0;
    end else begin
        sclk_prev <= sclk;
        case (state) 
        IDLE: begin
            if (clear) data_ready <= 1'b0;
            busy <= 1'b0;
            mosi <= 1'b0;
            ss <= 1'b1; 
            if (enable && sclk_enable) begin
                state <= START;
                mosi_buffer <= data_out;
            end
        end
        START: begin
            if (~sclk_enable) begin
                state <= IDLE;
            end else begin
                busy <= 1'b1; //İletişime başlandı
                ss <= 1'b0; // LOW olduğnda haberleşme olr
                mosi <= mosi_buffer[7]; // mode 0 SPI da sclk'nın ilk pozitif kenarında önce MSB çıkış hattına yerleştirilir.
                state <= DATA;
            end 
        end
        DATA: begin
            if (~sclk_enable) begin
                state <= IDLE;
            end
            else if (sclk_prev == 0 && sclk == 1) begin //posedge algılama
                miso_buffer <= miso_buffer << 1; // bir sola kaydırdık
                miso_buffer[0] <= miso; // LSB'ye slaveden gelen (miso inputu) biti yerleştirdik
            end else if (sclk_prev == 1 && sclk == 0) begin //negedge algılama
                if (bit_index == 3'd7) begin
                    state <= STOP;
                    bit_index <= 0;
                end else begin
                    bit_index <= bit_index + 1;
                    mosi_buffer <= mosi_buffer << 1; // bir sola kaydırdık
                    mosi <= mosi_buffer[6]; // MSB'yi mosi hattına koyduk
                end 
            end
        end
        STOP: begin
            state <= IDLE;
            busy <= 1'b0;
            data_in <= miso_buffer;
            data_ready <= 1'b1;
            ss <= 1'b1;
        end
        endcase
    end        
end
endmodule