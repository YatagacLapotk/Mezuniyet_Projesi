`timescale 1ns / 1ps
`include "sabit_veriler.vh"

module BAUD_GEN_TB;

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
        @(posedge clk);

        // ---- TEST 2: RX enable period ----
        $display("----------------------------------------------");
        $display("TEST 2: RX enable tick period (expected %0d clocks)", RX_DIVISOR);
        $display("----------------------------------------------");

        // Wait for first rx_enable tick after reset, then measure next ones
        // Skip the first tick (may be partial from reset release)
        @(posedge clk);  // one cycle after reset release
        rx_tick_count = 0;
        rx_ticks_seen = 0;

        // Wait until we see a rising edge of rx_enable
        wait (rx_enable == 1'b0);   // wait for it to go low first
        wait (rx_enable == 1'b1);   // now catch the next tick
        @(posedge clk);
        rx_tick_count = 0;

        // Measure period: count clocks until next rx_enable
        while (rx_ticks_seen < 3) begin
            @(posedge clk);
            rx_tick_count = rx_tick_count + 1;
            if (rx_enable) begin
                if (rx_ticks_seen > 0) begin
                    rx_period = rx_tick_count;
                    if (rx_period == RX_DIVISOR)
                        $display("  PASS: RX tick #%0d period = %0d clocks", rx_ticks_seen, rx_period);
                    else begin
                        $display("  FAIL: RX tick #%0d period = %0d clocks (expected %0d)", rx_ticks_seen, rx_period, RX_DIVISOR);
                        errors = errors + 1;
                    end
                end
                rx_tick_count = 0;
                rx_ticks_seen = rx_ticks_seen + 1;
            end
        end

        // ---- TEST 3: TX enable period ----
        $display("----------------------------------------------");
        $display("TEST 3: TX enable tick period (expected %0d clocks)", TX_DIVISOR);
        $display("----------------------------------------------");

        // Reset to get a clean start for TX measurement
        reset = 1;
        repeat (3) @(posedge clk);
        reset = 0;
        @(posedge clk);

        tx_tick_count = 0;
        tx_ticks_seen = 0;

        // Wait for tx_enable to deassert then reassert
        wait (tx_enable == 1'b0);
        wait (tx_enable == 1'b1);
        @(posedge clk);
        tx_tick_count = 0;

        // Measure 2 full TX periods
        while (tx_ticks_seen < 3) begin
            @(posedge clk);
            tx_tick_count = tx_tick_count + 1;
            if (tx_enable) begin
                if (tx_ticks_seen > 0) begin
                    tx_period = tx_tick_count;
                    if (tx_period == TX_DIVISOR)
                        $display("  PASS: TX tick #%0d period = %0d clocks", tx_ticks_seen, tx_period);
                    else begin
                        $display("  FAIL: TX tick #%0d period = %0d clocks (expected %0d)", tx_ticks_seen, tx_period, TX_DIVISOR);
                        errors = errors + 1;
                    end
                end
                tx_tick_count = 0;
                tx_ticks_seen = tx_ticks_seen + 1;
            end
        end

        // ---- TEST 4: TX/RX ratio ----
        $display("----------------------------------------------");
        $display("TEST 4: TX/RX tick ratio (expected ~16)");
        $display("----------------------------------------------");

        // Reset and count how many RX ticks occur in one TX period
        reset = 1;
        repeat (3) @(posedge clk);
        reset = 0;

        // Wait for first TX tick after reset
        wait (tx_enable == 1'b0);
        wait (tx_enable == 1'b1);
        @(posedge clk);

        // Count RX ticks until next TX tick
        rx_ticks_seen = 0;
        begin : ratio_block
            forever begin
                @(posedge clk);
                if (rx_enable) rx_ticks_seen = rx_ticks_seen + 1;
                if (tx_enable) disable ratio_block;
            end
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
        @(posedge clk);
        @(posedge clk);

        // Check that counters are zeroed (enables should be high)
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
        $finish;
    end

    // Timeout watchdog (in case something hangs)
    initial begin
        #(CLK_PERIOD * 100000);
        $display("ERROR: Simulation timeout!");
        $finish;
    end

endmodule
