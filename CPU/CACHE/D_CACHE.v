`include "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/SABIT_VERILER/sabit_veriler.vh"
module D_CACHE (
    input clk,
    input reset,

    //Hit Miss and Memory İnterface
    input mem_ready,
    input mem_ack,
    input [`DATA_WIDTH-1:0] mem_rdata, 
    output [`CACHE_ADDRESS-1:0] memory_addr,
    output [`DATA_WIDTH-1:0] mem_wdata,
    output reg mem_req,
    output reg mem_we,
    
    //CPU - CACHE interface
    input [`DATA_WIDTH-1:0] data_in_cpu,
    input [`CACHE_ADDRESS-1:0] cpu_addr,
    input [`FUNCT3_WIDTH-1:0] cpu_funct3, 
    input cpu_we,
    input cpu_req,
    output reg stall,
    output reg [`DATA_WIDTH-1:0] data_out_cpu
);

parameter IDLE = 0, 
          START = 1, 
          DONE = 2, 
          WRITEB = 3;
reg [1:0] state;

//Write mask
wire [3:0] store_mask;
reg  [`CACHE_WIDTH-1:0] way0_cache [0:`D_CACHE_SIZE]; // 0. Cache yolu
reg  [`CACHE_WIDTH  :0] way1_cache [0:`D_CACHE_SIZE]; // 1. cache yolu
wire [`DATA_WIDTH-1:0]  way0_data;
wire [`DATA_WIDTH-1:0]  way1_data;
wire [`TAG_WIDTH-1:0]   tag;
wire [`SET_WIDTH-1:0]   set;
wire [`TAG_WIDTH-1:0]   way0_tag;
wire [`TAG_WIDTH-1:0]   way1_tag;
wire lru;       //Hangi kısım daha önce değiştirildi.
wire way0_valid;
wire way1_valid;
wire way0_dirty;      //Daha önce kullanıldı mı?
wire way1_dirty;      //Daha önce kullanıldı mı?
wire dirty;           // way0 veya way1 de dirty biti varsa 1 olur.
wire hit0;
wire hit1;
wire hit;
reg miss;
wire [`DATA_WIDTH-1:0] data_temp;
reg [`DATA_WIDTH-1:0] d_cache;
//reg [`DATA_WIDTH-1:0] merged_data;

assign set = cpu_addr[8:2];
assign tag = cpu_addr[31:9];
assign way0_data = way0_cache[set][`DATA_WIDTH-1:0];
assign way1_data = way1_cache[set][`DATA_WIDTH-1:0];

assign way0_tag = way0_cache[set][54:32];
assign way1_tag = way1_cache[set][54:32];

assign way0_valid = way0_cache[set][56];
assign way1_valid = way1_cache[set][57];

assign hit0 = (tag == way0_tag) ? way0_valid :1'b0;
assign hit1 = (tag == way1_tag) ? way1_valid :1'b0;
assign hit = hit0 | hit1;

assign lru = way1_cache[set][56];
assign way0_dirty = way0_cache[set][55];
assign way1_dirty = way1_cache[set][55];

wire victim_dirty = lru ? way1_dirty : way0_dirty;
wire victim_valid = lru ? way1_valid : way0_valid;

assign stall = cpu_req && (!hit || (state != IDLE));

//MASK
always @(*) begin
    case (cpu_funct3)
        3'b000: begin // SB (Store Byte)
            case (cpu_addr[1:0])
                2'b00: store_mask = 4'b0001;
                2'b01: store_mask = 4'b0010;
                2'b10: store_mask = 4'b0100;
                2'b11: store_mask = 4'b1000;
            endcase
        end
        3'b001: begin // SH (Store Halfword)
            case (cpu_addr[1])
                1'b0:  store_mask = 4'b0011;
                1'b1:  store_mask = 4'b1100;
            endcase
        end
        3'b010:  store_mask = 4'b1111; // SW (Store Word)
        default: store_mask = 4'b0000;
    endcase
end

//CPU ya gönderilecek değer için seçim yapan sistemdir.
function  [31:0] aligned_wdata;
    input [31:0] data_in;
    input [2:0]  funct;
    reg   [7:0]  byte_payload;
    reg   [15:0] half_payload;
    begin
        byte_payload = data_in[7:0];
        half_payload = data_in[15:0];
        case (funct)
            3'b000 : aligned_wdata = {{24{byte_payload[7]}}, byte_payload};  // LB
            3'b001 : aligned_wdata = {{16{half_payload[15]}}, half_payload}; // LH
            3'b010 : aligned_wdata = data_in;                                  // LW
            3'b100 : aligned_wdata = {24'b0, byte_payload};                   // LBU
            3'b101 : aligned_wdata = {16'b0, half_payload};                   // LHU
            default: aligned_wdata = data_in;
        endcase
    end   
endfunction

//Maskeleme değerine göre depolamayı gerçekleştirir.
function [31:0] apply_store;
        input [31:0] orig_word;
        input [31:0] new_payload;
        input [3:0]  mask;
        begin
            apply_store[7:0]   = mask[0] ? new_payload[7:0]   : orig_word[7:0];
            apply_store[15:8]  = mask[1] ? new_payload[15:8]  : orig_word[15:8];
            apply_store[23:16] = mask[2] ? new_payload[23:16] : orig_word[23:16];
            apply_store[31:24] = mask[3] ? new_payload[31:24] : orig_word[31:24];
        end
endfunction

always @(posedge clk) begin
    if(reset)begin
        miss <= 0;
        state <= IDLE;
    end
    else begin
        case (state)
            IDLE: begin
                if(cpu_req)begin
                    if(hit)begin
                        if(cpu_we) begin
                            //İşlemciden belleğe yazma durumu STORE
                            if(hit0)begin
                                way0_cache[set] <= apply_store(way0_data,data_in_cpu,store_mask);
                                way0_cache[set][55] <= 1'b1; //dirty bit change
                                way1_cache[set][56] <= 1'b1; //lru change;
                            end else begin
                                way1_cache[set] <= apply_store(way1_data,data_in_cpu,store_mask);
                                way1_cache[set][55] <= 1'b1; //dirty bit change
                                way1_cache[set][56] <= 1'b0; //lru change; 
                            end
                        end else begin
                            //Bellekten işlemciye yazma durumu LOAD
                            if(hit0) begin
                                data_out_cpu <= aligned_wdata(way0_data,cpu_funct3);
                                way1_cache[set][56] <= 1'b1;
                            end else begin
                                data_out_cpu <= aligned_wdata(way1_data,cpu_funct3);
                                way1_cache[set][56] <= 1'b0; 
                            end
                        end
                    end else begin
                        //Dirty hesaplama 
                        
                    end
                end
            end
            WRITEB: begin
                
            end
            START: begin
                if (valid)begin
                    state <= DONE;
                    if(lru)begin
                        way1_cache[set] <= {valid,!lru,1'b1,tag,data_in_cpu};
                    end
                    else begin
                        way0_cache[set] <= {valid,1'b1,tag,data_in_cpu};
                        way1_cache[set][56] <= 1'b1;
                    end
                end
                else state <= START; 
            end
            DONE: begin
                miss <= 0;
                state <= IDLE;
            end
        endcase
    end

end


    
endmodule