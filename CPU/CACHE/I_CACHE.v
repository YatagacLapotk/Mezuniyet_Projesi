`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module I_CACHE (
    input clk,
    input reset,

    //Hit Miss and Memory İnterface
    input valid,
    output reg miss,
    output reg stall,
    input [`INSTRUCTION_WIDTH-1:0] inst_in,

    // comm interface
    //input we,
    //input [`CACHE_ADDRESS-1:0] w_addr,
    
    //FETCH inst
    input [`CACHE_ADDRESS-1:0] r_addr,
    output reg [`INSTRUCTION_WIDTH-1:0] inst_out
);

parameter IDLE = 0, START = 1, DONE = 2;
reg [1:0] state;

reg [`CACHE_WIDTH-1:0] way0_cache [0:`I_CACHE_SIZE]; // 0. Cache yolu
reg [`CACHE_WIDTH  :0] way1_cache [0:`I_CACHE_SIZE]; // 1. cache yolu
wire [`INSTRUCTION_WIDTH-1:0] way0_data;
wire [`INSTRUCTION_WIDTH-1:0] way1_data;
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
wire [`INSTRUCTION_WIDTH-1:0] i_temp;
reg [`INSTRUCTION_WIDTH-1:0] i_cache;
//reg [`INSTRUCTION_WIDTH-1:0] merged_data;

assign set = r_addr[8:2];
assign tag = r_addr[31:9];
assign way0_data = way0_cache[set][`INSTRUCTION_WIDTH-1:0];
assign way1_data = way1_cache[set][`INSTRUCTION_WIDTH-1:0];

assign way0_tag = way0_cache[set][54:32];
assign way1_tag = way1_cache[set][54:32];

assign way0_valid = way0_cache[set][55];
assign way1_valid = way1_cache[set][56];

assign hit0 = (tag == way0_tag) ? way0_valid :1'b0;
assign hit1 = (tag == way1_tag) ? way1_valid :1'b0;
assign hit = hit0 | hit1;

assign lru = way1_cache[set][55];

assign i_temp = (hit1) ? way1_data : way0_data;

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
                    i_cache <= i_temp;
                    miss <= 0;
                end
            end
            START: begin
                if (valid)begin
                    state <= DONE;
                    if(lru)begin
                        way1_cache[set] <= {valid,!lru,tag,inst_in};
                    end
                    else begin
                        way0_cache[set] <= {valid,tag,inst_in};
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

always @(*) begin
    if(hit)begin
        inst_out = i_cache;
    end
end

endmodule