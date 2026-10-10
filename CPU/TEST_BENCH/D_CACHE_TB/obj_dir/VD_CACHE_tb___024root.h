// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VD_CACHE_tb.h for the primary calling header

#ifndef VERILATED_VD_CACHE_TB___024ROOT_H_
#define VERILATED_VD_CACHE_TB___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class VD_CACHE_tb__Syms;

class alignas(VL_CACHE_LINE_BYTES) VD_CACHE_tb___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ D_CACHE_tb__DOT__clk;
    CData/*0:0*/ D_CACHE_tb__DOT__reset;
    CData/*0:0*/ D_CACHE_tb__DOT__mem_ack;
    CData/*0:0*/ D_CACHE_tb__DOT__mem_ready;
    CData/*0:0*/ D_CACHE_tb__DOT__mem_req;
    CData/*0:0*/ D_CACHE_tb__DOT__mem_we;
    CData/*2:0*/ D_CACHE_tb__DOT__cpu_funct3;
    CData/*0:0*/ D_CACHE_tb__DOT__cpu_we;
    CData/*0:0*/ D_CACHE_tb__DOT__cpu_req;
    CData/*0:0*/ D_CACHE_tb__DOT__saw_miss;
    CData/*2:0*/ D_CACHE_tb__DOT__access__Vstatic__f3;
    CData/*0:0*/ D_CACHE_tb__DOT__access__Vstatic__we;
    CData/*0:0*/ D_CACHE_tb__DOT__uut__DOT__stall;
    CData/*1:0*/ D_CACHE_tb__DOT__uut__DOT__state;
    CData/*3:0*/ D_CACHE_tb__DOT__uut__DOT__store_mask;
    CData/*0:0*/ D_CACHE_tb__DOT__uut__DOT__lru;
    CData/*0:0*/ D_CACHE_tb__DOT__uut__DOT__way0_valid;
    CData/*0:0*/ D_CACHE_tb__DOT__uut__DOT__way1_valid;
    CData/*0:0*/ D_CACHE_tb__DOT__uut__DOT__dirty;
    CData/*0:0*/ D_CACHE_tb__DOT__uut__DOT__hit0;
    CData/*0:0*/ D_CACHE_tb__DOT__uut__DOT__hit;
    CData/*0:0*/ D_CACHE_tb__DOT__uut__DOT__miss;
    CData/*0:0*/ D_CACHE_tb__DOT__uut__DOT__victim_dirty;
    CData/*7:0*/ D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__byte_payload;
    CData/*0:0*/ __Vtrigprevexpr___TOP__D_CACHE_tb__DOT__clk__0;
    SData/*15:0*/ D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__half_payload;
    IData/*31:0*/ D_CACHE_tb__DOT__mem_rdata;
    IData/*31:0*/ D_CACHE_tb__DOT__memory_addr;
    IData/*31:0*/ D_CACHE_tb__DOT__mem_wdata;
    IData/*31:0*/ D_CACHE_tb__DOT__data_in_cpu;
    IData/*31:0*/ D_CACHE_tb__DOT__cpu_addr;
    IData/*31:0*/ D_CACHE_tb__DOT__data_out_cpu;
    IData/*31:0*/ D_CACHE_tb__DOT__mem_cnt;
    IData/*31:0*/ D_CACHE_tb__DOT__mem_rd_count;
    IData/*31:0*/ D_CACHE_tb__DOT__mem_wr_count;
    IData/*31:0*/ D_CACHE_tb__DOT__pass_count;
    IData/*31:0*/ D_CACHE_tb__DOT__fail_count;
    IData/*31:0*/ D_CACHE_tb__DOT__test_count;
    IData/*31:0*/ D_CACHE_tb__DOT__rdata;
    IData/*31:0*/ D_CACHE_tb__DOT__access__Vstatic__addr;
    IData/*31:0*/ D_CACHE_tb__DOT__access__Vstatic__wdata;
    IData/*31:0*/ D_CACHE_tb__DOT__store__Vstatic__lane;
    IData/*31:0*/ D_CACHE_tb__DOT__init_cache__DOT__i;
    IData/*31:0*/ D_CACHE_tb__DOT__clean_evict__DOT__wr_before;
    IData/*31:0*/ D_CACHE_tb__DOT__uut__DOT____VlemCall_1__apply_store;
    IData/*31:0*/ D_CACHE_tb__DOT__uut__DOT____VlemCall_0__apply_store;
    IData/*31:0*/ D_CACHE_tb__DOT__uut__DOT__way0_data;
    IData/*31:0*/ D_CACHE_tb__DOT__uut__DOT__way1_data;
    IData/*22:0*/ D_CACHE_tb__DOT__uut__DOT__way0_tag;
    IData/*22:0*/ D_CACHE_tb__DOT__uut__DOT__way1_tag;
    IData/*31:0*/ D_CACHE_tb__DOT__uut__DOT__cpu_bff_addr;
    IData/*31:0*/ D_CACHE_tb__DOT__uut__DOT__data_temp;
    IData/*31:0*/ D_CACHE_tb__DOT__uut__DOT__d_cache;
    IData/*31:0*/ __Vi;
    VlUnpacked<IData/*31:0*/, 16384> D_CACHE_tb__DOT__mem;
    VlUnpacked<QData/*56:0*/, 129> D_CACHE_tb__DOT__uut__DOT__way0_cache;
    VlUnpacked<QData/*57:0*/, 129> D_CACHE_tb__DOT__uut__DOT__way1_cache;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VicoTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlUnpacked<CData/*0:0*/, 6> __Vm_traceActivity;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_h883832f6__0;

    // INTERNAL VARIABLES
    VD_CACHE_tb__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    VD_CACHE_tb___024root(VD_CACHE_tb__Syms* symsp, const char* namep);
    ~VD_CACHE_tb___024root();
    VL_UNCOPYABLE(VD_CACHE_tb___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
