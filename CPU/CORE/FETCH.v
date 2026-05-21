`include "sabit_veriler.vh"

module FETCH (
    input clk,
    input reset,
    input stallF,
    input stallD,
    input flushD,    
    input exception,
    input pc_src,
    input [`DATA_WIDTH-1:0] exception_handler_address,                          
    input [`DATA_WIDTH-1:0] cache_input,  
    input [`DATA_WIDTH-1:0] branch_target,
    // Program loader interface
    input loader_we,
    input load_done,                   
    input [`DATA_WIDTH-1:0] loader_addr,
    input [`DATA_WIDTH-1:0] loader_data,
    input cpu_halt,
    output reg [`DATA_WIDTH-1:0] instruction_out, 
    output reg [`DATA_WIDTH-1:0] pc_4_out, 
    output reg [`DATA_WIDTH-1:0] pc_out 
);

    wire [31:0] pc;
    wire [31:0] pc_4_out_reg;
    wire [31:0] instruction_out_reg;
    reg [31:0] pc_out_reg;

    wire [`DATA_WIDTH-1:0] cache_w_addr = (loader_we) ? loader_addr : exception_handler_address;
    wire [`DATA_WIDTH-1:0] cache_w_data = (loader_we) ? loader_data : cache_input;

    I_CACHE I_CACHE(
        .clk(clk),
        .reset(reset),
        .we(loader_we),
        .inst_in(cache_w_data),
        .w_addr(cache_w_addr>>2),
        .r_addr(pc_out_reg>>2),
        .inst_out(instruction_out_reg)
    );
    

    assign pc = (exception) ? exception_handler_address :
                (pc_src) ? (branch_target) : (pc_4_out_reg);
    //PC
    always @(posedge clk) begin
        if (reset) begin
            pc_out_reg <= `FIRST_ADDR;
        end
        else if(load_done)begin
            pc_out_reg <= `UART_ADDR; 
        end
        else if (~stallF) begin
            pc_out_reg <= pc;
        end
    end 
    assign pc_4_out_reg = pc_out_reg + 4;
    always @(posedge clk) begin
        if (flushD) begin
            pc_4_out <= 0;
            pc_out <= 0;
            instruction_out <= 0;
        end
        else if(~stallD)begin
            pc_4_out <= pc_4_out_reg;
            pc_out <= pc_out_reg;
            instruction_out <= instruction_out_reg;
        end
    end
   

endmodule
