`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module CSR (
    input clk,
    input reset,
    input [`DATA_WIDTH-1:0] pc,
    input [`DATA_WIDTH-1:0] instr,
    input [`CSR_ADDR_WIDTH-1:0] csr_addr,
    input exception,
    input [7:0] exception_code,
    input [`DATA_WIDTH-1:0] csr_data_in,
    input [1:0] csr_cntrl,
    input csr_rd,
    input csr_wr,
    output [`DATA_WIDTH-1:0] csr_data_out,
    output [`DATA_WIDTH-1:0] csr_mtvec,
    output [`DATA_WIDTH-1:0] csr_mepc
);

wire exception_edge;
reg exception_prev;
wire [`DATA_WIDTH-1:0] mtval_tmp;
wire [`DATA_WIDTH-1:0] mcause_tmp;

reg [`DATA_WIDTH-1:0] mstatus;
reg [`DATA_WIDTH-1:0] mie;
reg [`DATA_WIDTH-1:0] mtvec;
reg [`DATA_WIDTH-1:0] mepc;
reg [`DATA_WIDTH-1:0] mcause;
reg [`DATA_WIDTH-1:0] mtval;

assign exception_edge = exception & ~exception_prev;
assign mtval_tmp = (exception_code == 8'h02) ? instr : 32'b0; 
assign mcause_tmp = {24'b0, exception_code}; 


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
        exception_prev <= exception;
        if(csr_wr) begin
            if(csr_cntrl == 2'b00)begin
                case (csr_addr)
                    `MSTATUS: mstatus <= csr_data_in;
                    `MIE:     mie     <= csr_data_in;
                    `MTVEC:   mtvec   <= csr_data_in;
                    `MTVAL:   mtval   <= csr_data_in;
                endcase
            end
            else if (csr_cntrl == 2'b01) begin
                case (csr_addr)
                    `MSTATUS: mstatus <= mstatus | csr_data_in;
                    `MIE:     mie     <= mie     | csr_data_in;
                    `MTVEC:   mtvec   <= mtvec   | csr_data_in;
                    `MTVAL:   mtval   <= mtval   | csr_data_in;
                endcase
            end
            else if (csr_cntrl == 2'b10) begin
                case (csr_addr)
                    `MSTATUS: mstatus <= mstatus & ~csr_data_in;
                    `MIE:     mie     <= mie     & ~csr_data_in;
                    `MTVEC:   mtvec   <= mtvec   & ~csr_data_in;
                    `MTVAL:   mtval   <= mtval   & ~csr_data_in;
                endcase
            end
        end
        if(exception_edge) begin
            mepc <= pc;
            mcause <= mcause_tmp;
            mtval <= mtval_tmp;
            if (csr_wr) begin
                if (csr_cntrl == 2'b00) begin
                    case (csr_addr)
                        `MCAUSE : mcause <= csr_data_in;
                        `MTVAL : mtval  <= csr_data_in;
                    endcase    
                end
                if (csr_cntrl == 2'b01) begin
                    case (csr_addr)
                        `MCAUSE : mcause <= mcause | csr_data_in;
                        `MTVAL : mtval  <= mtval  | csr_data_in;
                    endcase    
                end
                if (csr_cntrl == 2'b10) begin
                    case (csr_addr)
                        `MCAUSE : mcause <= mcause & ~csr_data_in;
                        `MTVAL : mtval  <= mtval  & ~csr_data_in;
                    endcase    
                end
            end
        end
    end
    
end

assign csr_mtvec = {mtvec[31:2], 2'b00};
assign csr_data_out = (csr_rd) ? 
    (csr_addr == `MSTATUS) ? mstatus :
    (csr_addr == `MIE) ? mie :
    (csr_addr == `MTVEC) ? mtvec :
    (csr_addr == `MEPC) ? mepc :
    (csr_addr == `MCAUSE) ? mcause :
    (csr_addr == `MTVAL) ? mtval : 0
    : 0;
    
endmodule