
module UART_rx (
    input wire clk,
    input wire data_in, // hat üzerinden seri olarak bitlerin geleceği wire 
    input wire reset, 
    input wire rx_baudena, //baudgen'en gelecek rx enable sinyali 
    input wire rxena, // Veri alma işlemni başlatacak harici bir sinyal
    input wire clear,
    output reg [7:0] rx_in, // UART hattından gelen veriyi tutacak reg
    output reg rx_busy,
    output reg data_ready // Verinin hazır olduğunu belirten reg
); 


parameter START = 2'b00;
parameter DATA = 2'b01;
parameter STOP = 2'b10;

reg [7:0] data_buffer = 8'b0; // gelen veriyi geçici olarak tutacak reg
reg [1:0] state = START;
reg [3:0] bit_index = 4'b0; // bit pozisyonunu takip etmek için reg
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
    end else begin
    if (clear)
        data_ready <= 0; // clear sinyali geldiğinde data_ready'ı sıfırlıyoruz.
    if (~rxena && rx_baudena) begin
        case (state) 
            START: begin
                if (!data_in || sample_count != 0) begin // Start biti LOW olmalı burada start bitinin LOW olduğunu kontrol ediyoruz, sample_count 0. sampledan 15.sample kadar devam edecek.
                    rx_busy <= 1; // veri alma işlemi başladığında rx_busy sinyalini aktif ediyoruz.
                    sample_count <= sample_count + 1; // start biti LOW olduğu müddetçe sample_count'u arttırmaya devam ediyoruz.
                end else begin
                    rx_busy <= 0;
                end
                if (sample_count == 15) begin // 16 tane örnek aldıktan sonra data okumaya başlıyoruz.
                    state <= DATA;
                    bit_index <= 0;
                    sample_count <= 0;
                    data_buffer <= 0;
                end
            end
            DATA: begin
                if (sample_count == 15) begin
                    sample_count <= 0;
                end else begin
                    sample_count <= sample_count + 1; // her biti 8. sample'da okuyoruz
                end

                if (sample_count == 8) begin
                    data_buffer[bit_index] <= data_in;
                    bit_index <= bit_index + 1;
                end else if (bit_index == 8 && sample_count == 15) begin
                    state <= STOP;
                end       
            end
            STOP: begin
                if (sample_count == 15 || (sample_count >= 8 && data_in)) begin
                    sample_count <= 0;
                    bit_index <= 0;
                    rx_in <= data_buffer; // data_buffer'daki veriyi rx_in'e atıyoruz.
                    data_ready <= 1; // verinin hazır olduğunu belirtiyoruz.
                    state <= START;
                    rx_busy <= 0;
                end else
                    sample_count <= sample_count + 1; // yukarıdaki koşullar sağlanmazsa sample_count'u arttırmaya devam
            end  
            default: begin
                state <= START;
            end        
        endcase
    end
    end
end

endmodule