`timescale 1ns / 1ps

module UART_TX_TB;

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
        .tx_enable(tx_enable),
        .enable(enable),
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
        $finish;
    end

    // -------------------------------------------------------
    // Timeout watchdog
    // -------------------------------------------------------
    initial begin
        #(CLK_PERIOD * 500000);
        $display("ERROR: Simulation timeout!");
        $finish;
    end

endmodule
