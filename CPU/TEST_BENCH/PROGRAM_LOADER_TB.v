`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module PROGRAM_LOADER_TB ();
    reg clk;
    reg reset;
    reg data_ready;
    reg busy;
    reg [7:0] data_in;
    wire cpu_halt;
    wire clear;
    wire we;
    wire [`DATA_WIDTH-1:0] w_addr;
    wire [`DATA_WIDTH-1:0] w_data;

    // Simulated I_CACHE memory (to verify writes)
    reg [`DATA_WIDTH-1:0] fake_cache [0:`CACHE_SIZE];

    // Track test results
    integer test_pass = 0;
    integer test_fail = 0;

    PROGRAM_LOADER uut (
        .clk(clk),
        .reset(reset),
        .data_ready(data_ready),
        .busy(busy),
        .data_in(data_in),
        .cpu_halt(cpu_halt),
        .clear(clear),
        .we(we),
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
            $display("  [CACHE WRITE] addr=%0d, data=0x%08X", w_addr, w_data);
        end
    end

    // Task: simulate UART delivering one byte
    task send_byte;
        input [7:0] byte_val;
        begin
            @(negedge clk);
            data_in = byte_val;
            data_ready = 1;
            busy = 1;

            wait (clear == 1);
            @(posedge clk);
            
            @(negedge clk);
            data_ready = 0;

            wait (clear == 0);
            @(posedge clk);
        end
    endtask

    // Task: send a 32-bit word as 4 little-endian bytes
    task send_word;
        input [31:0] word_val;
        input is_last_word;
        begin
            send_byte(word_val[7:0]);
            send_byte(word_val[15:8]);
            send_byte(word_val[23:16]);
            send_byte(word_val[31:24]);

            if (is_last_word) begin
                @(negedge clk);
                busy = 0;
                data_ready = 0;
            end
        end
    endtask

    // Assertion helpers
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

    // Main test sequence
    initial begin
        // Initialize
        reset = 1;
        data_ready = 0;
        busy = 0;
        data_in = 8'h00;

        repeat (4) @(posedge clk);
        @(negedge clk);
        reset = 0;

        repeat (2) @(posedge clk);
        $display("\n--- TEST 0: Reset state ---");
        check_1bit("cpu_halt", cpu_halt, 1'b0);
        check_1bit("we", we, 1'b0);

        // =============================================
        // TEST 1: Load 3 instructions in one burst
        // =============================================
        $display("\n--- TEST 1: Load 3 instructions in one burst ---");
        send_word(32'hDEADBEEF, 0);  // addr 0
        repeat (3) @(posedge clk);   // let LOAD/we happen
        
        send_word(32'hCAFEBABE, 0);  // addr 1
        repeat (3) @(posedge clk);
        
        send_word(32'h12345678, 1);  // addr 2 (last word)
        repeat (3) @(posedge clk);

        // Wait for writes to complete
        repeat (5) @(posedge clk);

        $display("  Verifying cache contents:");
        check("cache[UART_ADDR]",   fake_cache[`UART_ADDR],   32'hDEADBEEF);
        check("cache[UART_ADDR+1]", fake_cache[`UART_ADDR+1], 32'hCAFEBABE);
        check("cache[UART_ADDR+2]", fake_cache[`UART_ADDR+2], 32'h12345678);

        // =============================================
        // TEST 2: cpu_halt deasserts after burst
        // =============================================
        $display("\n--- TEST 2: cpu_halt deasserts after burst ---");
        repeat (20) @(posedge clk);
        check_1bit("cpu_halt", cpu_halt, 1'b0);

        // =============================================
        // TEST 3: Write pointer resets — new session starts from addr 0
        // =============================================
        $display("\n--- TEST 3: New session starts from addr 0 ---");
        send_word(32'hAAAABBBB, 0);  // should go to addr 0 again
        repeat (3) @(posedge clk);

        send_word(32'hCCCCDDDD, 1);  // should go to addr 1
        repeat (5) @(posedge clk);

        check("cache[UART_ADDR]",   fake_cache[`UART_ADDR],   32'hAAAABBBB);
        check("cache[UART_ADDR+1]", fake_cache[`UART_ADDR+1], 32'hCCCCDDDD);

        // =============================================
        // TEST 4: cpu_halt deasserts again
        // =============================================
        $display("\n--- TEST 4: cpu_halt deasserts again ---");
        repeat (20) @(posedge clk);
        check_1bit("cpu_halt", cpu_halt, 1'b0);

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
