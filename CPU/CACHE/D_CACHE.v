`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module D_CACHE (
    input clk,
    input reset,

    //Hit Miss and Memory İnterface
    input [`DATA_WIDTH-1:0] ram_data_in,
    input [`TAG_WIDTH-1:0] tag,
    input [`SET_WIDTH-1:0] set,
    output miss,

    // comm interface
    input we,
    input [`DATA_WIDTH-1:0] data_in,
    input [`CACHE_ADDRESS-1:0] w_addr,
    input [`FUNCT3_WIDTH-1:0] funct3, 

    //FETCH inst
    input [`CACHE_ADDRESS-1:0] r_addr,
    output reg [`DATA_WIDTH-1:0] data_out
);

reg [`CACHE_WIDTH-1:0] way0_cache [0:`D_CACHE_SIZE];
reg [`CACHE_WIDTH-1:0] way1_cache [0:`D_CACHE_SIZE];
wire [`DATA_WIDTH-1:0] way0_data;
wire [`DATA_WIDTH-1:0] way1_data;
wire [`TAG_WIDTH-1:0] way0_tag;
wire [`TAG_WIDTH-1:0] way1_tag;
wire way0_valid;
wire way1_valid;
reg [`DATA_WIDTH-1:0] d_cache;
reg [`DATA_WIDTH-1:0] merged_data;
reg [7:0]  selected_byte;
reg [15:0] selected_half;


assign way0_data = way0_cache[set][`DATA_WIDTH-1:0];
assign way1_data = way1_cache[set][`DATA_WIDTH-1:0];

assign way0_tag = way0_cache[set][54:32];
assign way1_tag = way1_cache[set][54:32];

assign way0_valid = way0_cache[set][55];
assign way1_valid = way1_cache[set][55];

always @(posedge clk) begin

end

always @(*) begin
    merged_data = d_cache;
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

integer i;
always @(posedge clk) begin
    if (reset)begin
        for(i = 0; i<`D_CACHE_SIZE; i = i + 1)begin
            d_cache[i]<= 0;
        end
    end 
    else if (we)begin
        d_cache[w_addr[31:2]] <= merged_data;
    end
end

always @(*) begin
    case (r_addr[1:0])
        2'b00: selected_byte = d_cache[7:0];
        2'b01: selected_byte = d_cache[15:8];
        2'b10: selected_byte = d_cache[23:16];
        2'b11: selected_byte = d_cache[31:24];
    endcase
    case (r_addr[1])
        1'b0: selected_half = d_cache[15:0];
        1'b1: selected_half = d_cache[31:16];
    endcase
    case (funct3)
        3'b000: data_out = {{24{selected_byte[7]}}, selected_byte};  // LB
        3'b001: data_out = {{16{selected_half[15]}}, selected_half}; // LH
        3'b010: data_out = d_cache;                                  // LW
        3'b100: data_out = {24'b0, selected_byte};                   // LBU
        3'b101: data_out = {16'b0, selected_half};                   // LHU
        default: data_out = d_cache;
    endcase
end

    
endmodule