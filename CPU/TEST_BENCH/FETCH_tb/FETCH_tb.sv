`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
`timescale 1ns / 1ps

module FETCH_tb;

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
    wire [`DATA_WIDTH-1:0] pc_4_out;
    wire [`DATA_WIDTH-1:0] pc_out;

    FETCH uut (
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
        .pc_4_out(pc_4_out),
        .pc_out(pc_out)
    );

    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end

    initial begin
        $dumpfile("FETCH_tb.vcd");
        $dumpvars(0, FETCH_tb);

        // Test 1: Reset
        reset = 1;
        stallF = 0; stallD = 0; flushD = 0;
        exception = 0; pc_src = 0;
        exception_handler_address = 0;
        cache_input = 0;
        branch_target = 0;
        #20;
        reset = 0;
        #10;
        $display("Reset: PC=0x%08h (expect 0x00000000)", pc_out);
        $display("Reset: instr=0x%08h (expect 0x00000000)", instruction_out);

        // Test 2: Normal increment - load instruction first
        exception_handler_address = 32'h0000_0000;
        cache_input = 32'h0000_0013;
        exception = 1;
        @(posedge clk);
        @(posedge clk);
        exception = 0;
        @(posedge clk);
        $display("Normal: PC=0x%08h (expect 0x00000004)", pc_out);
        $display("Normal: instr=0x%08h (expect 0x00000013)", instruction_out);

        // Test 3: Branch
        branch_target = 32'h0000_0100;
        pc_src = 1;
        @(posedge clk);
        @(posedge clk);
        @(posedge clk);
        $display("Branch: PC=0x%08h (expect 0x00000100)", pc_out);
        pc_src = 0;

        // Test 4: Stall
        stallF = 1;
        @(posedge clk);
        @(posedge clk);
        $display("Stall: PC=0x%08h (expect 0x00000100)", pc_out);
        stallF = 0;

        #10;
        $finish;
    end

endmodule
