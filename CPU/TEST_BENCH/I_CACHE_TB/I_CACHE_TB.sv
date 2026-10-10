`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
`timescale 1ns / 1ps

module I_CACHE_TB;

    // Clock and Reset
    reg clk;
    reg reset;

    // Miss/Fill interface
    reg valid;
    wire miss;
    wire stall;
    reg [`INSTRUCTION_WIDTH-1:0] inst_in;

    // Fetch interface
    reg [`CACHE_ADDRESS-1:0] r_addr;
    wire [`INSTRUCTION_WIDTH-1:0] inst_out;

    // Test counters
    integer pass_count = 0;
    integer fail_count = 0;
    integer test_count = 0;
    integer miss_count = 0;

    // Backdoor instruction memory model
    reg [`INSTRUCTION_WIDTH-1:0] mem [0:4095];

    localparam CLK_PERIOD = 10;

    // Instantiate the Unit Under Test (UUT)
    I_CACHE uut (
        .clk(clk),
        .reset(reset),
        .valid(valid),
        .miss(miss),
        .stall(stall),
        .inst_in(inst_in),
        .r_addr(r_addr),
        .inst_out(inst_out)
    );

    // Clock generation
    initial begin
        clk = 0;
        forever #(CLK_PERIOD/2) clk = ~clk;
    end

    // RTL reset only clears the FSM, not the storage arrays.
    // Zero them hierarchically so valid/LRU bits are deterministic.
    integer j;
    initial begin
        for (j = 0; j < `I_CACHE_SIZE; j = j + 1) begin
            uut.way0_cache[j] = 0;
            uut.way1_cache[j] = 0;
        end
    end

    // Check task for instruction data
    task check_inst;
        input [`INSTRUCTION_WIDTH-1:0] expected;
        input [`INSTRUCTION_WIDTH-1:0] actual;
        // placeholder, replaced below
    endtask

    // Re-declared check task (actual proper form)
    task verify_inst;
        input [`INSTRUCTION_WIDTH-1:0] expected;
        input [`INSTRUCTION_WIDTH-1:0] actual;
        input [200*8:0] test_name;
        begin
            test_count = test_count + 1;
            if (expected === actual) begin
                $display("[PASS] Test %0d: %s | Expected: 0x%08h, Got: 0x%08h",
                         test_count, test_name, expected, actual);
                pass_count = pass_count + 1;
            end else begin
                $display("[FAIL] Test %0d: %s | Expected: 0x%08h, Got: 0x%08h",
                         test_count, test_name, expected, actual);
                fail_count = fail_count + 1;
            end
        end
    endtask

    // Helper task: apply reset (sample during reset for miss/stall checks)
    task reset_cache;
        begin
            reset = 1;
            valid = 0;
            inst_in = 0;
            r_addr = 0;
            @(posedge clk);
            #1;
            reset = 0;
            @(posedge clk);
            #1;
        end
    endtask

    // Read an instruction, handling the miss/fill handshake automatically.
    // Returns nothing; reles on verify_inst being called separately.
    task read_inst;
        input [`CACHE_ADDRESS-1:0] address;
        begin
            r_addr = address;
            #1;
            @(posedge clk); #1;        // edge A: IDLE decision (miss -> START)
            if (stall === 1'b1) begin
                miss_count = miss_connt + 1;
                inst_in = mem[address >> 2];
                valid = 1'b1;
                @(posedge clk); #1;   // edge B: START -> DONE, line written
                valid = 1'b 0;
                @(posedge clk); #1;   // edge C: DONE -> IDLE, miss/stall clear
            end
            @(posedge clk); #1;       // edge D: IDLE hit, i_cache captured
        end
    endtask

    // Convenience: read and verify in one step
    task read_verify_inst;
        input [`CACHE_ADDRESS-1:0] address;
        input [`INSTRUCTION_WIDTH-1:0] expected;
        input [200*8:0] test_name;
        begin
            read_inst(address);
            verify_inst(expected, inst_out, test_name);
        end
    endtask

    // Main test sequence
    initial begin
        $dumpfile("I_CACHE_TB.vcd");
        $dumpvars(0, I_CACHE_TB);

        $display("========================================");
        $display("   Instruction Cache Test Bench (FSM)   ");
        $display("========================================");

        // Seed the backdoor memory model
        mem[32'h0000_0000 >> 2] = 32'hDEAD_BEEF;
        mem[32'h0000_0004 >> 2] = 32'h1234_5678;
        mem[32'h0000_0200 >> 2] = 32'hAAAA_AAAA;
        mem[32'h0000_0080 >> 2] = 32'hCAFE_BABE;
        mem[32'h0000_0400 >> 2] = 32'h8BAD_F00D;

        // Initialize signals
        clk = 0;
        reset = 0;
        valid = 0;
        inst_in = 0;
        r_addr = 0;

        #20;

        // Test 1: Reset behaviour (sample DURING reset)
        $display("\n--- Test 1: Reset clears handshake ---");
        reset = 1;
        @(posedge clk); #1;
        test_count = test_count + 1;
        if (miss === 0 && stall === 0) begin
            $display("[PASS] Test %0d: Reset clears miss and stall", test_count);
            pass_count = pass_count + 1;
        end else begin
            $display("[FAIL] Test %0d: Reset should clear miss/stall (miss=%b stall=%b)", test_count, miss, stall);
            fail_count = fail_count + 1;
        end
        reset = 0;
        @(posedge clk); #1;

        // Test 2: First access -> MISS, then fill returns the word
        $display("\n--- Test 2: Miss + fill handshake ---");
        read_verify_inst(32'h0000_0000, 32'hDEAD_BEEF, "First Access - Address 0 (miss)");

        // Test 3: Resident re-read -> HIT (no refill, stale value kept)
        $display("\n--- Test 3: Hit on re-access ---");
        mem[32'h0000_0000 >> 2] = 32'h1111_1111;  // change backing store
        read_verify_inst(32'h0000_0000, 32'hDEAD_BEEF, "Re-access - Address 0 (hit, cached)");

        // Test 4: Different set
        $display("\n--- Test 4: Access another set ---");
        read_verify_inst(32'h0000_0004, 32'h1234_5678, "Address 4 - set 1 (miss)");
        read_verify_inst(32'h0000_0004, 32'h1234_5678, "Address 4 - set 1 (hit)");

        // Test 5: Conflict in set 0 (different tag -> LRU replacement)
        $display("\n--- Test 5: LRU replacement in set 0 ---");
        read_verify_inst(32'h0000_0200, 32'hAAAA_AAAA, "Address 0x200 - set 0 tag B (miss)");
        read_verify_inst(32'h0000_0000, 32'hDEAD_BEEF, "Address 0 - set 0 still resident (hit)");
        read_verify_inst(32'h0000_0200, 32'hAAAA_AAAA, "Address 0x200 - still resident (hit)");

        // Test 6: Another set + third tag in set 0
        $display("\n--- Test 6: More sets and tags ---");
        read_verify_inst(32'h0000_0080, 32'hCAFE_BABE, "Address 0x80 - set 0x20 (miss)");
        read_verify_inst(32'h0000_0400, 32'h8BAD_F00D, "Address 0x400 - set 0 tag C (miss)");

        // Final summary
        #20;
        $display("\n========================================");
        $display("        Test Summary");
        $display("========================================");
        $display("Total Tests: %0d", test_count);
        $display("Passed:      %0d", pass_count);
        $display("Failed:      %0d", fail_count);
        $display("Misses seen: %0d (expected 6)", miss_count);
        $display("========================================");
        if (fail_count == 0) begin
            $display("*** ALL TESTS PASSED ***");
        end else begin
            $display("*** SOME TESTS FAILED ***");
        end
        $display("========================================\n");

        $finish;
    end

endmodule