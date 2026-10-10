`timescale 1ns / 1ps

module SPI_tb();

    reg clk;
    reg reset;
    reg [7:0] data_out;
    reg enable;
    reg sclk_enable;
    reg miso;

    wire data_ready;
    wire busy;
    wire ss;
    wire mosi;
    wire [7:0] data_in;

    // Instantiate the top-level SPI module
    SPI uut (
        .clk(clk),
        .reset(reset),
        .data_out(data_out),
        .enable(enable),
        .sclk_enable(sclk_enable),
        .miso(miso),
        .data_ready(data_ready),
        .busy(busy),
        .ss(ss),
        .mosi(mosi),
        .data_in(data_in)
    );

    // Clock generation (100MHz)
    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end

    // Test variables
    reg [7:0] expected_data_in = 8'hA5; // 10100101
    reg [7:0] expected_data_out = 8'h5A; // 01011010
    reg [7:0] mosi_captured;
    integer i;

    // We need to monitor the generated sclk from the submodule for simulation synchronization
    wire internal_sclk = uut.sclk_w;

    initial begin
        // Initialize Inputs
        reset = 1;
        data_out = 0;
        enable = 0;
        sclk_enable = 0;
        miso = 0;
        mosi_captured = 0;

        // Wait 100 ns for global reset to finish
        #100;
        reset = 0;
        
        #100;
        
        $display("Starting Top-Level SPI Transmission...");
        data_out = expected_data_out;
        enable = 1;
        sclk_enable = 1;
        
        // Wait for busy to go high
        wait(busy == 1);
        
        // Simulate slave receiving MOSI and sending data back on MISO
        for (i = 7; i >= 0; i = i - 1) begin
            // Setup MISO before posedge
            miso = expected_data_in[i];
            
            // Wait for posedge of internal SCLK to capture MOSI
            wait(internal_sclk == 1);
            mosi_captured[i] = mosi;
            
            // Wait for negedge of internal SCLK to advance to next bit
            wait(internal_sclk == 0);
        end
        
        // Wait for transaction to complete
        wait(data_ready == 1);
        enable = 0;
        sclk_enable = 0;
        
        #1000;
        $display("Master Transmitted (MOSI). Expected: %h, Got: %h", expected_data_out, mosi_captured);
        $display("Master Received (data_in). Expected: %h, Got: %h", expected_data_in, data_in);
        
        if (data_in == expected_data_in && mosi_captured == expected_data_out)
            $display("Top-Level SPI TEST PASSED!");
        else
            $display("Top-Level SPI TEST FAILED!");
            
        $finish;
    end

endmodule
