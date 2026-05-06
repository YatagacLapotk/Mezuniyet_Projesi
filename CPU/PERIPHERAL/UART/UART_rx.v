
module UART_rx (
    input wire clk,
    input wire data_in, // hat üzerinden seri olarak bitlerin geleceği wire 
    input wire reset, 
    input wire enable, //baudgen'en gelecek rx enable sinyali 
    input wire rx_enable, // Veri alma işlemni başlatacak harici bir sinyal
    output reg [7:0] rx_in, // UART hattından gelen veriyi tutacak reg
    output reg rx_busy,
    output reg data_ready // Verinin hazır olduğunu belirten reg
); 

initial begin
    rx_in = 8'b0; 
    data_ready = 0;
end
    
parameter START = 2'b00;
parameter DATA = 2'b01;
parameter STOP = 2'b10;

reg [7:0] data_buffer = 8'b0; // gelen veriyi geçici olarak tutacak reg
reg [1:0] state = START;
reg [3:0] bit_index = 3'b0; // bit pozisyonunu takip etmek için reg
reg [3:0] sample_count = 4'b0; // her bit için kaç örnek alındığını takip etmek için reg

always @ (posedge clk or posedge reset) begin
    if (reset) begin
        rx_busy <= 0;
        rx_in <= 8'b0;
        state <= START;
        bit_index <= 0;
        sample_count <= 0;
        data_buffer <= 8'b0;
        data_ready <= 0;
    end else if (~rx_enable && enable) begin
        case (state) 
            START: begin
                rx_busy <= 1; // veri alma işlemi başladığında rx_busy sinyalini aktif ediyoruz.
                if (!data_in || sample_count != 0) // Start biti LOW olmalı burada start bitinin LOW olduğunu kontrol ediyoruz, sample_count 0. sampledan 15.sample kadar devam edecek.
                    sample_count = sample_count + 1; // start biti LOW olduğu müddetçe sample_count'u arttırmaya devam ediyoruz.
                if (sample_count == 15) begin // 16 tane örnek aldıktan sonra data okumaya başlıyoruz.
                    state <= DATA;
                    bit_index <= 0;
                    sample_count <= 0;
                    data_buffer <= 0;
                end
            end
            DATA: begin
                sample_count <= sample_count + 1; // her biti 8. sample'da oluyoruz
                if (sample_count == 8) begin
                    data_buffer[bit_index] <= data_in;
                    bit_index <= bit_index + 1;
                end else if (bit_index == 8 && sample_count == 15) begin// sample_count 15 olduğunda + 1 geldiği vakit otomatik olarak sample_count 0 olur.
                    state <= STOP;
                end       
            end
            STOP: begin
                if (sample_count == 15 || (sample_count >= 8 && !data_in)) begin
                    sample_count <= 0;
                    bit_index <= 0;
                    rx_in <= data_buffer; // data_buffer'daki veriyi rx_in'e atıyoruz.
                    data_ready <= 1; // verinin hazır olduğunu belirtiyoruz.
                end else
                    sample_count <= sample_count + 1; // yukarıdaki koşullar sağlanmazsa sample_count'u arttırmaya devam
            end  
            default: begin
                state <= START;
            end        
        endcase
    end
end

endmodule