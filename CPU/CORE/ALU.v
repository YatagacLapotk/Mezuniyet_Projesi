`include "Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module ALU ( 
    input [`DATA_WIDTH-1:0] s1,
    input [`DATA_WIDTH-1:0] s2,
    input [`OPCODE_WIDTH-1:0] opcode,
    input [`FUNCT3_WIDTH-1:0] f3,
    input [`FUNCT7_WIDTH-1:0] f7,
    output [`DATA_WIDTH-1:0] d3

);


// Register-Register operations
localparam [31:0] ADD = `ADD;
localparam [31:0] SUB = `SUB;
localparam [31:0] OR = `OR;
localparam [31:0] AND = `AND;
localparam [31:0] XOR = `XOR;
localparam [31:0] SLL = `SLL; // Shift Left Logical
localparam [31:0] SRL = `SRL; // Shift Right Logical
localparam [31:0] SRA = `SRA; // Shift Right Arithmetic 
localparam [31:0] SLT = `SLT;  // Set Less Than 
localparam [31:0] SLTU = `SLTU; // Set Less Than Unsigned

endmodule


