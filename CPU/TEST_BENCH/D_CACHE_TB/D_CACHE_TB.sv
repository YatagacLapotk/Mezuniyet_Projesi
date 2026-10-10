`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
`timescale 1ns / 1ps

module D_CACHE_tb;

    // ------------------------------------------------------------------
    // DUT interface (current D_CACHE.v: write-back, 2-way, mem handshake)
    // ------------------------------------------------------------------
    reg  clk;
    reg  reset;

    // Memory side
    reg                          mem_ack;
    reg  [`DATA_WIDTH-1:0]       mem_rdata;
    wire [`CACHE_ADDRESS-1:0]    memory_addr;
    wire [`DATA_WIDTH-1:0]       mem_wdata;
    wire                         mem_req;
    wire                         mem_we;

    // CPU side
    reg  [`DATA_WIDTH-1:0]       data_in_cpu;   // store payload (byte-lane aligned)
    reg  [`CACHE_ADDRESS-1:0]    cpu_addr;
    reg  [`FUNCT3_WIDTH-1:0]     cpu_funct3;
    reg                          cpu_we;
    reg                          cpu_req;
    wire                         stall;
    wire [`DATA_WIDTH-1:0]       data_out_cpu;

    D_CACHE uut (
        .clk         (clk),
        .reset       (reset),
        .mem_ack     (mem_ack),
        .mem_rdata   (mem_rdata),
        .memory_addr (memory_addr),
        .mem_wdata   (mem_wdata),
        .mem_req     (mem_req),
        .mem_we      (mem_we),
        .data_in_cpu (data_in_cpu),
        .cpu_addr    (cpu_addr),
        .cpu_funct3  (cpu_funct3),
        .cpu_we      (cpu_we),
        .cpu_req     (cpu_req),
        .stall       (stall),
        .data_out_cpu(data_out_cpu)
    );

    // ------------------------------------------------------------------
    // Backdoor main memory model (word-addressable) + ack generator.
    // While mem_req is high, a 1-cycle mem_ack pulse is produced every
    // MEM_LAT cycles. On the pulse: mem_we=1 -> write mem_wdata,
    // mem_we=0 -> return mem[memory_addr] on mem_rdata.
    // ------------------------------------------------------------------
    localparam MEM_LAT = 2;
    reg [`DATA_WIDTH-1:0] mem [0:4095];
    integer mem_cnt;
    integer mem_rd_count;
    integer mem_wr_count;

    initial begin
        mem_ack      = 0;
        mem_rdata    = 0;
        mem_cnt      = 0;
        mem_rd_count = 0;
        mem_wr_count = 0;
    end

    always @(posedge clk) begin
        mem_ack <= 1'b0;
        if (reset || !mem_req) begin
            mem_cnt <= 0;
        end else begin
            mem_cnt <= mem_cnt + 1;
            if (mem_cnt == MEM_LAT-1) begin
                mem_cnt <= 0;
                mem_ack <= 1'b1;
                if (mem_we) begin
                    mem[memory_addr[31:2]] <= mem_wdata;
                    mem_wr_count = mem_wr_count + 1;
                end else begin
                    mem_rdata <= mem[memory_addr[31:2]];
                    mem_rd_count = mem_rd_count + 1;
                end
            end
        end
    end

    // ------------------------------------------------------------------
    // Test infrastructure
    // ------------------------------------------------------------------
    integer pass_count = 0;
    integer fail_count = 0;
    integer test_count = 0;
    reg     saw_miss;
    reg [`DATA_WIDTH-1:0] rdata;

    // funct3 codes (loads and stores)
    localparam [2:0] F3_B  = 3'b000,   // LB / SB
                     F3_H  = 3'b001,   // LH / SH
                     F3_W  = 3'b010,   // LW / SW
                     F3_BU = 3'b100,
                     F3_HU = 3'b101;

    localparam CLK_PERIOD = 10;

    initial begin
        clk = 0;
        forever #(CLK_PERIOD/2) clk = ~clk;
    end

    // Watchdog
    initial begin
        #2000000;
        $display("[FAIL] watchdog timeout (DUT stuck, stall never released?)");
        $finish;
    end

    // Clear cache arrays so valid/dirty/LRU bits are deterministic.
    // Testbench-only hierarchical access.
    initial begin : init_cache
        integer i;
        for (i = 0; i <= `D_CACHE_SIZE; i = i + 1) begin
            uut.way0_cache[i] = 0;
            uut.way1_cache[i] = 0;
        end
    end

    // ------------------------------------------------------------------
    // Helpers
    // ------------------------------------------------------------------
    task write_mem;
        input [`CACHE_ADDRESS-1:0] addr;
        input [`DATA_WIDTH-1:0]    word;
        begin
            mem[addr[31:2]] = word;
        end
    endtask

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

    task check_hit_miss;
        input            expect_miss;
        input            got_miss;
        input [200*8:0]  name;
        begin
            test_count = test_count + 1;
            if (expect_miss === got_miss) begin
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

    // One CPU access. Holds cpu_req until stall releases, then gives one
    // more edge so the hit is serviced (load data latched / store merged).
    task access;
        input [`CACHE_ADDRESS-1:0] addr;
        input [`FUNCT3_WIDTH-1:0]  f3;
        input                      we;
        input [`DATA_WIDTH-1:0]    wdata;
        begin
            cpu_addr    = addr;
            cpu_funct3  = f3;
            cpu_we      = we;
            data_in_cpu = wdata;
            cpu_req     = 1;
            saw_miss    = 0;
            #1;
            if (stall) saw_miss = 1;
            while (stall) begin
                @(posedge clk); #1;
            end
            @(posedge clk); #1;           // hit serviced on this edge
            rdata   = data_out_cpu;
            cpu_req = 0;
            cpu_we  = 0;
            @(posedge clk); #1;
        end
    endtask

    task load;
        input [`CACHE_ADDRESS-1:0] addr;
        input [`FUNCT3_WIDTH-1:0]  f3;
        input [`DATA_WIDTH-1:0]    expected;
        input                      expect_miss;
        input [200*8:0]            name;
        begin
            access(addr, f3, 1'b0, 32'd0);
            check_data(expected, rdata, name);
            check_hit_miss(expect_miss, saw_miss, name);
        end
    endtask

    // Store. Payload is placed in its byte lane (DUT masks the raw payload).
    task store;
        input [`CACHE_ADDRESS-1:0] addr;
        input [`FUNCT3_WIDTH-1:0]  f3;
        input [`DATA_WIDTH-1:0]    value;     // unshifted value
        input                      expect_miss;
        input [200*8:0]            name;
        reg   [`DATA_WIDTH-1:0]    lane;
        begin
            lane = value << (8 * addr[1:0]);
            access(addr, f3, 1'b1, lane);
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
        $display("  D_CACHE write-back testbench");
        $display("==============================================");

        cpu_req     = 0;
        cpu_we      = 0;
        cpu_addr    = 0;
        cpu_funct3  = F3_W;
        data_in_cpu = 0;

        // ---------------------------------------------------------------
        // T1: Reset
        // ---------------------------------------------------------------
        $display("\n--- Test 1: Reset ---");
        reset = 1;
        @(posedge clk); #1;
        @(posedge clk); #1;
        check_data(1'b0, stall,   "stall==0 during reset");
        check_data(1'b0, mem_req, "mem_req==0 during reset");
        check_data(1'b0, mem_we,  "mem_we==0 during reset");
        reset = 0;
        @(posedge clk); #1;

        // ---------------------------------------------------------------
        // T2: Cold load miss -> memory read -> fill -> data
        // ---------------------------------------------------------------
        $display("\n--- Test 2: Cold load miss ---");
        write_mem(32'h0000_0020, 32'hDEAD_BEEF);
        load(32'h0000_0020, F3_W, 32'hDEAD_BEEF, 1, "LW 0x20 (cold miss)");
        check_data(1, mem_rd_count, "1 memory read issued");
        check_data(0, mem_wr_count, "no memory write on clean miss");

        // ---------------------------------------------------------------
        // T3: Hit on re-access (no stall, no memory traffic)
        // ---------------------------------------------------------------
        $display("\n--- Test 3: Hit on re-access ---");
        load(32'h0000_0020, F3_W, 32'hDEAD_BEEF, 0, "LW 0x20 (hit)");
        check_data(1, mem_rd_count, "no extra memory read on hit");

        // ---------------------------------------------------------------
        // T4: LW across sets
        // ---------------------------------------------------------------
        $display("\n--- Test 4: LW across sets ---");
        write_mem(32'h0000_0000, 32'h1234_5678);
        write_mem(32'h0000_0008, 32'hCAFE_BABE);
        write_mem(32'h0000_0100, 32'h89AB_CDEF);
        load(32'h0000_0000, F3_W, 32'h1234_5678, 1, "LW 0x00 (cold)");
        load(32'h0000_0008, F3_W, 32'hCAFE_BABE, 1, "LW 0x08 (cold)");
        load(32'h0000_0100, F3_W, 32'h89AB_CDEF, 1, "LW 0x100 (cold)");
        load(32'h0000_0100, F3_W, 32'h89AB_CDEF, 0, "LW 0x100 (hit)");

        // ---------------------------------------------------------------
        // T5: LB sign extension. word 0x807FFF01 at 0x40
        // ---------------------------------------------------------------
        $display("\n--- Test 5: LB sign extension ---");
        write_mem(32'h0000_0040, 32'h807F_FF01);
        load(32'h0000_0040, F3_B, 32'h0000_0001, 1, "LB 0x40 byte0 (cold)");
        load(32'h0000_0041, F3_B, 32'hFFFF_FFFF, 0, "LB 0x41 byte1");
        load(32'h0000_0042, F3_B, 32'h0000_007F, 0, "LB 0x42 byte2");
        load(32'h0000_0043, F3_B, 32'hFFFF_FF80, 0, "LB 0x43 byte3");

        // ---------------------------------------------------------------
        // T6: LBU zero extension
        // ---------------------------------------------------------------
        $display("\n--- Test 6: LBU zero extension ---");
        load(32'h0000_0041, F3_BU, 32'h0000_00FF, 0, "LBU 0x41 byte1");
        load(32'h0000_0043, F3_BU, 32'h0000_0080, 0, "LBU 0x43 byte3");

        // ---------------------------------------------------------------
        // T7: LH / LHU. word 0x80017FFF at 0x60
        // ---------------------------------------------------------------
        $display("\n--- Test 7: LH / LHU ---");
        write_mem(32'h0000_0060, 32'h8001_7FFF);
        load(32'h0000_0060, F3_H,  32'h0000_7FFF, 1, "LH  0x60 lower (cold)");
        load(32'h0000_0062, F3_H,  32'hFFFF_8001, 0, "LH  0x62 upper");
        load(32'h0000_0060, F3_HU, 32'h0000_7FFF, 0, "LHU 0x60 lower");
        load(32'h0000_0062, F3_HU, 32'h0000_8001, 0, "LHU 0x62 upper");

        // ---------------------------------------------------------------
        // T8: Store hit (SW), read back; write-back => memory unchanged
        // ---------------------------------------------------------------
        $display("\n--- Test 8: SW hit, write-back (memory not updated) ---");
        write_mem(32'h0000_0080, 32'hAAAA_AAAA);
        load (32'h0000_0080, F3_W, 32'hAAAA_AAAA, 1, "LW 0x80 (cold)");
        store(32'h0000_0080, F3_W, 32'h5555_5555, 0, "SW 0x80 (hit)");
        load (32'h0000_0080, F3_W, 32'h5555_5555, 0, "LW 0x80 reads stored value");
        check_data(32'hAAAA_AAAA, mem[32'h0000_0080 >> 2], "mem[0x80] still old (write-back)");

        // ---------------------------------------------------------------
        // T9: SB / SH byte-lane merge
        // ---------------------------------------------------------------
        $display("\n--- Test 9: SB / SH merge ---");
        write_mem(32'h0000_00C0, 32'h0000_0000);
        load (32'h0000_00C0, F3_W, 32'h0000_0000, 1, "LW 0xC0 (cold)");
        store(32'h0000_00C0, F3_B, 32'h0000_00AA, 0, "SB 0xC0");
        store(32'h0000_00C1, F3_B, 32'h0000_00BB, 0, "SB 0xC1");
        store(32'h0000_00C2, F3_H, 32'h0000_CCDD, 0, "SH 0xC2");
        load (32'h0000_00C0, F3_W, 32'hCCDD_BBAA, 0, "LW 0xC0 merged");

        // ---------------------------------------------------------------
        // T10: Boundary set (set 127 -> 0x1FC)
        // ---------------------------------------------------------------
        $display("\n--- Test 10: Boundary set ---");
        write_mem(32'h0000_01FC, 32'hBAAD_F00D);
        load(32'h0000_01FC, F3_W,  32'hBAAD_F00D, 1, "LW  0x1FC (set 127, cold)");
        load(32'h0000_01FC, F3_BU, 32'h0000_000D, 0, "LBU 0x1FC (hit)");

        // ---------------------------------------------------------------
        // T11: 2-way associativity. A,B same set (differ by 0x200).
        // ---------------------------------------------------------------
        $display("\n--- Test 11: 2-way associativity ---");
        write_mem(32'h0000_3000, 32'h1111_1111);
        write_mem(32'h0000_3200, 32'h2222_2222);
        load(32'h0000_3000, F3_W, 32'h1111_1111, 1, "A 0x3000 (cold)");
        load(32'h0000_3200, F3_W, 32'h2222_2222, 1, "B 0x3200 (cold)");
        load(32'h0000_3000, F3_W, 32'h1111_1111, 0, "A 0x3000 (hit)");
        load(32'h0000_3200, F3_W, 32'h2222_2222, 0, "B 0x3200 (hit)");

        // ---------------------------------------------------------------
        // T12: Clean eviction (no write-back traffic)
        // ---------------------------------------------------------------
        $display("\n--- Test 12: Clean eviction ---");
        write_mem(32'h0000_3400, 32'h3333_3333);
        begin : clean_evict
            integer wr_before;
            wr_before = mem_wr_count;
            load(32'h0000_3400, F3_W, 32'h3333_3333, 1, "C 0x3400 (capacity miss)");
            check_data(wr_before, mem_wr_count, "clean victim: no memory write");
        end
        load(32'h0000_3400, F3_W, 32'h3333_3333, 0, "C 0x3400 (hit)");

        // ---------------------------------------------------------------
        // T13: Dirty eviction -> write-back to memory, data survives.
        //      Set 0x60: X=0x5000, Y=0x5200, Z=0x5400, W=0x5600.
        //      Dirty X, then load Y,Z,W (all same set): X must be evicted
        //      regardless of LRU order and written back.
        // ---------------------------------------------------------------
        $display("\n--- Test 13: Dirty eviction / write-back ---");
        write_mem(32'h0000_5000, 32'h0101_0101);
        write_mem(32'h0000_5200, 32'h0202_0202);
        write_mem(32'h0000_5400, 32'h0303_0303);
        write_mem(32'h0000_5600, 32'h0404_0404);
        load (32'h0000_5000, F3_W, 32'h0101_0101, 1, "X 0x5000 (cold)");
        store(32'h0000_5000, F3_W, 32'hFEED_FACE, 0, "SW X 0x5000 (dirty)");
        load (32'h0000_5200, F3_W, 32'h0202_0202, 1, "Y 0x5200 (cold)");
        load (32'h0000_5400, F3_W, 32'h0303_0303, 1, "Z 0x5400 (evict)");
        load (32'h0000_5600, F3_W, 32'h0404_0404, 1, "W 0x5600 (evict)");
        check_data(32'hFEED_FACE, mem[32'h0000_5000 >> 2], "mem[0x5000] holds written-back dirty data");
        load (32'h0000_5000, F3_W, 32'hFEED_FACE, 1, "X 0x5000 reload (miss, data survived)");

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