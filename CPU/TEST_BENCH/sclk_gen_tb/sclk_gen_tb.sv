`timescale 1ns/1ps

module sclk_gen_tb;

    reg clk;
    reg reset;
    reg sclk_enable;
    wire sclk_fast;
    wire sclk_real;
    integer pass_count = 0;
    integer fail_count = 0;
    integer cycle_count;
    integer test_section = 0;

    task section;
        input [255:0] name;
        begin
            test_section = test_section + 1;
            $display("");
            $display("--- SECTION %0d: %0s ---", test_section, name);
        end
    endtask

    task check_fast;
        input expected;
        input [255:0] msg;
        begin
            if (sclk_fast === expected) begin
                $display("  PASS: %0s", msg);
                pass_count = pass_count + 1;
            end else begin
                $display("  FAIL: %0s (got %b, expected %b)", msg, sclk_fast, expected);
                fail_count = fail_count + 1;
            end
        end
    endtask

    task measure_period_fast;
        input [255:0] label;
        input expected_value;
        input [31:0] expected_cycles;
        begin
            cycle_count = 0;
            while (sclk_fast === expected_value) begin
                @(negedge clk);
                cycle_count = cycle_count + 1;
            end
            if (cycle_count == expected_cycles) begin
                $display("  PASS: %0s = %b for %0d cycles", label, expected_value, cycle_count);
                pass_count = pass_count + 1;
            end else begin
                $display("  FAIL: %0s = %b for %0d cycles (expected %0d)", label, expected_value, cycle_count, expected_cycles);
                fail_count = fail_count + 1;
            end
        end
    endtask

    sclk_gen uut_fast (
        .clk(clk),
        .reset(reset),
        .sclk_enable(sclk_enable),
        .sclk(sclk_fast)
    );
    defparam uut_fast.counter_sclk = 5;

    sclk_gen uut_real (
        .clk(clk),
        .reset(reset),
        .sclk_enable(sclk_enable),
        .sclk(sclk_real)
    );
    defparam uut_real.counter_sclk = 434;

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("sclk_gen_tb.vcd");
        $dumpvars(0, sclk_gen_tb);

        $display("========================================");
        $display("sclk_gen COMPREHENSIVE TESTBENCH");
        $display("========================================");

        // ============================================================
        section("1. RESET BEHAVIOR");
        reset = 1;
        sclk_enable = 0;
        repeat(3) @(posedge clk);
        check_fast(0, "sclk low during reset with enable=0");

        reset = 1;
        sclk_enable = 1;
        repeat(3) @(posedge clk);
        check_fast(0, "sclk low during reset with enable=1");

        reset = 0;
        sclk_enable = 0;
        repeat(2) @(posedge clk);
        check_fast(0, "sclk low after reset with enable=0");

        // ============================================================
        section("2. BASIC TOGGLE WITH FAST PARAM (counter_sclk=5)");
        sclk_enable = 1;
        check_fast(0, "sclk starts at 0 when enabled");

        measure_period_fast("Initial low period", 0, 5);
        measure_period_fast("First high period", 1, 5);
        measure_period_fast("Second low period", 0, 5);
        measure_period_fast("Second high period", 1, 5);
        measure_period_fast("Third low period", 0, 5);
        measure_period_fast("Third high period", 1, 5);
        measure_period_fast("Fourth low period", 0, 5);

        // ============================================================
        section("3. DISABLE DURING OPERATION");
        sclk_enable = 0;
        @(posedge clk);
        #1;
        check_fast(0, "sclk returns to 0 immediately after disable");

        repeat(10) @(posedge clk);
        check_fast(0, "sclk stays 0 while disabled");

        // ============================================================
        section("4. RE-ENABLE AFTER DISABLE (CLEAN RESTART)");
        sclk_enable = 1;
        check_fast(0, "sclk starts at 0 on re-enable");
        measure_period_fast("Re-enable low period", 0, 5);
        measure_period_fast("Re-enable high period", 1, 5);
        measure_period_fast("Re-enable second low", 0, 5);

        // ============================================================
        section("5. RESET DURING OPERATION");
        sclk_enable = 1;
        @(posedge clk);
        @(posedge clk);
        reset = 1;
        @(posedge clk);
        check_fast(0, "sclk goes low when reset asserted mid-operation");
        @(posedge clk);
        check_fast(0, "sclk stays low while reset asserted");
        @(posedge clk);
        check_fast(0, "sclk stays low while reset asserted");

        reset = 0;
        sclk_enable = 1;
        check_fast(0, "sclk low after reset release, still enabled");
        measure_period_fast("Post-reset low period", 0, 5);
        measure_period_fast("Post-reset high period", 1, 5);

        // ============================================================
        section("6. DISABLE THEN RE-ENABLE WITH DELAY");
        sclk_enable = 0;
        repeat(20) @(posedge clk);
        check_fast(0, "sclk stays 0 during long disable");

        sclk_enable = 1;
        check_fast(0, "sclk starts at 0 after long disable");
        measure_period_fast("Delayed re-enable low", 0, 5);
        measure_period_fast("Delayed re-enable high", 1, 5);

        // ============================================================
        section("7. MULTIPLE RESET PULSES");
        sclk_enable = 1;
        repeat(3) @(posedge clk);
        reset = 1;
        @(posedge clk);
        reset = 0;
        check_fast(0, "sclk low after first short reset pulse");
        measure_period_fast("After first reset low", 0, 5);

        @(posedge clk);
        reset = 1;
        @(posedge clk);
        reset = 0;
        check_fast(0, "sclk low after second short reset pulse");
        measure_period_fast("After second reset low", 0, 5);
        measure_period_fast("After second reset high", 1, 5);

        // ============================================================
        section("8. REAL PARAMETER VERIFICATION (counter_sclk=434)");
        $display("  Testing uut_real with counter_sclk=434");
        reset = 1;
        sclk_enable = 0;
        repeat(3) @(negedge clk);

        if (sclk_real === 0) begin
            $display("  PASS: sclk_real low during reset");
            pass_count = pass_count + 1;
        end else begin
            $display("  FAIL: sclk_real low during reset (got %b)", sclk_real);
            fail_count = fail_count + 1;
        end

        sclk_enable = 1;
        reset = 0;

        if (sclk_real === 0) begin
            $display("  PASS: sclk_real starts at 0 with real parameter");
            pass_count = pass_count + 1;
        end else begin
            $display("  FAIL: sclk_real starts at 0 (got %b)", sclk_real);
            fail_count = fail_count + 1;
        end

        cycle_count = 0;
        while (sclk_real === 0) begin
            @(negedge clk);
            cycle_count = cycle_count + 1;
        end
        if (cycle_count == 434) begin
            $display("  PASS: Real param initial low = 0 for %0d cycles", cycle_count);
            pass_count = pass_count + 1;
        end else begin
            $display("  FAIL: Real param initial low = 0 for %0d cycles (expected 434)", cycle_count);
            fail_count = fail_count + 1;
        end

        cycle_count = 0;
        while (sclk_real === 1) begin
            @(negedge clk);
            cycle_count = cycle_count + 1;
        end
        if (cycle_count == 434) begin
            $display("  PASS: Real param first high = 1 for %0d cycles", cycle_count);
            pass_count = pass_count + 1;
        end else begin
            $display("  FAIL: Real param first high = 1 for %0d cycles (expected 434)", cycle_count);
            fail_count = fail_count + 1;
        end

        cycle_count = 0;
        while (sclk_real === 0) begin
            @(negedge clk);
            cycle_count = cycle_count + 1;
        end
        if (cycle_count == 434) begin
            $display("  PASS: Real param second low = 0 for %0d cycles", cycle_count);
            pass_count = pass_count + 1;
        end else begin
            $display("  FAIL: Real param second low = 0 for %0d cycles (expected 434)", cycle_count);
            fail_count = fail_count + 1;
        end

        cycle_count = 0;
        while (sclk_real === 1) begin
            @(negedge clk);
            cycle_count = cycle_count + 1;
        end
        if (cycle_count == 434) begin
            $display("  PASS: Real param second high = 1 for %0d cycles", cycle_count);
            pass_count = pass_count + 1;
        end else begin
            $display("  FAIL: Real param second high = 1 for %0d cycles (expected 434)", cycle_count);
            fail_count = fail_count + 1;
        end

        // ============================================================
        section("9. TIMING SUMMARY");
        $display("  Total tests passed: %0d", pass_count);
        $display("  Total tests failed: %0d", fail_count);
        if (fail_count == 0)
            $display("  STATUS: ALL TESTS PASSED");
        else
            $display("  STATUS: %0d FAILURE(S) DETECTED", fail_count);

        $display("========================================");
        $finish;
    end

endmodule
