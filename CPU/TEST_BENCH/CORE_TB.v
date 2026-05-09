`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module CORE_TB ();
    reg clk;
    reg reset;
    reg interrupt;
    reg [`DATA_WIDTH-1:0] comm_data_in;
    wire [`DATA_WIDTH-1:0] comm_data_out;


    CORE uut(
        .clk(clk),
        .reset(reset),
        .interrupt(interrupt),
        .comm_data_in(comm_data_in),
        .comm_data_out(comm_data_out)
    );
  
    initial begin
        forever #5 clk = ~clk;
    end

    initial begin
        reset = 1;
        interrupt = 0;
        comm_data_in = 0;
        comm_data_out = 0;
        #10;
        
        
    end




    
    
    
    
    
    
    
    
    initial begin
        $dumpfile("CORE_TB.vcd");
        $dumpvars(0, CORE_TB);
    end

endmodule