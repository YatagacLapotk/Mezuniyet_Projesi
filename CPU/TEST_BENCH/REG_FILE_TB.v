module REG_FILE_TB ();

reg          clk;
reg          res;
wire [4:0]    A1;
wire [4:0]    A2;
wire [4:0]    A3;
wire [31:0]   WD;
reg  [31:0]   RD1;
reg  [31:0]   RD2;

REG_FILE U_REG_FILE (
    .clk(clk),
    .res(res),
    .A1(A1),
    .A2(A2),
    .A3(A3),
    .WD(WD),
    .RD1(RD1),
    .RD2(RD2)
);
    
initial begin
    clk = 0;
    res = 1;
    #10;
    res = 0;
    
    // Test writing and reading from the register file
    // Write 42 to register 5
    #10;
    A3 = 5'd5;
    WD = 32'd42;
    
    // Read from register 5 and register 0
    #10;
    A1 = 5'd5;
    A2 = 5'd0;
    
    // Write 100 to register 10
    #10;
    A3 = 5'd10;
    WD = 32'd100;
    
    // Read from register 10 and register 5
    #10;
    A1 = 5'd10;
    A2 = 5'd5;
    
    // Finish simulation
    #20;
    $finish;
end

initial begin
    forever #5 clk = ~clk;
end


endmodule