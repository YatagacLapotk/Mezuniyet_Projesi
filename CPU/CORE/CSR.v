`include "sabit_veriler.vh"
module CSR (
    input clk,
    input reset,
    input [`DATA_WIDTH-1:0] pc,
    input [`DATA_WIDTH-1:0] instr,
    input [`CSR_ADDR_WIDTH-1:0] csr_addr,
    input exception,
    input interrupt,
    input [7:0] exception_code,
    input [`DATA_WIDTH-1:0] csr_data_in,
    input [1:0] csr_cntrl,
    input csr_rd,
    input csr_wr,
    output [`DATA_WIDTH-1:0] csr_data_out,
    output [`DATA_WIDTH-1:0] csr_mtvec,
    output [`DATA_WIDTH-1:0] csr_mepc
);

// ---- Trap-context registers (the Zicsr core) ----
reg [`DATA_WIDTH-1:0] mtvec;   // handler address; consumed by FETCH
reg [`DATA_WIDTH-1:0] mepc;    // PC of the faulting instruction
reg [`DATA_WIDTH-1:0] mcause;  // trap cause: bit31=interrupt, low bits=reason
reg [`DATA_WIDTH-1:0] mtval;   // trap value (fault detail, e.g. faulting instr)

// ---- Interrupt gating ----
// mstatus[3] = MIE (global interrupt enable). Exceptions (ecall/ebreak) are
//              ALWAYS honored; only asynchronous interrupts consult MIE.
// mie        = per-source enable bitmap (e.g. bit4 = MSIE / UART).
reg [`DATA_WIDTH-1:0] mstatus;
reg [`DATA_WIDTH-1:0] mie;

// Edge detector. Tracks the EFFECTIVE exception so that an interrupt which
// arrives while MIE=0 is still caught once MIE is restored (no lost trap).
reg exception_prev;
wire exception_edge;
wire [`DATA_WIDTH-1:0] mtval_tmp;
wire [`DATA_WIDTH-1:0] mcause_tmp;

wire interrupt_allowed = interrupt ? (mstatus[3] & mie[exception_code]) : 1'b1;
wire effective_exception = exception & interrupt_allowed;

assign exception_edge = effective_exception & ~exception_prev;
assign mtval_tmp = (exception_code == 8'h02) ? instr : 32'b0;
assign mcause_tmp = {interrupt, 23'b0, exception_code};

always @(posedge clk) begin
    if (reset) begin
        exception_prev <= 0;
        mstatus <= 0;
        mie <= 0;
        mtvec <= 0;
        mepc <= 0;
        mcause <= 0;
        mtval <= 0;
    end
    else begin
        // FIX: sample the effective (masked) exception, not the raw input,
        // so a pending trap that arrived while MIE was 0 is still detected
        // once MIE is re-enabled.
        exception_prev <= effective_exception;

        // Software writes: csrw (01), csrs set (10), csrrc clear (11).
        if(csr_wr) begin
            if(csr_cntrl == 2'b01) begin
                case (csr_addr)
                    `MSTATUS: mstatus <= csr_data_in;
                    `MIE:     mie     <= csr_data_in;
                    `MTVEC:   mtvec   <= csr_data_in;
                    `MCAUSE:  mcause  <= csr_data_in;
                    `MTVAL:   mtval   <= csr_data_in;
                endcase
            end
            else if (csr_cntrl == 2'b10) begin
                case (csr_addr)
                    `MSTATUS: mstatus <= mstatus | csr_data_in;
                    `MIE:     mie     <= mie     | csr_data_in;
                    `MTVEC:   mtvec   <= mtvec   | csr_data_in;
                    `MCAUSE:  mcause  <= mcause  | csr_data_in;
                    `MTVAL:   mtval   <= mtval   | csr_data_in;
                endcase
            end
            else if (csr_cntrl == 2'b11) begin
                case (csr_addr)
                    `MSTATUS: mstatus <= mstatus & ~csr_data_in;
                    `MIE:     mie     <= mie     & ~csr_data_in;
                    `MTVEC:   mtvec   <= mtvec   & ~csr_data_in;
                    `MCAUSE:  mcause  <= mcause  & ~csr_data_in;
                    `MTVAL:   mtval   <= mtval   & ~csr_data_in;
                endcase
            end
        end

        // Trap edge: latch context. MIE is cleared here so only one trap
        // is serviced at a time (no nested interrupts). MPIE/MPP saving and
        // the 2-bit privilege ring were removed: nothing in this bare-metal
        // core enforces them, so they were dead state.
        if(exception_edge) begin
            mepc  <= pc;
            mcause<= mcause_tmp;
            mtval <= mtval_tmp;
            mstatus[3] <= 1'b0;   // MIE=0 in handler
        end
    end
end

assign csr_mtvec = {mtvec[31:2], 2'b00};
assign csr_mepc  = mepc;

assign csr_data_out = (csr_rd) ?
    (csr_addr == `MSTATUS) ? mstatus :
    (csr_addr == `MIE) ? mie :
    (csr_addr == `MTVEC) ? mtvec :
    (csr_addr == `MEPC) ? mepc :
    (csr_addr == `MCAUSE) ? mcause :
    (csr_addr == `MTVAL) ? mtval : 0
    : 0;

endmodule