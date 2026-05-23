`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
`timescale 1ns / 1ps

module ALU_tb;

    reg  [`DATA_WIDTH-1:0]  s1;
    reg  [`DATA_WIDTH-1:0]  s2;
    reg  [`ALU_CNTR-1:0]    ALU_CNTR;
    wire [`DATA_WIDTH-1:0]  ALU_OUT;

    
    ALU uut (
        .s1(s1),
        .s2(s2),
        .ALU_CNTR(ALU_CNTR),
        .ALU_OUT(ALU_OUT)
    );

   
    localparam [3:0] ADD  = 4'b0000,
                     SUB  = 4'b0001,
                     OR   = 4'b0010,
                     AND  = 4'b0011,
                     XOR  = 4'b0100,
                     SLL  = 4'b0101,
                     SRL  = 4'b0110,
                     SRA  = 4'b0111,
                     SLT  = 4'b1000,
                     SLTU = 4'b1001,
                     EQ   = 4'b1010,
                     GE   = 4'b1011,
                     LT   = 4'b1100,
                     NE   = 4'b1101,
                     LTU  = 4'b1110,
                     GEU  = 4'b1111;

    // -------------------------------------------------------
    // Test Counters
    // -------------------------------------------------------
    integer pass_count = 0;
    integer fail_count = 0;
    integer test_count = 0;

    // -------------------------------------------------------
    // Check Task – compares ALU_OUT against expected value
    // -------------------------------------------------------
    task check;
        input [`DATA_WIDTH-1:0] expected;
        input [63:0] test_name; // 8 ASCII chars max
        begin
            test_count = test_count + 1;
            if (ALU_OUT !== expected) begin
                $display("[FAIL] %0s | s1=%h  s2=%h  ALU_CNTR=%b | Got=%h  Expected=%h",
                         test_name, s1, s2, ALU_CNTR, ALU_OUT, expected);
                fail_count = fail_count + 1;
            end else begin
                $display("[PASS] %0s | s1=%h  s2=%h  ALU_CNTR=%b | Out=%h",
                         test_name, s1, s2, ALU_CNTR, ALU_OUT);
                pass_count = pass_count + 1;
            end
        end
    endtask

    // -------------------------------------------------------
    // Main Stimulus
    // -------------------------------------------------------
    initial begin
        // Optional: waveform dump
        $dumpfile("ALU_tb.vcd");
        $dumpvars(0, ALU_tb);

        $display("========================================");
        $display("       ALU Test Bench Started");
        $display("========================================");

        // ===================================================
        //  ADD (0000)
        // ===================================================
        s1 = 32'd10;     s2 = 32'd20;      ALU_CNTR = ADD; #10;
        check(32'd30, "ADD     ");

        s1 = 32'd0;      s2 = 32'd0;       ALU_CNTR = ADD; #10;
        check(32'd0,  "ADD_ZERO");

        s1 = 32'hFFFFFFFF; s2 = 32'd1;     ALU_CNTR = ADD; #10;
        check(32'd0,  "ADD_OVFL");   // overflow wraps around

        s1 = 32'hFFFFFFFE; s2 = 32'hFFFFFFFE; ALU_CNTR = ADD; #10;
        check(32'hFFFFFFFC, "ADD_NEG ");   // -2 + -2 = -4

        // ===================================================
        //  SUB (0001)
        // ===================================================
        s1 = 32'd30;     s2 = 32'd10;      ALU_CNTR = SUB; #10;
        check(32'd20, "SUB     ");

        s1 = 32'd10;     s2 = 32'd30;      ALU_CNTR = SUB; #10;
        check(32'hFFFFFFEC, "SUB_NEG ");   // 10 - 30 = -20 (two's complement)

        s1 = 32'd0;      s2 = 32'd0;       ALU_CNTR = SUB; #10;
        check(32'd0,  "SUB_ZERO");

        // ===================================================
        //  OR (0010)
        // ===================================================
        s1 = 32'hFF00FF00; s2 = 32'h00FF00FF; ALU_CNTR = OR; #10;
        check(32'hFFFFFFFF, "OR      ");

        s1 = 32'h00000000; s2 = 32'h00000000; ALU_CNTR = OR; #10;
        check(32'h00000000, "OR_ZERO ");

        s1 = 32'hAAAAAAAA; s2 = 32'h55555555; ALU_CNTR = OR; #10;
        check(32'hFFFFFFFF, "OR_CHKR ");

        // ===================================================
        //  AND (0011)
        // ===================================================
        s1 = 32'hFF00FF00; s2 = 32'h00FF00FF; ALU_CNTR = AND; #10;
        check(32'h00000000, "AND     ");

        s1 = 32'hFFFFFFFF; s2 = 32'h12345678; ALU_CNTR = AND; #10;
        check(32'h12345678, "AND_MASK");

        s1 = 32'hAAAAAAAA; s2 = 32'hFFFFFFFF; ALU_CNTR = AND; #10;
        check(32'hAAAAAAAA, "AND_AA  ");

        // ===================================================
        //  XOR (0100)
        // ===================================================
        s1 = 32'hFFFFFFFF; s2 = 32'hFFFFFFFF; ALU_CNTR = XOR; #10;
        check(32'h00000000, "XOR_SAME");

        s1 = 32'hFF00FF00; s2 = 32'h00FF00FF; ALU_CNTR = XOR; #10;
        check(32'hFFFFFFFF, "XOR     ");

        s1 = 32'h00000000; s2 = 32'h12345678; ALU_CNTR = XOR; #10;
        check(32'h12345678, "XOR_ZERO");

        // ===================================================
        //  SLL – Shift Left Logical (0101)
        // ===================================================
        s1 = 32'd1;      s2 = 32'd4;       ALU_CNTR = SLL; #10;
        check(32'd16, "SLL     ");    // 1 << 4 = 16

        s1 = 32'hDEADBEEF; s2 = 32'd0;    ALU_CNTR = SLL; #10;
        check(32'hDEADBEEF, "SLL_0   ");   // shift by 0

        s1 = 32'd1;      s2 = 32'd31;      ALU_CNTR = SLL; #10;
        check(32'h80000000, "SLL_31  ");   // 1 << 31

        // ===================================================
        //  SRL – Shift Right Logical (0110)
        // ===================================================
        s1 = 32'd16;     s2 = 32'd4;       ALU_CNTR = SRL; #10;
        check(32'd1,  "SRL     ");    // 16 >> 4 = 1

        s1 = 32'h80000000; s2 = 32'd31;    ALU_CNTR = SRL; #10;
        check(32'd1,  "SRL_MSB ");    // logical: MSB filled with 0

        s1 = 32'hFFFFFFFF; s2 = 32'd16;    ALU_CNTR = SRL; #10;
        check(32'h0000FFFF, "SRL_FF  ");

        // ===================================================
        //  SRA – Shift Right Arithmetic (0111)
        // ===================================================
        s1 = 32'h80000000; s2 = 32'd4;     ALU_CNTR = SRA; #10;
        check(32'hF8000000, "SRA_NEG ");   // sign-extend: MSB=1

        s1 = 32'h7FFFFFFF; s2 = 32'd4;     ALU_CNTR = SRA; #10;
        check(32'h07FFFFFF, "SRA_POS ");   // MSB=0, no sign extension

        s1 = 32'hFFFFFFFF; s2 = 32'd31;    ALU_CNTR = SRA; #10;
        check(32'hFFFFFFFF, "SRA_ALL ");   // -1 >>> 31 = -1

        // ===================================================
        //  SLT – Set Less Than (signed) (1000)
        // ===================================================
        s1 = 32'd5;      s2 = 32'd10;      ALU_CNTR = SLT; #10;
        check(32'd1,  "SLT_T   ");    // 5 < 10 → 1

        s1 = 32'd10;     s2 = 32'd5;       ALU_CNTR = SLT; #10;
        check(32'd0,  "SLT_F   ");    // 10 < 5 → 0

        s1 = 32'hFFFFFFFF; s2 = 32'd1;     ALU_CNTR = SLT; #10;
        check(32'd1,  "SLT_NEG ");    // -1 < 1 (signed) → 1

        s1 = 32'd5;      s2 = 32'd5;       ALU_CNTR = SLT; #10;
        check(32'd0,  "SLT_EQ  ");    // equal → 0

        // ===================================================
        //  SLTU – Set Less Than Unsigned (1001)
        // ===================================================
        s1 = 32'd5;      s2 = 32'd10;      ALU_CNTR = SLTU; #10;
        check(32'd1,  "SLTU_T  ");

        s1 = 32'd10;     s2 = 32'd5;       ALU_CNTR = SLTU; #10;
        check(32'd0,  "SLTU_F  ");

        s1 = 32'hFFFFFFFF; s2 = 32'd1;     ALU_CNTR = SLTU; #10;
        check(32'd0,  "SLTU_BIG");    // 0xFFFFFFFF > 1 (unsigned) → 0

        // ===================================================
        //  EQ – Equal (1010)
        // ===================================================
        s1 = 32'd42;     s2 = 32'd42;      ALU_CNTR = EQ; #10;
        check(32'd1,  "EQ_T    ");

        s1 = 32'd42;     s2 = 32'd99;      ALU_CNTR = EQ; #10;
        check(32'd0,  "EQ_F    ");

        s1 = 32'd0;      s2 = 32'd0;       ALU_CNTR = EQ; #10;
        check(32'd1,  "EQ_ZERO ");

        // ===================================================
        //  GE – Greater or Equal (signed) (1011)
        // ===================================================
        s1 = 32'd20;     s2 = 32'd10;      ALU_CNTR = GE; #10;
        check(32'd1,  "GE_GT   ");

        s1 = 32'd10;     s2 = 32'd10;      ALU_CNTR = GE; #10;
        check(32'd1,  "GE_EQ   ");

        s1 = 32'd5;      s2 = 32'd10;      ALU_CNTR = GE; #10;
        check(32'd0,  "GE_LT   ");

        s1 = 32'hFFFFFFFF; s2 = 32'd0;     ALU_CNTR = GE; #10;
        check(32'd0,  "GE_NEG  ");    // -1 >= 0 → 0

        // ===================================================
        //  LT – Less Than (signed) (1100)
        // ===================================================
        s1 = 32'd5;      s2 = 32'd10;      ALU_CNTR = LT; #10;
        check(32'd1,  "LT_T    ");

        s1 = 32'd10;     s2 = 32'd5;       ALU_CNTR = LT; #10;
        check(32'd0,  "LT_F    ");

        s1 = 32'h80000000; s2 = 32'd0;     ALU_CNTR = LT; #10;
        check(32'd1,  "LT_MIN  ");    // INT_MIN < 0 → 1

        // ===================================================
        //  NE – Not Equal (1101)
        // ===================================================
        s1 = 32'd42;     s2 = 32'd99;      ALU_CNTR = NE; #10;
        check(32'd1,  "NE_T    ");

        s1 = 32'd42;     s2 = 32'd42;      ALU_CNTR = NE; #10;
        check(32'd0,  "NE_F    ");

        // ===================================================
        //  LTU – Less Than Unsigned (1110)
        // ===================================================
        s1 = 32'd5;      s2 = 32'd10;      ALU_CNTR = LTU; #10;
        check(32'd1,  "LTU_T   ");

        s1 = 32'hFFFFFFFF; s2 = 32'd1;     ALU_CNTR = LTU; #10;
        check(32'd0,  "LTU_BIG ");    // 0xFFFFFFFF > 1 unsigned

        s1 = 32'd0;      s2 = 32'hFFFFFFFF; ALU_CNTR = LTU; #10;
        check(32'd1,  "LTU_ZERO");

        // ===================================================
        //  GEU – Greater or Equal Unsigned (1111)
        // ===================================================
        s1 = 32'hFFFFFFFF; s2 = 32'd1;     ALU_CNTR = GEU; #10;
        check(32'd1,  "GEU_BIG ");

        s1 = 32'd10;     s2 = 32'd10;      ALU_CNTR = GEU; #10;
        check(32'd1,  "GEU_EQ  ");

        s1 = 32'd0;      s2 = 32'd1;       ALU_CNTR = GEU; #10;
        check(32'd0,  "GEU_LT  ");

        // ===================================================
        //  Summary
        // ===================================================
        $display("========================================");
        $display("       ALU Test Bench Finished");
        $display("========================================");
        $display("  Total : %0d", test_count);
        $display("  PASS  : %0d", pass_count);
        $display("  FAIL  : %0d", fail_count);
        $display("========================================");

        if (fail_count == 0)
            $display(">>> ALL TESTS PASSED <<<");
        else
            $display(">>> SOME TESTS FAILED <<<");

        $finish;
    end

endmodule
