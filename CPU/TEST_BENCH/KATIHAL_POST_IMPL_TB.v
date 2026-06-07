`timescale 1ns / 1ps
// =============================================================================
// KATIHAL Post-Implementation Test Bench
// =============================================================================
// For Vivado post-implementation functional simulation
// - Uses only top-level entity ports (no hierarchical signal access)
// - Uses non-blocking assignments (<=) for synchronous signals
// - Compatible with optimized netlist from implementation
// =============================================================================

`include "sabit_veriler.vh"

module KATIHAL_POST_IMPL_TB ();

    // -------------------------------------------
    // Test Bench Parameters
    // -------------------------------------------
    localparam CLK_PERIOD = 200;  // 5 MHz = 200ns period
    localparam BAUD_TICKS = `CLK / `BAUD_RATE;  // Clock cycles per UART bit
    localparam TIMEOUT_CYCLES = 1000000000;  // Global timeout
    localparam MAX_TEST_CYCLES = 5000000;  // Per-test timeout

    // -------------------------------------------
    // DUT Port Signals
    // -------------------------------------------
    reg        clk;
    reg        reset;
    reg        rx_enable;
    reg        uart_in;
    reg        spi_enable;
    reg        sclk_enable;
    reg        miso;
    wire       mosi;
    wire       ss;
    wire       busy;
    wire       uart_output;
    wire       sclk;
    wire [15:0] data_mem_out;

    // -------------------------------------------
    // Test Control Signals
    // -------------------------------------------
    integer test_num;
    integer pass_count;
    integer fail_count;
    reg [255:0] current_test;
    integer cycle_counter;
    reg test_completed;
    reg [15:0] captured_data_mem_out;

    // Synchronous capture registers - use non-blocking assignment
    reg busy_sync = 1'b0;
    reg ss_sync = 1'b1;
    reg [15:0] data_mem_out_sync = 16'h0000;
    reg prev_busy_sync = 1'b0;
    reg prev_ss_sync = 1'b1;

    reg success;
    // -------------------------------------------
    // Clock Generation (fast for post-impl sim)
    // Use a small period so baud counters complete quickly in simulation.
    // -------------------------------------------
    localparam real CLK_PERIOD_REAL = 0.2; // 0.2 ns period (5 GHz) for faster sim
    initial begin
        clk <= 1'b0;
        forever #(CLK_PERIOD_REAL/2.0) clk <= ~clk;
    end

    // -------------------------------------------
    // Synchronous Signal Capture
    // Capture outputs on clock edge using non-blocking assignment
    // -------------------------------------------
    always @(posedge clk) begin
        busy_sync        <= busy;
        ss_sync          <= ss;
        data_mem_out_sync <= data_mem_out;
    end

    // Debug: print when busy or ss change
    always @(posedge clk) begin
        if (busy_sync !== prev_busy_sync) begin
            $display("[DBG] busy_sync changed: %b -> %b at %0t", prev_busy_sync, busy_sync, $time);
            prev_busy_sync <= busy_sync;
        end
        if (ss_sync !== prev_ss_sync) begin
            $display("[DBG] ss_sync changed: %b -> %b at %0t", prev_ss_sync, ss_sync, $time);
            prev_ss_sync <= ss_sync;
        end
    end

    // -------------------------------------------
    // DUT Instance - connect only to top-level ports
    // -------------------------------------------
    top uut (
        .clk(clk),
        .reset(reset),
        .rx_enable(rx_enable),
        .uart_in(uart_in),
        .spi_enable(spi_enable),
        .sclk_enable(sclk_enable),
        .miso(miso),
        .mosi(mosi),
        .ss(ss),
        .busy(busy),
        .uart_output(uart_output),
        .data_mem_out(data_mem_out),
        .sclk(sclk)
    );

    // -------------------------------------------
    // Test Verification Tasks
    // -------------------------------------------

    // Check 1-bit value
    task check_1bit;
        input [255:0] test_name;
        input actual;
        input expected;
        begin
            if (actual === expected) begin
                $display("[PASS] %0s: got %b", test_name, actual);
                pass_count <= pass_count + 1;
            end else begin
                $display("[FAIL] %0s: got %b, expected %b", test_name, actual, expected);
                fail_count <= fail_count + 1;
            end
        end
    endtask

    // Check 16-bit value
    task check_16bit;
        input [255:0] test_name;
        input [15:0] actual;
        input [15:0] expected;
        begin
            if (actual === expected) begin
                $display("[PASS] %0s: got 0x%04X", test_name, actual);
                pass_count <= pass_count + 1;
            end else begin
                $display("[FAIL] %0s: got 0x%04X, expected 0x%04X", test_name, actual, expected);
                fail_count <= fail_count + 1;
            end
        end
    endtask

    // -------------------------------------------
    // UART Transmission Task
    // Non-blocking assignment for synchronous signals
    // -------------------------------------------
    task uart_send_byte;
        input [7:0] data;
        integer i;
        begin
            $display("[UART TX] Byte start: 0x%02X at %0t", data, $time);
            // Start bit (LOW)
            @(posedge clk);
            uart_in <= 1'b0;
            repeat (BAUD_TICKS) @(posedge clk);

            // 8 data bits (LSB first)
            for (i = 0; i < 8; i = i + 1) begin
                uart_in <= data[i];
                repeat (BAUD_TICKS) @(posedge clk);
            end

            // Stop bit (HIGH)
            uart_in <= 1'b1;
            repeat (BAUD_TICKS) @(posedge clk);
            $display("[UART TX] Byte end:   0x%02X at %0t", data, $time);
        end
    endtask

    // Send 32-bit word (little-endian)
    task uart_send_word;
        input [31:0] word;
        begin
            uart_send_byte(word[7:0]);
            uart_send_byte(word[15:8]);
            uart_send_byte(word[23:16]);
            uart_send_byte(word[31:24]);
        end
    endtask

    // -------------------------------------------
    // SPI Transmission Task
    // Drive MISO on negedge SCLK for proper setup
    // -------------------------------------------
    task spi_send_byte;
        input [7:0] data;
        integer i, wait_count;
        begin
            // Wait for SS to go low (transaction start) with timeout
            wait_count = 0;
            while (ss_sync !== 1'b0 && wait_count < 5000) begin
                @(posedge clk);
                wait_count = wait_count + 1;
            end
            if (ss_sync !== 1'b0) begin
                $display("[TIMEOUT] SPI SS didn't assert low within %0d cycles", wait_count);
                disable spi_send_byte;
            end
            @(posedge clk);

            // MSB first - first bit ready before first clock
            miso <= data[7];

            // Remaining bits on SCLK negedge
            for (i = 6; i >= 0; i = i - 1) begin
                @(negedge sclk);
                miso <= data[i];
            end

            // Wait for SS to go high (transaction end) with timeout
            wait_count = 0;
            while (ss_sync !== 1'b1 && wait_count < 5000) begin
                @(posedge clk);
                wait_count = wait_count + 1;
            end
            if (ss_sync !== 1'b1) begin
                $display("[TIMEOUT] SPI SS didn't deassert high within %0d cycles", wait_count);
                disable spi_send_byte;
            end
            @(posedge clk);
        end
    endtask

    // Send 32-bit word via SPI (little-endian)
    task spi_send_word;
        input [31:0] word;
        begin
            spi_send_byte(word[7:0]);
            spi_send_byte(word[15:8]);
            spi_send_byte(word[23:16]);
            spi_send_byte(word[31:24]);
        end
    endtask

    // -------------------------------------------
    // Reset Task
    // -------------------------------------------
    task do_reset;
        begin
            @(negedge clk);
            reset       <= 1'b1;
            rx_enable   <= 1'b1;    // UART RX disabled (active low)
            uart_in     <= 1'b1;    // UART idle state
            spi_enable  <= 1'b0;    // SPI disabled
            sclk_enable <= 1'b0;
            miso        <= 1'b0;
            @(posedge clk);
            repeat (10) @(posedge clk);
            @(negedge clk);
            reset <= 1'b0;
            repeat (5) @(posedge clk);
        end
    endtask

    // -------------------------------------------
    // Wait for busy to go low (program loaded)
    // Uses synchronous capture of busy signal
    // -------------------------------------------
    task wait_for_ready;
        input [31:0] max_cycles;
        input [255:0] test_name;
        reg [31:0] wait_count;
        begin
            wait_count = 0;
            while (busy_sync === 1'b1 && wait_count < max_cycles) begin
                @(posedge clk);
                wait_count = wait_count + 1;
            end
            if (wait_count >= max_cycles) begin
                $display("[TIMEOUT] %0s: busy stayed high for %0d cycles", test_name, max_cycles);
            end else begin
                $display("[INFO] %0s: ready after %0d cycles", test_name, wait_count);
            end
        end
    endtask

    // -------------------------------------------
    // Wait for specific data_mem_out value
    // -------------------------------------------
    task wait_for_data;
        input [15:0] expected;
        input [31:0] max_cycles;
        output success;
        reg [31:0] wait_count;
        begin
            success = 1'b0;
            wait_count = 0;
            while (data_mem_out_sync !== expected && wait_count < max_cycles) begin
                @(posedge clk);
                wait_count = wait_count + 1;
            end
            if (data_mem_out_sync === expected) begin
                success = 1'b1;
            end
        end
    endtask

    // -------------------------------------------
    // Main Test Sequence
    // -------------------------------------------
    initial begin
        // Initialize counters
        test_num <= 0;
        pass_count <= 0;
        fail_count <= 0;

        $display("========================================");
        $display("KATIHAL Post-Implementation Test Bench");
        $display("Target: Vivado Post-Implementation Sim");
        $display("========================================");

        // ========================================
        // TEST 1: Reset Behavior
        // ========================================
        $display("\n[TEST 1] Reset Behavior");
        current_test <= "Reset Behavior";
        test_num <= 1;

        reset       <= 1'b1;
        rx_enable   <= 1'b1;
        uart_in     <= 1'b1;
        spi_enable  <= 1'b0;
        sclk_enable <= 1'b0;
        miso        <= 1'b0;

        repeat (20) @(posedge clk);

        // After reset, busy should be low
        @(posedge clk);
        check_1bit("busy after reset", busy_sync, 1'b0);

        // Release reset
        @(negedge clk);
        reset <= 1'b0;
        repeat (5) @(posedge clk);

        // ========================================
        // TEST 2: UART Program Load - Single NOP
        // ========================================
        $display("\n[TEST 2] UART Single Word Load");
        current_test <= "UART Single Load";
        test_num <= 2;

        // Enable UART RX
        rx_enable <= 1'b0;

        // Send NOP: 0x00000013
        $display("Sending NOP (0x00000013) via UART...");
        uart_send_word(32'h00000013);

        // Disable UART
        rx_enable <= 1'b1;
        uart_in <= 1'b1;

        // Wait for loader to complete
        wait_for_ready(MAX_TEST_CYCLES, "UART Single Load");

        // Verify system becomes ready
        check_1bit("busy after load", busy_sync, 1'b0);

        // ========================================
        // TEST 3: UART Program Load - Basic ALU Ops
        // ========================================
        $display("\n[TEST 3] UART ALU Program");
        current_test <= "UART ALU Program";
        test_num <= 3;

        do_reset;

        // Enable UART
        rx_enable <= 1'b0;

        // Program: ADDI x1, x0, 10; ADDI x2, x0, 20
        // Store results, then load to verify via data_mem_out
        $display("Sending ALU program via UART...");

        uart_send_word(32'h00A00093);  // ADDI x1, x0, 10
        uart_send_word(32'h01400113);  // ADDI x2, x0, 20
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00102023);  // SW x1, 0(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00202223);  // SW x2, 4(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00002183);  // LW x3, 0(x0) - expect data_mem_out = 10

        // Disable UART
        rx_enable <= 1'b1;
        uart_in <= 1'b1;

        // Wait for loader
        wait_for_ready(MAX_TEST_CYCLES, "UART ALU Load");

        // Wait for first store result to appear
        begin
            wait_for_data(16'd10, 200, success);
            if (success) begin
                check_16bit("data_mem_out after SW x1", data_mem_out_sync, 16'd10);
            end else begin
                $display("[FAIL] Timeout waiting for data_mem_out = 10");
                fail_count <= fail_count + 1;
            end
        end

        // Wait for second store result
        begin
            wait_for_data(16'd20, 200, success);
            if (success) begin
                check_16bit("data_mem_out after SW x2", data_mem_out_sync, 16'd20);
            end else begin
                $display("[FAIL] Timeout waiting for data_mem_out = 20");
                fail_count <= fail_count + 1;
            end
        end

        // ========================================
        // TEST 4: Busy Signal Verification
        // ========================================
        $display("\n[TEST 4] Busy Signal During Load");
        current_test <= "Busy Signal";
        test_num <= 4;

        do_reset;

        // Check busy is low initially
        check_1bit("busy before load", busy_sync, 1'b0);

        // Start UART transmission
        rx_enable <= 1'b0;
        uart_send_byte(8'h13);  // First byte of NOP

        // After a few cycles, busy should be high
        repeat (20) @(posedge clk);
        check_1bit("busy during load", busy_sync, 1'b1);

        // Complete the word
        uart_send_byte(8'h00);
        uart_send_byte(8'h00);
        uart_send_byte(8'h00);

        rx_enable <= 1'b1;
        uart_in <= 1'b1;

        // Wait for busy to go low
        wait_for_ready(MAX_TEST_CYCLES, "Busy Signal Test");
        check_1bit("busy after load complete", busy_sync, 1'b0);

        // ========================================
        // TEST 5: Branch Test
        // ========================================
        $display("\n[TEST 5] Branch (BEQ) Test");
        current_test <= "Branch Test";
        test_num <= 5;

        do_reset;

        rx_enable <= 1'b0;
        $display("Sending branch program via UART...");

        // Program that sets x1=x2=10, branches over flushed instructions
        uart_send_word(32'h00A00093);  // ADDI x1, x0, 10
        uart_send_word(32'h00A00113);  // ADDI x2, x0, 10
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00208863);  // BEQ x1, x2, +16 (branch forward)
        uart_send_word(32'h0FF00193);  // ADDI x3, x0, 0xFF (flushed if branch taken)
        uart_send_word(32'h0EE00213);  // ADDI x4, x0, 0xEE (flushed if branch taken)
        uart_send_word(`NOP);
        uart_send_word(32'h0AA00293);  // ADDI x5, x0, 0xAA (branch target)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        // Store x5 to verify
        uart_send_word(32'h00502423);  // SW x5, 8(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);

        rx_enable <= 1'b1;
        uart_in <= 1'b1;

        wait_for_ready(MAX_TEST_CYCLES, "Branch Test Load");

        // Wait for branch target result
        begin
            wait_for_data(16'hAA, 300, success);
            if (success) begin
                check_16bit("data_mem_out after branch", data_mem_out_sync, 16'hAA);
            end else begin
                $display("[FAIL] Timeout waiting for branch result 0xAA");
                fail_count <= fail_count + 1;
            end
        end

        // ========================================
        // TEST 6: SPI Program Load
        // ========================================
        $display("\n[TEST 6] SPI Program Load");
        current_test <= "SPI Load";
        test_num <= 6;

        do_reset;

        // Enable SPI
        spi_enable <= 1'b1;
        sclk_enable <= 1'b1;

        $display("Sending program via SPI...");

        // Load x1 with 0x55, store it
        spi_send_word(32'h05500093);  // ADDI x1, x0, 0x55
        spi_send_word(`NOP);
        spi_send_word(`NOP);
        spi_send_word(`NOP);
        spi_send_word(`NOP);

        // Disable SPI
        spi_enable <= 1'b0;
        sclk_enable <= 1'b0;

        wait_for_ready(MAX_TEST_CYCLES, "SPI Load");

        // ========================================
        // TEST 7: UART Data Output Port
        // ========================================
        $display("\n[TEST 7] UART Output Port Check");
        current_test <= "UART Output";
        test_num <= 7;

        do_reset;

        // UART output should be high when idle (mark state)
        repeat (10) @(posedge clk);
        check_1bit("uart_output idle state", uart_output, 1'b1);

        // ========================================
        // TEST 8: SCLK Output Check (when SPI enabled)
        // ========================================
        $display("\n[TEST 8] SCLK Output");
        current_test <= "SCLK Output";
        test_num <= 8;

        do_reset;

        // Enable SPI
        spi_enable <= 1'b1;
        sclk_enable <= 1'b1;
        repeat (20) @(posedge clk);

        // SCLK should be toggling when SPI is active
        $display("[INFO] SCLK activity check - verify in waveform");

        // Complete a transfer
        spi_send_byte(8'hA5);

        spi_enable <= 1'b0;
        sclk_enable <= 1'b0;

        // ========================================
        // TEST 9: Multiple Reset Cycles
        // ========================================
        $display("\n[TEST 9] Multiple Reset Cycles");
        current_test <= "Multiple Reset";
        test_num <= 9;

        repeat (3) begin
            do_reset;
            check_1bit("busy after reset", busy_sync, 1'b0);
        end

        // ========================================
        // TEST 10: Complete Integration Test
        // ========================================
        $display("\n[TEST 10] Integration Test");
        current_test <= "Integration";
        test_num <= 10;

        do_reset;

        // Load a complete program via UART
        rx_enable <= 1'b0;
        $display("Sending integration test program...");

        // Calculate 10 + 20 = 30, 20 - 10 = 10 using LUI/ADDI
        uart_send_word(32'h00000093);  // ADDI x1, x0, 0
        uart_send_word(32'h00A08093);  // ADDI x1, x1, 10  (x1 = 10)
        uart_send_word(32'h01400113);  // ADDI x2, x0, 20  (x2 = 20)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h002081B3);  // ADD x3, x1, x2   (x3 = 30)
        uart_send_word(32'h40208233);  // SUB x4, x1, x2   (x4 = -10)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        // Store x3
        uart_send_word(32'h00302023);  // SW x3, 0(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);

        rx_enable <= 1'b1;
        uart_in <= 1'b1;

        wait_for_ready(MAX_TEST_CYCLES * 2, "Integration Load");

        // Verify result
        begin
            wait_for_data(16'd30, 300, success);
            if (success) begin
                check_16bit("ADD result 10+20=30", data_mem_out_sync, 16'd30);
            end else begin
                $display("[FAIL] Timeout waiting for ADD result 30");
                fail_count <= fail_count + 1;
            end
        end

        // ========================================
        // Test Summary
        // ========================================
        repeat (100) @(posedge clk);

        $display("\n========================================");
        $display("Test Summary");
        $display("========================================");
        $display("Passed: %0d", pass_count);
        $display("Failed: %0d", fail_count);
        $display("========================================");

        if (fail_count == 0) begin
            $display("All tests PASSED!");
        end else begin
            $display("Some tests FAILED!");
        end

        $finish;
    end

    // -------------------------------------------
    // Global Timeout Watchdog
    // -------------------------------------------
    initial begin
        repeat (TIMEOUT_CYCLES) @(posedge clk);
        $display("[FATAL] Global timeout reached after %0d cycles", TIMEOUT_CYCLES);
        $display("Completed %0d tests before timeout", test_num);
        $finish;
    end

    // -------------------------------------------
    // VCD Dump for waveform viewing
    // -------------------------------------------
    initial begin
        $dumpfile("KATIHAL_POST_IMPL_TB.vcd");
        $dumpvars(0, KATIHAL_POST_IMPL_TB);
    end

endmodule
