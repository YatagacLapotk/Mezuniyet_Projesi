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
    
    // Read Interface
    reg [`CACHE_ADDRESS-1:0] r_addr;
    wire [`DATA_WIDTH-1:0] data_out;
    
    // Test counters
    integer pass_count = 0;
    integer fail_count = 0;
    integer test_count = 0;
    
    // Clock parameters
    localparam CLK_PERIOD = 10;
    
    // Instantiate the Unit Under Test (UUT)
    D_CACHE uut (
        .clk(clk),
        .reset(reset),
        .we(we),
        .data_in(data_in),
        .w_addr(w_addr),
        .r_addr(r_addr),
        .data_out(data_out)
    );
    
    // Clock generation
    initial begin
        clk = 0;
        forever #(CLK_PERIOD/2) clk = ~clk;
    end
    
    // Check task for data
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
            @(posedge clk);
            #1;
            reset = 0;
            @(posedge clk);
            #1;
        end
    endtask
    
    // Helper task: Write data
    task write_data;
        input [`CACHE_ADDRESS-1:0] address;
        input [`DATA_WIDTH-1:0] data;
        begin
            we = 1;
            w_addr = address;
            data_in = data;
            @(posedge clk);
            #1;
            we = 0;
        end
    endtask
    
    // Helper task: Read and verify data
    task read_verify;
        input [`CACHE_ADDRESS-1:0] address;
        input [`DATA_WIDTH-1:0] expected;
        input [200*8:0] test_name;
        begin
            r_addr = address;
            #1;
            check_data(expected, data_out, test_name);
        end
    endtask
    
    // Main test sequence
    initial begin
        $dumpfile("D_CACHE_TB.vcd");
        $dumpvars(0, D_CACHE_TB);
        
        $display("========================================");
        $display("      Data Cache Test Bench");
        $display("========================================");
        
        // Initialize signals
        clk = 0;
        reset = 0;
        we = 0;
        data_in = 0;
        w_addr = 0;
        r_addr = 0;
        
        // Wait for initialization
        #20;
        
        // Test 1: Reset behavior
        $display("\n--- Test 1: Reset Behavior ---");
        reset_cache();
        read_verify(32'h0000_0000, 32'h0000_0000, "Reset - Address 0 should be 0");
        read_verify(32'h0000_0004, 32'h0000_0000, "Reset - Address 4 should be 0");
        
        // Test 2: Basic Write and Read
        $display("\n--- Test 2: Basic Write and Read ---");
        write_data(32'h0000_0000, 32'hDEAD_BEEF);
        read_verify(32'h0000_0000, 32'hDEAD_BEEF, "Write/Read address 0");
        
        write_data(32'h0000_0004, 32'h1234_5678);
        read_verify(32'h0000_0004, 32'h1234_5678, "Write/Read address 4");
        
        // Test 3: Multiple sequential writes
        $display("\n--- Test 3: Sequential Writes ---");
        write_data(32'h0000_0008, 32'hAAAA_AAAA);
        write_data(32'h0000_000C, 32'h5555_5555);
        write_data(32'h0000_0010, 32'hFFFF_FFFF);
        
        read_verify(32'h0000_0008, 32'hAAAA_AAAA, "Sequential write - Address 8");
        read_verify(32'h0000_000C, 32'h5555_5555, "Sequential write - Address C");
        read_verify(32'h0000_0010, 32'hFFFF_FFFF, "Sequential write - Address 10");
        
        // Test 4: Overwrite existing data
        $display("\n--- Test 4: Overwrite Data ---");
        write_data(32'h0000_0000, 32'h9999_9999);
        read_verify(32'h0000_0000, 32'h9999_9999, "Overwrite address 0");
        
        // Test 5: Different data patterns
        $display("\n--- Test 5: Data Patterns ---");
        write_data(32'h0000_0100, 32'h0000_0000);  // All zeros
        write_data(32'h0000_0104, 32'hFFFF_FFFF);  // All ones
        write_data(32'h0000_0108, 32'hA5A5_A5A5);  // Alternating pattern
        write_data(32'h0000_010C, 32'h5A5A_5A5A);  // Inverse alternating
        
        read_verify(32'h0000_0100, 32'h0000_0000, "All zeros");
        read_verify(32'h0000_0104, 32'hFFFF_FFFF, "All ones");
        read_verify(32'h0000_0108, 32'hA5A5_A5A5, "Alternating pattern");
        read_verify(32'h0000_010C, 32'h5A5A_5A5A, "Inverse alternating");
        
        // Test 6: Byte-aligned addresses
        $display("\n--- Test 6: Byte-Aligned Addresses ---");
        write_data(32'h0000_0200, 32'h1111_1111);
        write_data(32'h0000_0201, 32'h2222_2222);
        write_data(32'h0000_0202, 32'h3333_3333);
        write_data(32'h0000_0203, 32'h4444_4444);
        
        read_verify(32'h0000_0200, 32'h1111_1111, "Byte address 0x200");
        read_verify(32'h0000_0201, 32'h2222_2222, "Byte address 0x201");
        read_verify(32'h0000_0202, 32'h3333_3333, "Byte address 0x202");
        read_verify(32'h0000_0203, 32'h4444_4444, "Byte address 0x203");
        
        // Test 7: Boundary addresses
        $display("\n--- Test 7: Boundary Addresses ---");
        write_data(32'h0000_0000, 32'h0000_0001);  // First address
        write_data(32'h0000_07FC, 32'hFFFF_FFFE);  // Last address (2047)
        
        read_verify(32'h0000_0000, 32'h0000_0001, "First address (0)");
        read_verify(32'h0000_07FC, 32'hFFFF_FFFE, "Last address (2047)");
        
        // Test 8: Read without write (uninitialized)
        $display("\n--- Test 8: Uninitialized Read ---");
        reset_cache();
        read_verify(32'h0000_0500, 32'h0000_0000, "Read uninitialized address");
        
        // Test 9: Rapid write/read cycles
        $display("\n--- Test 9: Rapid Write/Read Cycles ---");
        write_data(32'h0000_0300, 32'h1000_0001);
        read_verify(32'h0000_0300, 32'h1000_0001, "Rapid cycle 1");
        
        write_data(32'h0000_0304, 32'h2000_0002);
        read_verify(32'h0000_0304, 32'h2000_0002, "Rapid cycle 2");
        
        write_data(32'h0000_0308, 32'h3000_0003);
        read_verify(32'h0000_0308, 32'h3000_0003, "Rapid cycle 3");
        
        // Test 10: Multiple reads of same address
        $display("\n--- Test 10: Multiple Reads ---");
        write_data(32'h0000_0400, 32'hCAFE_BABE);
        read_verify(32'h0000_0400, 32'hCAFE_BABE, "First read");
        read_verify(32'h0000_0400, 32'hCAFE_BABE, "Second read");
        read_verify(32'h0000_0400, 32'hCAFE_BABE, "Third read");
        
        // Test 11: Interleaved addresses
        $display("\n--- Test 11: Interleaved Access ---");
        write_data(32'h0000_0020, 32'h1111_1111);
        write_data(32'h0000_0024, 32'h2222_2222);
        write_data(32'h0000_0028, 32'h3333_3333);
        
        read_verify(32'h0000_0024, 32'h2222_2222, "Read middle address first");
        read_verify(32'h0000_0020, 32'h1111_1111, "Read first address");
        read_verify(32'h0000_0028, 32'h3333_3333, "Read last address");
        
        // Test 12: Write enable control
        $display("\n--- Test 12: Write Enable Control ---");
        write_data(32'h0000_0030, 32'hAAAA_AAAA);
        read_verify(32'h0000_0030, 32'hAAAA_AAAA, "Initial write");
        
        // Attempt write without enable
        we = 0;
        w_addr = 32'h0000_0030;
        data_in = 32'hBBBB_BBBB;
        @(posedge clk);
        #1;
        read_verify(32'h0000_0030, 32'hAAAA_AAAA, "Write without enable - data unchanged");
        
        // Test 13: Reset clears all data
        $display("\n--- Test 13: Reset Clears Data ---");
        write_data(32'h0000_0040, 32'h8888_8888);
        write_data(32'h0000_0044, 32'h7777_7777);
        read_verify(32'h0000_0040, 32'h8888_8888, "Before reset - address 0x40");
        read_verify(32'h0000_0044, 32'h7777_7777, "Before reset - address 0x44");
        
        reset_cache();
        read_verify(32'h0000_0040, 32'h0000_0000, "After reset - address 0x40");
        read_verify(32'h0000_0044, 32'h0000_0000, "After reset - address 0x44");
        
        // Final summary
        #20;
        $display("\n========================================");
        $display("        Test Summary");
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
