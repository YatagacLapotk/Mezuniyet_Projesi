`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module top (
    input clk,
    input reset,
    input rx_enable,
    input uart_in,
    input spi_enable,
    input sclk_enable,
    input miso,
    output mosi,
    output ss,
    output busy
);

wire [`DATA_WIDTH-1:0] write_ptr;
wire [`DATA_WIDTH-1:0] loader_addr;
wire [`DATA_WIDTH-1:0] loader_data;
wire cpu_halt;
wire loader_done;
wire loader_we;
wire uart_busy;
wire spi_busy;
wire data_ready_uart;
wire data_ready_spi;
wire clear;
wire [7:0] data_in_uart;
wire [7:0] data_in_spi;

wire [7:0] uart_out_buffer;
wire [7:0] spi_output_buffer;
wire tx_enable;
wire uart_output;
wire spi_output;

CORE CORE (
    .clk(clk),
    .reset(reset),
    .loader_we(loader_we),
    .load_done(loader_done),
    .loader_addr(loader_addr),
    .loader_data(loader_data),
    .cpu_halt(cpu_halt)
);

UART UART(
    .clk(clk),
    .reset(reset),
    .tx_enable(tx_enable), //Harici sinyal
    .rx_enable(rx_enable), //Harici sinyal
    .clear(clear),
    .data_in(uart_in),  //UART hattına seri olarak gelecek veri
    .data_out(uart_out_buffer), //UART üzerinden dışarı gönderilecek 8 bitlik veri
    .rx_busy(uart_busy),
    .rx_in(data_in_uart), //UART üzerinden içeri alınacak 8 bitlik veri
    .tx_out(uart_output), //UART üzerinden seri olarak dışarı gönderilen veri
    .data_ready(data_ready_uart)
);

SPI SPI(
    .clk(clk),
    .reset(reset),
    .data_out(spi_output_buffer),
    .enable(spi_enable),
    .sclk_enable(sclk_enable),
    .miso(miso),
    .data_ready(data_ready_spi),
    .busy(spi_busy),
    .ss(ss),
    .mosi(mosi),
    .data_in(data_in_spi)
);

PROGRAM_LOADER PROGRAM_LOADER(
    .clk(clk),
    .reset(reset),
    .data_ready_uart(data_ready_uart),
    .data_ready_spi(data_ready_spi),
    .busy_uart(uart_busy),
    .busy_spi(spi_busy),
    .data_in_uart(data_in_uart),
    .data_in_spi(data_in_spi),
    .done(loader_done),
    .cpu_halt(cpu_halt),
    .clear(clear),
    .we(loader_we),
    .write_ptr(write_ptr),
    .w_addr(loader_addr),
    .w_data(loader_data)
);  

assign busy = cpu_halt;
endmodule