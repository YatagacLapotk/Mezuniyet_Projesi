`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module PROGRAM_LOADER (
    input clk,
    input reset,
    input data_ready_uart,
    input data_ready_spi,
    input busy_spi,
    input busy_uart,
    input [7:0] data_in_uart,
    input [7:0] data_in_spi,
    output reg done,
    output reg cpu_halt,
    output reg clear,
    output reg we,
    output reg [`DATA_WIDTH-1:0] write_ptr,
    output reg [`DATA_WIDTH-1:0] w_addr,
    output reg [`DATA_WIDTH-1:0] w_data
);
  
localparam STALL = 0, START_U = 1,START_S = 7, DATA_U = 2, DATA_S = 8, WAIT_ACK_U = 3, WAIT_ACK_S = 9, LOAD_U = 4, LOAD_S = 10, PC_TRANSFER_U = 5, PC_TRANSFER_S = 11,DONE = 6;

reg [1:0] wait_for_data;
reg [3:0] state;
reg [`DATA_WIDTH-1:0] data_temp;

always @(posedge clk) begin
    if(reset) begin
        state <= STALL;
        write_ptr <= `UART_ADDR;
        cpu_halt <= 0;
        clear <= 0;
        we <= 0;
        wait_for_data <= 0;
        data_temp <= 0;
        done <= 0;
    end
    else begin
        case (state)
            STALL : begin
                we <= 0;
                done <= 0;
                if(data_ready_uart|busy_uart) begin 
                    state <= START_U;
                    write_ptr <= `UART_ADDR; // reset write pointer for next session
                end
                else if(data_ready_spi|busy_spi) begin 
                    state <= START_S;
                    write_ptr <= `SPI_ADDR; // reset write pointer for next session
                end
                else begin
                    state <= STALL;
                end
            end

            START_U: begin
                state <= DATA_U;
                cpu_halt <= 1;
            end
            START_S: begin
                state <= DATA_S;
                cpu_halt <= 1;
            end
            DATA_U : begin
                if(data_ready_uart) begin
                        case (wait_for_data)        //8 bit dataların 32 bite çevirimi
                        2'd0 : data_temp[7:0] <= data_in_uart;
                        2'd1 : data_temp[15:8] <= data_in_uart;
                        2'd2 : data_temp[23:16] <= data_in_uart;
                        2'd3 : data_temp[31:24] <= data_in_uart;
                        endcase
                    wait_for_data <= wait_for_data + 1;
                    clear <= 1;
                    state <= WAIT_ACK_U;
                end
            end
            DATA_S : begin
                if(data_ready_spi) begin
                        case (wait_for_data)        //8 bit dataların 32 bite çevirimi
                        2'd0 : data_temp[7:0] <= data_in_spi;
                        2'd1 : data_temp[15:8] <= data_in_spi;
                        2'd2 : data_temp[23:16] <= data_in_spi;
                        2'd3 : data_temp[31:24] <= data_in_spi;
                        endcase
                    wait_for_data <= wait_for_data + 1;
                    state <= WAIT_ACK_S;
                end
            end
            WAIT_ACK_U : begin
                clear <= 0;
                if(!data_ready_uart) begin
                    // wait_for_data wraps 3+1=0 when all 4 bytes collected
                    if(wait_for_data == 0) state <= LOAD_U;
                    else state <= DATA_U;
                end
            end
            WAIT_ACK_S : begin
                if(!data_ready_spi) begin
                    // wait_for_data wraps 3+1=0 when all 4 bytes collected
                    if(wait_for_data == 0) state <= LOAD_S;
                    else state <= DATA_S;
                end
            end
            LOAD_U : begin
                w_addr <= write_ptr;
                w_data <= data_temp;
                we <= 1;
                state <= PC_TRANSFER_U;
            end
            LOAD_S : begin
                w_addr <= write_ptr;
                w_data <= data_temp;
                we <= 1;
                state <= PC_TRANSFER_S;
            end
            PC_TRANSFER_U : begin
                we <= 0;
                if(data_ready_uart|busy_uart) begin // Eğer yeni bir data gelirse direkt sonraki adrese yazılıyor. 
                    state <= DATA_U;
                    write_ptr <= write_ptr + 4;
                end 
                else begin //Gelmezse sistem normal konumuna dönüyor
                    state <= DONE;
                end
            end
            PC_TRANSFER_S : begin
                we <= 0;
                if(data_ready_spi|busy_spi) begin // Eğer yeni bir data gelirse direkt sonraki adrese yazılıyor. 
                    state <= DATA_S;
                    write_ptr <= write_ptr + 4;
                end 
                else begin //Gelmezse sistem normal konumuna dönüyor
                    state <= DONE;
                end
            end
            DONE : begin
                done <= 1;
                cpu_halt <= 0;
                state <= STALL;
            end
            default: state <= STALL;
        endcase
    end
end
endmodule