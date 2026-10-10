`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
`timescale 1ns / 1ps

module MEM_TB;

    // Clock and Reset
    reg clk;
    reg reset;
    
    // Input signals
    reg [`DATA_WIDTH-1:0] execute_result_in;
    reg [`DATA_WIDTH-1:0] mem_write_data;
    reg [`WB_CNTRL-1:0] wb_controlM;
    reg reg_write;
    reg mem_write;
    reg [`ADDRESS_WIDTH-1:0] rdM;
    
    // Output signals
    wire [`ADDRESS_WIDTH-1:0] rdM_hazard_out;
    wire reg_write_hazard;
    wire reg_write_out;
    wire [`WB_CNTRL-1:0] wb_control_out;
    wire [`ADDRESS_WIDTH-1:0] rdW;
    wire [`DATA_WIDTH-1:0] execute_result_out;
    wire [`DATA_WIDTH-1:0] mem_result_out;
    wire [`DATA_WIDTH-1:0] wb_result_out;
    
    // Test counters
    integer pass_count = 0;
    integer fail_count = 0;
    integer test_count = 0;
    
    // Clock parameters
    localparam CLK_PERIOD = 10;
    
    // Instantiate the Unit Under Test (UUT)
    MEM uut (
        .clk(clk),
        .reset(reset),
        .execute_result_in(execute_result_in),
        .mem_write_data(mem_write_data),
        .wb_controlM(wb_controlM),
        .reg_write(reg_write),
        .mem_write(mem_write),
        .rdM(rdM),
        .rdM_hazard_out(rdM_hazard_out),
        .reg_write_hazard(reg_write_hazard),
        .reg_write_out(reg_write_out),
        .wb_control_out(wb_control_out),
        .rdW(rdW),
        .execute_result_out(execute_result_out),
        .mem_result_out(mem_result_out),
        .wb_result_out(wb_result_out)
    );
    
    // Clock generation
    initial begin
        clk = 0;
        forever #(CLK_PERIOD/2) clk = ~clk;
    end
    
    // Check task for 32-bit data
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
    
    // Check task for 5-bit addresses
    task check_addr;
        input [`ADDRESS_WIDTH-1:0] expected;
        input [`ADDRESS_WIDTH-1:0] actual;
        input [200*8:0] test_name;
        begin
            test_count = test_count + 1;
            if (expected === actual) begin
                $display("[PASS] Test %0d: %s | Expected: 0x%02h, Got: 0x%02h", 
                         test_count, test_name, expected, actual);
                pass_count = pass_count + 1;
            end else begin
                $display("[FAIL] Test %0d: %s | Expected: 0x%02h, Got: 0x%02h", 
                         test_count, test_name, expected, actual);
                fail_count = fail_count + 1;
            end
        end
    endtask
    
    // Check task for 2-bit control signals
    task check_control;
        input [`WB_CNTRL-1:0] expected;
        input [`WB_CNTRL-1:0] actual;
        input [200*8:0] test_name;
        begin
            test_count = test_count + 1;
            if (expected === actual) begin
                $display("[PASS] Test %0d: %s | Expected: 0b%02b, Got: 0b%02b", 
                         test_count, test_name, expected, actual);
                pass_count = pass_count + 1;
            end else begin
                $display("[FAIL] Test %0d: %s | Expected: 0b%02b, Got: 0b%02b", 
                         test_count, test_name, expected, actual);
                fail_count = fail_count + 1;
            end
        end
    endtask
    
    // Check task for 1-bit signals
    task check_bit;
        input expected;
        input actual;
        input [200*8:0] test_name;
        begin
            test_count = test_count + 1;
            if (expected === actual) begin
                $display("[PASS] Test %0d: %s | Expected: %0b, Got: %0b", 
                         test_count, test_name, expected, actual);
                pass_count = pass_count + 1;
            end else begin
                $display("[FAIL] Test %0d: %s | Expected: %0b, Got: %0b", 
                         test_count, test_name, expected, actual);
                fail_count = fail_count + 1;
            end
        end
    endtask
    
    // Helper task: Reset module
    task reset_module;
        begin
            reset = 1;
            execute_result_in = 0;
            mem_write_data = 0;
            wb_controlM = 0;
            reg_write = 0;
            mem_write = 0;
            rdM = 0;
            @(posedge clk);
            #1;
            reset = 0;
            @(posedge clk);
            #1;
        end
    endtask
    
    // Helper task: Write to memory
    task write_memory;
        input [`DATA_WIDTH-1:0] address;
        input [`DATA_WIDTH-1:0] data;
        begin
            execute_result_in = address;
            mem_write_data = data;
            mem_write = 1;
            @(posedge clk);
            #1;
            mem_write = 0;
        end
    endtask
    
    // Helper task: Read from memory and verify
    task read_memory_verify;
        input [`DATA_WIDTH-1:0] address;
        input [`DATA_WIDTH-1:0] expected;
        input [200*8:0] test_name;
        begin
            execute_result_in = address;
            mem_write = 0;
            @(posedge clk);
            #1;
            check_data(expected, mem_result_out, test_name);
        end
    endtask
    
    // Main test sequence
    initial begin
        $dumpfile("MEM_TB.vcd");
        $dumpvars(0, MEM_TB);
        
        $display("========================================");
        $display("      MEM Stage Test Bench");
        $display("========================================");
        
        // Initialize signals
        clk = 0;
        reset = 0;
        execute_result_in = 0;
        mem_write_data = 0;
        wb_controlM = 0;
        reg_write = 0;
        mem_write = 0;
        rdM = 0;
        
        // Wait for initialization
        #20;
        
        // Test 1: Reset behavior
        $display("\n--- Test 1: Reset Behavior ---");
        reset_module();
        check_bit(0, reg_write_out, "Reset - reg_write_out should be 0");
        check_control(2'b00, wb_control_out, "Reset - wb_control_out should be 0");
        check_addr(5'h00, rdW, "Reset - rdW should be 0");
        check_data(32'h0000_0000, mem_result_out, "Reset - mem_result_out should be 0");
        
        // Test 2: Pass-through signals (combinational)
        $display("\n--- Test 2: Combinational Pass-Through ---");
        execute_result_in = 32'hDEAD_BEEF;
        rdM = 5'h0A;
        reg_write = 1;
        #1;
        check_data(32'hDEAD_BEEF, execute_result_out, "Pass-through execute_result");
        check_addr(5'h0A, rdM_hazard_out, "Pass-through rdM to hazard");
        check_bit(1, reg_write_hazard, "Pass-through reg_write to hazard");
        
        // Test 3: Pipeline register propagation
        $display("\n--- Test 3: Pipeline Register Propagation ---");
        execute_result_in = 32'h1234_5678;
        mem_write_data = 32'h0000_0000;
        wb_controlM = 2'b01;
        reg_write = 1;
        mem_write = 0;
        rdM = 5'h05;
        @(posedge clk);
        #1;
        check_bit(1, reg_write_out, "Pipeline - reg_write propagated");
        check_control(2'b01, wb_control_out, "Pipeline - wb_control propagated");
        check_addr(5'h05, rdW, "Pipeline - rdM propagated to rdW");
        
        // Test 4: Memory write operation
        $display("\n--- Test 4: Memory Write Operations ---");
        reset_module();
        write_memory(32'h0000_0000, 32'hCAFE_BABE);
        write_memory(32'h0000_0004, 32'hDEAD_BEEF);
        write_memory(32'h0000_0008, 32'h1234_5678);
        $display("Written data to addresses 0x00, 0x04, 0x08");
        
        // Test 5: Memory read operation
        $display("\n--- Test 5: Memory Read Operations ---");
        read_memory_verify(32'h0000_0000, 32'hCAFE_BABE, "Read address 0x00");
        read_memory_verify(32'h0000_0004, 32'hDEAD_BEEF, "Read address 0x04");
        read_memory_verify(32'h0000_0008, 32'h1234_5678, "Read address 0x08");
        
        // Test 6: Write-Read sequence same address
        $display("\n--- Test 6: Write-Read Same Address ---");
        write_memory(32'h0000_0010, 32'hAAAA_AAAA);
        read_memory_verify(32'h0000_0010, 32'hAAAA_AAAA, "Write then read 0x10");
        
        // Test 7: Overwrite data
        $display("\n--- Test 7: Overwrite Existing Data ---");
        write_memory(32'h0000_0000, 32'h9999_9999);
        read_memory_verify(32'h0000_0000, 32'h9999_9999, "Overwritten address 0x00");
        
        // Test 8: Write enable control
        $display("\n--- Test 8: Write Enable Control ---");
        write_memory(32'h0000_0020, 32'h1111_1111);
        // Attempt write without enable
        execute_result_in = 32'h0000_0020;
        mem_write_data = 32'h2222_2222;
        mem_write = 0;
        @(posedge clk);
        #1;
        read_memory_verify(32'h0000_0020, 32'h1111_1111, "Write disabled - data unchanged");
        
        // Test 9: Multiple control signal combinations
        $display("\n--- Test 9: WB Control Signal Combinations ---");
        execute_result_in = 32'hABCD_0000;
        wb_controlM = 2'b00;
        reg_write = 0;
        rdM = 5'h10;
        @(posedge clk);
        #1;
        check_control(2'b00, wb_control_out, "WB control = 00");
        check_bit(0, reg_write_out, "reg_write = 0");
        check_addr(5'h10, rdW, "rdW = 0x10");
        
        wb_controlM = 2'b11;
        reg_write = 1;
        rdM = 5'h1F;
        @(posedge clk);
        #1;
        check_control(2'b11, wb_control_out, "WB control = 11");
        check_bit(1, reg_write_out, "reg_write = 1");
        check_addr(5'h1F, rdW, "rdW = 0x1F");
        
        // Test 10: Register address range
        $display("\n--- Test 10: Register Address Range ---");
        rdM = 5'h00;
        @(posedge clk);
        #1;
        check_addr(5'h00, rdW, "Min register address (0)");
        
        rdM = 5'h1F;
        @(posedge clk);
        #1;
        check_addr(5'h1F, rdW, "Max register address (31)");
        
        // Test 11: Boundary memory addresses
        $display("\n--- Test 11: Boundary Memory Addresses ---");
        write_memory(32'h0000_0000, 32'h0000_0001);
        write_memory(32'h0000_07FC, 32'hFFFF_FFFE);
        read_memory_verify(32'h0000_0000, 32'h0000_0001, "First cache address");
        read_memory_verify(32'h0000_07FC, 32'hFFFF_FFFE, "Last cache address");
        
        // Test 12: Load instruction simulation
        $display("\n--- Test 12: Load Instruction Simulation ---");
        // Pre-write data to memory
        write_memory(32'h0000_0100, 32'h5555_5555);
        // Simulate LOAD: address in execute_result, mem_write=0
        execute_result_in = 32'h0000_0100;
        mem_write = 0;
        reg_write = 1;
        rdM = 5'h0C;
        wb_controlM = 2'b10;  // Select memory data for WB
        @(posedge clk);
        #1;
        check_data(32'h5555_5555, mem_result_out, "LOAD - data from memory");
        check_bit(1, reg_write_out, "LOAD - reg_write enabled");
        check_addr(5'h0C, rdW, "LOAD - destination register");
        
        // Test 13: Store instruction simulation
        $display("\n--- Test 13: Store Instruction Simulation ---");
        execute_result_in = 32'h0000_0200;
        mem_write_data = 32'h7777_7777;
        mem_write = 1;
        reg_write = 0;
        rdM = 5'h00;
        wb_controlM = 2'b00;
        @(posedge clk);
        #1;
        check_bit(0, reg_write_out, "STORE - reg_write disabled");
        // Verify data was written
        read_memory_verify(32'h0000_0200, 32'h7777_7777, "STORE - data written to memory");
        
        // Test 14: ALU-only instruction (no memory access)
        $display("\n--- Test 14: ALU Result Pass-Through ---");
        execute_result_in = 32'hABCD_1234;
        mem_write = 0;
        reg_write = 1;
        rdM = 5'h08;
        wb_controlM = 2'b01;  // Select ALU result for WB
        @(posedge clk);
        #1;
        check_data(32'hABCD_1234, execute_result_out, "ALU result pass-through (comb)");
        check_bit(1, reg_write_out, "ALU op - reg_write enabled");
        check_addr(5'h08, rdW, "ALU op - destination register");
        
        // Test 15: Hazard detection signals
        $display("\n--- Test 15: Hazard Detection Signals ---");
        rdM = 5'h0F;
        reg_write = 1;
        execute_result_in = 32'h8888_8888;
        #1;
        check_addr(5'h0F, rdM_hazard_out, "Hazard - immediate rdM forward");
        check_bit(1, reg_write_hazard, "Hazard - immediate reg_write forward");
        check_data(32'h8888_8888, execute_result_out, "Hazard - immediate result forward");
        
        // Test 16: Rapid instruction sequence
        $display("\n--- Test 16: Rapid Instruction Sequence ---");
        // Instruction 1: STORE
        execute_result_in = 32'h0000_0300;
        mem_write_data = 32'h1111_1111;
        mem_write = 1;
        reg_write = 0;
        rdM = 5'h00;
        @(posedge clk);
        #1;
        
        // Instruction 2: LOAD
        execute_result_in = 32'h0000_0300;
        mem_write = 0;
        reg_write = 1;
        rdM = 5'h0A;
        @(posedge clk);
        #1;
        check_data(32'h1111_1111, mem_result_out, "Rapid seq - load after store");
        
        // Instruction 3: ALU
        execute_result_in = 32'h2222_2222;
        reg_write = 1;
        rdM = 5'h0B;
        @(posedge clk);
        #1;
        
        // Test 17: Reset during operation
        $display("\n--- Test 17: Reset During Operation ---");
        execute_result_in = 32'h0000_0400;
        mem_write_data = 32'hFFFF_FFFF;
        mem_write = 1;
        reg_write = 1;
        rdM = 5'h15;
        wb_controlM = 2'b10;
        @(posedge clk);
        #1;
        reset_module();
        check_bit(0, reg_write_out, "After reset - reg_write cleared");
        check_addr(5'h00, rdW, "After reset - rdW cleared");
        check_data(32'h0000_0000, mem_result_out, "After reset - mem_result cleared");
        
        // Test 18: Data patterns
        $display("\n--- Test 18: Various Data Patterns ---");
        write_memory(32'h0000_0500, 32'h0000_0000);  // All zeros
        write_memory(32'h0000_0504, 32'hFFFF_FFFF);  // All ones
        write_memory(32'h0000_0508, 32'hA5A5_A5A5);  // Alternating
        write_memory(32'h0000_050C, 32'h5A5A_5A5A);  // Inverse alternating
        
        read_memory_verify(32'h0000_0500, 32'h0000_0000, "Pattern - all zeros");
        read_memory_verify(32'h0000_0504, 32'hFFFF_FFFF, "Pattern - all ones");
        read_memory_verify(32'h0000_0508, 32'hA5A5_A5A5, "Pattern - alternating");
        read_memory_verify(32'h0000_050C, 32'h5A5A_5A5A, "Pattern - inverse alt");
        
        // Test 19: Pipeline preservation across multiple cycles
        $display("\n--- Test 19: Pipeline Data Preservation ---");
        execute_result_in = 32'h1010_1010;
        reg_write = 1;
        rdM = 5'h07;
        wb_controlM = 2'b01;
        @(posedge clk);
        #1;
        check_addr(5'h07, rdW, "First cycle - rdW has new value");

        // Cycle 2  
        rdM = 5'h08;
        #1;  // BEFORE clock edge
        check_addr(5'h07, rdW, "Still holding old value before clock");

        @(posedge clk);
        #1;
        check_addr(5'h08, rdW, "Second cycle - rdW updated to new value");
        
        // Change inputs
        execute_result_in = 32'h2020_2020;
        @(posedge clk);
        #1;
        
        // Check that previous values are still in pipeline output
        check_bit(1, reg_write_out, "Pipeline preserved - reg_write");
        
        // Test 20: Multiple reads same address
        $display("\n--- Test 20: Multiple Reads Same Address ---");
        write_memory(32'h0000_0600, 32'hBEEF_CAFE);
        read_memory_verify(32'h0000_0600, 32'hBEEF_CAFE, "Multiple read - first");
        read_memory_verify(32'h0000_0600, 32'hBEEF_CAFE, "Multiple read - second");
        read_memory_verify(32'h0000_0600, 32'hBEEF_CAFE, "Multiple read - third");
        
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
        $display("========================================");
        $display("\nNOTE: Line 49 in MEM.v has a bug:");
        $display("      Uses 'exe_result_in' instead of 'execute_result_in'");
        $display("      This will cause wb_result_out pipeline errors.");
        $display("========================================\n");
        
        $finish;
    end
    
endmodule
