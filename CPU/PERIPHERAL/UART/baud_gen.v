`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module baudrate (
    input wire clk,
    input wire reset,
    output wire rx_enable,
    output wire tx_enable
);
    parameter counter_tx = `CLK / `BAUD_RATE; // 868
    parameter counter_rx = `CLK / (`BAUD_RATE * 16); // 54 reciver için 16x oversampling yapıyoruz. yani her 868 clock atımında değil, her 54 clock atımında bir enable sinyali üretiyor.Yani 16 kat daha sık enable sinyali üretiyor. UART recieverlerde yapılan bir uygulama imiş.BAUD_GEN_TB
    reg [9:0] tx_acc = 0;
    reg [5:0] rx_acc = 0;

    assign tx_enable = (tx_acc == 0) ? 1'b1 : 1'b0;
    assign rx_enable = (rx_acc == 0) ? 1'b1 : 1'b0; 
    
    always @ (posedge clk) begin
        if (reset) begin
            tx_acc <= 0;
            rx_acc <= 0;
        end else begin
            if (rx_acc == counter_rx - 1) 
                rx_acc <= 0;
            else 
                rx_acc <= rx_acc + 1;
            if (tx_acc == counter_tx - 1) 
                tx_acc <= 0;
            else 
                tx_acc <= tx_acc + 1;
        end
    end

endmodule
