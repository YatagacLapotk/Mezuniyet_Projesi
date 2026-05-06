`timescale 1ns / 1ps

module UART_RX_TB;

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
        .enable(enable),
        .rx_enable(rx_enable),
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
        $finish;
    end

    // -------------------------------------------------------
    // Timeout watchdog
    // -------------------------------------------------------
    initial begin
        #(CLK_PERIOD * 5000000);
        $display("ERROR: Simulation timeout!");
        $finish;
    end

endmodule
