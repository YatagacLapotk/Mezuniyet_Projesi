module register_and_alu #(
    parameter WIDTH = 4,
    parameter CTRLWORD = 14
) (
    input [WIDTH-1:0] in,
    input clk,
    input [CTRLWORD-1:0] control,
    output [WIDTH-1:0] out
);

wire [WIDTH-1:0] regs_out [0:6];
reg [WIDTH-1:0] A;
reg [WIDTH-1:0] B;
reg [WIDTH-1:0] alu_out [0:7];
wire [WIDTH-1:0] alu_out_1;


always @(*) begin
    case (control[7:5])
        3'b000 :  alu_out[0] = 4'b0000; 
        3'b001 :  alu_out[1] = alu_out_1; 
        3'b010 :  alu_out[2] = alu_out_1; 
        3'b011 :  alu_out[3] = alu_out_1; 
        3'b100 :  alu_out[4] = alu_out_1; 
        3'b101 :  alu_out[5] = alu_out_1; 
        3'b110 :  alu_out[6] = alu_out_1; 
        3'b111 :  alu_out[7] = alu_out_1; 
    endcase
end

register R1(.clk(clk),.in(alu_out[1]),.out(regs_out[0]));
register R2(.clk(clk),.in(alu_out[2]),.out(regs_out[1]));
register R3(.clk(clk),.in(alu_out[3]),.out(regs_out[2]));
register R4(.clk(clk),.in(alu_out[4]),.out(regs_out[3]));
register R5(.clk(clk),.in(alu_out[5]),.out(regs_out[4]));
register R6(.clk(clk),.in(alu_out[6]),.out(regs_out[5]));
register R7(.clk(clk),.in(alu_out[7]),.out(regs_out[6]));


always @(*) begin
    case (control[13:11])
        3'b000 : A = in;   
        3'b001 : A = regs_out[0];   
        3'b010 : A = regs_out[1];   
        3'b011 : A = regs_out[2];   
        3'b100 : A = regs_out[3];   
        3'b101 : A = regs_out[4];   
        3'b110 : A = regs_out[5];   
        3'b111 : A = regs_out[6];   
    endcase
    case (control[10:8])
        3'b000 : B = in;   
        3'b001 : B = regs_out[0];   
        3'b010 : B = regs_out[1];   
        3'b011 : B = regs_out[2];   
        3'b100 : B = regs_out[3];   
        3'b101 : B = regs_out[4];   
        3'b110 : B = regs_out[5];   
        3'b111 : B = regs_out[6];   
    endcase
end


alu l(.A(A),.B(B),.control(control[4:0]),.out(alu_out_1));

assign out = alu_out_1;
    
endmodule


module register #(
    parameter WIDTH = 4
) (
    input clk,
    input [WIDTH-1:0] in,
    output  reg [WIDTH-1:0] out
);

    always @(posedge clk) begin
        out <= in;
    end
    
endmodule


module alu #(
    parameter WIDTH = 4
) (
    input [WIDTH-1:0] A,
    input [WIDTH-1:0] B,
    input [4:0] control,
    output reg [WIDTH-1:0] out
);

    always @(*) begin
        case (control)
            5'b00000: out = A; 
            5'b00001: out = A+1; 
            5'b00010: out = A+B; 
            5'b00101: out = A-B; 
            5'b00110: out = A-1; 
            5'b01000: out = A&B; 
            5'b01010: out = A|B; 
            5'b01100: out = A^B; 
            5'b01110: out = ~A; 
            5'b10000: out = A>>1; 
            5'b11000: out = A<<1; 
        endcase
    end
    
endmodule
