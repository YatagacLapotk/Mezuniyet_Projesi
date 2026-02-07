`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"

module FETCH (
    input clk,
    input reset,
    input stall,
    input flush,
    input [`DATA_WIDTH-1:0] cache_in,
    input cache_valid,
    input [`DATA_WIDTH-1:0] branch_target,
    input branch,
    output [`DATA_WIDTH-1:0] instruction_address_out,
    output [`DATA_WIDTH-1:0] pc_plus_4_out,
    output [`DATA_WIDTH-1:0] instruction_out
);
    
    reg [31:0] pc_reg;


    always @(posedge clk) begin
        if(reset)begin
            pc_reg <= `FIRST_ADDR;
        end
        else begin
            if (~stall) begin
                if(branch) pc_reg <= branch_target;
                else       pc_reg <= pc_reg+4;
            end
        end
    end

    assign instruction_address_out = pc_reg;
    assign instruction_out = cache_in;
    assign pc_plus_4_out = pc_reg + 4;


endmodule
