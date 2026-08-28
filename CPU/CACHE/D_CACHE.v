`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module D_CACHE (
    input clk,
    input reset,

    //Hit Miss and Memory İnterface
    input valid,
    output reg miss,
    output reg stall,
    input [`DATA_WIDTH-1:0] data_in,

    // comm interface
    //input we,
    //input [`CACHE_ADDRESS-1:0] w_addr,
    
    //Data Read
    input [`CACHE_ADDRESS-1:0] r_addr,
    input [`FUNCT3_WIDTH-1:0] funct3, 
    output reg [`DATA_WIDTH-1:0] data_out
);

parameter IDLE = 0, START = 1, DONE = 2;
reg [1:0] state;

reg [`CACHE_WIDTH-1:0] way0_cache [0:`D_CACHE_SIZE]; // 0. Cache yolu
reg [`CACHE_WIDTH  :0] way1_cache [0:`D_CACHE_SIZE]; // 1. cache yolu
wire [`DATA_WIDTH-1:0] way0_data;
wire [`DATA_WIDTH-1:0] way1_data;
wire [`TAG_WIDTH-1:0] tag;
wire [`SET_WIDTH-1:0] set;
wire [`TAG_WIDTH-1:0] way0_tag;
wire [`TAG_WIDTH-1:0] way1_tag;
wire lru;       //Hangi kısım daha önce değiştirildi.
wire way0_valid;
wire way1_valid;
wire hit0;
wire hit1;
wire hit;
reg target;
wire [`DATA_WIDTH-1:0] data_temp;
reg [`DATA_WIDTH-1:0] d_cache;
//reg [`DATA_WIDTH-1:0] merged_data;
reg [7:0]  selected_byte;
reg [15:0] selected_half;

assign set = r_addr[8:2];
assign tag = r_addr[31:9];
assign way0_data = way0_cache[set][`DATA_WIDTH-1:0];
assign way1_data = way1_cache[set][`DATA_WIDTH-1:0];

assign way0_tag = way0_cache[set][54:32];
assign way1_tag = way1_cache[set][54:32];

assign way0_valid = way0_cache[set][55];
assign way1_valid = way1_cache[set][56];

assign hit0 = (tag == way0_tag) ? way0_valid :1'b0;
assign hit1 = (tag == way1_tag) ? way1_valid :1'b0;
assign hit = hit0 | hit1;

assign lru = way1_cache[set][55];

assign data_temp = (hit1) ? way1_data : way0_data;

always @(posedge clk) begin
    if(reset)begin
        miss <= 0;
        stall <= 0;
        target <= 0;
        state <= IDLE;
    end
    else begin
        case (state)
            IDLE: begin
                if(!hit)begin
                    miss <= 1;
                    stall <= 1;
                    state <= START;
                end
                else begin
                    d_cache <= data_temp;
                    miss <= 0;
                end
            end
            START: begin
                if (valid)begin
                    state <= DONE;
                    if(lru)begin
                        way1_cache[set] <= {valid,!lru,tag,data_in};
                    end
                    else begin
                        way0_cache[set] <= {valid,tag,data_in};
                        way1_cache[set][55] <= 1'b1;
                    end
                end
                else state <= START; 
            end
            DONE: begin
                miss <= 0;
                stall <= 0;
                state <= IDLE;
            end
        endcase
    end

end


/*
always @(*) begin
    merged_data <= d_cache;
    case (funct3)
        3'b000: 
            begin
                case (w_addr[1:0])
                    2'b00 : merged_data[7:0] <= data_in[7:0];  
                    2'b01 : merged_data[15:8] <= data_in[7:0];  
                    2'b10 : merged_data[23:16] <= data_in[7:0];  
                    2'b11 : merged_data[31:24] <= data_in[7:0];  
                endcase
            end
        3'b001:
            begin
                case (w_addr[1])
                    1'b0: merged_data[15:0]  <= data_in[15:0];
                    1'b1: merged_data[31:16] <= data_in[15:0];  
                endcase
            end
        default : merged_data = data_in;
    endcase
    d_cache[w_addr[31:2]] <= merged_data;
end


// Eski yazma sistemi artık cache mantığına geçildiği için yazma miss olması durumunda yapılıyor.

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
*/
always @(*) begin
    if(hit)begin
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
end

    
endmodule