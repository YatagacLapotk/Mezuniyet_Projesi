`include "Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"

module MDU_TB (
    // ports
);
    reg clk;
    reg[`DATA_WIDTH-1:0] s1;
    reg[`DATA_WIDTH-1:0] s2;
    reg[`FUNCT3_WIDTH-1:0] funct3;
    wire[`DATA_WIDTH-1:0] d3;

    MDU uut (
        .s1(s1),
        .s2(s2),
        .funct3(funct3),
        .d3(d3)
    );

    initial begin
        // Test MUL
        s1 = 32'd6;
        s2 = 32'd7;
        funct3 = 3'b000; // MUL
        #10;


        // Test DIV
        s1 = 32'd20;
        s2 = 32'd4;
        funct3 = 3'b100; // DIV
        #10;


        // Test REM
        s1 = 32'd20;
        s2 = 32'd6;
        funct3 = 3'b110; // REM
        #10;
        
        // Test MULH
        s1 = 32'd20;
        s2 = 32'd6;
        funct3 = 3'b001; // MULH
        #10;
        
        // Test MULH-2
        s1 = 32'd200000;
        s2 = 32'd60000;
        funct3 = 3'b001; // MULH
        #10;

        // Test MULH-3
        s1 = 32'd200000;
        s2 = 32'd60000;
        funct3 = 3'b000; // MULH
        #10;


        // Add more test cases as needed

        $finish;
    end

    initial begin
        forever #5 clk = ~clk;
    end
    initial begin
        $dumpfile("MDU_TB.vcd");
        $dumpvars(0, MDU_TB);
    end

endmodule