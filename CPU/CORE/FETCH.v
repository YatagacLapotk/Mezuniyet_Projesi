`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"

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
    output reg [`DATA_WIDTH-1:0] instruction_out, 
    output reg [`DATA_WIDTH-1:0] pc_4_out, 
    output reg [`DATA_WIDTH-1:0] pc_out 
);

    wire [31:0] pc;
    wire [31:0] pc_4_out_reg;
    wire [31:0] instruction_out_reg;
    reg [31:0] pc_out_reg;

    
    I_CACHE I_CACHE(
        .clk(clk),
        .reset(reset),
        .we(exception),
        .inst_in(cache_input),
        .w_addr(exception_handler_address),
        .r_addr(pc_out),
        .inst_out(instruction_out_reg)
    );
    

    assign pc = (pc_src) ? (branch_target) : (pc_4_out);
    //PC
    always @(posedge clk) begin
        if (reset)begin
            pc_out_reg <= `FIRST_ADDR;
        end
        if (stallF) begin
            if(exception)begin
                pc_out_reg <=  exception_handler_address;
            end
        end
        else begin
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
        else begin
            pc_4_out <= pc_4_out_reg;
            pc_out <= pc_out_reg;
            instruction_out <= instruction_out_reg;
        end
    end
   

endmodule
