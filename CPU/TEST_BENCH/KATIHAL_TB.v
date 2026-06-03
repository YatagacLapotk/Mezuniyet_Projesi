`define BEHAVIORAL_SIM
// Comment out the line above (or define it as `undef BEHAVIORAL_SIM) to run 
// post-implementation or post-synthesis functional simulation in Vivado.

`include "sabit_veriler.vh"

// =============================================================================
// KATIHAL (Top Module) Testbench
// =============================================================================
// Bu testbench, top modülünü (KATIHAL.v) tam entegrasyon seviyesinde test eder.
// Test edilen alt sistemler:
//   1. UART üzerinden program yükleme (gerçek seri zamanlama ile)
//   2. SPI üzerinden program yükleme (gerçek SPI zamanlama ile)
//   3. CPU'nun yüklenen programı çalıştırması
//   4. Reset davranışı
//   5. busy sinyali kontrolü
// =============================================================================

module KATIHAL_TB ();

    // -------------------------------------------
    // DUT Sinyalleri
    // -------------------------------------------
    reg clk;
    reg reset;
    reg rx_enable;
    reg uart_in;
    reg spi_enable;
    reg sclk_enable;
    reg miso;
    wire mosi;
    wire ss;
    wire busy;
    wire sclk;
    wire [15:0] data_mem_out;

    // Test takip değişkenleri
    integer test_pass = 0;
    integer test_fail = 0;
    reg loader_done_captured;
    integer cycle_count;

    always @(posedge clk) begin
        if (reset) begin
            loader_done_captured <= 0;
        end else begin
`ifdef BEHAVIORAL_SIM
            if (uut.PROGRAM_LOADER.done) begin
                loader_done_captured <= 1;
            end
`else
            loader_done_captured <= 0;
`endif
        end
    end

    // -------------------------------------------
    // DUT Bağlantısı
    // -------------------------------------------
    top uut (
        .clk(clk),
        .reset(reset),
        .rx_enable(rx_enable),
        .uart_in(uart_in),
        .spi_enable(spi_enable),
        .sclk_enable(sclk_enable),
        .miso(miso),
        .mosi(mosi),
        .ss(ss),
        .busy(busy),
        .sclk(sclk),
        .data_mem_out(data_mem_out)
    );

    // -------------------------------------------
    // 100 MHz Clock (10 ns periyot)
    // -------------------------------------------
    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end

    // -------------------------------------------
    // Baud Rate Zamanlama Sabitleri
    // -------------------------------------------
    localparam BAUD_TICKS = `CLK / `BAUD_RATE;  // 868 clock cycles per bit
    localparam SCLK_HALF_PERIOD = (`CLK / `BAUD_RATE) / 2; // 434 cycles

    // -------------------------------------------
    // Doğrulama Görevleri (Assertion Tasks)
    // -------------------------------------------
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

    // -------------------------------------------
    // Yardımcı: Register okuma (hiyerarşik erişim)
    // -------------------------------------------
    function [31:0] read_reg;
        input [4:0] idx;
        begin
`ifdef BEHAVIORAL_SIM
            read_reg = uut.CORE.DECODE.REG_FILE.REG32[idx];
`else
            read_reg = 32'h0;
`endif
        end
    endfunction

    function [31:0] read_icache;
        input [31:0] word_idx;
        begin
`ifdef BEHAVIORAL_SIM
            read_icache = uut.CORE.FETCH.I_CACHE.i_cache[word_idx];
`else
            read_icache = 32'h0;
`endif
        end
    endfunction

    task check_reg;
        input [255:0] test_name;
        input [4:0]   reg_idx;
        input [31:0]  expected;
        reg   [31:0]  actual;
        begin
`ifdef BEHAVIORAL_SIM
            actual = read_reg(reg_idx);
            if (actual === expected) begin
                $display("[PASS] %0s | x%0d = 0x%08X", test_name, reg_idx, actual);
                test_pass = test_pass + 1;
            end else begin
                $display("[FAIL] %0s | x%0d = 0x%08X (expected 0x%08X)", test_name, reg_idx, actual, expected);
                test_fail = test_fail + 1;
            end
`else
            $display("[INFO] %0s | Skipped hierarchical reg check (x%0d expected 0x%08X)", test_name, reg_idx, expected);
`endif
        end
    endtask

    // -------------------------------------------
    // UART Seri Byte Gönderme Görevi
    // -------------------------------------------
    task uart_send_byte;
        input [7:0] byte_val;
        integer bit_i;
        begin
            // Start bit (LOW) - tam bir bit süresi
            @(posedge clk);
            uart_in = 1'b0;
            repeat (BAUD_TICKS) @(posedge clk);

            // 8 data bit (LSB first) - her biri bir bit süresi
            for (bit_i = 0; bit_i < 8; bit_i = bit_i + 1) begin
                uart_in = byte_val[bit_i];
                repeat (BAUD_TICKS) @(posedge clk);
            end

            // Stop bit (HIGH) - tam bir bit süresi
            uart_in = 1'b1;
            repeat (BAUD_TICKS) @(posedge clk);
        end
    endtask

    // -------------------------------------------
    // UART ile 32-bit Kelime Gönderme (Little-Endian)
    // -------------------------------------------
    task uart_send_word;
        input [31:0] word_val;
        begin
            uart_send_byte(word_val[7:0]);
            uart_send_byte(word_val[15:8]);
            uart_send_byte(word_val[23:16]);
            uart_send_byte(word_val[31:24]);
        end
    endtask

    // -------------------------------------------
    // SPI Byte Gönderme Görevi
    // -------------------------------------------
    task spi_send_byte;
        input [7:0] byte_val;
        integer bit_i;
        begin
            // SPI master'ın START durumuna geçmesini bekle
            wait (ss == 1'b0);

            // İlk bit (MSB) negedge beklemeden hemen verilmeli
            miso = byte_val[7];

            // Kalan 7 bit için sclk negedge'lerinde güncelliyoruz
            for (bit_i = 6; bit_i >= 0; bit_i = bit_i - 1) begin
                // sclk negedge'i bekle (data setup)
                @(negedge sclk);
                miso = byte_val[bit_i];
            end

            // Master STOP durumuna geçmesini bekle
            wait (ss == 1'b1);
        end
    endtask

    // -------------------------------------------
    // SPI ile 32-bit Kelime Gönderme (Little-Endian)
    // -------------------------------------------
    task spi_send_word;
        input [31:0] word_val;
        begin
            spi_send_byte(word_val[7:0]);
            spi_send_byte(word_val[15:8]);
            spi_send_byte(word_val[23:16]);
            spi_send_byte(word_val[31:24]);
        end
    endtask

    // -------------------------------------------
    // Program Loader'ın DONE olmasını bekleme
    // -------------------------------------------
    task wait_loader_done;
        begin
`ifdef BEHAVIORAL_SIM
            wait (uut.PROGRAM_LOADER.done == 1'b1);
            @(posedge clk);
            @(posedge clk);
`else
            wait (busy == 1'b0);
`endif
        end
    endtask

    task wait_loader_done_timeout;
        input [31:0] max_cycles;
        input [255:0] test_name;
        integer cycle_count;
        begin
            cycle_count = 0;
            while (busy == 1'b1 && cycle_count < max_cycles) begin
                @(posedge clk);
                cycle_count = cycle_count + 1;
            end
            if (cycle_count >= max_cycles) begin
                $display("  [WARN] %0s: Loader DONE timeout", test_name);
            end
        end
    endtask

    // -------------------------------------------
    // Reset görevi
    // -------------------------------------------
    task do_reset;
        begin
            @(negedge clk);
            reset       = 1;
            rx_enable   = 1;
            uart_in     = 1;
            spi_enable  = 0;
            sclk_enable = 0;
            miso        = 0;
            repeat (10) @(posedge clk);
            @(negedge clk);
            reset = 0;
            repeat (5) @(posedge clk);
        end
    endtask

    // =========================================================================
    // ANA TEST SEKANSLARI
    // =========================================================================
    initial begin

        // -----------------------------------------------
        // Başlangıç Değerleri
        // -----------------------------------------------
        reset       = 1;
        rx_enable   = 1;    // UART RX başlangıçta pasif
        uart_in     = 1;    // UART hattı IDLE = HIGH
        spi_enable  = 0;    // SPI başlangıçta pasif
        sclk_enable = 0;
        miso        = 0;

        // Reset süresi
        repeat (10) @(posedge clk);
        @(negedge clk);
        reset = 0;
        repeat (5) @(posedge clk);

        // =============================================================
        // TEST 0: Reset Sonrası Başlangıç Durumu
        // =============================================================
        $display("\n============================================================");
        $display("  TEST 0: Reset Sonrasi Baslangic Durumu");
        $display("============================================================");

        check_1bit("busy (reset sonrasi)", busy, 1'b0);
`ifdef BEHAVIORAL_SIM
        check_1bit("loader done", uut.PROGRAM_LOADER.done, 1'b0);
        check_1bit("loader we", uut.PROGRAM_LOADER.we, 1'b0);
        check_1bit("cpu_halt", uut.cpu_halt, 1'b0);
        check("loader write_ptr", uut.PROGRAM_LOADER.write_ptr, `UART_ADDR);
`endif

        // =============================================================
        // TEST 1: UART ile Tek Kelime Yükleme
        // =============================================================
        $display("\n============================================================");
        $display("  TEST 1: UART ile Tek Kelime Yukleme (NOP)");
        $display("============================================================");

        // UART RX'i aktifle
        rx_enable = 0;

        // NOP komutunu gönder: 0x00000013
        $display("  [%0t] UART ile NOP (0x00000013) gonderiliyor...", $time);
        uart_send_word(32'h00000013);
        $display("  [%0t] UART gonderim tamamlandi", $time);

        // Hattı idle'a çek
        uart_in = 1;
        rx_enable = 1;

        // Loader DONE bekle
        $display("  [%0t] Loader DONE bekleniyor...", $time);
        wait_loader_done_timeout(50000, "TEST 1");

        repeat (5) @(posedge clk);

        $display("  I_CACHE icerigini dogrulama:");
`ifdef BEHAVIORAL_SIM
        check("I_CACHE[UART_ADDR>>2]", read_icache(`UART_ADDR >> 2), 32'h00000013);
`else
        $display("  [INFO] Skipping direct I_CACHE check (Post-Implementation Simulation)");
`endif
        check_1bit("busy (yukleme sonrasi)", busy, 1'b0);

        // Reset
        do_reset;

        // =============================================================
        // TEST 2: UART ile Çoklu Kelime Yükleme ve CPU Çalıştırma
        // =============================================================
        $display("\n============================================================");
        $display("  TEST 2: UART ile Coklu Kelime Yukleme ve CPU Calistirma");
        $display("============================================================");

        // Program:
        //   ADDI x1, x0, 10    -> 0x00A00093
        //   ADDI x2, x0, 20    -> 0x01400113
        //   SW x1, 0(x0)       -> 0x00102023
        //   SW x2, 4(x0)       -> 0x00202223
        //   NOPs
        //   LW x3, 0(x0)       -> 0x00002183
        //   NOPs
        //   LW x4, 4(x0)       -> 0x00402203

        rx_enable = 0;

        $display("  [%0t] Program gonderiliyor...", $time);
        uart_send_word(32'h00A00093);  // ADDI x1, x0, 10
        uart_send_word(32'h01400113);  // ADDI x2, x0, 20
        uart_send_word(32'h00102023);  // SW x1, 0(x0)
        uart_send_word(32'h00202223);  // SW x2, 4(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00002183);  // LW x3, 0(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00402203);  // LW x4, 4(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);

        uart_in = 1;
        rx_enable = 1;
        $display("  [%0t] Program gonderim tamamlandi", $time);

        // Loader DONE bekle
        wait_loader_done_timeout(50000, "TEST 2");

        // CPU'nun programı çalıştırmasını bekle ve data_mem_out kontrol et
        begin
            cycle_count = 0;
            while (data_mem_out !== 16'd10 && cycle_count < 150) begin
                @(posedge clk);
                cycle_count = cycle_count + 1;
            end
            check("data_mem_out (x1 value)", data_mem_out, 16'd10);

            cycle_count = 0;
            while (data_mem_out !== 16'd20 && cycle_count < 150) begin
                @(posedge clk);
                cycle_count = cycle_count + 1;
            end
            check("data_mem_out (x2 value)", data_mem_out, 16'd20);
        end

        $display("  Register dogrulama:");
        check_reg("ADDI x1, x0, 10", 1, 32'd10);
        check_reg("ADDI x2, x0, 20", 2, 32'd20);
        check_reg("x0 hala sifir",   0, 32'd0);

        do_reset;

        // =============================================================
        // TEST 3: UART ile Dallanma (Branch) Testi
        // =============================================================
        $display("\n============================================================");
        $display("  TEST 3: UART ile Dallanma (BEQ) Testi");
        $display("============================================================");

        rx_enable = 0;

        $display("  [%0t] Branch programi gonderiliyor...", $time);
        uart_send_word(32'h00A00093);  // [0] ADDI x1, x0, 10
        uart_send_word(32'h00A00113);  // [1] ADDI x2, x0, 10
        uart_send_word(`NOP);          // [2-5] NOP x4
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00208863);  // [6] BEQ x1, x2, +16 (-> [10])
        uart_send_word(32'h0FF00193);  // [7] ADDI x3, x0, 0xFF (flushed)
        uart_send_word(32'h0EE00213);  // [8] ADDI x4, x0, 0xEE (flushed)
        uart_send_word(`NOP);          // [9] NOP x4
        uart_send_word(32'h0AA00293);  // [10] ADDI x5, x0, 0xAA (target)
        uart_send_word(`NOP);          // pipeline delay
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        
        // Store results to verify
        uart_send_word(32'h00302023);  // SW x3, 0(x0)
        uart_send_word(32'h00402223);  // SW x4, 4(x0)
        uart_send_word(32'h00502423);  // SW x5, 8(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        
        // Load them to read via data_mem_out
        uart_send_word(32'h00002183);  // LW x3, 0(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00402203);  // LW x4, 4(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00802283);  // LW x5, 8(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);

        uart_in = 1;
        rx_enable = 1;

        wait_loader_done_timeout(50000, "TEST 3");

        // Verify via data_mem_out
        begin
            check("data_mem_out (x3 BEQ flushed)", data_mem_out, 16'd0);
            check("data_mem_out (x4 BEQ flushed)", data_mem_out, 16'd0);

            cycle_count = 0;
            while (data_mem_out !== 16'hAA && cycle_count < 150) begin
                @(posedge clk);
                cycle_count = cycle_count + 1;
            end
            check("data_mem_out (x5 BEQ target)", data_mem_out, 16'hAA);
        end

        $display("  Branch dogrulama:");
        check_reg("BEQ flushed: x3=0",    3, 32'h00000000);
        check_reg("BEQ flushed: x4=0",    4, 32'h00000000);
        check_reg("BEQ target: x5=0xAA",  5, 32'h000000AA);

        do_reset;

        // =============================================================
        // TEST 4: busy Sinyali Doğrulaması
        // =============================================================
        $display("\n============================================================");
        $display("  TEST 4: busy Sinyali Dogrulamasi");
        $display("============================================================");

        check_1bit("busy (yukleme oncesi)", busy, 1'b0);

        rx_enable = 0;

        // Bir byte gönder ve busy'yi kontrol et
        uart_send_byte(8'h13);

        // Loader tetiklendikten sonra busy HIGH olmalı
        repeat (10) @(posedge clk);
        check_1bit("busy (yukleme sirasinda)", busy, 1'b1);

        // Kalan 3 byte'ı gönder
        uart_send_byte(8'h00);
        uart_send_byte(8'h00);
        uart_send_byte(8'h00);

        uart_in = 1;
        rx_enable = 1;

        wait_loader_done_timeout(50000, "TEST 4");

        repeat (5) @(posedge clk);
        check_1bit("busy (yukleme tamamlandi)", busy, 1'b0);

        do_reset;

        // =============================================================
        // TEST 5: SPI ile Program Yükleme
        // =============================================================
        $display("\n============================================================");
        $display("  TEST 5: SPI ile Program Yukleme");
        $display("============================================================");
        
        spi_enable  = 1;
        sclk_enable = 1;

        $display("  [%0t] SPI ile Program gonderiliyor...", $time);

        // SPI ile yüklenen program:
        // ADDI x1, x0, 0x99 -> 0x09900093
        // SW x1, 0(x0)      -> 0x00102023
        // NOPs
        // LW x2, 0(x0)      -> 0x00002103
        
        spi_send_word(32'h09900093);
        spi_send_word(32'h00102023);
        spi_send_word(`NOP);
        spi_send_word(`NOP);
        spi_send_word(`NOP);
        spi_send_word(`NOP);
        spi_send_word(32'h00002103);
        spi_send_word(`NOP);
        spi_send_word(`NOP);
        spi_send_word(`NOP);
        spi_send_word(`NOP);

        spi_enable  = 0;
        sclk_enable = 0;

        $display("  [%0t] SPI gonderim tamamlandi", $time);

        wait_loader_done_timeout(100000, "TEST 5");

        // CPU'nun programı çalıştırmasını bekle
        begin
            cycle_count = 0;
            while (data_mem_out !== 16'h99 && cycle_count < 150) begin
                @(posedge clk);
                cycle_count = cycle_count + 1;
            end
            check("data_mem_out (SPI loaded program execution)", data_mem_out, 16'h99);
        end

        $display("  SPI I_CACHE dogrulama:");
`ifdef BEHAVIORAL_SIM
        check("I_CACHE[SPI_ADDR>>2]", read_icache(`SPI_ADDR >> 2), 32'h09900093);
`endif
        check_1bit("busy (SPI yukleme sonrasi)", busy, 1'b0);

        do_reset;

        // =============================================================
        // TEST 6: Reset Davranışı
        // =============================================================
        $display("\n============================================================");
        $display("  TEST 6: Reset Davranisi");
        $display("============================================================");

        check_1bit("busy (reset sonrasi)", busy, 1'b0);
`ifdef BEHAVIORAL_SIM
        check_1bit("cpu_halt (reset sonrasi)", uut.cpu_halt, 1'b0);
        check_1bit("loader we (reset sonrasi)", uut.PROGRAM_LOADER.we, 1'b0);
        check_1bit("loader done (reset sonrasi)", uut.PROGRAM_LOADER.done, 1'b0);
        check("loader state (STALL)", uut.PROGRAM_LOADER.state, 4'd0);
`endif

        // =============================================================
        // TEST 7: UART ile ALU Programı (ADD, SUB)
        // =============================================================
        $display("\n============================================================");
        $display("  TEST 7: UART ile ALU Programi (ADD, SUB)");
        $display("============================================================");

        rx_enable = 0;

        $display("  [%0t] ALU programi gonderiliyor...", $time);
        uart_send_word(32'h00F00093);  // [0] ADDI x1, x0, 15
        uart_send_word(32'h00700113);  // [1] ADDI x2, x0, 7
        uart_send_word(`NOP);          // [2-5] NOP x4
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h002081B3);  // [6] ADD x3, x1, x2
        uart_send_word(32'h40208233);  // [7] SUB x4, x1, x2
        uart_send_word(`NOP);          // pipeline delay
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        
        // Store results to verify
        uart_send_word(32'h00302023);  // SW x3, 0(x0)
        uart_send_word(32'h00402223);  // SW x4, 4(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        
        // Load them
        uart_send_word(32'h00002183);  // LW x3, 0(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00402203);  // LW x4, 4(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);

        uart_in = 1;
        rx_enable = 1;

        wait_loader_done_timeout(50000, "TEST 7");

        // Verify via data_mem_out
        begin
            cycle_count = 0;
            while (data_mem_out !== 16'd22 && cycle_count < 150) begin
                @(posedge clk);
                cycle_count = cycle_count + 1;
            end
            check("data_mem_out (x3 ADD value)", data_mem_out, 16'd22);

            cycle_count = 0;
            while (data_mem_out !== 16'd8 && cycle_count < 150) begin
                @(posedge clk);
                cycle_count = cycle_count + 1;
            end
            check("data_mem_out (x4 SUB value)", data_mem_out, 16'd8);
        end

        $display("  ALU dogrulama:");
        check_reg("ADD x3 = x1+x2 = 22", 3, 32'd22);
        check_reg("SUB x4 = x1-x2 = 8",  4, 32'd8);
        check_reg("x1 = 15",              1, 32'd15);
        check_reg("x2 = 7",               2, 32'd7);

        do_reset;

        // =============================================================
        // TEST 8: LUI Testi
        // =============================================================
        $display("\n============================================================");
        $display("  TEST 8: LUI Testi");
        $display("============================================================");

        rx_enable = 0;

        uart_send_word(32'hDEADB0B7);  // [0] LUI x1, 0xDEADB
        uart_send_word(`NOP);          // [1-4] NOP x4
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        
        // Store
        uart_send_word(32'h00102023);  // SW x1, 0(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        
        // Load
        uart_send_word(32'h00002183);  // LW x3, 0(x0)
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);

        uart_in = 1;
        rx_enable = 1;

        wait_loader_done_timeout(50000, "TEST 8");

        // Verify via data_mem_out
        begin
            cycle_count = 0;
            while (data_mem_out !== 16'hB000 && cycle_count < 150) begin
                @(posedge clk);
                cycle_count = cycle_count + 1;
            end
            check("data_mem_out (x1 LUI lower 16 bits)", data_mem_out, 16'hB000);
        end

        $display("  LUI dogrulama:");
        check_reg("LUI x1 = 0xDEADB000", 1, 32'hDEADB000);

        do_reset;

        // =============================================================
        // TEST 9: Store/Load Testi (SW/LW)
        // =============================================================
        $display("\n============================================================");
        $display("  TEST 9: Store/Load Testi (SW/LW)");
        $display("============================================================");

        rx_enable = 0;

        uart_send_word(32'h04200093);  // [0]  ADDI x1, x0, 0x42
        uart_send_word(32'h10000113);  // [1]  ADDI x2, x0, 0x100
        uart_send_word(`NOP);          // [2-5]  NOP x4
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00112023);  // [6]  SW x1, 0(x2)
        uart_send_word(`NOP);          // [7-10] NOP x4
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(32'h00012183);  // [11] LW x3, 0(x2)
        uart_send_word(`NOP);          // [12-15] NOP x4
        uart_send_word(`NOP);
        uart_send_word(`NOP);
        uart_send_word(`NOP);

        uart_in = 1;
        rx_enable = 1;

        wait_loader_done_timeout(50000, "TEST 9");

        // Verify via data_mem_out
        begin
            cycle_count = 0;
            while (data_mem_out !== 16'h42 && cycle_count < 150) begin
                @(posedge clk);
                cycle_count = cycle_count + 1;
            end
            check("data_mem_out (LW x3 = 0x42)", data_mem_out, 16'h42);
        end

        $display("  Store/Load dogrulama:");
        check_reg("LW x3 = mem[0x100] = 0x42", 3, 32'h00000042);

        // =============================================================
        // SONUÇLAR
        // =============================================================
        $display("\n========================================");
        $display("  TEST SONUCLARI: %0d basarili, %0d basarisiz", test_pass, test_fail);
        $display("========================================\n");

        #1000;
        $finish;
    end

    // -------------------------------------------
    // Timeout Watchdog
    // -------------------------------------------
    initial begin
        #2000000000; // 2 milyar time unit
        $display("[TIMEOUT] Simulasyon zaman limitini asti");
        $finish;
    end

    // -------------------------------------------
    // VCD Dump
    // -------------------------------------------
    initial begin
        $dumpfile("KATIHAL_TB.vcd");
        $dumpvars(0, KATIHAL_TB);
    end

endmodule
