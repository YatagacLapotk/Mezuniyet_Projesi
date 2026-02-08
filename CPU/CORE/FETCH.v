`include "/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"

module FETCH (
    input clk,
    input reset,
    input stall,
    input flush,    
    input exception,
    input [`DATA_WIDTH-1:0] exception_handler_address,                          
    input [`DATA_WIDTH-1:0] cache_in,
    input cache_valid,
    input [`DATA_WIDTH-1:0] branch_target,
    input branch,
    output [`DATA_WIDTH-1:0] instruction_address_out,
    output [`DATA_WIDTH-1:0] pc_plus_4_out,
    output reg [`DATA_WIDTH-1:0] instruction_out,
    output reg instruction_valid_out                       
);
    
    reg [31:0] pc_reg;
    
    always @(posedge clk) begin
        if (reset) begin
            pc_reg <= `FIRST_ADDR;
        end
        else if (exception) begin
            pc_reg <= exception_handler_address;
        end
        else if(~stall) begin
            if (branch) 
                pc_reg <= branch_target;
            else 
                pc_reg <= pc_reg + 4;
        end
    end

    always @(posedge clk) begin
        if (reset) begin
            instruction_out <= `NOP;
            instruction_valid_out <= 1'b0;
        end
        else if (flush) begin
            instruction_out <= `NOP;
            instruction_valid_out <= 1'b0;             
        end
        else if (~stall && cache_valid) begin
            instruction_out <= cache_in;
            instruction_valid_out <= 1'b1;              
        end
        else if (stall) begin
            instruction_valid_out <= 1'b0;
        end
    end

    assign instruction_address_out = pc_reg;
    assign pc_plus_4_out = pc_reg + 4;


endmodule
