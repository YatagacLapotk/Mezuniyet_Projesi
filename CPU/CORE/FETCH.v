`include "Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"

module FETCH (
    input clk,
    input reset,
    input stall,
    input [`DATA_WIDTH-1:0] memory_in,
    input [`DATA_WIDTH-1:0] branch_target,
    input branch,
    output [`DATA_WIDTH-1:0] pc_out,
    output [`DATA_WIDTH-1:0] branch_reg_addr,
    output [`DATA_WIDTH-1:0] instruction_out
);
    
    reg [31:0] pc_reg;


    always @(posedge clk) begin
        if(reset)begin
            pc_reg <= 0;
        end
        else begin
            if (~stall) begin
                if(branch) pc_reg <= branch_target;
                else       pc_reg <= pc_reg+4;
            end
        end
    end

    assign pc_out = pc_reg;
    assign instruction_out = memory_in;
    assign branch_reg_addr = pc_out+4;


endmodule
