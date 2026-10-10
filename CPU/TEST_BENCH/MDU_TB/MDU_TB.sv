`timescale 1ns/1ps
`include "sabit_veriler.vh"

module MDU_TB;

    reg[`DATA_WIDTH-1:0] s1;
    reg[`DATA_WIDTH-1:0] s2;
    reg[`FUNCT3_WIDTH-1:0] funct3;
    wire[`DATA_WIDTH-1:0] d3;

    MDU uut (
        .s1(s1),
        .s2(s2),
        .funct3(funct3),
        .d3(d3)
    );

    integer pass_count;
    integer fail_count;
    integer test_count;
    reg [63:0] current_test_name;

    // Named operation codes to mirror ALU_tb style for waveform visibility
    wire [2:0] MUL     = 3'b000;
    wire [2:0] MULH    = 3'b001;
    wire [2:0] MULHSU  = 3'b010;
    wire [2:0] MULHU   = 3'b011;
    wire [2:0] DIV     = 3'b100;
    wire [2:0] DIVU    = 3'b101;
    wire [2:0] REM     = 3'b110;
    wire [2:0] REMU    = 3'b111;

    // expose current funct3 value as a named wire for waveform viewers
    wire [2:0] FUNCT3_CODE = funct3;

    // Golden model to compute expected results
    function [31:0] golden;
        input [31:0] a_in;
        input [31:0] b_in;
        input [2:0] op;
        reg signed [31:0] a_s;
        reg signed [31:0] b_s;
        reg signed [63:0] sprod;
        reg signed [63:0] sprod2;
        reg [63:0] uprod;
        begin
            a_s = a_in;
            b_s = b_in;
            sprod = a_s * b_s;
            uprod = a_in * b_in;
            sprod2 = a_s * $signed({1'b0, b_in});
            case (op)
                MUL: golden = sprod[31:0];                         // MUL (low)
                MULH: golden = sprod[63:32];                        // MULH (signed high)
                MULHSU: golden = sprod2[63:32];                       // MULHSU (signed x unsigned high)
                MULHU: golden = uprod[63:32];                        // MULHU (unsigned high)
                DIV: begin                                         // DIV (signed)
                    if (b_in == 32'b0) golden = 32'hFFFFFFFF;
                    else golden = a_s / b_s;
                end
                DIVU: begin                                         // DIVU (unsigned)
                    if (b_in == 32'b0) golden = 32'hFFFFFFFE;
                    else golden = a_in / b_in;
                end
                REM: begin                                         // REM (signed)
                    if (b_in == 32'b0) golden = a_in;
                    else golden = a_s % b_s;
                end
                REMU: begin                                         // REMU (unsigned)
                    if (b_in == 32'b0) golden = a_in;
                    else golden = a_in % b_in;
                end
                default: golden = 32'b0;
            endcase
        end
    endfunction

    // Task to apply inputs and check result (shows test name like ALU_tb)
    task do_check;
        input [31:0] a_in;
        input [31:0] b_in;
        input [2:0] op;
        input [63:0] test_name; // up to 8 ASCII chars
        reg [31:0] exp;
        begin
            test_count = test_count + 1;
            current_test_name = test_name; // drive a visible register for waveform
            s1 = a_in;
            s2 = b_in;
            funct3 = op;
            #10; // allow combinational propagation and make label visible in waveform
            exp = golden(a_in, b_in, op);
            if (d3 !== exp) begin
                $display("[FAIL] %0s | op=%b s1=0x%h s2=0x%h expected=0x%h got=0x%h", current_test_name, op, a_in, b_in, exp, d3);
                fail_count = fail_count + 1;
            end else begin
                $display("[PASS] %0s | op=%b s1=0x%h s2=0x%h -> 0x%h", current_test_name, op, a_in, b_in, d3);
                pass_count = pass_count + 1;
            end
        end
    endtask

    initial begin
        pass_count = 0;
        fail_count = 0;
        test_count = 0;
        current_test_name = "        ";

        $display("\n--- MDU Testbench: Starting tests ---\n");

        // Basic small values
        do_check(32'd6, 32'd7, MUL, "MUL     ");
        do_check(32'd6, 32'd7, MULH, "MULH    ");
        do_check(32'd6, 32'd7, MULHSU, "MULHSU  ");
        do_check(32'd6, 32'd7, MULHU, "MULHU   ");
        do_check(32'd6, 32'd7, DIV, "DIV     ");
        do_check(32'd6, 32'd7, DIVU, "DIVU    ");
        do_check(32'd6, 32'd7, REM, "REM     ");
        do_check(32'd6, 32'd7, REMU, "REMU    ");

        // Divisible and remainder cases
        do_check(32'd20, 32'd4, DIV, "DIV     ");
        do_check(32'd20, 32'd4, DIVU, "DIVU    ");
        do_check(32'd20, 32'd6, REM, "REM     ");
        do_check(32'd20, 32'd6, REMU, "REMU    ");

        // Large values to exercise high halves
        do_check(32'd200000, 32'd60000, MUL, "MUL     ");
        do_check(32'd200000, 32'd60000, MULH, "MULH    ");
        do_check(32'd200000, 32'd60000, MULHSU, "MULHSU  ");
        do_check(32'd200000, 32'd60000, MULHU, "MULHU   ");

        // Negative and mixed-sign behavior (use two's complement hex constants)
        do_check(32'hFFFFFFEC, 32'd6, MUL, "MUL_NEG "); // -20 * 6
        do_check(32'hFFFFFFEC, 32'd6, MULH, "MULH_NEG");
        do_check(32'd20, 32'hFFFFFFFA, DIV, "DIV_NEG "); // 20 / -6 (signed)
        do_check(32'hFFFFFFEC, 32'hFFFFFFFA, DIV, "DIV_NEG2"); // -20 / -6 (signed)

        // Unsigned edge cases
        do_check(32'hFFFFFFFF, 32'd2, MUL, "MUL_FF  ");
        do_check(32'hFFFFFFFF, 32'd2, MULHU, "MULHU_FF");
        do_check(32'hFFFFFFFF, 32'd2, DIVU, "DIVU_FF ");

        // Divide-by-zero expected behavior
        do_check(32'd12345, 32'd0, DIV, "DIV_Z  "); // DIV -> 0xFFFFFFFF
        do_check(32'd12345, 32'd0, DIVU, "DIVU_Z "); // DIVU -> 0xFFFFFFFE
        do_check(32'd12345, 32'd0, REM, "REM_Z  "); // REM -> s1
        do_check(32'd12345, 32'd0, REMU, "REMU_Z "); // REMU -> s1

        // More edge / sign cases
        do_check(32'h80000000, 32'hFFFFFFFF, MUL, "MUL_MIN ");
        do_check(32'h80000000, 32'hFFFFFFFF, MULH, "MULH_MIN");

        $display("\n--- MDU Testbench: Summary ---");
        $display("Total = %0d", test_count);
        $display("PASS = %0d, FAIL = %0d\n", pass_count, fail_count);
        if (fail_count) $display("Some tests failed. Check failures above.");
        else $display("All tests passed.");

        $finish;
    end

    initial begin
        $dumpfile("MDU_TB.vcd");
        $dumpvars(0, MDU_TB);
    end

endmodule
