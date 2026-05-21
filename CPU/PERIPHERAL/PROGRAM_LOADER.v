`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module PROGRAM_LOADER (
    input clk,
    input reset,
    input data_ready,
    input busy,
    input [7:0] data_in,
    output reg done,
    output reg cpu_halt,
    output reg clear,
    output reg we,
    output reg [`DATA_WIDTH-1:0] write_ptr,
    output reg [`DATA_WIDTH-1:0] w_addr,
    output reg [`DATA_WIDTH-1:0] w_data
);
  
localparam STALL = 0, START = 1, DATA = 2, WAIT_ACK = 3, LOAD = 4, PC_TRANSFER = 5,DONE = 6;

reg [1:0] wait_for_data;
reg [2:0] state;
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
                if(data_ready|busy) state <= START;
                else begin
                    state <= STALL;
                    cpu_halt <= 0;
                    write_ptr <= `UART_ADDR; // reset write pointer for next session
                end
            end
            START : begin
                state <= DATA;
                cpu_halt <= 1; 
            end
            DATA : begin
                if(data_ready) begin
                    case (wait_for_data)        //8 bit datalrın 32 bite çevirimi
                        2'd0 : data_temp[7:0] <= data_in;
                        2'd1 : data_temp[15:8] <= data_in;
                        2'd2 : data_temp[23:16] <= data_in;
                        2'd3 : data_temp[31:24] <= data_in;
                    endcase
                    wait_for_data <= wait_for_data + 1;
                    clear <= 1;
                    state <= WAIT_ACK;
                end
            end
            WAIT_ACK : begin
                clear <= 0;
                if(!data_ready) begin
                    // wait_for_data wraps 3+1=0 when all 4 bytes collected
                    if(wait_for_data == 0) state <= LOAD;
                    else state <= DATA;
                end
            end
            LOAD : begin
                w_addr <= write_ptr;
                w_data <= data_temp;
                we <= 1;
                state <= PC_TRANSFER;
            end
            PC_TRANSFER : begin
                we <= 0;
                if(data_ready|busy) begin // Eğer yeni bir data gelirse direkt sonraki adrese yazılıyor. 
                    state <= START;
                    write_ptr <= write_ptr + 4;
                end 
                else begin //Gelmezse sistem normal konumuna dönüyor
                    state <= DONE;
                end
            end
            DONE : begin
                done <= 1;
                state <= STALL;
            end
            default: state <= STALL;
        endcase
    end
end
endmodule