`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"

module FETCH_tb ();

reg clk;
reg reset;
reg stallF;
reg stallD;
reg flushD;
reg exception;
reg pc_src;
reg [`DATA_WIDTH-1:0] exception_handler_address;
reg [`DATA_WIDTH-1:0] cache_input;
reg [`DATA_WIDTH-1:0] branch_target;
wire [`DATA_WIDTH-1:0] instruction_out;
wire [`DATA_WIDTH-1:0] pc_out;

parameter CLK_PERIOD = 10;

always #(CLK_PERIOD/2) clk = ~clk;

FETCH fetch_inst (
    .clk(clk),
    .reset(reset),
    .stallF(stallF),
    .stallD(stallD),
    .flushD(flushD),
    .exception(exception),
    .pc_src(pc_src),
    .exception_handler_address(exception_handler_address),
    .cache_input(cache_input),
    .branch_target(branch_target),
    .instruction_out(instruction_out),
    .pc_out(pc_out)
);

initial begin
    clk       = 0;
    reset     = 1;
    stallF    = 0;
    stallD    = 0;
    flushD    = 0;
    exception = 0;
    pc_src    = 0;
    exception_handler_address = 32'h0;
    cache_input               = 32'h0;
    branch_target             = 32'h0;

    // hold reset
    @(posedge clk); #1;
    @(posedge clk); #1;
    reset = 0;

    // --- Test 1: normal PC increment ---
    // load 3 instructions into I_CACHE via exception path
    exception_handler_address = 32'd0;
    cache_input = 32'h00000013; // NOP
    exception = 1;
    @(posedge clk); #1;

    exception_handler_address = 32'd1;
    cache_input = 32'h00100093; // ADDI x1, x0, 1
    @(posedge clk); #1;

    exception_handler_address = 32'd2;
    cache_input = 32'h00200113; // ADDI x2, x0, 2
    @(posedge clk); #1;
    exception = 0;

    @(posedge clk); #1;
    @(posedge clk); #1;
    @(posedge clk); #1;

    // --- Test 2: stall ---
    stallF = 1;
    @(posedge clk); #1;
    @(posedge clk); #1;
    stallF = 0;

    @(posedge clk); #1;

    // --- Test 3: branch taken ---
    branch_target = 32'd0;
    pc_src = 1;
    @(posedge clk); #1;
    pc_src = 0;

    @(posedge clk); #1;
    @(posedge clk); #1;

    // --- Test 4: exception (load new instruction) ---
    exception_handler_address = 32'd5;
    cache_input = 32'hDEADBEEF;
    exception = 1;
    @(posedge clk); #1;
    exception = 0;

    @(posedge clk); #1;
    @(posedge clk); #1;

    // --- Test 5: flushD ---
    flushD = 1;
    @(posedge clk); #1;
    flushD = 0;

    @(posedge clk); #1;

    $finish;
end

initial begin
    $dumpfile("FETCH_tb.vcd");
    $dumpvars(0, FETCH_tb);
end

endmodule
