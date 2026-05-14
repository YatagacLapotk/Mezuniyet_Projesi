`timescale 1ns / 1ps
`include "sabit_veriler.vh"

module SPI_master_tb();

    reg clk;
    reg reset;
    reg miso;
    reg [7:0] data_out;
    reg sclk;
    reg enable;
    reg sclk_enable;

    wire mosi;
    wire [7:0] data_in;
    wire data_ready;
    wire busy;
    wire ss;

    // Move reg declarations to module level
    reg [7:0] captured_mosi;

    // Instantiate the SPI_master module
    SPI_master uut (
        .clk(clk),
        .reset(reset),
        .mosi(mosi),
        .miso(miso),
        .data_out(data_out),
        .data_in(data_in),
        .data_ready(data_ready),
        .busy(busy),
        .sclk(sclk),
        .ss(ss),
        .enable(enable),
        .sclk_enable(sclk_enable)
    );

    // Clock generation (100MHz)
    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end

    // SCLK generation (simulated sclk from sclk_gen, ~115200 Hz)
    // 115200 Hz -> ~8680.5 ns period -> 4340 ns half-period
    initial begin
        sclk = 0;
        forever begin
            if (sclk_enable)
                #4340 sclk = ~sclk;
            else begin
                sclk = 0;
                #5;
            end
        end
    end

    // Task to simulate slave response and capture MOSI
    task simulate_slave_and_capture(input [7:0] from_slave);
        integer i;
        begin
            captured_mosi = 8'h00;
            // Wait for busy and SS low
            wait(busy == 1 && ss == 0);
            
            for (i = 7; i >= 0; i = i - 1) begin
                miso = from_slave[i];
                // Wait for posedge sclk to capture (master samples on posedge)
                @(posedge sclk);
                captured_mosi[i] = mosi;
                // Wait for negedge sclk (master shifts on negedge)
                @(negedge sclk);
            end
        end
    endtask

    initial begin
        // Initialize Inputs
        reset = 1;
        miso = 0;
        data_out = 0;
        enable = 0;
        sclk_enable = 0;
        captured_mosi = 0;
        
        #100;
        reset = 0;
        #100;

        // --- TEST 1: Normal Operation & Signal Checks ---
        $display("TEST 1: Normal Operation Starting...");
        data_out = 8'hA5; // 10100101
        enable = 1;
        sclk_enable = 1;
        
        // Check busy goes high
        #50; 
        if (busy !== 1) $display("Error: busy should be high during transmission");
        if (ss !== 0)   $display("Error: ss should be low during transmission");
        
        // Simulate slave
        simulate_slave_and_capture(8'h3C);
        
        // Wait for completion
        wait(data_ready == 1);
        if (busy !== 0) $display("Error: busy should be low after transmission");
        if (ss !== 1)   $display("Error: ss should be high after transmission");
        if (data_in !== 8'h3C) $display("Error: Received data mismatch. Got %h, expected 3C", data_in);
        if (captured_mosi !== 8'hA5) $display("Error: MOSI data mismatch. Got %h, expected A5", captured_mosi);
        
        enable = 0;
        sclk_enable = 0;
        $display("TEST 1: Normal Operation Finished.");

        #1000;

        // --- TEST 2: Reset during transmission ---
        $display("TEST 2: Reset during transmission...");
        data_out = 8'hFF;
        enable = 1;
        sclk_enable = 1;
        
        wait(busy == 1);
        #10000; // Wait for some bits to transfer
        $display("Triggering Asynchronous Reset...");
        reset = 1;
        #20;
        if (busy == 0 && ss == 1) 
            $display("TEST 2: Successfully reset mid-transmission");
        else
            $display("Error: Module did not reset correctly. busy=%b, ss=%b", busy, ss);
            
        reset = 0;
        enable = 0;
        sclk_enable = 0;
        #1000;

        // --- TEST 3: sclk_enable goes low during transmission ---
        $display("TEST 3: sclk_enable going low during transmission...");
        data_out = 8'hAA;
        enable = 1;
        sclk_enable = 1;
        
        wait(busy == 1);
        #10000;
        $display("De-asserting sclk_enable...");
        sclk_enable = 0;
        
        #100; // Should return to IDLE
        if (busy == 0 && ss == 1)
            $display("TEST 3: Successfully returned to IDLE on sclk_enable low");
        else
            $display("Error: Did not return to IDLE on sclk_enable low. busy=%b, ss=%b", busy, ss);
            
        enable = 0;
        #1000;

        // --- TEST 4: enable goes low during transmission (Should NOT stop) ---
        $display("TEST 4: enable going low during transmission (should complete)...");
        data_out = 8'h12;
        enable = 1;
        sclk_enable = 1;
        
        wait(busy == 1);
        #10000;
        $display("De-asserting enable...");
        enable = 0; 
        
        // Transfer should continue
        #20000;
        if (busy == 1)
            $display("TEST 4: Transfer continuing as expected even if enable is low");
        else
            $display("Error: Transfer stopped unexpectedly on enable low");
            
        wait(data_ready == 1);
        $display("TEST 4: Transfer completed successfully");
        
        sclk_enable = 0;
        #1000;

        $display("All modified tests completed.");
        $finish;
    end

    // Monitor
    initial begin
        $monitor("Time=%0t | state=%b | ss=%b | busy=%b | data_ready=%b | data_in=%h", 
                 $time, uut.state, ss, busy, data_ready, data_in);
    end

endmodule
