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
    output [1:0] forwardA,
    output [1:0] forwardB,
    output pc_src,
    output stallF,
    output stallD,
    output flushD,
    output flushE
);


    
endmodule