`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module PROGRAM_LOADER_TB ();
    reg clk;
    reg reset;
    reg data_ready;
    reg busy;
    reg comm_slct;           // 1 = SPI, 0 = UART
    reg [7:0] data_in_uart;
    reg [7:0] data_in_spi;
    wire done;
    wire cpu_halt;
    wire clear;
    wire we;
    wire [`DATA_WIDTH-1:0] write_ptr;
    wire [`DATA_WIDTH-1:0] w_addr;
    wire [`DATA_WIDTH-1:0] w_data;

    // Simulated I_CACHE memory (to verify writes)
    reg [`DATA_WIDTH-1:0] fake_cache [0:8191];

    // Track test results
    integer test_pass = 0;
    integer test_fail = 0;

    // Sticky done flag — captures the 1-cycle done pulse
    reg done_seen;
    always @(posedge clk) begin
        if (reset || (uut.state == 1)) // clear on reset or entering START
            done_seen <= 0;
        else if (done)
            done_seen <= 1;
    end

    PROGRAM_LOADER uut (
        .clk(clk),
        .reset(reset),
        .data_ready(data_ready),
        .busy(busy),
        .comm_slct(comm_slct),
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
    // Task: simulate UART delivering one byte (comm_slct = 0)
    //   Uses clear handshake
    // -------------------------------------------------------
    task send_byte_uart;
        input [7:0] byte_val;
        begin
            @(negedge clk);
            data_in_uart = byte_val;
            data_ready = 1;
            busy = 1;

            // Wait for FSM to acknowledge (clear goes high in DATA->WAIT_ACK)
            wait (clear == 1);
            @(posedge clk);

            // Now deassert data_ready
            @(negedge clk);
            data_ready = 0;

            // Wait for FSM to finish WAIT_ACK (clear goes low)
            wait (clear == 0);
            @(posedge clk);
        end
    endtask

    // -------------------------------------------------------
    // Task: simulate SPI delivering one byte (comm_slct = 1)
    //   No clear handshake.
    //   FSM: DATA sees data_ready=1 -> latches -> WAIT_ACK
    //        WAIT_ACK sees !data_ready -> proceed
    //   We wait until FSM is in DATA state (state==2) before
    //   pulsing data_ready.
    // -------------------------------------------------------
    task send_byte_spi;
        input [7:0] byte_val;
        begin
            // Place data on the bus
            data_in_spi = byte_val;
            busy = 1;

            // Wait until FSM is in DATA state (state 2) and ready to latch
            @(negedge clk);
            while (uut.state != 2) begin
                @(negedge clk);
            end

            // Assert data_ready — FSM will see it on the next posedge
            data_ready = 1;

            // posedge: DATA latches the byte, transitions to WAIT_ACK
            @(posedge clk);

            // Deassert data_ready on the following negedge
            @(negedge clk);
            data_ready = 0;

            // posedge: WAIT_ACK sees !data_ready, transitions to DATA or LOAD
            @(posedge clk);
            @(posedge clk); // one extra for state transition to settle
        end
    endtask

    // -------------------------------------------------------
    // Task: send a 32-bit word as 4 little-endian bytes (UART)
    // -------------------------------------------------------
    task send_word_uart;
        input [31:0] word_val;
        input is_last_word;
        begin
            send_byte_uart(word_val[7:0]);
            send_byte_uart(word_val[15:8]);
            send_byte_uart(word_val[23:16]);
            send_byte_uart(word_val[31:24]);

            // After 4th byte: FSM goes LOAD -> PC_TRANSFER.
            // PC_TRANSFER checks data_ready|busy.
            // For the last word: deassert busy so FSM goes to DONE.
            if (is_last_word) begin
                @(negedge clk);
                busy = 0;
                data_ready = 0;
            end
        end
    endtask

    // -------------------------------------------------------
    // Task: send a 32-bit word as 4 little-endian bytes (SPI)
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
                busy = 0;
                data_ready = 0;
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
        reset       = 1;
        data_ready  = 0;
        busy        = 0;
        comm_slct   = 0;   // default UART
        data_in_uart = 8'h00;
        data_in_spi  = 8'h00;

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
        $display("\n--- TEST 1: Load 3 instructions via UART (comm_slct=0) ---");
        comm_slct = 0;

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
        // TEST 2: cpu_halt deasserts after burst
        // =============================================
        $display("\n--- TEST 2: cpu_halt deasserts after UART burst ---");
        repeat (5) @(posedge clk);
        check_1bit("cpu_halt", cpu_halt, 1'b0);

        // =============================================
        // TEST 3: Load 2 instructions via SPI
        // =============================================
        $display("\n--- TEST 3: Load 2 instructions via SPI (comm_slct=1) ---");
        comm_slct = 1;

        send_word_spi(32'hAAAABBBB, 0);   // word 0
        repeat (5) @(posedge clk);

        send_word_spi(32'hCCCCDDDD, 1);   // word 1 (last)

        // Wait for DONE pulse
        repeat (15) @(posedge clk);

        $display("  Verifying cache contents (SPI):");
        check("cache[UART_ADDR+0]", fake_cache[`UART_ADDR],     32'hAAAABBBB);
        check("cache[UART_ADDR+4]", fake_cache[`UART_ADDR + 4], 32'hCCCCDDDD);
        check_1bit("done_seen", done_seen, 1'b1);

        // =============================================
        // TEST 4: cpu_halt deasserts after SPI burst
        // =============================================
        $display("\n--- TEST 4: cpu_halt deasserts after SPI burst ---");
        repeat (5) @(posedge clk);
        check_1bit("cpu_halt", cpu_halt, 1'b0);

        // =============================================
        // TEST 5: Mixed — load first word via UART,
        //         then switch to SPI for second word
        // =============================================
        $display("\n--- TEST 5: Mixed UART then SPI session ---");
        comm_slct = 0;
        send_word_uart(32'h11223344, 0);  // word 0 via UART
        repeat (5) @(posedge clk);

        // Switch to SPI mid-session
        comm_slct = 1;
        send_word_spi(32'h55667788, 1);   // word 1 via SPI (last)

        repeat (15) @(posedge clk);

        $display("  Verifying cache contents (mixed):");
        check("cache[UART_ADDR+0]", fake_cache[`UART_ADDR],     32'h11223344);
        check("cache[UART_ADDR+4]", fake_cache[`UART_ADDR + 4], 32'h55667788);

        // =============================================
        // TEST 6: write_ptr resets after session
        // =============================================
        $display("\n--- TEST 6: write_ptr resets for new session ---");
        repeat (5) @(posedge clk);
        check("write_ptr", write_ptr, `UART_ADDR);

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
        #500000;
        $display("[TIMEOUT] Simulation exceeded time limit");
        $finish;
    end

    // VCD dump
    initial begin
        $dumpfile("PROGRAM_LOADER_TB.vcd");
        $dumpvars(0, PROGRAM_LOADER_TB);
    end

endmodule
