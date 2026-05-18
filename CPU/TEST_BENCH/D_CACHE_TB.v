`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
`timescale 1ns / 1ps

module D_CACHE_TB;

    // Clock and Reset
    reg clk;
    reg reset;
    
    // Write Interface
    reg we;
    reg [`DATA_WIDTH-1:0] data_in;
    reg [`CACHE_ADDRESS-1:0] w_addr;
    reg [`FUNCT3_WIDTH-1:0] funct3;
    
    // Read Interface
    reg [`CACHE_ADDRESS-1:0] r_addr;
    wire [`DATA_WIDTH-1:0] data_out;
    
    // Test counters
    integer pass_count = 0;
    integer fail_count = 0;
    integer test_count = 0;
    
    // Clock parameters
    localparam CLK_PERIOD = 10;

    // funct3 encodings
    localparam [2:0] F3_SB  = 3'b000,  // Store Byte
                     F3_SH  = 3'b001,  // Store Halfword
                     F3_SW  = 3'b010,  // Store Word
                     F3_LB  = 3'b000,  // Load Byte (signed)
                     F3_LH  = 3'b001,  // Load Halfword (signed)
                     F3_LW  = 3'b010,  // Load Word
                     F3_LBU = 3'b100,  // Load Byte (unsigned)
                     F3_LHU = 3'b101;  // Load Halfword (unsigned)
    
    // Instantiate the Unit Under Test (UUT)
    D_CACHE uut (
        .clk(clk),
        .reset(reset),
        .we(we),
        .data_in(data_in),
        .w_addr(w_addr),
        .funct3(funct3),
        .r_addr(r_addr),
        .data_out(data_out)
    );
    
    // Clock generation
    initial begin
        clk = 0;
        forever #(CLK_PERIOD/2) clk = ~clk;
    end
    
    // Check task
    task check_data;
        input [`DATA_WIDTH-1:0] expected;
        input [`DATA_WIDTH-1:0] actual;
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
    
    // Helper task: Reset cache
    task reset_cache;
        begin
            reset = 1;
            we = 0;
            data_in = 0;
            w_addr = 0;
            r_addr = 0;
            funct3 = F3_SW;
            @(posedge clk);
            #1;
            reset = 0;
            @(posedge clk);
            #1;
        end
    endtask
    
    // Helper task: Store data (write with funct3)
    task store_data;
        input [`CACHE_ADDRESS-1:0] address;
        input [`DATA_WIDTH-1:0] data;
        input [2:0] f3;
        begin
            we = 1;
            w_addr = address;
            data_in = data;
            funct3 = f3;
            @(posedge clk);
            #1;
            we = 0;
        end
    endtask
    
    // Helper task: Load and verify (read with funct3)
    task load_verify;
        input [`CACHE_ADDRESS-1:0] address;
        input [2:0] f3;
        input [`DATA_WIDTH-1:0] expected;
        input [200*8:0] test_name;
        begin
            r_addr = address;
            funct3 = f3;
            #1;
            check_data(expected, data_out, test_name);
        end
    endtask
    
    // Main test sequence
    initial begin
        $dumpfile("D_CACHE_TB.vcd");
        $dumpvars(0, D_CACHE_TB);
        
        $display("========================================");
        $display("   D_CACHE Byte-Addressable Test Bench  ");
        $display("========================================");
        
        // Initialize signals
        clk = 0;
        reset = 0;
        we = 0;
        data_in = 0;
        w_addr = 0;
        r_addr = 0;
        funct3 = F3_SW;
        
        #20;
        
        // =============================================
        // TEST 1: Reset behavior
        // =============================================
        $display("\n--- Test 1: Reset Behavior ---");
        reset_cache();
        load_verify(32'h0000_0000, F3_LW, 32'h0000_0000, "Reset - Addr 0x00 = 0");
        load_verify(32'h0000_0004, F3_LW, 32'h0000_0000, "Reset - Addr 0x04 = 0");
        load_verify(32'h0000_0008, F3_LW, 32'h0000_0000, "Reset - Addr 0x08 = 0");
        
        // =============================================
        // TEST 2: SW (Store Word) + LW (Load Word)
        // =============================================
        $display("\n--- Test 2: SW + LW ---");
        store_data(32'h0000_0000, 32'hDEAD_BEEF, F3_SW);
        load_verify(32'h0000_0000, F3_LW, 32'hDEAD_BEEF, "SW/LW addr 0x00");
        
        store_data(32'h0000_0004, 32'h1234_5678, F3_SW);
        load_verify(32'h0000_0004, F3_LW, 32'h1234_5678, "SW/LW addr 0x04");
        
        store_data(32'h0000_0008, 32'hCAFE_BABE, F3_SW);
        load_verify(32'h0000_0008, F3_LW, 32'hCAFE_BABE, "SW/LW addr 0x08");
        
        // =============================================
        // TEST 3: SB (Store Byte) — byte merging
        // Store a known word, then overwrite individual bytes
        // =============================================
        $display("\n--- Test 3: SB Byte Merging ---");
        reset_cache();
        
        // Fill word at addr 0x00 with a known value
        store_data(32'h0000_0000, 32'hAABB_CCDD, F3_SW);
        load_verify(32'h0000_0000, F3_LW, 32'hAABB_CCDD, "Initial word = 0xAABBCCDD");
        
        // SB 0x11 at byte offset 0 — should change only byte 0
        // Word: AA BB CC DD → AA BB CC 11
        store_data(32'h0000_0000, 32'h0000_0011, F3_SB);
        load_verify(32'h0000_0000, F3_LW, 32'hAABB_CC11, "SB offset 0: DD->11");
        
        // SB 0x22 at byte offset 1 — should change only byte 1
        // Word: AA BB CC 11 → AA BB 22 11
        store_data(32'h0000_0001, 32'h0000_0022, F3_SB);
        load_verify(32'h0000_0000, F3_LW, 32'hAABB_2211, "SB offset 1: CC->22");
        
        // SB 0x33 at byte offset 2 — should change only byte 2
        // Word: AA BB 22 11 → AA 33 22 11
        store_data(32'h0000_0002, 32'h0000_0033, F3_SB);
        load_verify(32'h0000_0000, F3_LW, 32'hAA33_2211, "SB offset 2: BB->33");
        
        // SB 0x44 at byte offset 3 — should change only byte 3
        // Word: AA 33 22 11 → 44 33 22 11
        store_data(32'h0000_0003, 32'h0000_0044, F3_SB);
        load_verify(32'h0000_0000, F3_LW, 32'h4433_2211, "SB offset 3: AA->44");
        
        // =============================================
        // TEST 4: SH (Store Halfword) — halfword merging
        // =============================================
        $display("\n--- Test 4: SH Halfword Merging ---");
        reset_cache();
        
        // Fill word at addr 0x10 with a known value
        store_data(32'h0000_0010, 32'hFFFF_FFFF, F3_SW);
        load_verify(32'h0000_0010, F3_LW, 32'hFFFF_FFFF, "Initial word = 0xFFFFFFFF");
        
        // SH 0xABCD at lower half (offset 0)
        // Word: FFFF FFFF → FFFF ABCD
        store_data(32'h0000_0010, 32'h0000_ABCD, F3_SH);
        load_verify(32'h0000_0010, F3_LW, 32'hFFFF_ABCD, "SH lower half: FFFF->ABCD");
        
        // SH 0x1234 at upper half (offset 2)
        // Word: FFFF ABCD → 1234 ABCD
        store_data(32'h0000_0012, 32'h0000_1234, F3_SH);
        load_verify(32'h0000_0010, F3_LW, 32'h1234_ABCD, "SH upper half: FFFF->1234");
        
        // =============================================
        // TEST 5: LB (Load Byte signed) — sign extension
        // =============================================
        $display("\n--- Test 5: LB Sign Extension ---");
        reset_cache();
        
        // Store word with bytes: [0x80, 0x7F, 0xFF, 0x01]
        // Memory layout (little-endian): byte0=0x01, byte1=0xFF, byte2=0x7F, byte3=0x80
        store_data(32'h0000_0020, 32'h807F_FF01, F3_SW);
        
        // LB from byte 0: 0x01 → positive, sign-extend = 0x00000001
        load_verify(32'h0000_0020, F3_LB, 32'h0000_0001, "LB byte0: 0x01 (positive)");
        
        // LB from byte 1: 0xFF → negative, sign-extend = 0xFFFFFFFF
        load_verify(32'h0000_0021, F3_LB, 32'hFFFF_FFFF, "LB byte1: 0xFF (negative)");
        
        // LB from byte 2: 0x7F → positive, sign-extend = 0x0000007F
        load_verify(32'h0000_0022, F3_LB, 32'h0000_007F, "LB byte2: 0x7F (positive)");
        
        // LB from byte 3: 0x80 → negative, sign-extend = 0xFFFFFF80
        load_verify(32'h0000_0023, F3_LB, 32'hFFFF_FF80, "LB byte3: 0x80 (negative)");
        
        // =============================================
        // TEST 6: LBU (Load Byte unsigned) — zero extension
        // =============================================
        $display("\n--- Test 6: LBU Zero Extension ---");
        // Same word as test 5: 0x807FFF01
        
        // LBU from byte 0: 0x01 → 0x00000001
        load_verify(32'h0000_0020, F3_LBU, 32'h0000_0001, "LBU byte0: 0x01");
        
        // LBU from byte 1: 0xFF → 0x000000FF
        load_verify(32'h0000_0021, F3_LBU, 32'h0000_00FF, "LBU byte1: 0xFF");
        
        // LBU from byte 2: 0x7F → 0x0000007F
        load_verify(32'h0000_0022, F3_LBU, 32'h0000_007F, "LBU byte2: 0x7F");
        
        // LBU from byte 3: 0x80 → 0x00000080
        load_verify(32'h0000_0023, F3_LBU, 32'h0000_0080, "LBU byte3: 0x80");
        
        // =============================================
        // TEST 7: LH (Load Halfword signed) — sign extension
        // =============================================
        $display("\n--- Test 7: LH Sign Extension ---");
        reset_cache();
        
        // Store word: 0x8001_7FFF
        // lower half = 0x7FFF (positive), upper half = 0x8001 (negative)
        store_data(32'h0000_0030, 32'h8001_7FFF, F3_SW);
        
        // LH from lower half (offset 0): 0x7FFF → sign-extend = 0x00007FFF
        load_verify(32'h0000_0030, F3_LH, 32'h0000_7FFF, "LH lower: 0x7FFF (positive)");
        
        // LH from upper half (offset 2): 0x8001 → sign-extend = 0xFFFF8001
        load_verify(32'h0000_0032, F3_LH, 32'hFFFF_8001, "LH upper: 0x8001 (negative)");
        
        // =============================================
        // TEST 8: LHU (Load Halfword unsigned) — zero extension
        // =============================================
        $display("\n--- Test 8: LHU Zero Extension ---");
        // Same word as test 7: 0x80017FFF
        
        // LHU from lower half: 0x7FFF → 0x00007FFF
        load_verify(32'h0000_0030, F3_LHU, 32'h0000_7FFF, "LHU lower: 0x7FFF");
        
        // LHU from upper half: 0x8001 → 0x00008001
        load_verify(32'h0000_0032, F3_LHU, 32'h0000_8001, "LHU upper: 0x8001");
        
        // =============================================
        // TEST 9: SB at different word addresses
        // Verify SB works on multiple words independently
        // =============================================
        $display("\n--- Test 9: SB Across Different Words ---");
        reset_cache();
        
        // Store two words
        store_data(32'h0000_0040, 32'h0000_0000, F3_SW);
        store_data(32'h0000_0044, 32'h0000_0000, F3_SW);
        
        // SB into word 0 at offset 1
        store_data(32'h0000_0041, 32'h0000_00AB, F3_SB);
        // SB into word 1 at offset 3
        store_data(32'h0000_0047, 32'h0000_00CD, F3_SB);
        
        load_verify(32'h0000_0040, F3_LW, 32'h0000_AB00, "SB word0 offset1: 0xAB");
        load_verify(32'h0000_0044, F3_LW, 32'hCD00_0000, "SB word1 offset3: 0xCD");
        
        // Verify they didn't corrupt each other
        load_verify(32'h0000_0041, F3_LBU, 32'h0000_00AB, "Verify word0 byte1 = 0xAB");
        load_verify(32'h0000_0047, F3_LBU, 32'h0000_00CD, "Verify word1 byte3 = 0xCD");
        
        // =============================================
        // TEST 10: Write Enable control
        // =============================================
        $display("\n--- Test 10: Write Enable Control ---");
        reset_cache();
        
        store_data(32'h0000_0050, 32'hAAAA_AAAA, F3_SW);
        load_verify(32'h0000_0050, F3_LW, 32'hAAAA_AAAA, "Initial write");
        
        // Attempt write without we=1
        we = 0;
        w_addr = 32'h0000_0050;
        data_in = 32'hBBBB_BBBB;
        funct3 = F3_SW;
        @(posedge clk);
        #1;
        load_verify(32'h0000_0050, F3_LW, 32'hAAAA_AAAA, "Write disabled - data unchanged");
        
        // =============================================
        // TEST 11: Reset clears data
        // =============================================
        $display("\n--- Test 11: Reset Clears Data ---");
        store_data(32'h0000_0060, 32'h8888_8888, F3_SW);
        store_data(32'h0000_0064, 32'h7777_7777, F3_SW);
        load_verify(32'h0000_0060, F3_LW, 32'h8888_8888, "Before reset - addr 0x60");
        load_verify(32'h0000_0064, F3_LW, 32'h7777_7777, "Before reset - addr 0x64");
        
        reset_cache();
        load_verify(32'h0000_0060, F3_LW, 32'h0000_0000, "After reset - addr 0x60");
        load_verify(32'h0000_0064, F3_LW, 32'h0000_0000, "After reset - addr 0x64");
        
        // =============================================
        // TEST 12: Multiple SB build up a full word
        // =============================================
        $display("\n--- Test 12: Build Word from SB ---");
        reset_cache();
        
        // Build 0xDEADBEEF byte by byte
        store_data(32'h0000_0070, 32'h0000_00EF, F3_SB);  // byte 0 = 0xEF
        store_data(32'h0000_0071, 32'h0000_00BE, F3_SB);  // byte 1 = 0xBE
        store_data(32'h0000_0072, 32'h0000_00AD, F3_SB);  // byte 2 = 0xAD
        store_data(32'h0000_0073, 32'h0000_00DE, F3_SB);  // byte 3 = 0xDE
        
        load_verify(32'h0000_0070, F3_LW, 32'hDEAD_BEEF, "Built 0xDEADBEEF from SB");
        
        // Read each byte back individually
        load_verify(32'h0000_0070, F3_LBU, 32'h0000_00EF, "Readback byte0 = 0xEF");
        load_verify(32'h0000_0071, F3_LBU, 32'h0000_00BE, "Readback byte1 = 0xBE");
        load_verify(32'h0000_0072, F3_LBU, 32'h0000_00AD, "Readback byte2 = 0xAD");
        load_verify(32'h0000_0073, F3_LBU, 32'h0000_00DE, "Readback byte3 = 0xDE");
        
        // =============================================
        // TEST 13: Multiple SH build up a full word
        // =============================================
        $display("\n--- Test 13: Build Word from SH ---");
        reset_cache();
        
        // Build 0xCAFEBABE from two halfwords
        store_data(32'h0000_0080, 32'h0000_BABE, F3_SH);  // lower half = 0xBABE
        store_data(32'h0000_0082, 32'h0000_CAFE, F3_SH);  // upper half = 0xCAFE
        
        load_verify(32'h0000_0080, F3_LW, 32'hCAFE_BABE, "Built 0xCAFEBABE from SH");
        load_verify(32'h0000_0080, F3_LHU, 32'h0000_BABE, "Readback lower = 0xBABE");
        load_verify(32'h0000_0082, F3_LHU, 32'h0000_CAFE, "Readback upper = 0xCAFE");
        
        // =============================================
        // TEST 14: Overwrite existing data patterns
        // =============================================
        $display("\n--- Test 14: Overwrite Patterns ---");
        reset_cache();
        
        store_data(32'h0000_0090, 32'hFFFF_FFFF, F3_SW);
        store_data(32'h0000_0090, 32'h0000_0000, F3_SW);
        load_verify(32'h0000_0090, F3_LW, 32'h0000_0000, "Overwrite FFFFFFFF with 00000000");
        
        store_data(32'h0000_0090, 32'hA5A5_A5A5, F3_SW);
        load_verify(32'h0000_0090, F3_LW, 32'hA5A5_A5A5, "Overwrite with alternating pattern");
        
        // =============================================
        // TEST 15: Boundary address — last cache entry
        // =============================================
        $display("\n--- Test 15: Boundary Address ---");
        reset_cache();
        
        // CACHE_SIZE = 2048, last word index = 2047, byte addr = 2047*4 = 0x1FFC
        store_data(32'h0000_1FFC, 32'hBAAD_F00D, F3_SW);
        load_verify(32'h0000_1FFC, F3_LW, 32'hBAAD_F00D, "Last cache entry SW/LW");
        
        // SB at last word, byte offset 2
        store_data(32'h0000_1FFE, 32'h0000_0042, F3_SB);
        load_verify(32'h0000_1FFC, F3_LW, 32'hBA42_F00D, "SB at last entry offset 2");
        
        // Final summary
        #20;
        $display("\n========================================");
        $display("           Test Summary");
        $display("========================================");
        $display("Total Tests: %0d", test_count);
        $display("Passed:      %0d", pass_count);
        $display("Failed:      %0d", fail_count);
        if (fail_count == 0) begin
            $display("\n*** ALL TESTS PASSED ***");
        end else begin
            $display("\n*** SOME TESTS FAILED ***");
        end
        $display("========================================\n");
        
        $finish;
    end
    
endmodule
