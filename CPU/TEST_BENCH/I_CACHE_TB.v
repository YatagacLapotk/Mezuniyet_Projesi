`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
`timescale 1ns / 1ps

module I_CACHE_TB;

    // Clock and Reset
    reg clk;
    reg reset;
    
    // Write Interface
    reg we;
    reg [`INSTRUCTION_WIDTH-1:0] inst_in;
    reg [`CACHE_ADDRESS-1:0] w_addr;
    
    // Read Interface
    reg [`CACHE_ADDRESS-1:0] r_addr;
    wire [`INSTRUCTION_WIDTH-1:0] inst_out;
    
    // Test counters
    integer pass_count = 0;
    integer fail_count = 0;
    integer test_count = 0;
    
    // Clock parameters
    localparam CLK_PERIOD = 10;
    
    // Instantiate the Unit Under Test (UUT)
    I_CACHE uut (
        .clk(clk),
        .reset(reset),
        .we(we),
        .inst_in(inst_in),
        .w_addr(w_addr),
        .r_addr(r_addr),
        .inst_out(inst_out)
    );
    
    // Clock generation
    initial begin
        clk = 0;
        forever #(CLK_PERIOD/2) clk = ~clk;
    end
    
    // Check task for instruction data
    task check_inst;
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
    
    // Helper task: Reset cache
    task reset_cache;
        begin
            reset = 1;
            we = 0;
            inst_in = 0;
            w_addr = 0;
            r_addr = 0;
            @(posedge clk);
            #1;
            reset = 0;
            @(posedge clk);
            #1;
        end
    endtask
    
    // Helper task: Write instruction
    task write_instruction;
        input [`CACHE_ADDRESS-1:0] address;
        input [`INSTRUCTION_WIDTH-1:0] instruction;
        begin
            we = 1;
            w_addr = address;
            inst_in = instruction;
            @(posedge clk);
            #1;
            we = 0;
        end
    endtask
    
    // Helper task: Read and verify instruction
    task read_verify;
        input [`CACHE_ADDRESS-1:0] address;
        input [`INSTRUCTION_WIDTH-1:0] expected;
        input [200*8:0] test_name;
        begin
            r_addr = address;
            #1;
            check_inst(expected, inst_out, test_name);
        end
    endtask
    
    // Main test sequence
    initial begin
        $dumpfile("I_CACHE_TB.vcd");
        $dumpvars(0, I_CACHE_TB);
        
        $display("========================================");
        $display("   Instruction Cache Test Bench");
        $display("========================================");
        
        // Initialize signals
        clk = 0;
        reset = 0;
        we = 0;
        inst_in = 0;
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
        write_instruction(32'h0000_0000, 32'hDEAD_BEEF);
        read_verify(32'h0000_0000, 32'hDEAD_BEEF, "Write/Read address 0");
        
        write_instruction(32'h0000_0004, 32'h1234_5678);
        read_verify(32'h0000_0004, 32'h1234_5678, "Write/Read address 4");
        
        // Test 3: Multiple sequential writes
        $display("\n--- Test 3: Sequential Writes ---");
        write_instruction(32'h0000_0008, 32'hAAAA_AAAA);
        write_instruction(32'h0000_000C, 32'h5555_5555);
        write_instruction(32'h0000_0010, 32'hFFFF_FFFF);
        
        read_verify(32'h0000_0008, 32'hAAAA_AAAA, "Sequential write - Address 8");
        read_verify(32'h0000_000C, 32'h5555_5555, "Sequential write - Address C");
        read_verify(32'h0000_0010, 32'hFFFF_FFFF, "Sequential write - Address 10");
        
        // Test 4: Overwrite existing data
        $display("\n--- Test 4: Overwrite Data ---");
        write_instruction(32'h0000_0000, 32'h1111_1111);
        read_verify(32'h0000_0000, 32'h1111_1111, "Overwrite address 0");
        
        // Test 5: Different addresses
        $display("\n--- Test 5: Various Addresses ---");
        write_instruction(32'h0000_0100, 32'hCAFE_BABE);
        write_instruction(32'h0000_0200, 32'hFEED_FACE);
        write_instruction(32'h0000_0400, 32'h8BAD_F00D);
        
        read_verify(32'h0000_0100, 32'hCAFE_BABE, "Address 0x100");
        read_verify(32'h0000_0200, 32'hFEED_FACE, "Address 0x200");
        read_verify(32'h0000_0400, 32'h8BAD_F00D, "Address 0x400");
        
        // Test 6: Boundary addresses
        $display("\n--- Test 6: Boundary Addresses ---");
        write_instruction(32'h0000_0000, 32'h0000_0001);  // First address
        write_instruction(32'h0000_07FC, 32'hFFFF_FFFE);  // Last address (2047)
        
        read_verify(32'h0000_0000, 32'h0000_0001, "First address (0)");
        read_verify(32'h0000_07FC, 32'hFFFF_FFFE, "Last address (2047)");
        
        // Test 7: Read without write (uninitialized after reset)
        $display("\n--- Test 7: Uninitialized Read ---");
        reset_cache();
        read_verify(32'h0000_0500, 32'h0000_0000, "Read uninitialized address");
        
        // Test 8: Simultaneous write and read (different addresses)
        $display("\n--- Test 8: Concurrent Operations ---");
        write_instruction(32'h0000_0020, 32'h2222_2222);
        r_addr = 32'h0000_0024;  // Read different address
        @(posedge clk);
        #1;
        write_instruction(32'h0000_0024, 32'h3333_3333);
        read_verify(32'h0000_0020, 32'h2222_2222, "Concurrent - Read address 0x20");
        read_verify(32'h0000_0024, 32'h3333_3333, "Concurrent - Read address 0x24");
        
        // Test 9: NOP instruction pattern
        $display("\n--- Test 9: Common Instructions ---");
        write_instruction(32'h0000_0030, 32'h0000_0013);  // NOP (ADDI x0, x0, 0)
        write_instruction(32'h0000_0034, 32'h00A00093);  // ADDI x1, x0, 10
        write_instruction(32'h0000_0038, 32'hFE208EE3);  // BEQ example
        
        read_verify(32'h0000_0030, 32'h0000_0013, "NOP instruction");
        read_verify(32'h0000_0034, 32'h00A00093, "ADDI instruction");
        read_verify(32'h0000_0038, 32'hFE208EE3, "BEQ instruction");
        
        // Test 10: Reset clears previous data
        $display("\n--- Test 10: Reset Clears Data ---");
        write_instruction(32'h0000_0040, 32'hABCD_EF01);
        read_verify(32'h0000_0040, 32'hABCD_EF01, "Before reset");
        reset_cache();
        read_verify(32'h0000_0040, 32'h0000_0000, "After reset - should be 0");
        
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
