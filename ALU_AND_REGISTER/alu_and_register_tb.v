module test ();
    
    reg [3:0] in;
    reg clk;
    reg [13:0] control;
    wire [3:0] out;

    register_and_alu t(.in(in),.clk(clk),.control(control),.out(out));

    initial begin
        clk = 0;
        forever #5 clk= ~clk;
    end

    initial begin
        in = 4'b1000;
        control = 14'b000_000_001_00000;
        #10;
        in = 4'b1010;
        control = 14'b000_000_010_00000; 
        #10;
        control = 14'b010_001_011_00010;
        #10 $finish;
    end

    initial begin
        $dumpfile("cpu_2_tb.vcd");
        $dumpvars(0,test);
    end

endmodule