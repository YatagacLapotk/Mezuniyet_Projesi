`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"

module FETCH_tb ();

reg clk;
reg reset;
reg stall;
reg flush;
reg exception;
reg [`DATA_WIDTH-1:0] exception_handler_address;
reg [`DATA_WIDTH-1:0] cache_in;
reg cache_valid;
reg [`DATA_WIDTH-1:0] branch_target;
reg branch;
wire [`DATA_WIDTH-1:0] instruction_address_out;
wire [`DATA_WIDTH-1:0] pc_plus_4_out;
wire [`DATA_WIDTH-1:0] instruction_out;
wire instruction_valid_out;

initial begin
    forever #5 clk = ~clk;
end

FETCH fetch_inst (
    .clk(clk),
    .reset(reset),
    .stall(stall),
    .flush(flush),
    .exception(exception),
    .exception_handler_address(exception_handler_address),
    .cache_in(cache_in),
    .cache_valid(cache_valid),
    .branch_target(branch_target),
    .branch(branch),
    .instruction_address_out(instruction_address_out),
    .pc_plus_4_out(pc_plus_4_out),
    .instruction_out(instruction_out),
    .instruction_valid_out(instruction_valid_out)
);
    
initial begin
    // Initialize signals
    clk = 0;
    reset = 1;
    stall = 0;
    flush = 0;
    exception = 0;
    exception_handler_address = `DATA_WIDTH'b0;
    cache_in = `DATA_WIDTH'b0;
    cache_valid = 0;
    branch_target = `DATA_WIDTH'b0;
    branch = 0;

    #20;

    reset = 0;
    cache_in = 32'h00000001; 
    cache_valid = 1;

    #10; 

    cache_valid = 0;
    branch_target = 32'h00001000; // Example branch target
    branch = 1;

    #10; 

    branch = 0; 
    exception_handler_address = 32'h00002000; // Example exception handler address
    exception = 1;

    #10; 

    exception = 0; 
    flush = 1;
    
    #10; 

    flush = 0; 
    cache_in = 32'h00000002; 
    cache_valid = 1;

    #10;

    cache_in = 32'h00020002; 
    cache_valid = 0;

    #10;
    $finish;
end

initial begin
    $dumpfile("FETCH_tb.vcd");
    $dumpvars(0, FETCH_tb);
end
endmodule