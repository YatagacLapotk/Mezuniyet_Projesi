`include "CPU\SABIT_VERILER\sabit_veriler.vh"

module ALU ( 
    input [`DATA_WIDTH-1:0] s1,
    input [`DATA_WIDTH-1:0] s2,
    input [`ALU_CNTR-1:0] ALU_CNTR,
    output [`DATA_WIDTH-1:0] ALU_OUT  
);



localparam [3:0] ADD = 4'b0000,
                 SUB = 4'b0001,
                 OR  = 4'b0010,
                 AND = 4'b0011,
                 XOR = 4'b0100,
                 SLL = 4'b0101, // Shift Left Logical
                 SRL = 4'b0110, // Shift Right Logical
                 SRA = 4'b0111, // Shift Right Arithmetic 
                 SLT = 4'b1000,  // Set Less Than 
                 SLTU= 4'b1001, // Set Less Than Unsigned
                 EQ  = 4'b1010, // Equal
                 GE = 4'b1011, // Greater or Equal
                 LT = 4'b1100, // Less Than
                 NE = 4'b1101, // Not Equal
                 LTU = 4'b1110, // Less Than Unsigned
                 GEU = 4'b1111; // Greater or Equal Unsigned

always @ (*) begin    
    case (ALU_CNTR)
        ADD: ALU_OUT = s1 + s2;
        SUB: ALU_OUT = s1 - s2;
        OR: ALU_OUT = s1 | s2;
        AND: ALU_OUT = s1 & s2;
        XOR: ALU_OUT = s1 ^ s2;
        SLT: ALU_OUT =  ($signed(s1) < $signed(s2)) ? 32'b1 : 32'b0;
        SLTU: ALU_OUT = ($unsigned(s1) < $unsigned(s2)) ? 32'b1 : 32'b0;   
        // Shift Operations 
        SLL: ALU_OUT = s1 <<  [4:0];
        SRL: ALU_OUT = s1 >> s2[4:0];
        SRA: ALU_OUT = $signed(s1) >>> s2[4:0];
        // Branch Operations
        EQ: ALU_OUT = (s1 == s2) ? 32'b1 : 32'b0;
        GE: ALU_OUT = ($signed(s1) >= $signed(s2)) ? 32'b1 : 32'b0;
        LT: ALU_OUT = ($signed(s1) < $signed(s2)) ? 32'b1 : 32'b0;
        NE: ALU_OUT = (s1 != s2) ? 32'b1 : 32'b0;
        LTU: ALU_OUT = ($unsigned(s1) < $unsigned(s2)) ? 32'b1 : 32'b0;
        GEU: ALU_OUT = ($unsigned(s1) >= $unsigned(s2)) ? 32'b1 : 32'b0;
        default : ALU_OUT = 32'b0;
    endcase
end 
    



endmodule


