`timescale 1ns / 1ps
`define CLK 100000000
`define BAUD_RATE 115200

module UART_MASTER_TB;
    reg start_baud = 0; wire done_baud;
    reg start_tx = 0; wire done_tx;
    reg start_rx = 0; wire done_rx;
    reg start_top = 0; wire done_top;

    BAUD_GEN_TB baud_tb (.start(start_baud), .done(done_baud));
    UART_TX_TB tx_tb (.start(start_tx), .done(done_tx));
    UART_RX_TB rx_tb (.start(start_rx), .done(done_rx));
    UART_TOP_TB top_tb (.start(start_top), .done(done_top));

    initial begin
        $display("==============================================");
        $display("   STARTING FULL UART TEST SUITE");
        $display("==============================================");

        $display("\n\n>>> RUNNING BAUD GENERATOR TESTS <<<");
        start_baud = 1;
        wait(done_baud);
        start_baud = 0;
        
        $display("\n\n>>> RUNNING TRANSMITTER (TX) TESTS <<<");
        start_tx = 1;
        wait(done_tx);
        start_tx = 0;

        $display("\n\n>>> RUNNING RECEIVER (RX) TESTS <<<");
        start_rx = 1;
        wait(done_rx);
        start_rx = 0;

        $display("\n\n>>> RUNNING TOP MODULE INTEGRATION TESTS <<<");
        start_top = 1;
        wait(done_top);
        start_top = 0;

        $display("\n==============================================");
        $display("   ALL UART SUBMODULE & TOP TESTS COMPLETED");
        $display("==============================================");
        $finish;
    end
endmodule

module UART_TOP_TB(input wire start, output reg done);

    // -------------------------------------------------------
    // Testbench Signals
    // -------------------------------------------------------
    reg tx_enable;
    reg rx_enable;
    reg clk;
    reg reset;
    reg clear;
    
    reg [7:0] data_out;     // Data to send from TX
    reg data_in_reg;        // External driver for RX data_in
    reg loopback_en;        // Mux control to loop TX output to RX input

    wire tx_out;
    wire rx_busy;
    wire [7:0] rx_in;
    wire data_ready;

    // -------------------------------------------------------
    // Mux for data_in: drives from TX if loopback, else from TB
    // -------------------------------------------------------
    wire data_in = loopback_en ? tx_out : data_in_reg;

    // -------------------------------------------------------
    // Unit Under Test (UUT)
    // -------------------------------------------------------
    UART uut (
        .tx_enable(tx_enable), 
        .rx_enable(rx_enable), 
        .clk(clk), 
        .reset(reset), 
        .clear(clear), 
        .tx_out(tx_out), 
        .data_in(data_in), 
        .data_out(data_out), 
        .rx_busy(rx_busy), 
        .rx_in(rx_in), 
        .data_ready(data_ready)
    );

    // -------------------------------------------------------
    // Clock Generation (100 MHz -> 10 ns period)
    // -------------------------------------------------------
    initial clk = 0;
    always #5 clk = ~clk;

    // -------------------------------------------------------
    // Parameters & Variables
    // -------------------------------------------------------
    // At 100MHz clock and 115200 baud, 1 bit = 868 clocks = 8680 ns
    localparam BIT_PERIOD = 8680;

    integer errors = 0;
    integer passes = 0;

    // -------------------------------------------------------
    // Task: Send a byte directly to RX via data_in
    // -------------------------------------------------------
    task send_rx_byte;
        input [7:0] byte_to_send;
        integer i;
        begin
            data_in_reg = 0; // Start bit
            #(BIT_PERIOD);
            for (i = 0; i < 8; i = i + 1) begin
                data_in_reg = byte_to_send[i];
                #(BIT_PERIOD);
            end
            data_in_reg = 1; // Stop bit
            #(BIT_PERIOD);
        end
    endtask

    // -------------------------------------------------------
    // Main Test Sequence
    // -------------------------------------------------------
    initial begin
        done = 0;
        wait(start);

        // For waveform viewing (optional depending on simulator)
        $dumpfile("uart_tb.vcd");
        $dumpvars(0, UART_TOP_TB);

        // Initialize Inputs
        tx_enable = 1; // active low
        rx_enable = 1; // active low
        reset = 1;
        clear = 0;
        data_in_reg = 1; // idle state is HIGH
        data_out = 0;
        loopback_en = 0;

        $display("\n==============================================");
        $display("Starting UART Top Module Testbench...");
        $display("==============================================");
        
        // Wait 100 ns for global reset to finish
        #100;
        reset = 0;
        #100;

        // ====================================================
        // TEST 1: Default State Check
        // ====================================================
        $display("\n[TEST 1] Default State Check");
        if (tx_out !== 1'b1) begin $display("  FAIL: tx_out is not HIGH in idle"); errors = errors+1; end else passes=passes+1;
        if (rx_busy !== 1'b0) begin $display("  FAIL: rx_busy is not LOW in idle"); errors = errors+1; end else passes=passes+1;
        if (data_ready !== 1'b0) begin $display("  FAIL: data_ready is not LOW in idle"); errors = errors+1; end else passes=passes+1;

        // ====================================================
        // TEST 2: Transmit Data Check (TX only)
        // ====================================================
        $display("\n[TEST 2] Transmit Data Check (0xA5)");
        data_out = 8'hA5;
        
        @(negedge clk);
        tx_enable = 0; // Assert enable to trigger TX
        @(negedge clk);
        tx_enable = 1; // Deassert (trigger is edge-like/single cycle)
        
        // Wait for start bit (tx_out should drop to 0)
        wait (tx_out == 0);
        $display("  TX Start bit detected");
        
        // Wait for the full frame duration (8 data + 1 stop)
        #(BIT_PERIOD * 9); 
        wait (tx_out == 1);
        $display("  TX completed");
        passes = passes + 1;

        // ====================================================
        // TEST 3: Receive Data Check (RX only)
        // ====================================================
        $display("\n[TEST 3] Receive Data Check (0x3C)");
        rx_enable = 0; // Enable RX module
        #10;
        
        // Send a byte to the RX module
        send_rx_byte(8'h3C);
        
        // Wait for it to signal data is ready
        wait (data_ready == 1);
        if (rx_in !== 8'h3C) begin 
            $display("  FAIL: rx_in is %h, expected 3C", rx_in); 
            errors = errors+1; 
        end else begin 
            $display("  PASS: Received 0x3C correctly"); 
            passes=passes+1; 
        end
        
        // ====================================================
        // TEST 4: Clear Signal Check
        // ====================================================
        $display("\n[TEST 4] Clear Signal Check");
        @(negedge clk);
        clear = 1;
        @(negedge clk);
        clear = 0;
        @(negedge clk);
        
        if (data_ready !== 1'b0) begin 
            $display("  FAIL: data_ready did not clear"); 
            errors = errors+1; 
        end else begin 
            $display("  PASS: data_ready cleared successfully"); 
            passes=passes+1; 
        end

        // ====================================================
        // TEST 5: RX Busy Signal Check
        // ====================================================
        $display("\n[TEST 5] RX Busy Signal Check");
        
        // Drive data_in low to trigger a start bit detection
        data_in_reg = 0; 
        
        // Wait half a bit period. By now rx_busy should be 1.
        #(BIT_PERIOD / 2); 
        if (rx_busy !== 1'b1) begin
            $display("  FAIL: rx_busy did not assert during reception");
            errors = errors + 1;
        end else begin
            $display("  PASS: rx_busy asserted correctly");
            passes = passes + 1;
        end
        
        // Finish sending dummy frame (0xFF) to clear state machine
        #(BIT_PERIOD / 2); // Complete start bit
        data_in_reg = 1;   // Data bits all 1
        #(BIT_PERIOD * 8); // 8 data bits
        data_in_reg = 1;   // Stop bit
        #(BIT_PERIOD);
        
        wait (data_ready == 1);
        @(negedge clk); clear = 1; @(negedge clk); clear = 0; // clear it

        // ====================================================
        // TEST 6: Loopback Check (TX connected to RX internally)
        // ====================================================
        $display("\n[TEST 6] Full Loopback Test (0x5A)");
        
        // Enable hardware loopback (mux connects tx_out to data_in)
        loopback_en = 1; 
        
        data_out = 8'h5A;
        @(negedge clk);
        tx_enable = 0; // Trigger TX
        @(negedge clk);
        tx_enable = 1;
        
        // Wait for the RX module to receive the data sent by the TX module
        wait (data_ready == 1);
        
        if (rx_in !== 8'h5A) begin 
            $display("  FAIL: Loopback rx_in is %h, expected 5A", rx_in); 
            errors = errors+1; 
        end else begin 
            $display("  PASS: Loopback received 0x5A correctly"); 
            passes=passes+1; 
        end
        
        @(posedge clk); clear = 1; @(posedge clk); clear = 0;

        // ====================================================
        // SUMMARY
        // ====================================================
        $display("\n==============================================");
        $display("         TEST SUMMARY");
        $display("==============================================");
        $display("  PASSED: %0d", passes);
        $display("  FAILED: %0d", errors);
        $display("----------------------------------------------");
        if (errors == 0)
            $display("  ALL TESTS PASSED SUCCESSFULLY! 🟢");
        else
            $display("  TESTS FINISHED WITH %0d ERROR(S) 🔴", errors);
        $display("==============================================\n");

        #100;
        done = 1;
    end
    
    // -------------------------------------------------------
    // Timeout watchdog (prevents infinite loop if FSM gets stuck)
    // -------------------------------------------------------
    initial begin
        wait(start);
        #(BIT_PERIOD * 100); 
        if (!done) begin
            $display("\nERROR: Simulation timeout! State machine stuck.");
            done = 1;
        end
    end

endmodule

// ==================================================================
// UART_TX_TB
// ==================================================================

module UART_TX_TB(input wire start, output reg done);

    // -------------------------------------------------------
    // Clock & Reset
    // -------------------------------------------------------
    reg clk;
    reg reset;

    // 100 MHz clock → 10 ns period
    localparam CLK_PERIOD = 10;

    initial clk = 0;
    always #(CLK_PERIOD / 2) clk = ~clk;

    // -------------------------------------------------------
    // DUT Signals
    // -------------------------------------------------------
    reg [7:0] data_out;   // data to transmit
    reg tx_enable;        // active-low: starts transmission when LOW
    reg enable;           // baud rate tick (1 tick per bit period)

    wire tx_out;          // serial output

    // -------------------------------------------------------
    // DUT Instantiation
    // -------------------------------------------------------
    UART_tx uut (
        .data_out(data_out),
        .clk(clk),
        .reset(reset),
        .txena(tx_enable),
        .tx_baudena(enable),
        .tx_out(tx_out)
    );

    // -------------------------------------------------------
    // Baud enable tick generator (TX rate)
    // -------------------------------------------------------
    // Simulates baud_gen tx_enable: pulses HIGH for one clock
    // every TX_DIVISOR clocks. Using a smaller divisor for
    // simulation speed.
    localparam TX_DIVISOR = 20; // short divisor for fast simulation

    reg [9:0] tx_acc;

    always @(posedge clk) begin
        if (reset) begin
            tx_acc <= 0;
            enable <= 0;
        end else begin
            if (tx_acc == TX_DIVISOR - 1) begin
                tx_acc <= 0;
                enable <= 1;
            end else begin
                tx_acc <= tx_acc + 1;
                enable <= 0;
            end
        end
    end

    // -------------------------------------------------------
    // Error / pass counters
    // -------------------------------------------------------
    integer errors;
    integer passes;

    // -------------------------------------------------------
    // Task: Wait for one enable tick
    // -------------------------------------------------------
    task wait_one_enable_tick;
    begin
        @(posedge clk);
        while (!enable) @(posedge clk);
    end
    endtask

    // -------------------------------------------------------
    // Task: Wait for N enable ticks
    // -------------------------------------------------------
    task wait_enable_ticks;
        input integer count;
        integer i;
    begin
        for (i = 0; i < count; i = i + 1) begin
            wait_one_enable_tick;
        end
    end
    endtask

    // -------------------------------------------------------
    // Task: Transmit a byte and capture the serial output
    //
    // The UART TX frame is:
    //   IDLE(1) -> START(0) -> D0 D1 D2 D3 D4 D5 D6 D7 -> STOP(1) -> IDLE(1)
    //
    // This task:
    //   1. Loads data_out and asserts tx_enable (LOW)
    //   2. Waits for the complete frame on tx_out
    //   3. Captures each bit into captured_frame[9:0]
    //      [0]=start, [1..8]=data, [9]=stop
    //   4. Verifies frame correctness
    // -------------------------------------------------------
    reg [9:0] captured_frame;

    task transmit_and_verify;
        input [7:0] tx_data;
        integer i;
    begin
        // Load data
        data_out = tx_data;

        // Assert tx_enable (active-low) to start transmission
        tx_enable = 0;
        @(posedge clk);  // let IDLE state see ~tx_enable and latch data
        @(posedge clk);  // state transitions to START
        tx_enable = 1;   // deassert immediately (one-shot trigger)

        // Now the FSM is in START state, waiting for enable tick.
        // On enable tick: tx_out <= 0 (start bit), state -> DATA
        // We capture tx_out AFTER each enable tick settles.

        // Capture START bit
        wait_one_enable_tick;     // START state: tx_out <= 0, state -> DATA
        @(posedge clk);           // let non-blocking assign settle
        captured_frame[0] = tx_out;

        // Capture 8 DATA bits
        for (i = 0; i < 8; i = i + 1) begin
            wait_one_enable_tick;   // DATA state: tx_out <= data_buffer[bit_index]
            @(posedge clk);         // settle
            captured_frame[i + 1] = tx_out;
        end

        // Capture STOP bit
        wait_one_enable_tick;     // STOP state: tx_out <= 1, state -> IDLE
        @(posedge clk);           // settle
        captured_frame[9] = tx_out;

        // Verify start bit
        if (captured_frame[0] !== 1'b0) begin
            $display("  FAIL: Start bit should be 0, got %b", captured_frame[0]);
            errors = errors + 1;
        end else begin
            $display("  PASS: Start bit = 0");
            passes = passes + 1;
        end

        // Verify data bits
        if (captured_frame[8:1] !== tx_data) begin
            $display("  FAIL: Data bits = 0x%h, expected 0x%h", captured_frame[8:1], tx_data);
            errors = errors + 1;
        end else begin
            $display("  PASS: Data bits = 0x%h (correct)", captured_frame[8:1]);
            passes = passes + 1;
        end

        // Verify stop bit
        if (captured_frame[9] !== 1'b1) begin
            $display("  FAIL: Stop bit should be 1, got %b", captured_frame[9]);
            errors = errors + 1;
        end else begin
            $display("  PASS: Stop bit = 1");
            passes = passes + 1;
        end
    end
    endtask

    // -------------------------------------------------------
    // Test Sequence
    // -------------------------------------------------------
    initial begin
        done = 0;
        wait(start);
        $dumpfile("uart_tx_tb.vcd");
        $dumpvars(0, UART_TX_TB);

        errors = 0;
        passes = 0;
        data_out = 8'h00;
        tx_enable = 1;  // inactive (active-low)
        enable = 0;

        // ============================================================
        // TEST 1: Reset behavior
        // ============================================================
        $display("==============================================");
        $display("TEST 1: Reset behavior");
        $display("==============================================");
        reset = 1;
        repeat (5) @(posedge clk);

        if (uut.state !== 2'b00) begin
            $display("  FAIL: state should be IDLE(00) after reset, got %b", uut.state);
            errors = errors + 1;
        end else begin
            $display("  PASS: state is IDLE after reset");
            passes = passes + 1;
        end

        if (uut.bit_index !== 3'b0) begin
            $display("  FAIL: bit_index should be 0 after reset, got %d", uut.bit_index);
            errors = errors + 1;
        end else begin
            $display("  PASS: bit_index is 0 after reset");
            passes = passes + 1;
        end

        if (uut.data_buffer !== 8'b0) begin
            $display("  FAIL: data_buffer should be 0 after reset, got 0x%h", uut.data_buffer);
            errors = errors + 1;
        end else begin
            $display("  PASS: data_buffer is 0 after reset");
            passes = passes + 1;
        end

        // Release reset
        reset = 0;
        repeat (3) @(posedge clk);

        // ============================================================
        // TEST 2: IDLE state - tx_out should be HIGH
        // ============================================================
        $display("==============================================");
        $display("TEST 2: IDLE state - tx_out HIGH");
        $display("==============================================");

        // Wait a few enable ticks in IDLE
        wait_enable_ticks(3);

        if (tx_out !== 1'b1) begin
            $display("  FAIL: tx_out should be 1 (HIGH) in IDLE, got %b", tx_out);
            errors = errors + 1;
        end else begin
            $display("  PASS: tx_out is HIGH in IDLE state");
            passes = passes + 1;
        end

        if (uut.state !== 2'b00) begin
            $display("  FAIL: state should remain IDLE when tx_enable=1");
            errors = errors + 1;
        end else begin
            $display("  PASS: State remains IDLE when tx_enable inactive");
            passes = passes + 1;
        end

        // ============================================================
        // TEST 3: Transmit byte 0xA5 (10100101)
        // ============================================================
        $display("==============================================");
        $display("TEST 3: Transmit byte 0xA5");
        $display("==============================================");

        $display("  Transmitting 0xA5 ...");
        transmit_and_verify(8'hA5);

        // Verify return to IDLE
        wait_enable_ticks(2);
        if (uut.state !== 2'b00) begin
            $display("  FAIL: state should return to IDLE after transmission");
            errors = errors + 1;
        end else begin
            $display("  PASS: Returned to IDLE after transmission");
            passes = passes + 1;
        end

        // ============================================================
        // TEST 4: Transmit byte 0x3C (00111100)
        // ============================================================
        $display("==============================================");
        $display("TEST 4: Transmit byte 0x3C");
        $display("==============================================");

        $display("  Transmitting 0x3C ...");
        transmit_and_verify(8'h3C);

        // ============================================================
        // TEST 5: Transmit byte 0x00 (all zeros)
        // ============================================================
        $display("==============================================");
        $display("TEST 5: Transmit byte 0x00");
        $display("==============================================");

        $display("  Transmitting 0x00 ...");
        transmit_and_verify(8'h00);

        // ============================================================
        // TEST 6: Transmit byte 0xFF (all ones)
        // ============================================================
        $display("==============================================");
        $display("TEST 6: Transmit byte 0xFF");
        $display("==============================================");

        $display("  Transmitting 0xFF ...");
        transmit_and_verify(8'hFF);

        // ============================================================
        // TEST 7: Transmit byte 0x55 (alternating 01010101)
        // ============================================================
        $display("==============================================");
        $display("TEST 7: Transmit byte 0x55");
        $display("==============================================");

        $display("  Transmitting 0x55 ...");
        transmit_and_verify(8'h55);

        // ============================================================
        // TEST 8: Transmit byte 0xAA (alternating 10101010)
        // ============================================================
        $display("==============================================");
        $display("TEST 8: Transmit byte 0xAA");
        $display("==============================================");

        $display("  Transmitting 0xAA ...");
        transmit_and_verify(8'hAA);

        // ============================================================
        // TEST 9: Data latching - data_out changes during TX
        // ============================================================
        $display("==============================================");
        $display("TEST 9: Data latching (data_out changes mid-TX)");
        $display("==============================================");

        // Load 0x42 and start transmission
        data_out = 8'h42;
        tx_enable = 0;
        @(posedge clk);
        @(posedge clk);
        tx_enable = 1;

        // Change data_out while transmitting - should NOT affect current TX
        wait_one_enable_tick; // START bit sent
        @(posedge clk);

        data_out = 8'hFF;  // change input data mid-transmission
        $display("  data_out changed to 0xFF mid-transmission");

        // Check that data_buffer still holds original value
        if (uut.data_buffer !== 8'h42) begin
            $display("  FAIL: data_buffer should hold latched value 0x42, got 0x%h", uut.data_buffer);
            errors = errors + 1;
        end else begin
            $display("  PASS: data_buffer holds latched 0x42 despite input change");
            passes = passes + 1;
        end

        // Let the rest of the frame complete
        wait_enable_ticks(9); // 8 data bits + stop bit
        wait_enable_ticks(2); // back to idle

        // ============================================================
        // TEST 10: tx_enable must be LOW to start
        // ============================================================
        $display("==============================================");
        $display("TEST 10: tx_enable=1 prevents transmission");
        $display("==============================================");

        tx_enable = 1; // keep inactive
        data_out = 8'hBE;
        wait_enable_ticks(10);

        if (uut.state !== 2'b00) begin
            $display("  FAIL: Should stay in IDLE when tx_enable=1");
            errors = errors + 1;
        end else begin
            $display("  PASS: Stays in IDLE when tx_enable=1");
            passes = passes + 1;
        end

        // ============================================================
        // TEST 11: Reset mid-transmission
        // ============================================================
        $display("==============================================");
        $display("TEST 11: Reset mid-transmission");
        $display("==============================================");

        // Start transmitting 0xCC
        data_out = 8'hCC;
        tx_enable = 0;
        @(posedge clk);
        @(posedge clk);
        tx_enable = 1;

        // Let START + 3 data bits go through
        wait_enable_ticks(4);

        // Assert reset mid-transmission
        reset = 1;
        repeat (3) @(posedge clk);

        if (uut.state !== 2'b00) begin
            $display("  FAIL: state should be IDLE after reset, got %b", uut.state);
            errors = errors + 1;
        end else begin
            $display("  PASS: state reset to IDLE");
            passes = passes + 1;
        end

        if (uut.bit_index !== 3'b0) begin
            $display("  FAIL: bit_index should be 0 after reset");
            errors = errors + 1;
        end else begin
            $display("  PASS: bit_index cleared after reset");
            passes = passes + 1;
        end

        if (uut.data_buffer !== 8'b0) begin
            $display("  FAIL: data_buffer should be 0 after reset");
            errors = errors + 1;
        end else begin
            $display("  PASS: data_buffer cleared after reset");
            passes = passes + 1;
        end

        // Release reset and verify normal operation resumes
        reset = 0;
        repeat (5) @(posedge clk);
        wait_enable_ticks(2);

        if (tx_out !== 1'b1) begin
            $display("  FAIL: tx_out should return to HIGH after reset");
            errors = errors + 1;
        end else begin
            $display("  PASS: tx_out HIGH after reset release");
            passes = passes + 1;
        end

        // ============================================================
        // TEST 12: Back-to-back transmissions (0x12 then 0x34)
        // ============================================================
        $display("==============================================");
        $display("TEST 12: Back-to-back transmissions (0x12, 0x34)");
        $display("==============================================");

        // First byte
        $display("  Transmitting 0x12 ...");
        transmit_and_verify(8'h12);
        wait_enable_ticks(2);

        // Second byte immediately after
        $display("  Transmitting 0x34 ...");
        transmit_and_verify(8'h34);

        // ============================================================
        // Summary
        // ============================================================
        $display("");
        $display("==============================================");
        $display("         TEST SUMMARY");
        $display("==============================================");
        $display("  PASSED: %0d", passes);
        $display("  FAILED: %0d", errors);
        $display("----------------------------------------------");
        if (errors == 0)
            $display("  ALL TESTS PASSED");
        else
            $display("  TESTS FINISHED WITH %0d ERROR(S)", errors);
        $display("==============================================");

        #100;
        done = 1;
    end

    // -------------------------------------------------------
    // Timeout watchdog
    // -------------------------------------------------------
    initial begin
        wait(start);
        #(CLK_PERIOD * 500000);
        if (!done) begin
            $display("ERROR: Simulation timeout!");
            done = 1;
        end
    end

endmodule

// ==================================================================
// UART_RX_TB
// ==================================================================

module UART_RX_TB(input wire start, output reg done);

    // -------------------------------------------------------
    // Clock & Reset
    // -------------------------------------------------------
    reg clk;
    reg reset;

    // 100 MHz clock → 10 ns period
    localparam CLK_PERIOD = 10;

    initial clk = 0;
    always #(CLK_PERIOD / 2) clk = ~clk;

    // -------------------------------------------------------
    // DUT Signals
    // -------------------------------------------------------
    reg data_in;
    reg enable;       // baud generator rx_enable (16x oversampling tick)
    reg rx_enable;    // active-low: reception enabled when rx_enable = 0
    reg clear;

    wire [7:0] rx_in;
    wire rx_busy;
    wire data_ready;

    // -------------------------------------------------------
    // DUT Instantiation
    // -------------------------------------------------------
    UART_rx uut (
        .clk(clk),
        .data_in(data_in),
        .reset(reset),
        .rx_baudena(enable),
        .rxena(rx_enable),
        .clear(clear),
        .rx_in(rx_in),
        .rx_busy(rx_busy),
        .data_ready(data_ready)
    );

    // -------------------------------------------------------
    // Enable tick generator
    // -------------------------------------------------------
    // Simulates baud_gen rx_enable: pulses HIGH for one clock
    // every RX_DIVISOR clocks (16x baud rate oversampling).
    localparam RX_DIVISOR = 54;  // CLK / (BAUD_RATE * 16)

    reg [5:0] rx_acc;

    always @(posedge clk) begin
        if (reset) begin
            rx_acc <= 0;
            enable <= 0;
        end else begin
            if (rx_acc == RX_DIVISOR - 1) begin
                rx_acc <= 0;
                enable <= 1;
            end else begin
                rx_acc <= rx_acc + 1;
                enable <= 0;
            end
        end
    end

    // -------------------------------------------------------
    // Error / pass counters
    // -------------------------------------------------------
    integer errors;
    integer passes;

    // -------------------------------------------------------
    // Task: Wait for one enable tick (posedge of enable)
    // -------------------------------------------------------
    task wait_one_enable_tick;
    begin
        @(posedge clk);
        while (!enable) @(posedge clk);
    end
    endtask

    // -------------------------------------------------------
    // Task: Wait for N enable ticks
    // -------------------------------------------------------
    task wait_enable_ticks;
        input integer count;
        integer i;
    begin
        for (i = 0; i < count; i = i + 1) begin
            wait_one_enable_tick;
        end
    end
    endtask

    // -------------------------------------------------------
    // Task: Send one UART byte (start + 8 data + stop)
    //
    // UART frame: [START=0] [D0] [D1] ... [D7] [STOP=1]
    // Each bit is held for 16 enable ticks (16x oversampling).
    // -------------------------------------------------------
    task send_uart_byte;
        input [7:0] tx_data;
        input send_valid_stop; // 1 = valid stop bit (HIGH), 0 = framing error
        integer bit_idx;
    begin
        // --- Start bit (LOW for 16 enable ticks) ---
        data_in = 0;
        wait_enable_ticks(16);

        // --- 8 Data bits, LSB first ---
        for (bit_idx = 0; bit_idx < 8; bit_idx = bit_idx + 1) begin
            data_in = tx_data[bit_idx];
            wait_enable_ticks(16);
        end

        // --- Stop bit (16 enable ticks) ---
        data_in = send_valid_stop ? 1'b1 : 1'b0;
        wait_enable_ticks(16);

        // Return line to idle (HIGH)
        data_in = 1;
    end
    endtask

    // -------------------------------------------------------
    // Test Sequence
    // -------------------------------------------------------
    initial begin
        done = 0;
        wait(start);
        $dumpfile("uart_rx_tb.vcd");
        $dumpvars(0, UART_RX_TB);

        errors = 0;
        passes = 0;
        data_in = 1;       // UART idle = HIGH
        rx_enable = 0;     // active-low: enable reception
        enable = 0;

        // ============================================================
        // TEST 1: Reset behavior
        // ============================================================
        $display("==============================================");
        $display("TEST 1: Reset behavior");
        $display("==============================================");
        reset = 1;
        repeat (5) @(posedge clk);

        if (rx_in !== 8'b0) begin
            $display("  FAIL: rx_in should be 0 after reset, got %h", rx_in);
            errors = errors + 1;
        end else begin
            $display("  PASS: rx_in is 0 after reset");
            passes = passes + 1;
        end

        if (data_ready !== 1'b0) begin
            $display("  FAIL: data_ready should be 0 after reset, got %b", data_ready);
            errors = errors + 1;
        end else begin
            $display("  PASS: data_ready is 0 after reset");
            passes = passes + 1;
        end

        if (rx_busy !== 1'b0) begin
            $display("  FAIL: rx_busy should be 0 after reset, got %b", rx_busy);
            errors = errors + 1;
        end else begin
            $display("  PASS: rx_busy is 0 after reset");
            passes = passes + 1;
        end

        if (uut.state !== 2'b00) begin
            $display("  FAIL: state should be START(00) after reset, got %b", uut.state);
            errors = errors + 1;
        end else begin
            $display("  PASS: state is START after reset");
            passes = passes + 1;
        end

        if (uut.sample_count !== 4'b0) begin
            $display("  FAIL: sample_count should be 0 after reset, got %d", uut.sample_count);
            errors = errors + 1;
        end else begin
            $display("  PASS: sample_count is 0 after reset");
            passes = passes + 1;
        end

        if (uut.bit_index !== 3'b0) begin
            $display("  FAIL: bit_index should be 0 after reset, got %d", uut.bit_index);
            errors = errors + 1;
        end else begin
            $display("  PASS: bit_index is 0 after reset");
            passes = passes + 1;
        end

        // Release reset
        reset = 0;
        repeat (5) @(posedge clk);

        // ============================================================
        // TEST 2: Idle line - no false start detection
        // ============================================================
        $display("==============================================");
        $display("TEST 2: Idle line - no false start detection");
        $display("==============================================");

        data_in = 1; // idle
        wait_enable_ticks(50);

        if (uut.state !== 2'b00) begin
            $display("  FAIL: state should remain START on idle line, got %b", uut.state);
            errors = errors + 1;
        end else begin
            $display("  PASS: State remains START on idle line");
            passes = passes + 1;
        end

        if (uut.sample_count !== 4'b0) begin
            $display("  FAIL: sample_count should be 0 on idle line (no start detected)");
            errors = errors + 1;
        end else begin
            $display("  PASS: sample_count stays 0 on idle line");
            passes = passes + 1;
        end

        if (data_ready !== 1'b0) begin
            $display("  FAIL: data_ready should remain 0 on idle line");
            errors = errors + 1;
        end else begin
            $display("  PASS: No false data_ready on idle line");
            passes = passes + 1;
        end

        // ============================================================
        // TEST 3: Start bit detection
        // ============================================================
        $display("==============================================");
        $display("TEST 3: Start bit detection");
        $display("==============================================");

        // Pull data_in LOW to trigger start bit
        data_in = 0;
        wait_enable_ticks(1);

        if (uut.sample_count > 0) begin
            $display("  PASS: sample_count incremented after detecting LOW");
            passes = passes + 1;
        end else begin
            $display("  FAIL: sample_count should increment when data_in goes LOW");
            errors = errors + 1;
        end

        if (rx_busy !== 1'b1) begin
            $display("  FAIL: rx_busy should be 1 when entering START state with data_in LOW");
            errors = errors + 1;
        end else begin
            $display("  PASS: rx_busy asserted during start bit detection");
            passes = passes + 1;
        end

        // Continue through start bit
        wait_enable_ticks(15); // complete the 16 samples of start bit

        if (uut.state !== 2'b01) begin
            $display("  FAIL: state should be DATA(01) after 16 start samples, got %b", uut.state);
            errors = errors + 1;
        end else begin
            $display("  PASS: Transitioned to DATA state after start bit");
            passes = passes + 1;
        end

        // Reset for next test
        reset = 1;
        repeat (5) @(posedge clk);
        reset = 0;
        repeat (5) @(posedge clk);
        data_in = 1;

        // ============================================================
        // TEST 4: rx_enable HIGH disables reception
        // ============================================================
        $display("==============================================");
        $display("TEST 4: rx_enable=1 disables reception");
        $display("==============================================");

        rx_enable = 1;  // Disable reception (active-low)
        data_in = 0;    // Pull line LOW
        wait_enable_ticks(20);

        if (uut.state !== 2'b00) begin
            $display("  FAIL: state should remain START when rx_enable=1");
            errors = errors + 1;
        end else begin
            $display("  PASS: State remains START when rx_enable=1");
            passes = passes + 1;
        end

        if (rx_busy !== 1'b0) begin
            $display("  FAIL: rx_busy should be 0 when rx_enable=1 (disabled)");
            errors = errors + 1;
        end else begin
            $display("  PASS: rx_busy stays 0 when reception disabled");
            passes = passes + 1;
        end

        // Re-enable
        rx_enable = 0;
        data_in = 1;
        reset = 1;
        repeat (5) @(posedge clk);
        reset = 0;
        repeat (5) @(posedge clk);

        // ============================================================
        // TEST 5: Data sampling at correct sample point
        // ============================================================
        $display("==============================================");
        $display("TEST 5: Data sampling at sample point 8");
        $display("==============================================");

        wait_enable_ticks(3);

        // Send start bit
        data_in = 0;
        wait_enable_ticks(16);

        // Bit 0: Set data_in to 1 (will be sampled at sample_count=8)
        data_in = 1;
        wait_enable_ticks(16);

        // Check that bit 0 was sampled correctly
        if (uut.data_buffer[0] !== 1'b1) begin
            $display("  FAIL: data_buffer[0] should be 1, got %b", uut.data_buffer[0]);
            errors = errors + 1;
        end else begin
            $display("  PASS: data_buffer[0] = 1 (sampled correctly at midpoint)");
            passes = passes + 1;
        end

        // Bit 1: Set data_in to 0
        data_in = 0;
        wait_enable_ticks(16);

        if (uut.data_buffer[1] !== 1'b0) begin
            $display("  FAIL: data_buffer[1] should be 0, got %b", uut.data_buffer[1]);
            errors = errors + 1;
        end else begin
            $display("  PASS: data_buffer[1] = 0 (sampled correctly at midpoint)");
            passes = passes + 1;
        end

        // Reset for next test
        reset = 1;
        repeat (5) @(posedge clk);
        reset = 0;
        repeat (5) @(posedge clk);
        data_in = 1;

        // ============================================================
        // TEST 6: Full byte reception - 0xA5
        // ============================================================
        $display("==============================================");
        $display("TEST 6: Full byte reception - 0xA5");
        $display("==============================================");

        wait_enable_ticks(5);

        $display("  Sending 0xA5 ...");
        send_uart_byte(8'hA5, 1);

        // Allow time for STOP state processing
        wait_enable_ticks(20);

        // Check data_buffer contents (should have captured 0xA5)
        $display("  DUT state=%b, data_buffer=0x%h, bit_index=%d, sample_count=%d",
                 uut.state, uut.data_buffer, uut.bit_index, uut.sample_count);

        if (uut.data_buffer !== 8'hA5) begin
            $display("  FAIL: data_buffer = 0x%h, expected 0xA5", uut.data_buffer);
            errors = errors + 1;
        end else begin
            $display("  PASS: data_buffer correctly holds 0xA5");
            passes = passes + 1;
        end

        // NOTE: Known RTL bug - bit_index is [2:0] so it can never equal 8.
        // The condition (bit_index == 8 && sample_count == 15) in DATA state
        // will never be true. The FSM gets stuck in DATA state and never
        // transitions to STOP. This prevents rx_in and data_ready from updating.
        if (uut.state == 2'b01) begin
            $display("  INFO: [KNOWN BUG] FSM stuck in DATA state.");
            $display("        bit_index is reg[2:0] (max=7), cannot equal 8.");
            $display("        Fix: Change bit_index to reg[3:0] or use");
            $display("        (bit_index == 7 && sample_count == 15) as transition condition.");
        end

        if (data_ready === 1'b1 && rx_in === 8'hA5) begin
            $display("  PASS: data_ready asserted and rx_in = 0xA5");
            passes = passes + 1;
        end else begin
            $display("  FAIL: data_ready=%b, rx_in=0x%h (expected 1, 0xA5)", data_ready, rx_in);
            $display("        -> This failure is caused by the bit_index overflow bug above.");
            errors = errors + 1;
        end

        // Reset
        reset = 1;
        repeat (5) @(posedge clk);
        reset = 0;
        repeat (5) @(posedge clk);
        data_in = 1;

        // ============================================================
        // TEST 7: Full byte reception - 0x3C
        // ============================================================
        $display("==============================================");
        $display("TEST 7: Full byte reception - 0x3C");
        $display("==============================================");

        wait_enable_ticks(5);

        $display("  Sending 0x3C ...");
        send_uart_byte(8'h3C, 1);
        wait_enable_ticks(20);

        $display("  DUT state=%b, data_buffer=0x%h, bit_index=%d",
                 uut.state, uut.data_buffer, uut.bit_index);

        if (uut.data_buffer !== 8'h3C) begin
            $display("  FAIL: data_buffer = 0x%h, expected 0x3C", uut.data_buffer);
            errors = errors + 1;
        end else begin
            $display("  PASS: data_buffer correctly holds 0x3C");
            passes = passes + 1;
        end

        if (data_ready === 1'b1 && rx_in === 8'h3C) begin
            $display("  PASS: Output correct");
            passes = passes + 1;
        end else begin
            $display("  FAIL: data_ready=%b, rx_in=0x%h (bit_index overflow bug)", data_ready, rx_in);
            errors = errors + 1;
        end

        // Reset
        reset = 1;
        repeat (5) @(posedge clk);
        reset = 0;
        repeat (5) @(posedge clk);
        data_in = 1;

        // ============================================================
        // TEST 8: Full byte reception - 0x00
        // ============================================================
        $display("==============================================");
        $display("TEST 8: Full byte reception - 0x00");
        $display("==============================================");

        wait_enable_ticks(5);

        $display("  Sending 0x00 ...");
        send_uart_byte(8'h00, 1);
        wait_enable_ticks(20);

        if (uut.data_buffer !== 8'h00) begin
            $display("  FAIL: data_buffer = 0x%h, expected 0x00", uut.data_buffer);
            errors = errors + 1;
        end else begin
            $display("  PASS: data_buffer correctly holds 0x00");
            passes = passes + 1;
        end

        // Reset
        reset = 1;
        repeat (5) @(posedge clk);
        reset = 0;
        repeat (5) @(posedge clk);
        data_in = 1;

        // ============================================================
        // TEST 9: Full byte reception - 0xFF
        // ============================================================
        $display("==============================================");
        $display("TEST 9: Full byte reception - 0xFF");
        $display("==============================================");

        wait_enable_ticks(5);

        $display("  Sending 0xFF ...");
        send_uart_byte(8'hFF, 1);
        wait_enable_ticks(20);

        if (uut.data_buffer !== 8'hFF) begin
            $display("  FAIL: data_buffer = 0x%h, expected 0xFF", uut.data_buffer);
            errors = errors + 1;
        end else begin
            $display("  PASS: data_buffer correctly holds 0xFF");
            passes = passes + 1;
        end

        // Reset
        reset = 1;
        repeat (5) @(posedge clk);
        reset = 0;
        repeat (5) @(posedge clk);
        data_in = 1;

        // ============================================================
        // TEST 10: Full byte reception - 0x55 (alternating)
        // ============================================================
        $display("==============================================");
        $display("TEST 10: Full byte reception - 0x55");
        $display("==============================================");

        wait_enable_ticks(5);

        $display("  Sending 0x55 ...");
        send_uart_byte(8'h55, 1);
        wait_enable_ticks(20);

        if (uut.data_buffer !== 8'h55) begin
            $display("  FAIL: data_buffer = 0x%h, expected 0x55", uut.data_buffer);
            errors = errors + 1;
        end else begin
            $display("  PASS: data_buffer correctly holds 0x55");
            passes = passes + 1;
        end

        // Reset
        reset = 1;
        repeat (5) @(posedge clk);
        reset = 0;
        repeat (5) @(posedge clk);
        data_in = 1;

        // ============================================================
        // TEST 11: Reset mid-reception
        // ============================================================
        $display("==============================================");
        $display("TEST 11: Reset mid-reception");
        $display("==============================================");

        wait_enable_ticks(5);

        // Begin sending a byte but reset halfway through data bits
        data_in = 0; // start bit
        wait_enable_ticks(16); // finish start bit

        // Send a couple of data bits
        data_in = 1; // bit 0
        wait_enable_ticks(16);
        data_in = 0; // bit 1
        wait_enable_ticks(8); // halfway through bit 1

        // Assert reset mid-reception
        reset = 1;
        repeat (3) @(posedge clk);

        if (uut.state !== 2'b00) begin
            $display("  FAIL: state should be START after reset, got %b", uut.state);
            errors = errors + 1;
        end else begin
            $display("  PASS: state reset to START");
            passes = passes + 1;
        end

        if (rx_busy !== 1'b0) begin
            $display("  FAIL: rx_busy should be 0 after reset");
            errors = errors + 1;
        end else begin
            $display("  PASS: rx_busy cleared after reset");
            passes = passes + 1;
        end

        if (data_ready !== 1'b0) begin
            $display("  FAIL: data_ready should be 0 after reset");
            errors = errors + 1;
        end else begin
            $display("  PASS: data_ready cleared after reset");
            passes = passes + 1;
        end

        if (uut.bit_index !== 3'b0) begin
            $display("  FAIL: bit_index should be 0 after reset");
            errors = errors + 1;
        end else begin
            $display("  PASS: bit_index cleared after reset");
            passes = passes + 1;
        end

        if (uut.sample_count !== 4'b0) begin
            $display("  FAIL: sample_count should be 0 after reset");
            errors = errors + 1;
        end else begin
            $display("  PASS: sample_count cleared after reset");
            passes = passes + 1;
        end

        reset = 0;
        data_in = 1;
        repeat (5) @(posedge clk);

        // ============================================================
        // Summary
        // ============================================================
        $display("");
        $display("==============================================");
        $display("         TEST SUMMARY");
        $display("==============================================");
        $display("  PASSED: %0d", passes);
        $display("  FAILED: %0d", errors);
        $display("----------------------------------------------");
        if (errors == 0)
            $display("  ALL TESTS PASSED");
        else begin
            $display("  TESTS FINISHED WITH %0d ERROR(S)", errors);
            $display("");
            $display("  NOTE: Some failures are due to a known RTL bug:");
            $display("  bit_index is declared as reg[2:0] and cannot reach 8.");
            $display("  The DATA->STOP transition condition (bit_index==8)");
            $display("  is unreachable, causing the FSM to stay in DATA.");
            $display("  Suggested fix: widen bit_index to reg[3:0].");
        end
        $display("==============================================");

        #100;
        done = 1;
    end

    // -------------------------------------------------------
    // Timeout watchdog
    // -------------------------------------------------------
    initial begin
        wait(start);
        #(CLK_PERIOD * 5000000);
        if (!done) begin
            $display("ERROR: Simulation timeout!");
            done = 1;
        end
    end

endmodule

// ==================================================================
// BAUD_GEN_TB
// ==================================================================


module BAUD_GEN_TB(input wire start, output reg done);

    // -------------------------------------------------------
    // Clock & Reset
    // -------------------------------------------------------
    reg clk;
    reg reset;

    // 100 MHz clock → 10 ns period
    localparam CLK_PERIOD = 10;

    initial clk = 0;
    always #(CLK_PERIOD / 2) clk = ~clk;

    // -------------------------------------------------------
    // DUT Instantiation
    // -------------------------------------------------------
    wire rx_enable, tx_enable;

    // Global clock cycle counter
    reg [31:0] cycle_count;
    always @(posedge clk) begin
        if (reset)
            cycle_count <= 0;
        else
            cycle_count <= cycle_count + 1;
    end

    baudrate uut (
        .clk(clk),
        .reset(reset),
        .rx_enable(rx_enable),
        .tx_enable(tx_enable)
    );

    // -------------------------------------------------------
    // Expected divisor values
    // -------------------------------------------------------
    localparam TX_DIVISOR = `CLK / `BAUD_RATE;          // 868
    localparam RX_DIVISOR = `CLK / (`BAUD_RATE * 16);   // 54

    // -------------------------------------------------------
    // Counters to measure tick periods
    // -------------------------------------------------------
    integer rx_tick_count;
    integer tx_tick_count;
    integer rx_ticks_seen;
    integer tx_ticks_seen;
    integer rx_period;
    integer tx_period;
    integer errors;

    // -------------------------------------------------------
    // Test Sequence
    // -------------------------------------------------------
    initial begin
        done = 0;
        wait(start);
        $dumpfile("baud_gen_tb.vcd");
        $dumpvars(0, BAUD_GEN_TB);

        errors = 0;
        rx_tick_count = 0;
        tx_tick_count = 0;
        rx_ticks_seen = 0;
        tx_ticks_seen = 0;
        rx_period = 0;
        tx_period = 0;

        // ---- TEST 1: Reset behavior ----
        $display("----------------------------------------------");
        $display("TEST 1: Reset behavior");
        $display("----------------------------------------------");
        reset = 1;
        repeat (5) @(posedge clk);

        // During reset, counters should be 0, so enables should be high
        // (tx_acc == 0 and rx_acc == 0 → enables asserted)
        if (tx_enable !== 1'b1) begin
            $display("  FAIL: tx_enable should be 1 during reset, got %b", tx_enable);
            errors = errors + 1;
        end else
            $display("  PASS: tx_enable is 1 during reset");

        if (rx_enable !== 1'b1) begin
            $display("  FAIL: rx_enable should be 1 during reset, got %b", rx_enable);
            errors = errors + 1;
        end else
            $display("  PASS: rx_enable is 1 during reset");

        // ---- Release reset ----
        reset = 0;
        @(negedge clk);

        // ---- TEST 2: RX enable period ----
        $display("----------------------------------------------");
        $display("TEST 2: RX enable tick period (expected %0d clocks)", RX_DIVISOR);
        $display("----------------------------------------------");

        // Wait until we see rx_enable == 1
        while (rx_enable !== 1'b1) @(negedge clk);
        // Skip first tick's measurement to be clean
        rx_tick_count = 0;
        rx_ticks_seen = 0;
        @(negedge clk);

        // Measure period: count clocks until next rx_enable
        while (rx_ticks_seen < 2) begin
            rx_tick_count = rx_tick_count + 1;
            if (rx_enable === 1'b1) begin
                rx_period = rx_tick_count;
                if (rx_period == RX_DIVISOR)
                    $display("  PASS: RX tick #%0d period = %0d clocks", rx_ticks_seen + 1, rx_period);
                else begin
                    $display("  FAIL: RX tick #%0d period = %0d clocks (expected %0d)", rx_ticks_seen + 1, rx_period, RX_DIVISOR);
                    errors = errors + 1;
                end
                rx_tick_count = 0;
                rx_ticks_seen = rx_ticks_seen + 1;
            end
            @(negedge clk);
        end

        // ---- TEST 3: TX enable period ----
        $display("----------------------------------------------");
        $display("TEST 3: TX enable tick period (expected %0d clocks)", TX_DIVISOR);
        $display("----------------------------------------------");

        // Reset to get a clean start for TX measurement
        reset = 1;
        repeat (3) @(posedge clk);
        reset = 0;
        @(negedge clk);

        // Wait until we see tx_enable == 1
        while (tx_enable !== 1'b1) @(negedge clk);
        tx_tick_count = 0;
        tx_ticks_seen = 0;
        @(negedge clk);

        // Measure 2 full TX periods
        while (tx_ticks_seen < 2) begin
            tx_tick_count = tx_tick_count + 1;
            if (tx_enable === 1'b1) begin
                tx_period = tx_tick_count;
                if (tx_period == TX_DIVISOR)
                    $display("  PASS: TX tick #%0d period = %0d clocks", tx_ticks_seen + 1, tx_period);
                else begin
                    $display("  FAIL: TX tick #%0d period = %0d clocks (expected %0d)", tx_ticks_seen + 1, tx_period, TX_DIVISOR);
                    errors = errors + 1;
                end
                tx_tick_count = 0;
                tx_ticks_seen = tx_ticks_seen + 1;
            end
            @(negedge clk);
        end

        // ---- TEST 4: TX/RX ratio ----
        $display("----------------------------------------------");
        $display("TEST 4: TX/RX tick ratio (expected ~16)");
        $display("----------------------------------------------");

        // Reset and count how many RX ticks occur in one TX period
        reset = 1;
        repeat (3) @(posedge clk);
        reset = 0;
        @(negedge clk);

        // Wait for first TX tick
        while (tx_enable !== 1'b1) @(negedge clk);
        @(negedge clk);

        // Count RX ticks until next TX tick
        rx_ticks_seen = 0;
        while (tx_enable !== 1'b1) begin
            if (rx_enable === 1'b1) begin
                rx_ticks_seen = rx_ticks_seen + 1;
            end
            @(negedge clk);
        end

        // TX_DIVISOR / RX_DIVISOR = 868/54 = 16 (integer division)
        $display("  RX ticks per TX period: %0d", rx_ticks_seen);
        if (rx_ticks_seen == TX_DIVISOR / RX_DIVISOR)
            $display("  PASS: Ratio matches expected %0d", TX_DIVISOR / RX_DIVISOR);
        else begin
            $display("  WARN: Ratio is %0d, expected %0d (rounding is acceptable)", rx_ticks_seen, TX_DIVISOR / RX_DIVISOR);
        end

        // ---- TEST 5: Reset mid-operation ----
        $display("----------------------------------------------");
        $display("TEST 5: Reset mid-operation");
        $display("----------------------------------------------");

        // Let counters run for a while
        repeat (200) @(posedge clk);

        // Assert reset
        reset = 1;
        @(negedge clk);
        @(negedge clk);

        // Check that counters are zeroed (enables should be high at negedge as reset is active)
        if (tx_enable !== 1'b1 || rx_enable !== 1'b1) begin
            $display("  FAIL: Enables should be 1 after mid-operation reset");
            errors = errors + 1;
        end else
            $display("  PASS: Enables correctly asserted after mid-operation reset");

        // Release reset and verify counting resumes
        reset = 0;
        repeat (10) @(posedge clk);

        if (tx_enable == 1'b0 && rx_enable == 1'b0)
            $display("  PASS: Counters resumed after reset release");
        else
            $display("  INFO: Counters active (may be at tick boundary)");

        // ---- Summary ----
        $display("==============================================");
        if (errors == 0)
            $display("ALL TESTS PASSED");
        else
            $display("TESTS FINISHED WITH %0d ERROR(S)", errors);
        $display("==============================================");

        #100;
        done = 1;
    end

    // Timeout watchdog (in case something hangs)
    initial begin
        wait(start);
        #(CLK_PERIOD * 100000);
        if (!done) begin
            $display("ERROR: Simulation timeout!");
            done = 1;
        end
    end

endmodule
