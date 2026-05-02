module UART_tx(
   input wire [7:0] data_in,
   input wire clk,
   input wire reset,
   input wire tx_enable, // transmit işlemini başlatmak için kullanılacak harici bir sinyal
   input wire enable, // Baudgenerate'den gelecek tx enable sinyali
   output reg tx_out
);

/*
inital begin
   tx_out = 1; 
end
Bura gerekli mi emin değilim.
*/
parameter IDLE = 2'b00;  
parameter START = 2'b01;
parameter DATA = 2'b10;
parameter STOP = 2'b11;

reg [1:0] state = IDLE;
reg [2:0] bit_index;  // 8 bit olduğu için 3 bit index kontroli için yeterli
reg [7:0] data_buffer; // Hafızdan gelen veriyi göndermek için geçici olarak tutan register

always @(posedge clk or posedge reset) begin
   if (reset) begin
      state <= IDLE; // reset durumunda IDLE geçiyoruz, aşağıda IDLE durumunda tx_out 1  yaptığımız için burada atama gereği duymadım.
      bit_index <= 0;
      data_buffer <= 0;
   end else begin
      case (state)
         IDLE: begin
            tx_out <= 1;
            if (~tx_enable) begin // harici olarak gelen enable sinyali LOW duruma geçince veri gönderimi başlar
               state <= START;
               data_buffer <= data_in;
               bit_index <= 0;
            end
         end
         START: begin
            if (enable) begin
               tx_out <= 0; // Start biti LOW olur
               state <= DATA;
            end
         end
         DATA: begin
            if (enable) begin
               tx_out <= data_buffer[bit_index];
               bit_index <= bit_index + 1;
               if (bit_index == 3'h7)
                  state <= STOP;
            end
         end
         STOP: begin
            if (enable) begin
               tx_out <= 1; // Stop biti HIGH olmalı (zaten IDLE durumunda HIGH yapıyoruz burası gerekli mi emin değilim)
               state <= IDLE; // Gönderim tamamlanınca tekrar IDLE durumuna geçiyoruz
            end
         end
         default: begin
            state <= IDLE;
            tx_out <= 1;
         end   
      endcase
   end

end
endmodule
