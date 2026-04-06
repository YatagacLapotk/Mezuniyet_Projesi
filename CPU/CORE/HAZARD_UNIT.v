`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"

module HU (  
    input [`ADDRESS_WIDTH-1:0] rs1D,
    input [`ADDRESS_WIDTH-1:0] rs2D,
    input [`ADDRESS_WIDTH-1:0] rs1E,
    input [`ADDRESS_WIDTH-1:0] rs2E,
    input [`ADDRESS_WIDTH-1:0] rdE,
    input [`ADDRESS_WIDTH-1:0] rdM,
    input [`ADDRESS_WIDTH-1:0] rdW,
    input reg_writeM,
    input reg_writeW,
    input result_srcE_zer,
    output reg [1:0] forwardA,
    output reg [1:0] forwardB,
    output pc_src,
    output stallF,
    output stallD,
    output flushD,
    output flushE
);
wire lwstall;
//Forwarding 
//A
always @(*) begin
    if(((rs1E==rdM) & (reg_writeM))&(rs1E!=0))  forwardA = 2'b01;
    if(((rs1E==rdW) & (reg_writeW))&(rs1D!=0))  forwardA = 2'b10;
    else                                        forwardA = 2'b00;
end
//B
always @(*) begin
    if(((rs2E==rdM) & (reg_writeM))&(rs2E!=0))  forwardB = 2'b01;
    if(((rs2E==rdW) & (reg_writeW))&(rs2D!=0))  forwardB = 2'b10;
    else                                        forwardB = 2'b00;
end

//Stalling
assign lwstall = result_srcE_zer & ((rs1D==rdE)|(rs2E==rdE));
assign stallD = lwstall; 
assign stallF = lwstall; 

//Flushing
assign flushE = lwstall|pc_src;
assign flushD = pc_src; 
    
endmodule