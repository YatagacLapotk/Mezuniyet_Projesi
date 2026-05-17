`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module D_CACHE (
    input clk,
    input reset,

    // comm interface
    input we,
    input [`DATA_WIDTH-1:0] data_in,
    input [`CACHE_ADDRESS-1:0] w_addr,
    input [`FUNCT3_WIDTH-1:0] funct3, 

    //FETCH inst
    input [`CACHE_ADDRESS-1:0] r_addr,
    output reg [`DATA_WIDTH-1:0] data_out
);

reg [`DATA_WIDTH-1:0] d_cache [0:`CACHE_SIZE];
reg [`DATA_WIDTH-1:0] merged_data;
reg [7:0]  selected_byte;
reg [15:0] selected_half;

always @(*) begin
    merged_data = d_cache[w_addr[31:2]];
    case (funct3)
        3'b000: 
            begin
                case (w_addr[1:0])
                    2'b00 : merged_data[7:0] = data_in[7:0];  
                    2'b01 : merged_data[15:8] = data_in[7:0];  
                    2'b10 : merged_data[23:16] = data_in[7:0];  
                    2'b11 : merged_data[31:24] = data_in[7:0];  
                endcase
            end
        3'b001:
            begin
                case (w_addr[1])
                    1'b0: merged_data[15:0]  = data_in[15:0];
                    1'b1: merged_data[31:16] = data_in[15:0];  
                endcase
            end
        default : merged_data = data_in;
    endcase
end

always @(posedge clk) begin
    if (reset)begin
        for(integer i = 0; i<`CACHE_SIZE;i+=1)begin
            d_cache[i]<= 0;
        end
    end 
    else if (we)begin
        d_cache[w_addr[31:2]] <= merged_data;
    end
end

always @(*) begin
    case (r_addr[1:0])
        2'b00: selected_byte = d_cache[r_addr[31:2]][7:0];
        2'b01: selected_byte = d_cache[r_addr[31:2]][15:8];
        2'b10: selected_byte = d_cache[r_addr[31:2]][23:16];
        2'b11: selected_byte = d_cache[r_addr[31:2]][31:24];
    endcase
    case (r_addr[1])
        1'b0: selected_half = d_cache[r_addr[31:2]][15:0];
        1'b1: selected_half = d_cache[r_addr[31:2]][31:16];
    endcase
    case (funct3)
        3'b000: data_out = {{24{selected_byte[7]}}, selected_byte};  // LB
        3'b001: data_out = {{16{selected_half[15]}}, selected_half}; // LH
        3'b010: data_out = d_cache[r_addr[31:2]];                    // LW
        3'b100: data_out = {24'b0, selected_byte};                   // LBU
        3'b101: data_out = {16'b0, selected_half};                   // LHU
        default: data_out = d_cache[r_addr[31:2]];
    endcase
end

    
endmodule