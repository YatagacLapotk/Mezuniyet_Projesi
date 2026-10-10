`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module PROGRAM_LOADER_TB ();
    reg clk;
    reg reset;
    reg data_ready_uart;
    reg data_ready_spi;
    reg busy_uart;
    reg busy_spi;
    reg [7:0] data_in_uart;
    reg [7:0] data_in_spi;
    wire done;
    wire cpu_halt;
    wire clear;
    wire we;
    wire [`DATA_WIDTH-1:0] write_ptr;
    wire [`DATA_WIDTH-1:0] w_addr;
    wire [`DATA_WIDTH-1:0] w_data;

    // State localparams (mirror PROGRAM_LOADER)
    localparam STALL = 0, START_U = 1, START_S = 7,
               DATA_U = 2, DATA_S = 8,
               WAIT_ACK_U = 3, WAIT_ACK_S = 9,
               LOAD_U = 4, LOAD_S = 10,
               PC_TRANSFER_U = 5, PC_TRANSFER_S = 11,
               DONE_ST = 6;

    // Simulated I_CACHE memory (to verify writes)
    reg [`DATA_WIDTH-1:0] fake_cache [0:20000];

    // Track test results
    integer test_pass = 0;
    integer test_fail = 0;

    // Sticky done flag — captures the 1-cycle done pulse
    reg done_seen;
    always @(posedge clk) begin
        if (reset || (uut.state == START_U) || (uut.state == START_S))
            done_seen <= 0;
        else if (done)
            done_seen <= 1;
    end

    PROGRAM_LOADER uut (
        .clk(clk),
        .reset(reset),
        .data_ready_uart(data_ready_uart),
        .data_ready_spi(data_ready_spi),
        .busy_uart(busy_uart),
        .busy_spi(busy_spi),
        .data_in_uart(data_in_uart),
        .data_in_spi(data_in_spi),
        .done(done),
        .cpu_halt(cpu_halt),
        .clear(clear),
        .we(we),
        .write_ptr(write_ptr),
        .w_addr(w_addr),
        .w_data(w_data)
    );

    // 100 MHz clock
    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end

    // Capture writes to fake cache (mimics I_CACHE behavior)
    always @(posedge clk) begin
        if (we) begin
            fake_cache[w_addr] <= w_data;
            $display("  [CACHE WRITE] addr=0x%08X, data=0x%08X @ time=%0t", w_addr, w_data, $time);
        end
    end

    // -------------------------------------------------------
    // Task: simulate UART delivering one byte
    //   DATA_U unconditionally transitions to WAIT_ACK_U
    //   in ONE cycle (increments wait_for_data, asserts clear).
    //   data_ready_uart MUST already be high when DATA_U executes.
    //   WAIT_ACK_U waits for !data_ready_uart, then clear<=0.
    //
    //   Strategy:
    //     1. Assert data + data_ready_uart BEFORE the FSM can
    //        enter DATA_U (the FSM needs at least 1 cycle to
    //        transition from wherever it is).
    //     2. Wait for FSM to reach WAIT_ACK_U (state 3).
    //     3. Deassert data_ready_uart so WAIT_ACK_U can proceed.
    //     4. Wait for FSM to leave WAIT_ACK_U.
    // -------------------------------------------------------
    task send_byte_uart;
        input [7:0] byte_val;
        begin
            @(negedge clk);
            data_in_uart = byte_val;
            data_ready_uart = 1;
            busy_uart = 1;

            // Wait for FSM to reach WAIT_ACK_U (it passed through DATA_U)
            wait (uut.state == WAIT_ACK_U);

            // Deassert data_ready so WAIT_ACK_U proceeds
            @(negedge clk);
            data_ready_uart = 0;

            // Wait for FSM to leave WAIT_ACK_U
            @(posedge clk);
            while (uut.state == WAIT_ACK_U) begin
                @(posedge clk);
            end
        end
    endtask

    // -------------------------------------------------------
    // Task: simulate SPI delivering one byte
    //   DATA_S unconditionally transitions to WAIT_ACK_S
    //   in ONE cycle (increments wait_for_data).
    //   data_ready_spi MUST already be high when DATA_S executes.
    //   WAIT_ACK_S waits for !data_ready_spi then proceeds.
    //
    //   Strategy: same as UART but without clear.
    // -------------------------------------------------------
    task send_byte_spi;
        input [7:0] byte_val;
        begin
            @(negedge clk);
            data_in_spi = byte_val;
            data_ready_spi = 1;
            busy_spi = 1;

            // Wait for FSM to reach WAIT_ACK_S
            wait (uut.state == WAIT_ACK_S);

            // Deassert data_ready so WAIT_ACK_S proceeds
            @(negedge clk);
            data_ready_spi = 0;

            // Wait for FSM to leave WAIT_ACK_S
            @(posedge clk);
            while (uut.state == WAIT_ACK_S) begin
                @(posedge clk);
            end
        end
    endtask

    // -------------------------------------------------------
    // Task: send a 32-bit word as 4 little-endian bytes (UART)
    //   PC_TRANSFER_U checks data_ready_uart|busy_uart.
    //   If more words follow, keep busy_uart=1.
    //   For last word, deassert busy so FSM goes to DONE.
    // -------------------------------------------------------
    task send_word_uart;
        input [31:0] word_val;
        input is_last_word;
        begin
            send_byte_uart(word_val[7:0]);
            send_byte_uart(word_val[15:8]);
            send_byte_uart(word_val[23:16]);
            send_byte_uart(word_val[31:24]);

            // After 4th byte: FSM goes LOAD_U -> PC_TRANSFER_U.
            // PC_TRANSFER_U checks data_ready_uart|busy_uart.
            // For the last word: deassert busy so FSM goes to DONE.
            if (is_last_word) begin
                @(negedge clk);
                busy_uart = 0;
                data_ready_uart = 0;
            end
        end
    endtask

    // -------------------------------------------------------
    // Task: send a 32-bit word as 4 little-endian bytes (SPI)
    //   PC_TRANSFER_S checks data_ready_spi|busy_spi.
    //   If more words follow, keep busy_spi=1.
    //   For last word, deassert busy so FSM goes to DONE.
    // -------------------------------------------------------
    task send_word_spi;
        input [31:0] word_val;
        input is_last_word;
        begin
            send_byte_spi(word_val[7:0]);
            send_byte_spi(word_val[15:8]);
            send_byte_spi(word_val[23:16]);
            send_byte_spi(word_val[31:24]);

            if (is_last_word) begin
                @(negedge clk);
                busy_spi = 0;
                data_ready_spi = 0;
            end
        end
    endtask

    // -------------------------------------------------------
    // Assertion helpers
    // -------------------------------------------------------
    task check;
        input [255:0] name;
        input [31:0] actual;
        input [31:0] expected;
        begin
            if (actual === expected) begin
                $display("[PASS] %0s = 0x%08X", name, actual);
                test_pass = test_pass + 1;
            end else begin
                $display("[FAIL] %0s = 0x%08X (expected 0x%08X)", name, actual, expected);
                test_fail = test_fail + 1;
            end
        end
    endtask

    task check_1bit;
        input [255:0] name;
        input actual;
        input expected;
        begin
            if (actual === expected) begin
                $display("[PASS] %0s = %b", name, actual);
                test_pass = test_pass + 1;
            end else begin
                $display("[FAIL] %0s = %b (expected %b)", name, actual, expected);
                test_fail = test_fail + 1;
            end
        end
    endtask

    // -------------------------------------------------------
    // Main test sequence
    // -------------------------------------------------------
    initial begin
        // Initialize
        reset           = 1;
        data_ready_uart = 0;
        data_ready_spi  = 0;
        busy_uart       = 0;
        busy_spi        = 0;
        data_in_uart    = 8'h00;
        data_in_spi     = 8'h00;

        repeat (4) @(posedge clk);
        @(negedge clk);
        reset = 0;

        repeat (2) @(posedge clk);
        $display("\n--- TEST 0: Reset state ---");
        check_1bit("cpu_halt", cpu_halt, 1'b0);
        check_1bit("we",       we,       1'b0);
        check_1bit("done",     done,     1'b0);
        check("write_ptr", write_ptr, `UART_ADDR);

        // =============================================
        // TEST 1: Load 3 instructions via UART
        // =============================================
        $display("\n--- TEST 1: Load 3 instructions via UART ---");

        send_word_uart(32'hDEADBEEF, 0);  // word 0
        repeat (5) @(posedge clk);

        send_word_uart(32'hCAFEBABE, 0);  // word 1
        repeat (5) @(posedge clk);

        send_word_uart(32'h12345678, 1);  // word 2 (last)

        // Wait for DONE pulse
        repeat (15) @(posedge clk);

        $display("  Verifying cache contents (UART):");
        check("cache[UART_ADDR+0]", fake_cache[`UART_ADDR],     32'hDEADBEEF);
        check("cache[UART_ADDR+4]", fake_cache[`UART_ADDR + 4], 32'hCAFEBABE);
        check("cache[UART_ADDR+8]", fake_cache[`UART_ADDR + 8], 32'h12345678);
        check_1bit("done_seen", done_seen, 1'b1);

        // =============================================
        // TEST 2: cpu_halt deasserts after UART burst
        // =============================================
        $display("\n--- TEST 2: cpu_halt deasserts after UART burst ---");
        repeat (5) @(posedge clk);
        check_1bit("cpu_halt", cpu_halt, 1'b0);

        // =============================================
        // TEST 3: Load 2 instructions via SPI
        // =============================================
        $display("\n--- TEST 3: Load 2 instructions via SPI ---");

        send_word_spi(32'hAAAABBBB, 0);   // word 0
        repeat (5) @(posedge clk);

        send_word_spi(32'hCCCCDDDD, 1);   // word 1 (last)

        // Wait for DONE pulse
        repeat (15) @(posedge clk);

        $display("  Verifying cache contents (SPI):");
        check("cache[SPI_ADDR+0]", fake_cache[`SPI_ADDR],     32'hAAAABBBB);
        check("cache[SPI_ADDR+4]", fake_cache[`SPI_ADDR + 4], 32'hCCCCDDDD);
        check_1bit("done_seen", done_seen, 1'b1);

        // =============================================
        // TEST 4: cpu_halt deasserts after SPI burst
        // =============================================
        $display("\n--- TEST 4: cpu_halt deasserts after SPI burst ---");
        repeat (5) @(posedge clk);
        check_1bit("cpu_halt", cpu_halt, 1'b0);

        // =============================================
        // TEST 5: Sequential — UART session then SPI session
        //   (mid-session switching is not supported in the
        //    new split-FSM design, so we test two back-to-back
        //    sessions instead)
        // =============================================
        $display("\n--- TEST 5: Sequential UART then SPI sessions ---");

        // First: one word via UART
        send_word_uart(32'h11223344, 1);  // word 0 via UART (last)
        repeat (15) @(posedge clk);

        $display("  Verifying UART session:");
        check("cache[UART_ADDR+0]", fake_cache[`UART_ADDR], 32'h11223344);
        check_1bit("done_seen", done_seen, 1'b1);
        check_1bit("cpu_halt", cpu_halt, 1'b0);

        // Then: one word via SPI
        send_word_spi(32'h55667788, 1);   // word 0 via SPI (last)
        repeat (15) @(posedge clk);

        $display("  Verifying SPI session:");
        check("cache[SPI_ADDR+0]", fake_cache[`SPI_ADDR], 32'h55667788);
        check_1bit("done_seen", done_seen, 1'b1);
        check_1bit("cpu_halt", cpu_halt, 1'b0);

        // =============================================
        // TEST 6: write_ptr resets for new session
        //   After DONE -> STALL, if UART triggers,
        //   write_ptr should be UART_ADDR.
        // =============================================
        $display("\n--- TEST 6: write_ptr resets for new UART session ---");
        repeat (5) @(posedge clk);
        // Start a new UART byte to trigger STALL -> START_U
        @(negedge clk);
        data_in_uart = 8'hAA;
        data_ready_uart = 1;
        busy_uart = 1;
        // Wait for FSM to enter START_U
        wait (uut.state == START_U);
        @(posedge clk);
        check("write_ptr", write_ptr, `UART_ADDR);
        // Clean up — deassert and let FSM settle
        @(negedge clk);
        data_ready_uart = 0;
        busy_uart = 0;
        // Force reset to get clean state for next test
        @(negedge clk);
        reset = 1;
        repeat (4) @(posedge clk);
        @(negedge clk);
        reset = 0;
        repeat (2) @(posedge clk);

        // =============================================
        // TEST 7: UART has priority when both trigger
        //   In STALL, UART `if` is checked before SPI
        //   `else if`, so UART wins when both assert.
        // =============================================
        $display("\n--- TEST 7: UART priority when both assert simultaneously ---");
        @(negedge clk);
        data_in_spi  = 8'hFF;
        data_in_uart = 8'h00;
        data_ready_uart = 1;
        data_ready_spi  = 1;
        busy_uart = 1;
        busy_spi  = 1;
        @(posedge clk); // STALL evaluates: UART if hits first
        @(posedge clk); // now in START_U
        check("write_ptr (UART wins)", write_ptr, `UART_ADDR);
        // Verify FSM took the UART path
        if (uut.state == START_U || uut.state == DATA_U) begin
            $display("[PASS] FSM entered UART path (state=%0d)", uut.state);
            test_pass = test_pass + 1;
        end else begin
            $display("[FAIL] FSM did not enter UART path (state=%0d, expected %0d or %0d)", uut.state, START_U, DATA_U);
            test_fail = test_fail + 1;
        end

        // Clean up
        @(negedge clk);
        data_ready_uart = 0;
        data_ready_spi  = 0;
        busy_uart = 0;
        busy_spi  = 0;
        @(negedge clk);
        reset = 1;
        repeat (4) @(posedge clk);
        @(negedge clk);
        reset = 0;
        repeat (2) @(posedge clk);

        // =============================================
        // Summary
        // =============================================
        $display("\n========================================");
        $display("  TEST RESULTS: %0d passed, %0d failed", test_pass, test_fail);
        $display("========================================\n");

        #100;
        $finish;
    end

    // Timeout watchdog
    initial begin
        #1000000;
        $display("[TIMEOUT] Simulation exceeded time limit");
        $finish;
    end

    // VCD dump
    initial begin
        $dumpfile("PROGRAM_LOADER_TB.vcd");
        $dumpvars(0, PROGRAM_LOADER_TB);
    end

endmodule
