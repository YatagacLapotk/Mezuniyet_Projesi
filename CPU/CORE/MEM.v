`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"

module MEM (
    input clk,
    input reset,
    input [`DATA_WIDTH-1:0] execute_result_in,
    input [`DATA_WIDTH-1:0] mem_write_data,
    input [`WB_CNTRL-1:0] wb_controlM,
    input reg_write,
    input mem_write,
    input [`DATA_WIDTH-1:0] pc_4,
    input [`ADDRESS_WIDTH-1:0] rdM,
    output [`ADDRESS_WIDTH-1:0] rdM_hazard_out,
    output reg_write_hazard,
    output reg reg_write_out,
    output reg [`WB_CNTRL-1:0] wb_control_out,
    output reg [`ADDRESS_WIDTH-1:0] rdW,
    output [`DATA_WIDTH-1:0] execute_result_out,
    output reg [`DATA_WIDTH-1:0] mem_result_out,
    output reg [`DATA_WIDTH-1:0] wb_result_out,
    output reg [`DATA_WIDTH-1:0] pc_4_out
);
//Buraya D_cache ekledim ancak tam olarak bizim tasarıma uymuyor sanırım 
// bunun için ne yapmamız gerekir onu bilmiyorum. 
// Mesela eğer bir veriyolu içerisine koyarsak sistem yavaşlar mı?
wire [`DATA_WIDTH-1:0] mem_result_out_temp;

D_CACHE D_CACHE (
    .clk(clk),
    .reset(reset),
    .we(mem_write),
    .data_in(mem_write_data),
    .w_addr(execute_result_in),
    .r_addr(execute_result_in),
    .data_out(mem_result_out_temp)
);

always @(posedge clk) begin
    if(reset) begin
        reg_write_out <= 0;
        wb_control_out <= 0;
        rdW <= 0;
        mem_result_out <= 0;
        wb_result_out <= 0;
        pc_4_out <= 0;
    end else begin
        reg_write_out <= reg_write;
        wb_control_out <= wb_controlM;
        rdW <= rdM;
        mem_result_out <= mem_result_out_temp;
        wb_result_out <= execute_result_in;
        pc_4_out <= pc_4;
    end
end

assign execute_result_out = execute_result_in;
assign rdM_hazard_out = rdM;
assign reg_write_hazard = reg_write;

endmodule