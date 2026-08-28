`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
`timescale 1ns / 1ps

module D_CACHE_tb;

    // ------------------------------------------------------------------
    // DUT interface (new D_CACHE.v: miss/hit handshake, no write port)
    // ------------------------------------------------------------------
    reg  clk;
    reg  reset;
    reg  valid;                             // memory ack: data_in holds the line
    wire miss;                              // asserted on a cache miss
    wire stall;                             // pipeline must stall while missing
    reg  [`DATA_WIDTH-1:0]        data_in;  // line returned by memory on miss
    reg  [`CACHE_ADDRESS-1:0]     r_addr;   // read address (byte-addressed)
    reg  [`FUNCT3_WIDTH-1:0]      funct3;   // load size/unsigned-ness
    wire [`DATA_WIDTH-1:0]        data_out;

    D_CACHE uut (
        .clk      (clk),
        .reset    (reset),
        .valid    (valid),
        .miss     (miss),
        .stall    (stall),
        .data_in  (data_in),
        .r_addr   (r_addr),
        .funct3   (funct3),
        .data_out (data_out)
    );

    // ------------------------------------------------------------------
    // Backdoor "main memory" model (word-addressable)
    // On a miss the TB feeds data_in = mem[addr>>2] to fill the line.
    // ------------------------------------------------------------------
    reg [`DATA_WIDTH-1:0] mem [0:4095];

    // Test infrastructure
    integer pass_count = 0;
    integer fail_count = 0;
    integer test_count = 0;
    reg     saw_miss;         // set inside load task if a miss/stall occurred

    // funct3 codes
    localparam [2:0] F3_LB = 3'b000,
                     F3_LH = 3'b001,
                     F3_LW = 3'b010,
                     F3_LBU= 3'b100,
                     F3_LHU= 3'b101;

    localparam CLK_PERIOD = 10;

    // ------------------------------------------------------------------
    // Clock
    // ------------------------------------------------------------------
    initial begin
        clk = 0;
        forever #(CLK_PERIOD/2) clk = ~clk;
    end

    // ------------------------------------------------------------------
    // Force the internal cache ways to zero so valid/LRU bits are
    // deterministic at start (the RTL only clears the FSM on reset).
    // This is testbench-only, requires iverilog hierarchical access.
    // ------------------------------------------------------------------
    initial begin
        integer i;
        for (i = 0; i <= `D_CACHE_SIZE; i = i + 1) begin
            uut.way0_cache[i] = 0;
            uut.way1_cache[i] = 0;
        end
    end

    // ------------------------------------------------------------------
    // Helpers
    // ------------------------------------------------------------------

    // Write a word into the backdoor memory (testbench-only).
    task write_mem;
        input [`CACHE_ADDRESS-1:0] addr;
        input [`DATA_WIDTH-1:0]    word;
        begin
            mem[addr[31:2]] = word;
        end
    endtask

    // Result checker: verifies data_out value.
    task check_data;
        input [`DATA_WIDTH-1:0] expected;
        input [`DATA_WIDTH-1:0] actual;
        input [200*8:0]         name;
        begin
            test_count = test_count + 1;
            if (expected === actual) begin
                $display("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h",
                         test_count, name, expected, actual);
                pass_count = pass_count + 1;
            end else begin
                $display("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h",
                         test_count, name, expected, actual);
                fail_count = fail_count + 1;
            end
        end
    endtask

    // Hit/miss checker: asserts the access behaved as declared.
    // expect_miss: 1 = must miss, 0 = must hit.
    task check_hit_miss;
        input [1:0]      expect_miss;   // 1/0, X-free to keep === clean
        input            got_miss;
        input [200*8:0]  name;
        begin
            test_count = test_count + 1;
            if (expect_miss == got_miss) begin
                $display("[PASS] %0d: %s | hit/miss OK (%s)",
                         test_count, name, (expect_miss ? "MISS expected and got" : "HIT expected and got"));
                pass_count = pass_count + 1;
            end else begin
                $display("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)",
                         test_count, name, (expect_miss ? "MISS" : "HIT"), (got_miss ? "MISS" : "HIT"));
                fail_count = fail_count + 1;
            end
        end
    endtask

    // Perform a load from addr with funct3 using the miss/fill handshake,
    // then verify (a) data_out value and (b) hit/miss behavior.
    // expect_miss: 1 = this access should miss, 0 = should hit.
    task load;
        input [`CACHE_ADDRESS-1:0] addr;
        input [`FUNCT3_WIDTH-1:0]  f3;
        input [`DATA_WIDTH-1:0]    expected;
        input [1:0]                expect_miss;
        input [200*8:0]            name;
        begin
            r_addr = addr;
            funct3 = f3;
            valid  = 0;
            saw_miss = 0;

            @(posedge clk); #1;

            if (stall) begin
                // A miss: the DUT is in START, waiting for the line.
                saw_miss = 1;
                valid  = 1;
                data_in = mem[addr[31:2]];   // memory returns the cache line
                @(posedge clk); #1;          // START -> DONE (line written)
                valid = 0;
                @(posedge clk); #1;          // DONE -> IDLE (miss/stall cleared)
                @(posedge clk); #1;          // IDLE: now a hit, latch d_cache
            end else begin
                // Already resident: IDLE latches d_cache this edge.
                @(posedge clk); #1;
            end

            check_data(expected, data_out, name);
            check_hit_miss(expect_miss, saw_miss, name);
        end
    endtask

    // ------------------------------------------------------------------
    // Main test sequence
    // ------------------------------------------------------------------
    initial begin
        $dumpfile("D_CACHE_tb.vcd");
        $dumpvars(0, D_CACHE_tb);
        $display("==============================================");
        $display("  D_CACHE  new-handshake testbench (functional)");
        $display("==============================================");

        // T1 performs the initial reset sequence.

        // ---------------------------------------------------------------
        // T1: Reset leaves miss/stall deasserted and idle
        // ---------------------------------------------------------------
        $display("\n--- Test 1: Reset clears handshake ---");
        // Sample while reset is still held: miss/stall must be deasserted.
        reset  = 1;
        valid  = 0;
        data_in= 0;
        r_addr = 0;
        funct3 = F3_LW;
        @(posedge clk); #1;
        @(posedge clk); #1;
        check_data(1'b0, stall, "stall==0 during reset");
        check_data(1'b0, miss,  "miss ==0 during reset");
        reset  = 0;
        @(posedge clk); #1;

        // ---------------------------------------------------------------
        // ---------------------------------------------------------------
        // T2: First access is a miss -> fill from memory -> then hit
        // ---------------------------------------------------------------
        $display("\n--- Test 2: Miss-fill handshake (cold miss) ---");
        write_mem(32'h0000_0020, 32'hDEAD_BEEF);
        load(32'h0000_0020, F3_LW, 32'hDEAD_BEEF, 1, "miss-fill 0x20, LW");

        // ---------------------------------------------------------------
        // T3: Re-read of the same line is a hit (no miss/stall)
        // ---------------------------------------------------------------
        $display("\n--- Test 3: Hit on re-access ---");
        load(32'h0000_0020, F3_LW, 32'hDEAD_BEEF, 0, "re-read 0x20, LW");

        // ---------------------------------------------------------------
        // T4: Word loads across different sets (all cold -> all miss)
        // ---------------------------------------------------------------
        $display("\n--- Test 4: LW across sets (cold misses) ---");
        write_mem(32'h0000_0000, 32'h1234_5678);
        write_mem(32'h0000_0008, 32'hCAFE_BABE);
        write_mem(32'h0000_0100, 32'h89AB_CDEF);   // a different set
        load(32'h0000_0000, F3_LW, 32'h1234_5678, 1, "LW 0x00 (cold)");
        load(32'h0000_0008, F3_LW, 32'hCAFE_BABE, 1, "LW 0x08 (cold)");
        load(32'h0000_0100, F3_LW, 32'h89AB_CDEF, 1, "LW 0x100 (cold)");
        load(32'h0000_0100, F3_LW, 32'h89AB_CDEF, 0, "re-read 0x100 (hit)");

        // ---------------------------------------------------------------
        // T5: LB sign extension  (0x40 cold miss, then 0x41..0x43 hits)
        // word 0x807FFF01 at 0x40  ->  byte3=0x80 byte2=0x7F byte1=0xFF byte0=0x01
        // ---------------------------------------------------------------
        $display("\n--- Test 5: LB sign extension ---");
        write_mem(32'h0000_0040, 32'h807F_FF01);
        load(32'h0000_0040, F3_LB,  32'h0000_0001, 1, "LB 0x40 byte0 (cold)");
        load(32'h0000_0041, F3_LB,  32'hFFFF_FFFF, 0, "LB 0x41 byte1 (hit)");
        load(32'h0000_0042, F3_LB,  32'h0000_007F, 0, "LB 0x42 byte2 (hit)");
        load(32'h0000_0043, F3_LB,  32'hFFFF_FF80, 0, "LB 0x43 byte3 (hit)");

        // ---------------------------------------------------------------
        // T6: LBU zero extension (all hits, line resident)
        // ---------------------------------------------------------------
        $display("\n--- Test 6: LBU zero extension ---");
        load(32'h0000_0040, F3_LBU, 32'h0000_0001, 0, "LBU 0x40 byte0 (hit)");
        load(32'h0000_0043, F3_LBU, 32'h0000_0080, 0, "LBU 0x43 byte3 (hit)");

        // ---------------------------------------------------------------
        // T7: LH sign extension  (0x60 cold miss, 0x62 hit same line)
        // word 0x8001_7FFF at 0x60 -> lower half 0x7FFF (pos), upper 0x8001 (neg)
        // ---------------------------------------------------------------
        $display("\n--- Test 7: LH sign extension ---");
        write_mem(32'h0000_0060, 32'h8001_7FFF);
        load(32'h0000_0060, F3_LH,  32'h0000_7FFF, 1, "LH 0x60 lower (cold)");
        load(32'h0000_0062, F3_LH,  32'hFFFF_8001, 0, "LH 0x62 upper (hit)");

        // ---------------------------------------------------------------
        // T8: LHU zero extension (all hits)
        // ---------------------------------------------------------------
        $display("\n--- Test 8: LHU zero extension ---");
        load(32'h0000_0060, F3_LHU, 32'h0000_7FFF, 0, "LHU 0x60 lower (hit)");
        load(32'h0000_0062, F3_LHU, 32'h0000_8001, 0, "LHU 0x62 upper (hit)");

        // ---------------------------------------------------------------
        // T9: Independent words / separate sets + re-read hit
        // ---------------------------------------------------------------
        $display("\n--- Test 9: Independent words ---");
        write_mem(32'h0000_0080, 32'hAAAA_AAAA);
        write_mem(32'h0000_0084, 32'hBBBB_BBBB);
        load(32'h0000_0080, F3_LW, 32'hAAAA_AAAA, 1, "LW 0x80 (cold)");
        load(32'h0000_0084, F3_LW, 32'hBBBB_BBBB, 1, "LW 0x84 (cold)");
        load(32'h0000_0080, F3_LW, 32'hAAAA_AAAA, 0, "re-read 0x80 (hit)");

        // ---------------------------------------------------------------
        // T10: Highest set index (set = addr[8:2], max = 127 -> 0x1FC)
        // ---------------------------------------------------------------
        $display("\n--- Test 10: Boundary set ---");
        write_mem(32'h0000_01FC, 32'hBAAD_F00D);
        load(32'h0000_01FC, F3_LW, 32'hBAAD_F00D, 1, "LW 0x1FC (set 127, cold)");
        load(32'h0000_01FC, F3_LBU, 32'h0000_000D, 0, "LBU 0x1FC byte0 (hit)");

        // ---------------------------------------------------------------
        // T11: Same-set byte-address reuse (0x40..0x43 map to set 0x10)
        // ---------------------------------------------------------------
        $display("\n--- Test 11: Same-set byte addressing ---");
        load(32'h0000_0041, F3_LBU, 32'h0000_00FF, 0, "same-set byte1 LBU (hit)");

        // ---------------------------------------------------------------
        // T12: 2-way set-associativity. A and B share a set (differ by
        //      0x200 -> same set[8:2], different tag). Both must HIT after
        //      their first cold fill, proving way0 AND way1 are both used.
        //      A=0x3000 set 0x40 tag 0x18 ; B=0x3200 set 0x40 tag 0x19
        // ---------------------------------------------------------------
        $display("\n--- Test 12: 2-way associativity (A+B same set both hit) ---");
        write_mem(32'h0000_3000, 32'h1111_1111);
        write_mem(32'h0000_3200, 32'h2222_2222);
        load(32'h0000_3000, F3_LW, 32'h1111_1111, 1, "A 0x3000 (cold)");
        load(32'h0000_3200, F3_LW, 32'h2222_2222, 1, "B 0x3200 (cold)");
        load(32'h0000_3000, F3_LW, 32'h1111_1111, 0, "re-A 0x3000 (hit)");
        load(32'h0000_3200, F3_LW, 32'h2222_2222, 0, "re-B 0x3200 (hit)");

        // ---------------------------------------------------------------
        // T13: Capacity conflict + eviction. A third address C (0x3400,
        //      tag 0x1A) in the SAME set 0x40 must MISS (both ways full),
        //      evict the LRU way, then C re-reads as a HIT while the
        //      evicted line (A) is now a MISS again.
        // ---------------------------------------------------------------
        $display("\n--- Test 13: Capacity miss + eviction ---");
        write_mem(32'h0000_3400, 32'h3333_3333);
        load(32'h0000_3400, F3_LW, 32'h3333_3333, 1, "C 0x3400 (capacity miss)");
        load(32'h0000_3400, F3_LW, 32'h3333_3333, 0, "re-C 0x3400 (hit)");
        load(32'h0000_3000, F3_LW, 32'h1111_1111, 1, "A 0x3000 evicted (miss)");

        // ---------------------------------------------------------------
        // Summary
        // ---------------------------------------------------------------
        #20;
        $display("\n==============================================");
        $display("                Test Summary");
        $display("==============================================");
        $display("Total Tests: %0d", test_count);
        $display("Passed:      %0d", pass_count);
        $display("Failed:      %0d", fail_count);
        if (fail_count == 0)
            $display("\n*** ALL TESTS PASSED ***");
        else
            $display("\n*** SOME TESTS FAILED ***");
        $display("==============================================\n");

        $finish;
    end

endmodule