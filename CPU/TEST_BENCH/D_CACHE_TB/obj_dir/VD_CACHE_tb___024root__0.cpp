// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VD_CACHE_tb.h for the primary calling header

#include "VD_CACHE_tb__pch.h"

VlCoroutine VD_CACHE_tb___024root___eval_initial__TOP__Vtiming__0(VD_CACHE_tb___024root* vlSelf);
VlCoroutine VD_CACHE_tb___024root___eval_initial__TOP__Vtiming__1(VD_CACHE_tb___024root* vlSelf);
VlCoroutine VD_CACHE_tb___024root___eval_initial__TOP__Vtiming__2(VD_CACHE_tb___024root* vlSelf);

void VD_CACHE_tb___024root___eval_initial(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_initial\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    {
        // Inlined CFunc: _eval_initial__TOP
        vlSelfRef.D_CACHE_tb__DOT__mem_ack = 0U;
        vlSelfRef.D_CACHE_tb__DOT__mem_ready = 0U;
        vlSelfRef.D_CACHE_tb__DOT__mem_rdata = 0U;
        vlSelfRef.D_CACHE_tb__DOT__mem_cnt = 0U;
        vlSelfRef.D_CACHE_tb__DOT__mem_rd_count = 0U;
        vlSelfRef.D_CACHE_tb__DOT__mem_wr_count = 0U;
        vlSelfRef.D_CACHE_tb__DOT__init_cache__DOT__i = 0U;
        while (VL_GTES_III(32, 0x00000080U, vlSelfRef.D_CACHE_tb__DOT__init_cache__DOT__i)) {
            if (VL_LIKELY(((0x80U >= (0x000000ffU & vlSelfRef.D_CACHE_tb__DOT__init_cache__DOT__i))))) {
                vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_cache[(0x000000ffU 
                                                                 & vlSelfRef.D_CACHE_tb__DOT__init_cache__DOT__i)] = 0ULL;
                vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache[(0x000000ffU 
                                                                 & vlSelfRef.D_CACHE_tb__DOT__init_cache__DOT__i)] = 0ULL;
            }
            vlSelfRef.D_CACHE_tb__DOT__init_cache__DOT__i 
                = ((IData)(1U) + vlSelfRef.D_CACHE_tb__DOT__init_cache__DOT__i);
        }
    }
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
    VD_CACHE_tb___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    VD_CACHE_tb___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    VD_CACHE_tb___024root___eval_initial__TOP__Vtiming__2(vlSelf);
}

void VD_CACHE_tb___024root___eval_sample(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_sample\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VD_CACHE_tb___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool VD_CACHE_tb___024root___eval_ico(VD_CACHE_tb___024root* vlSelf, CData/*0:0*/ firstIteration) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_ico\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered[0U]) 
                                     | (IData)((IData)(firstIteration)));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VD_CACHE_tb___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
    return (0U);
}

void VD_CACHE_tb___024root___timing_ready(VD_CACHE_tb___024root* vlSelf);
void VD_CACHE_tb___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in);
#ifdef VL_DEBUG
VL_ATTR_COLD void VD_CACHE_tb___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
bool VD_CACHE_tb___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);
void VD_CACHE_tb___024root___timing_resume(VD_CACHE_tb___024root* vlSelf);
void VD_CACHE_tb___024root___act_comb__TOP__0(VD_CACHE_tb___024root* vlSelf);

bool VD_CACHE_tb___024root___eval_act(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_act\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    {
        // Inlined CFunc: _eval_triggers_vec__act
        vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                        ((vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                          << 1U) 
                                                         | ((IData)(vlSelfRef.D_CACHE_tb__DOT__clk) 
                                                            & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__D_CACHE_tb__DOT__clk__0))))));
        vlSelfRef.__Vtrigprevexpr___TOP__D_CACHE_tb__DOT__clk__0 
            = vlSelfRef.D_CACHE_tb__DOT__clk;
    }
    VD_CACHE_tb___024root___timing_ready(vlSelf);
    VD_CACHE_tb___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VD_CACHE_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    VD_CACHE_tb___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = VD_CACHE_tb___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        VD_CACHE_tb___024root___timing_resume(vlSelf);
        {
            // Inlined CFunc: _eval_body__act
            if ((3ULL & vlSelfRef.__VactTriggered[0U])) {
                VD_CACHE_tb___024root___act_comb__TOP__0(vlSelf);
                vlSelfRef.__Vm_traceActivity[3U] = 1U;
            }
        }
    }
    return (__VactExecute);
}

bool VD_CACHE_tb___024root___eval_inact(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_inact\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 4, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void VD_CACHE_tb___024root___eval_body__nba(VD_CACHE_tb___024root* vlSelf);
void VD_CACHE_tb___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out);

bool VD_CACHE_tb___024root___eval_nba(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_nba\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = VD_CACHE_tb___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        VD_CACHE_tb___024root___eval_body__nba(vlSelf);
        VD_CACHE_tb___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

bool VD_CACHE_tb___024root___eval_obs(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_obs\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    return (0U);
}

bool VD_CACHE_tb___024root___eval_react(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_react\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    return (0U);
}

void VD_CACHE_tb___024root___eval_postponed(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_postponed\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VlCoroutine VD_CACHE_tb___024root___eval_initial__TOP__Vtiming__0(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_initial__TOP__Vtiming__0\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.D_CACHE_tb__DOT__clk = 0U;
    while (true) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             113);
        vlSelfRef.D_CACHE_tb__DOT__clk = (1U & (~ (IData)(vlSelfRef.D_CACHE_tb__DOT__clk)));
    }
    co_return;
}

VlCoroutine VD_CACHE_tb___024root___eval_initial__TOP__Vtiming__1(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_initial__TOP__Vtiming__1\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    co_await vlSelfRef.__VdlySched.delay(0x0000000077359400ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         118);
    VL_WRITEF_NX("[FAIL] watchdog timeout (DUT stuck, stall never released?)\n",0);
    VL_FINISH_MT("/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 120, "");
    co_return;
}

void VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(VD_CACHE_tb___024root* vlSelf, const char* __VeventDescription);
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_hc8661195_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h67988180_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_hdf5f5d62_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_hd54411ea_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h3df8aa30_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_he7e89ed9_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_hb71df3fc_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_he450a8a4_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h5ff31a4e_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_had322ff6_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h9af0c437_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_he80b4162_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h6b3bce4a_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h93f055be_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h9d5d6592_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_hddafe4b6_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_hb537c2ed_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h96405d94_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h8dfa189f_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_hca5c5548_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_hd0c07945_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h55c4e4d6_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_hd711b368_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h294b1dc1_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_he4371207_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h2866433b_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h6a025562_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h2dcce8d6_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_hc984ae36_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h360dcc9f_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h68602cbd_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h59e3c7a1_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h4a3fce6c_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h34c806d1_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_ha7acb184_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_hff4d6978_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h338e056b_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h952d790b_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h1031a607_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_ha442652b_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h1e1540f0_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_hebc43693_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h5853f4df_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h367192a5_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_heba49680_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_hf379d909_0;
extern const VlWide<51>/*1631:0*/ VD_CACHE_tb__ConstPool__CONST_h745c521e_0;

VlCoroutine VD_CACHE_tb___024root___eval_initial__TOP__Vtiming__2(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_initial__TOP__Vtiming__2\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__0__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__0__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__0__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__0__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__0__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__0__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__1__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__1__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__1__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__1__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__1__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__1__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__2__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__2__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__2__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__2__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__2__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__2__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__3__addr;
    __Vtask_D_CACHE_tb__DOT__write_mem__3__addr = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__3__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__3__word = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__4__addr;
    __Vtask_D_CACHE_tb__DOT__load__4__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__4__f3;
    __Vtask_D_CACHE_tb__DOT__load__4__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__4__expected;
    __Vtask_D_CACHE_tb__DOT__load__4__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__4__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__4__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__4__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__4__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__5__addr;
    __Vtask_D_CACHE_tb__DOT__access__5__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__5__f3;
    __Vtask_D_CACHE_tb__DOT__access__5__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__5__we;
    __Vtask_D_CACHE_tb__DOT__access__5__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__5__wdata;
    __Vtask_D_CACHE_tb__DOT__access__5__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__6__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__6__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__6__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__6__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__6__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__6__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__7__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__7__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__7__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__7__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__7__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__7__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__8__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__8__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__8__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__8__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__8__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__8__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__9__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__9__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__9__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__9__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__9__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__9__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__10__addr;
    __Vtask_D_CACHE_tb__DOT__load__10__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__10__f3;
    __Vtask_D_CACHE_tb__DOT__load__10__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__10__expected;
    __Vtask_D_CACHE_tb__DOT__load__10__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__10__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__10__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__10__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__10__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__11__addr;
    __Vtask_D_CACHE_tb__DOT__access__11__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__11__f3;
    __Vtask_D_CACHE_tb__DOT__access__11__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__11__we;
    __Vtask_D_CACHE_tb__DOT__access__11__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__11__wdata;
    __Vtask_D_CACHE_tb__DOT__access__11__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__12__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__12__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__12__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__12__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__12__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__12__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__13__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__13__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__13__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__13__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__13__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__13__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__14__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__14__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__14__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__14__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__14__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__14__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__15__addr;
    __Vtask_D_CACHE_tb__DOT__write_mem__15__addr = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__15__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__15__word = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__16__addr;
    __Vtask_D_CACHE_tb__DOT__write_mem__16__addr = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__16__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__16__word = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__17__addr;
    __Vtask_D_CACHE_tb__DOT__write_mem__17__addr = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__17__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__17__word = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__18__addr;
    __Vtask_D_CACHE_tb__DOT__load__18__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__18__f3;
    __Vtask_D_CACHE_tb__DOT__load__18__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__18__expected;
    __Vtask_D_CACHE_tb__DOT__load__18__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__18__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__18__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__18__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__18__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__19__addr;
    __Vtask_D_CACHE_tb__DOT__access__19__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__19__f3;
    __Vtask_D_CACHE_tb__DOT__access__19__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__19__we;
    __Vtask_D_CACHE_tb__DOT__access__19__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__19__wdata;
    __Vtask_D_CACHE_tb__DOT__access__19__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__20__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__20__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__20__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__20__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__20__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__20__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__21__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__21__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__21__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__21__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__21__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__21__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__22__addr;
    __Vtask_D_CACHE_tb__DOT__load__22__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__22__f3;
    __Vtask_D_CACHE_tb__DOT__load__22__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__22__expected;
    __Vtask_D_CACHE_tb__DOT__load__22__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__22__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__22__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__22__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__22__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__23__addr;
    __Vtask_D_CACHE_tb__DOT__access__23__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__23__f3;
    __Vtask_D_CACHE_tb__DOT__access__23__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__23__we;
    __Vtask_D_CACHE_tb__DOT__access__23__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__23__wdata;
    __Vtask_D_CACHE_tb__DOT__access__23__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__24__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__24__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__24__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__24__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__24__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__24__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__25__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__25__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__25__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__25__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__25__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__25__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__26__addr;
    __Vtask_D_CACHE_tb__DOT__load__26__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__26__f3;
    __Vtask_D_CACHE_tb__DOT__load__26__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__26__expected;
    __Vtask_D_CACHE_tb__DOT__load__26__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__26__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__26__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__26__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__26__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__27__addr;
    __Vtask_D_CACHE_tb__DOT__access__27__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__27__f3;
    __Vtask_D_CACHE_tb__DOT__access__27__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__27__we;
    __Vtask_D_CACHE_tb__DOT__access__27__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__27__wdata;
    __Vtask_D_CACHE_tb__DOT__access__27__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__28__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__28__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__28__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__28__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__28__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__28__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__29__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__29__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__29__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__29__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__29__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__29__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__30__addr;
    __Vtask_D_CACHE_tb__DOT__load__30__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__30__f3;
    __Vtask_D_CACHE_tb__DOT__load__30__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__30__expected;
    __Vtask_D_CACHE_tb__DOT__load__30__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__30__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__30__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__30__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__30__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__31__addr;
    __Vtask_D_CACHE_tb__DOT__access__31__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__31__f3;
    __Vtask_D_CACHE_tb__DOT__access__31__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__31__we;
    __Vtask_D_CACHE_tb__DOT__access__31__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__31__wdata;
    __Vtask_D_CACHE_tb__DOT__access__31__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__32__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__32__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__32__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__32__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__32__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__32__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__33__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__33__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__33__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__33__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__33__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__33__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__34__addr;
    __Vtask_D_CACHE_tb__DOT__write_mem__34__addr = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__34__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__34__word = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__35__addr;
    __Vtask_D_CACHE_tb__DOT__load__35__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__35__f3;
    __Vtask_D_CACHE_tb__DOT__load__35__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__35__expected;
    __Vtask_D_CACHE_tb__DOT__load__35__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__35__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__35__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__35__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__35__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__36__addr;
    __Vtask_D_CACHE_tb__DOT__access__36__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__36__f3;
    __Vtask_D_CACHE_tb__DOT__access__36__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__36__we;
    __Vtask_D_CACHE_tb__DOT__access__36__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__36__wdata;
    __Vtask_D_CACHE_tb__DOT__access__36__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__37__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__37__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__37__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__37__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__37__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__37__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__38__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__38__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__38__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__38__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__38__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__38__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__39__addr;
    __Vtask_D_CACHE_tb__DOT__load__39__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__39__f3;
    __Vtask_D_CACHE_tb__DOT__load__39__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__39__expected;
    __Vtask_D_CACHE_tb__DOT__load__39__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__39__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__39__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__39__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__39__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__40__addr;
    __Vtask_D_CACHE_tb__DOT__access__40__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__40__f3;
    __Vtask_D_CACHE_tb__DOT__access__40__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__40__we;
    __Vtask_D_CACHE_tb__DOT__access__40__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__40__wdata;
    __Vtask_D_CACHE_tb__DOT__access__40__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__41__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__41__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__41__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__41__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__41__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__41__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__42__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__42__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__42__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__42__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__42__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__42__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__43__addr;
    __Vtask_D_CACHE_tb__DOT__load__43__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__43__f3;
    __Vtask_D_CACHE_tb__DOT__load__43__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__43__expected;
    __Vtask_D_CACHE_tb__DOT__load__43__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__43__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__43__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__43__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__43__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__44__addr;
    __Vtask_D_CACHE_tb__DOT__access__44__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__44__f3;
    __Vtask_D_CACHE_tb__DOT__access__44__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__44__we;
    __Vtask_D_CACHE_tb__DOT__access__44__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__44__wdata;
    __Vtask_D_CACHE_tb__DOT__access__44__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__45__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__45__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__45__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__45__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__45__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__45__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__46__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__46__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__46__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__46__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__46__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__46__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__47__addr;
    __Vtask_D_CACHE_tb__DOT__load__47__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__47__f3;
    __Vtask_D_CACHE_tb__DOT__load__47__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__47__expected;
    __Vtask_D_CACHE_tb__DOT__load__47__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__47__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__47__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__47__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__47__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__48__addr;
    __Vtask_D_CACHE_tb__DOT__access__48__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__48__f3;
    __Vtask_D_CACHE_tb__DOT__access__48__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__48__we;
    __Vtask_D_CACHE_tb__DOT__access__48__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__48__wdata;
    __Vtask_D_CACHE_tb__DOT__access__48__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__49__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__49__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__49__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__49__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__49__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__49__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__50__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__50__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__50__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__50__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__50__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__50__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__51__addr;
    __Vtask_D_CACHE_tb__DOT__load__51__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__51__f3;
    __Vtask_D_CACHE_tb__DOT__load__51__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__51__expected;
    __Vtask_D_CACHE_tb__DOT__load__51__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__51__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__51__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__51__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__51__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__52__addr;
    __Vtask_D_CACHE_tb__DOT__access__52__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__52__f3;
    __Vtask_D_CACHE_tb__DOT__access__52__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__52__we;
    __Vtask_D_CACHE_tb__DOT__access__52__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__52__wdata;
    __Vtask_D_CACHE_tb__DOT__access__52__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__53__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__53__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__53__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__53__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__53__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__53__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__54__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__54__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__54__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__54__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__54__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__54__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__55__addr;
    __Vtask_D_CACHE_tb__DOT__load__55__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__55__f3;
    __Vtask_D_CACHE_tb__DOT__load__55__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__55__expected;
    __Vtask_D_CACHE_tb__DOT__load__55__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__55__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__55__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__55__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__55__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__56__addr;
    __Vtask_D_CACHE_tb__DOT__access__56__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__56__f3;
    __Vtask_D_CACHE_tb__DOT__access__56__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__56__we;
    __Vtask_D_CACHE_tb__DOT__access__56__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__56__wdata;
    __Vtask_D_CACHE_tb__DOT__access__56__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__57__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__57__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__57__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__57__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__57__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__57__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__58__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__58__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__58__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__58__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__58__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__58__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__59__addr;
    __Vtask_D_CACHE_tb__DOT__write_mem__59__addr = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__59__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__59__word = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__60__addr;
    __Vtask_D_CACHE_tb__DOT__load__60__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__60__f3;
    __Vtask_D_CACHE_tb__DOT__load__60__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__60__expected;
    __Vtask_D_CACHE_tb__DOT__load__60__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__60__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__60__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__60__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__60__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__61__addr;
    __Vtask_D_CACHE_tb__DOT__access__61__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__61__f3;
    __Vtask_D_CACHE_tb__DOT__access__61__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__61__we;
    __Vtask_D_CACHE_tb__DOT__access__61__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__61__wdata;
    __Vtask_D_CACHE_tb__DOT__access__61__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__62__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__62__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__62__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__62__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__62__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__62__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__63__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__63__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__63__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__63__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__63__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__63__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__64__addr;
    __Vtask_D_CACHE_tb__DOT__load__64__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__64__f3;
    __Vtask_D_CACHE_tb__DOT__load__64__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__64__expected;
    __Vtask_D_CACHE_tb__DOT__load__64__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__64__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__64__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__64__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__64__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__65__addr;
    __Vtask_D_CACHE_tb__DOT__access__65__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__65__f3;
    __Vtask_D_CACHE_tb__DOT__access__65__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__65__we;
    __Vtask_D_CACHE_tb__DOT__access__65__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__65__wdata;
    __Vtask_D_CACHE_tb__DOT__access__65__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__66__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__66__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__66__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__66__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__66__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__66__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__67__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__67__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__67__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__67__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__67__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__67__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__68__addr;
    __Vtask_D_CACHE_tb__DOT__load__68__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__68__f3;
    __Vtask_D_CACHE_tb__DOT__load__68__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__68__expected;
    __Vtask_D_CACHE_tb__DOT__load__68__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__68__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__68__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__68__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__68__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__69__addr;
    __Vtask_D_CACHE_tb__DOT__access__69__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__69__f3;
    __Vtask_D_CACHE_tb__DOT__access__69__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__69__we;
    __Vtask_D_CACHE_tb__DOT__access__69__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__69__wdata;
    __Vtask_D_CACHE_tb__DOT__access__69__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__70__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__70__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__70__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__70__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__70__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__70__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__71__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__71__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__71__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__71__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__71__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__71__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__72__addr;
    __Vtask_D_CACHE_tb__DOT__load__72__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__72__f3;
    __Vtask_D_CACHE_tb__DOT__load__72__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__72__expected;
    __Vtask_D_CACHE_tb__DOT__load__72__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__72__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__72__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__72__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__72__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__73__addr;
    __Vtask_D_CACHE_tb__DOT__access__73__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__73__f3;
    __Vtask_D_CACHE_tb__DOT__access__73__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__73__we;
    __Vtask_D_CACHE_tb__DOT__access__73__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__73__wdata;
    __Vtask_D_CACHE_tb__DOT__access__73__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__74__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__74__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__74__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__74__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__74__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__74__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__75__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__75__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__75__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__75__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__75__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__75__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__76__addr;
    __Vtask_D_CACHE_tb__DOT__write_mem__76__addr = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__76__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__76__word = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__77__addr;
    __Vtask_D_CACHE_tb__DOT__load__77__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__77__f3;
    __Vtask_D_CACHE_tb__DOT__load__77__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__77__expected;
    __Vtask_D_CACHE_tb__DOT__load__77__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__77__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__77__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__77__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__77__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__78__addr;
    __Vtask_D_CACHE_tb__DOT__access__78__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__78__f3;
    __Vtask_D_CACHE_tb__DOT__access__78__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__78__we;
    __Vtask_D_CACHE_tb__DOT__access__78__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__78__wdata;
    __Vtask_D_CACHE_tb__DOT__access__78__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__79__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__79__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__79__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__79__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__79__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__79__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__80__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__80__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__80__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__80__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__80__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__80__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__store__81__addr;
    __Vtask_D_CACHE_tb__DOT__store__81__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__store__81__f3;
    __Vtask_D_CACHE_tb__DOT__store__81__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__store__81__value;
    __Vtask_D_CACHE_tb__DOT__store__81__value = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__store__81__expect_miss;
    __Vtask_D_CACHE_tb__DOT__store__81__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__store__81__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__store__81__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__82__addr;
    __Vtask_D_CACHE_tb__DOT__access__82__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__82__f3;
    __Vtask_D_CACHE_tb__DOT__access__82__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__82__we;
    __Vtask_D_CACHE_tb__DOT__access__82__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__82__wdata;
    __Vtask_D_CACHE_tb__DOT__access__82__wdata = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__83__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__83__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__83__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__83__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__83__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__83__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__84__addr;
    __Vtask_D_CACHE_tb__DOT__load__84__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__84__f3;
    __Vtask_D_CACHE_tb__DOT__load__84__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__84__expected;
    __Vtask_D_CACHE_tb__DOT__load__84__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__84__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__84__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__84__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__84__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__85__addr;
    __Vtask_D_CACHE_tb__DOT__access__85__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__85__f3;
    __Vtask_D_CACHE_tb__DOT__access__85__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__85__we;
    __Vtask_D_CACHE_tb__DOT__access__85__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__85__wdata;
    __Vtask_D_CACHE_tb__DOT__access__85__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__86__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__86__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__86__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__86__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__86__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__86__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__87__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__87__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__87__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__87__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__87__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__87__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__88__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__88__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__88__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__88__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__88__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__88__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__89__addr;
    __Vtask_D_CACHE_tb__DOT__write_mem__89__addr = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__89__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__89__word = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__90__addr;
    __Vtask_D_CACHE_tb__DOT__load__90__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__90__f3;
    __Vtask_D_CACHE_tb__DOT__load__90__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__90__expected;
    __Vtask_D_CACHE_tb__DOT__load__90__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__90__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__90__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__90__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__90__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__91__addr;
    __Vtask_D_CACHE_tb__DOT__access__91__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__91__f3;
    __Vtask_D_CACHE_tb__DOT__access__91__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__91__we;
    __Vtask_D_CACHE_tb__DOT__access__91__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__91__wdata;
    __Vtask_D_CACHE_tb__DOT__access__91__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__92__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__92__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__92__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__92__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__92__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__92__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__93__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__93__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__93__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__93__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__93__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__93__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__store__94__addr;
    __Vtask_D_CACHE_tb__DOT__store__94__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__store__94__f3;
    __Vtask_D_CACHE_tb__DOT__store__94__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__store__94__value;
    __Vtask_D_CACHE_tb__DOT__store__94__value = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__store__94__expect_miss;
    __Vtask_D_CACHE_tb__DOT__store__94__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__store__94__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__store__94__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__95__addr;
    __Vtask_D_CACHE_tb__DOT__access__95__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__95__f3;
    __Vtask_D_CACHE_tb__DOT__access__95__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__95__we;
    __Vtask_D_CACHE_tb__DOT__access__95__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__95__wdata;
    __Vtask_D_CACHE_tb__DOT__access__95__wdata = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__96__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__96__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__96__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__96__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__96__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__96__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__store__97__addr;
    __Vtask_D_CACHE_tb__DOT__store__97__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__store__97__f3;
    __Vtask_D_CACHE_tb__DOT__store__97__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__store__97__value;
    __Vtask_D_CACHE_tb__DOT__store__97__value = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__store__97__expect_miss;
    __Vtask_D_CACHE_tb__DOT__store__97__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__store__97__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__store__97__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__98__addr;
    __Vtask_D_CACHE_tb__DOT__access__98__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__98__f3;
    __Vtask_D_CACHE_tb__DOT__access__98__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__98__we;
    __Vtask_D_CACHE_tb__DOT__access__98__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__98__wdata;
    __Vtask_D_CACHE_tb__DOT__access__98__wdata = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__99__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__99__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__99__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__99__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__99__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__99__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__store__100__addr;
    __Vtask_D_CACHE_tb__DOT__store__100__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__store__100__f3;
    __Vtask_D_CACHE_tb__DOT__store__100__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__store__100__value;
    __Vtask_D_CACHE_tb__DOT__store__100__value = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__store__100__expect_miss;
    __Vtask_D_CACHE_tb__DOT__store__100__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__store__100__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__store__100__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__101__addr;
    __Vtask_D_CACHE_tb__DOT__access__101__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__101__f3;
    __Vtask_D_CACHE_tb__DOT__access__101__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__101__we;
    __Vtask_D_CACHE_tb__DOT__access__101__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__101__wdata;
    __Vtask_D_CACHE_tb__DOT__access__101__wdata = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__102__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__102__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__102__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__102__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__102__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__102__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__103__addr;
    __Vtask_D_CACHE_tb__DOT__load__103__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__103__f3;
    __Vtask_D_CACHE_tb__DOT__load__103__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__103__expected;
    __Vtask_D_CACHE_tb__DOT__load__103__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__103__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__103__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__103__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__103__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__104__addr;
    __Vtask_D_CACHE_tb__DOT__access__104__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__104__f3;
    __Vtask_D_CACHE_tb__DOT__access__104__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__104__we;
    __Vtask_D_CACHE_tb__DOT__access__104__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__104__wdata;
    __Vtask_D_CACHE_tb__DOT__access__104__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__105__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__105__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__105__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__105__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__105__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__105__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__106__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__106__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__106__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__106__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__106__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__106__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__107__addr;
    __Vtask_D_CACHE_tb__DOT__write_mem__107__addr = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__107__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__107__word = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__108__addr;
    __Vtask_D_CACHE_tb__DOT__load__108__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__108__f3;
    __Vtask_D_CACHE_tb__DOT__load__108__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__108__expected;
    __Vtask_D_CACHE_tb__DOT__load__108__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__108__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__108__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__108__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__108__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__109__addr;
    __Vtask_D_CACHE_tb__DOT__access__109__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__109__f3;
    __Vtask_D_CACHE_tb__DOT__access__109__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__109__we;
    __Vtask_D_CACHE_tb__DOT__access__109__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__109__wdata;
    __Vtask_D_CACHE_tb__DOT__access__109__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__110__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__110__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__110__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__110__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__110__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__110__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__111__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__111__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__111__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__111__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__111__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__111__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__112__addr;
    __Vtask_D_CACHE_tb__DOT__load__112__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__112__f3;
    __Vtask_D_CACHE_tb__DOT__load__112__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__112__expected;
    __Vtask_D_CACHE_tb__DOT__load__112__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__112__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__112__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__112__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__112__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__113__addr;
    __Vtask_D_CACHE_tb__DOT__access__113__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__113__f3;
    __Vtask_D_CACHE_tb__DOT__access__113__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__113__we;
    __Vtask_D_CACHE_tb__DOT__access__113__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__113__wdata;
    __Vtask_D_CACHE_tb__DOT__access__113__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__114__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__114__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__114__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__114__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__114__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__114__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__115__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__115__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__115__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__115__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__115__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__115__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__116__addr;
    __Vtask_D_CACHE_tb__DOT__write_mem__116__addr = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__116__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__116__word = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__117__addr;
    __Vtask_D_CACHE_tb__DOT__write_mem__117__addr = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__117__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__117__word = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__118__addr;
    __Vtask_D_CACHE_tb__DOT__load__118__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__118__f3;
    __Vtask_D_CACHE_tb__DOT__load__118__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__118__expected;
    __Vtask_D_CACHE_tb__DOT__load__118__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__118__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__118__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__118__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__118__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__119__addr;
    __Vtask_D_CACHE_tb__DOT__access__119__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__119__f3;
    __Vtask_D_CACHE_tb__DOT__access__119__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__119__we;
    __Vtask_D_CACHE_tb__DOT__access__119__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__119__wdata;
    __Vtask_D_CACHE_tb__DOT__access__119__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__120__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__120__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__120__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__120__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__120__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__120__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__121__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__121__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__121__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__121__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__121__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__121__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__122__addr;
    __Vtask_D_CACHE_tb__DOT__load__122__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__122__f3;
    __Vtask_D_CACHE_tb__DOT__load__122__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__122__expected;
    __Vtask_D_CACHE_tb__DOT__load__122__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__122__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__122__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__122__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__122__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__123__addr;
    __Vtask_D_CACHE_tb__DOT__access__123__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__123__f3;
    __Vtask_D_CACHE_tb__DOT__access__123__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__123__we;
    __Vtask_D_CACHE_tb__DOT__access__123__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__123__wdata;
    __Vtask_D_CACHE_tb__DOT__access__123__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__124__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__124__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__124__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__124__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__124__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__124__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__125__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__125__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__125__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__125__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__125__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__125__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__126__addr;
    __Vtask_D_CACHE_tb__DOT__load__126__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__126__f3;
    __Vtask_D_CACHE_tb__DOT__load__126__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__126__expected;
    __Vtask_D_CACHE_tb__DOT__load__126__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__126__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__126__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__126__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__126__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__127__addr;
    __Vtask_D_CACHE_tb__DOT__access__127__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__127__f3;
    __Vtask_D_CACHE_tb__DOT__access__127__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__127__we;
    __Vtask_D_CACHE_tb__DOT__access__127__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__127__wdata;
    __Vtask_D_CACHE_tb__DOT__access__127__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__128__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__128__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__128__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__128__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__128__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__128__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__129__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__129__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__129__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__129__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__129__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__129__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__130__addr;
    __Vtask_D_CACHE_tb__DOT__load__130__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__130__f3;
    __Vtask_D_CACHE_tb__DOT__load__130__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__130__expected;
    __Vtask_D_CACHE_tb__DOT__load__130__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__130__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__130__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__130__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__130__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__131__addr;
    __Vtask_D_CACHE_tb__DOT__access__131__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__131__f3;
    __Vtask_D_CACHE_tb__DOT__access__131__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__131__we;
    __Vtask_D_CACHE_tb__DOT__access__131__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__131__wdata;
    __Vtask_D_CACHE_tb__DOT__access__131__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__132__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__132__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__132__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__132__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__132__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__132__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__133__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__133__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__133__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__133__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__133__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__133__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__134__addr;
    __Vtask_D_CACHE_tb__DOT__write_mem__134__addr = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__134__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__134__word = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__135__addr;
    __Vtask_D_CACHE_tb__DOT__load__135__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__135__f3;
    __Vtask_D_CACHE_tb__DOT__load__135__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__135__expected;
    __Vtask_D_CACHE_tb__DOT__load__135__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__135__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__135__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__135__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__135__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__136__addr;
    __Vtask_D_CACHE_tb__DOT__access__136__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__136__f3;
    __Vtask_D_CACHE_tb__DOT__access__136__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__136__we;
    __Vtask_D_CACHE_tb__DOT__access__136__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__136__wdata;
    __Vtask_D_CACHE_tb__DOT__access__136__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__137__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__137__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__137__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__137__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__137__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__137__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__138__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__138__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__138__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__138__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__138__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__138__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__139__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__139__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__139__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__139__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__139__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__139__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__140__addr;
    __Vtask_D_CACHE_tb__DOT__load__140__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__140__f3;
    __Vtask_D_CACHE_tb__DOT__load__140__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__140__expected;
    __Vtask_D_CACHE_tb__DOT__load__140__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__140__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__140__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__140__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__140__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__141__addr;
    __Vtask_D_CACHE_tb__DOT__access__141__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__141__f3;
    __Vtask_D_CACHE_tb__DOT__access__141__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__141__we;
    __Vtask_D_CACHE_tb__DOT__access__141__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__141__wdata;
    __Vtask_D_CACHE_tb__DOT__access__141__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__142__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__142__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__142__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__142__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__142__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__142__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__143__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__143__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__143__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__143__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__143__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__143__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__144__addr;
    __Vtask_D_CACHE_tb__DOT__write_mem__144__addr = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__144__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__144__word = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__145__addr;
    __Vtask_D_CACHE_tb__DOT__write_mem__145__addr = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__145__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__145__word = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__146__addr;
    __Vtask_D_CACHE_tb__DOT__write_mem__146__addr = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__146__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__146__word = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__147__addr;
    __Vtask_D_CACHE_tb__DOT__write_mem__147__addr = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__write_mem__147__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__147__word = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__148__addr;
    __Vtask_D_CACHE_tb__DOT__load__148__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__148__f3;
    __Vtask_D_CACHE_tb__DOT__load__148__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__148__expected;
    __Vtask_D_CACHE_tb__DOT__load__148__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__148__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__148__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__148__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__148__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__149__addr;
    __Vtask_D_CACHE_tb__DOT__access__149__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__149__f3;
    __Vtask_D_CACHE_tb__DOT__access__149__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__149__we;
    __Vtask_D_CACHE_tb__DOT__access__149__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__149__wdata;
    __Vtask_D_CACHE_tb__DOT__access__149__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__150__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__150__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__150__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__150__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__150__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__150__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__151__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__151__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__151__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__151__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__151__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__151__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__store__152__addr;
    __Vtask_D_CACHE_tb__DOT__store__152__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__store__152__f3;
    __Vtask_D_CACHE_tb__DOT__store__152__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__store__152__value;
    __Vtask_D_CACHE_tb__DOT__store__152__value = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__store__152__expect_miss;
    __Vtask_D_CACHE_tb__DOT__store__152__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__store__152__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__store__152__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__153__addr;
    __Vtask_D_CACHE_tb__DOT__access__153__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__153__f3;
    __Vtask_D_CACHE_tb__DOT__access__153__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__153__we;
    __Vtask_D_CACHE_tb__DOT__access__153__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__153__wdata;
    __Vtask_D_CACHE_tb__DOT__access__153__wdata = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__154__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__154__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__154__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__154__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__154__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__154__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__155__addr;
    __Vtask_D_CACHE_tb__DOT__load__155__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__155__f3;
    __Vtask_D_CACHE_tb__DOT__load__155__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__155__expected;
    __Vtask_D_CACHE_tb__DOT__load__155__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__155__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__155__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__155__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__155__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__156__addr;
    __Vtask_D_CACHE_tb__DOT__access__156__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__156__f3;
    __Vtask_D_CACHE_tb__DOT__access__156__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__156__we;
    __Vtask_D_CACHE_tb__DOT__access__156__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__156__wdata;
    __Vtask_D_CACHE_tb__DOT__access__156__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__157__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__157__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__157__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__157__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__157__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__157__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__158__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__158__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__158__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__158__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__158__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__158__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__159__addr;
    __Vtask_D_CACHE_tb__DOT__load__159__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__159__f3;
    __Vtask_D_CACHE_tb__DOT__load__159__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__159__expected;
    __Vtask_D_CACHE_tb__DOT__load__159__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__159__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__159__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__159__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__159__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__160__addr;
    __Vtask_D_CACHE_tb__DOT__access__160__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__160__f3;
    __Vtask_D_CACHE_tb__DOT__access__160__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__160__we;
    __Vtask_D_CACHE_tb__DOT__access__160__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__160__wdata;
    __Vtask_D_CACHE_tb__DOT__access__160__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__161__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__161__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__161__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__161__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__161__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__161__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__162__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__162__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__162__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__162__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__162__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__162__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__163__addr;
    __Vtask_D_CACHE_tb__DOT__load__163__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__163__f3;
    __Vtask_D_CACHE_tb__DOT__load__163__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__163__expected;
    __Vtask_D_CACHE_tb__DOT__load__163__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__163__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__163__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__163__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__163__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__164__addr;
    __Vtask_D_CACHE_tb__DOT__access__164__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__164__f3;
    __Vtask_D_CACHE_tb__DOT__access__164__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__164__we;
    __Vtask_D_CACHE_tb__DOT__access__164__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__164__wdata;
    __Vtask_D_CACHE_tb__DOT__access__164__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__165__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__165__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__165__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__165__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__165__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__165__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__166__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__166__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__166__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__166__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__166__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__166__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__167__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__167__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__167__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__167__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__167__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__167__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__168__addr;
    __Vtask_D_CACHE_tb__DOT__load__168__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__load__168__f3;
    __Vtask_D_CACHE_tb__DOT__load__168__f3 = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__load__168__expected;
    __Vtask_D_CACHE_tb__DOT__load__168__expected = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__load__168__expect_miss;
    __Vtask_D_CACHE_tb__DOT__load__168__expect_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__load__168__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__load__168__name);
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__169__addr;
    __Vtask_D_CACHE_tb__DOT__access__169__addr = 0;
    CData/*2:0*/ __Vtask_D_CACHE_tb__DOT__access__169__f3;
    __Vtask_D_CACHE_tb__DOT__access__169__f3 = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__access__169__we;
    __Vtask_D_CACHE_tb__DOT__access__169__we = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__access__169__wdata;
    __Vtask_D_CACHE_tb__DOT__access__169__wdata = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__170__expected;
    __Vtask_D_CACHE_tb__DOT__check_data__170__expected = 0;
    IData/*31:0*/ __Vtask_D_CACHE_tb__DOT__check_data__170__actual;
    __Vtask_D_CACHE_tb__DOT__check_data__170__actual = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_data__170__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__170__name);
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__171__expect_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__171__expect_miss = 0;
    CData/*0:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__171__got_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__171__got_miss = 0;
    VlWide<51>/*1600:0*/ __Vtask_D_CACHE_tb__DOT__check_hit_miss__171__name;
    VL_ZERO_W(1601, __Vtask_D_CACHE_tb__DOT__check_hit_miss__171__name);
    VlWide<6>/*191:0*/ __Vtemp_1;
    VlWide<6>/*191:0*/ __Vtemp_2;
    VlWide<6>/*191:0*/ __Vtemp_3;
    VlWide<6>/*191:0*/ __Vtemp_4;
    VlWide<6>/*191:0*/ __Vtemp_5;
    VlWide<6>/*191:0*/ __Vtemp_6;
    VlWide<6>/*191:0*/ __Vtemp_7;
    VlWide<6>/*191:0*/ __Vtemp_8;
    VlWide<6>/*191:0*/ __Vtemp_9;
    VlWide<6>/*191:0*/ __Vtemp_10;
    VlWide<6>/*191:0*/ __Vtemp_11;
    VlWide<6>/*191:0*/ __Vtemp_12;
    VlWide<6>/*191:0*/ __Vtemp_13;
    VlWide<6>/*191:0*/ __Vtemp_14;
    VlWide<6>/*191:0*/ __Vtemp_15;
    VlWide<6>/*191:0*/ __Vtemp_16;
    VlWide<6>/*191:0*/ __Vtemp_17;
    VlWide<6>/*191:0*/ __Vtemp_18;
    VlWide<6>/*191:0*/ __Vtemp_19;
    VlWide<6>/*191:0*/ __Vtemp_20;
    VlWide<6>/*191:0*/ __Vtemp_21;
    VlWide<6>/*191:0*/ __Vtemp_22;
    VlWide<6>/*191:0*/ __Vtemp_23;
    VlWide<6>/*191:0*/ __Vtemp_24;
    VlWide<6>/*191:0*/ __Vtemp_25;
    VlWide<6>/*191:0*/ __Vtemp_26;
    VlWide<6>/*191:0*/ __Vtemp_27;
    VlWide<6>/*191:0*/ __Vtemp_28;
    VlWide<6>/*191:0*/ __Vtemp_29;
    VlWide<6>/*191:0*/ __Vtemp_30;
    VlWide<6>/*191:0*/ __Vtemp_31;
    VlWide<6>/*191:0*/ __Vtemp_32;
    VlWide<6>/*191:0*/ __Vtemp_33;
    VlWide<6>/*191:0*/ __Vtemp_34;
    VlWide<6>/*191:0*/ __Vtemp_35;
    VlWide<6>/*191:0*/ __Vtemp_36;
    VlWide<6>/*191:0*/ __Vtemp_37;
    VlWide<6>/*191:0*/ __Vtemp_38;
    IData/*31:0*/ __Vilp1;
    IData/*31:0*/ __Vilp2;
    IData/*31:0*/ __Vilp3;
    IData/*31:0*/ __Vilp4;
    IData/*31:0*/ __Vilp5;
    IData/*31:0*/ __Vilp6;
    IData/*31:0*/ __Vilp7;
    IData/*31:0*/ __Vilp8;
    IData/*31:0*/ __Vilp9;
    IData/*31:0*/ __Vilp10;
    IData/*31:0*/ __Vilp11;
    IData/*31:0*/ __Vilp12;
    IData/*31:0*/ __Vilp13;
    IData/*31:0*/ __Vilp14;
    IData/*31:0*/ __Vilp15;
    IData/*31:0*/ __Vilp16;
    IData/*31:0*/ __Vilp17;
    IData/*31:0*/ __Vilp18;
    IData/*31:0*/ __Vilp19;
    IData/*31:0*/ __Vilp20;
    IData/*31:0*/ __Vilp21;
    IData/*31:0*/ __Vilp22;
    IData/*31:0*/ __Vilp23;
    IData/*31:0*/ __Vilp24;
    IData/*31:0*/ __Vilp25;
    IData/*31:0*/ __Vilp26;
    IData/*31:0*/ __Vilp27;
    IData/*31:0*/ __Vilp28;
    IData/*31:0*/ __Vilp29;
    IData/*31:0*/ __Vilp30;
    IData/*31:0*/ __Vilp31;
    IData/*31:0*/ __Vilp32;
    IData/*31:0*/ __Vilp33;
    IData/*31:0*/ __Vilp34;
    IData/*31:0*/ __Vilp35;
    IData/*31:0*/ __Vilp36;
    IData/*31:0*/ __Vilp37;
    IData/*31:0*/ __Vilp38;
    IData/*31:0*/ __Vilp39;
    IData/*31:0*/ __Vilp40;
    IData/*31:0*/ __Vilp41;
    IData/*31:0*/ __Vilp42;
    IData/*31:0*/ __Vilp43;
    IData/*31:0*/ __Vilp44;
    IData/*31:0*/ __Vilp45;
    IData/*31:0*/ __Vilp46;
    IData/*31:0*/ __Vilp47;
    IData/*31:0*/ __Vilp48;
    IData/*31:0*/ __Vilp49;
    IData/*31:0*/ __Vilp50;
    IData/*31:0*/ __Vilp51;
    IData/*31:0*/ __Vilp52;
    IData/*31:0*/ __Vilp53;
    IData/*31:0*/ __Vilp54;
    IData/*31:0*/ __Vilp55;
    IData/*31:0*/ __Vilp56;
    IData/*31:0*/ __Vilp57;
    IData/*31:0*/ __Vilp58;
    IData/*31:0*/ __Vilp59;
    IData/*31:0*/ __Vilp60;
    IData/*31:0*/ __Vilp61;
    IData/*31:0*/ __Vilp62;
    IData/*31:0*/ __Vilp63;
    IData/*31:0*/ __Vilp64;
    IData/*31:0*/ __Vilp65;
    IData/*31:0*/ __Vilp66;
    IData/*31:0*/ __Vilp67;
    IData/*31:0*/ __Vilp68;
    IData/*31:0*/ __Vilp69;
    IData/*31:0*/ __Vilp70;
    IData/*31:0*/ __Vilp71;
    // Body
    vlSymsp->_vm_contextp__->dumpfile("D_CACHE_tb.vcd"s);
    vlSymsp->_traceDumpOpen();
    VL_WRITEF_NX("==============================================\n  D_CACHE write-back testbench\n==============================================\n",0);
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = 2U;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = 0U;
    VL_WRITEF_NX("\n--- Test 1: Reset ---\n",0);
    vlSelfRef.D_CACHE_tb__DOT__reset = 1U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         256);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         256);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         257);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         257);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__0__name, VD_CACHE_tb__ConstPool__CONST_hc8661195_0);
    __Vtask_D_CACHE_tb__DOT__check_data__0__actual 
        = vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall;
    __Vtask_D_CACHE_tb__DOT__check_data__0__expected = 0U;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__0__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__0__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__0__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__0__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__0__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__0__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__0__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__0__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__1__name, VD_CACHE_tb__ConstPool__CONST_h67988180_0);
    __Vtask_D_CACHE_tb__DOT__check_data__1__actual 
        = vlSelfRef.D_CACHE_tb__DOT__mem_req;
    __Vtask_D_CACHE_tb__DOT__check_data__1__expected = 0U;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__1__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__1__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__1__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__1__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__1__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__1__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__1__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__1__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__2__name, VD_CACHE_tb__ConstPool__CONST_hdf5f5d62_0);
    __Vtask_D_CACHE_tb__DOT__check_data__2__actual 
        = vlSelfRef.D_CACHE_tb__DOT__mem_we;
    __Vtask_D_CACHE_tb__DOT__check_data__2__expected = 0U;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__2__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__2__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__2__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__2__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__2__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__2__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__2__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__2__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    vlSelfRef.D_CACHE_tb__DOT__reset = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         262);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         262);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    VL_WRITEF_NX("\n--- Test 2: Cold load miss ---\n",0);
    __Vtask_D_CACHE_tb__DOT__write_mem__3__word = 0xdeadbeefU;
    __Vtask_D_CACHE_tb__DOT__write_mem__3__addr = 0x00000020U;
    vlSelfRef.D_CACHE_tb__DOT__mem[(0x00003fffU & (__Vtask_D_CACHE_tb__DOT__write_mem__3__addr 
                                                   >> 2U))] 
        = __Vtask_D_CACHE_tb__DOT__write_mem__3__word;
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__4__name, VD_CACHE_tb__ConstPool__CONST_hd54411ea_0);
    __Vtask_D_CACHE_tb__DOT__load__4__expect_miss = 1U;
    __Vtask_D_CACHE_tb__DOT__load__4__expected = 0xdeadbeefU;
    __Vtask_D_CACHE_tb__DOT__load__4__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__4__addr = 0x00000020U;
    __Vtask_D_CACHE_tb__DOT__access__5__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__5__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__5__f3 = __Vtask_D_CACHE_tb__DOT__load__4__f3;
    __Vtask_D_CACHE_tb__DOT__access__5__addr = __Vtask_D_CACHE_tb__DOT__load__4__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__5__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__5__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__5__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__5__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp1 = 0U;
    while ((__Vilp1 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__6__name[__Vilp1] 
            = __Vtask_D_CACHE_tb__DOT__load__4__name
            [__Vilp1];
        __Vilp1 = ((IData)(1U) + __Vilp1);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__6__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__6__expected 
        = __Vtask_D_CACHE_tb__DOT__load__4__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__6__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__6__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__6__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__6__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__6__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__6__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__6__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__6__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp2 = 0U;
    while ((__Vilp2 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__7__name[__Vilp2] 
            = __Vtask_D_CACHE_tb__DOT__load__4__name
            [__Vilp2];
        __Vilp2 = ((IData)(1U) + __Vilp2);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__7__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__7__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__4__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__7__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__7__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__7__expect_miss) {
            __Vtemp_1[0U] = 0x20676f74U;
            __Vtemp_1[1U] = 0x20616e64U;
            __Vtemp_1[2U] = 0x63746564U;
            __Vtemp_1[3U] = 0x65787065U;
            __Vtemp_1[4U] = 0x49535320U;
            __Vtemp_1[5U] = 0x0000004dU;
        } else {
            __Vtemp_1[0U] = 0x20676f74U;
            __Vtemp_1[1U] = 0x20616e64U;
            __Vtemp_1[2U] = 0x63746564U;
            __Vtemp_1[3U] = 0x65787065U;
            __Vtemp_1[4U] = 0x48495420U;
            __Vtemp_1[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__7__name.data()
                     , '#',168,__Vtemp_1.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__7__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__7__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__7__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__8__name, VD_CACHE_tb__ConstPool__CONST_h3df8aa30_0);
    __Vtask_D_CACHE_tb__DOT__check_data__8__actual 
        = vlSelfRef.D_CACHE_tb__DOT__mem_rd_count;
    __Vtask_D_CACHE_tb__DOT__check_data__8__expected = 1U;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__8__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__8__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__8__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__8__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__8__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__8__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__8__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__8__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__9__name, VD_CACHE_tb__ConstPool__CONST_he7e89ed9_0);
    __Vtask_D_CACHE_tb__DOT__check_data__9__actual 
        = vlSelfRef.D_CACHE_tb__DOT__mem_wr_count;
    __Vtask_D_CACHE_tb__DOT__check_data__9__expected = 0U;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__9__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__9__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__9__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__9__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__9__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__9__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__9__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__9__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_WRITEF_NX("\n--- Test 3: Hit on re-access ---\n",0);
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__10__name, VD_CACHE_tb__ConstPool__CONST_hb71df3fc_0);
    __Vtask_D_CACHE_tb__DOT__load__10__expect_miss = 0U;
    __Vtask_D_CACHE_tb__DOT__load__10__expected = 0xdeadbeefU;
    __Vtask_D_CACHE_tb__DOT__load__10__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__10__addr = 0x00000020U;
    __Vtask_D_CACHE_tb__DOT__access__11__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__11__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__11__f3 = __Vtask_D_CACHE_tb__DOT__load__10__f3;
    __Vtask_D_CACHE_tb__DOT__access__11__addr = __Vtask_D_CACHE_tb__DOT__load__10__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__11__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__11__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__11__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__11__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp3 = 0U;
    while ((__Vilp3 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__12__name[__Vilp3] 
            = __Vtask_D_CACHE_tb__DOT__load__10__name
            [__Vilp3];
        __Vilp3 = ((IData)(1U) + __Vilp3);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__12__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__12__expected 
        = __Vtask_D_CACHE_tb__DOT__load__10__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__12__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__12__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__12__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__12__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__12__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__12__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__12__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__12__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp4 = 0U;
    while ((__Vilp4 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__13__name[__Vilp4] 
            = __Vtask_D_CACHE_tb__DOT__load__10__name
            [__Vilp4];
        __Vilp4 = ((IData)(1U) + __Vilp4);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__13__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__13__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__10__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__13__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__13__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__13__expect_miss) {
            __Vtemp_2[0U] = 0x20676f74U;
            __Vtemp_2[1U] = 0x20616e64U;
            __Vtemp_2[2U] = 0x63746564U;
            __Vtemp_2[3U] = 0x65787065U;
            __Vtemp_2[4U] = 0x49535320U;
            __Vtemp_2[5U] = 0x0000004dU;
        } else {
            __Vtemp_2[0U] = 0x20676f74U;
            __Vtemp_2[1U] = 0x20616e64U;
            __Vtemp_2[2U] = 0x63746564U;
            __Vtemp_2[3U] = 0x65787065U;
            __Vtemp_2[4U] = 0x48495420U;
            __Vtemp_2[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__13__name.data()
                     , '#',168,__Vtemp_2.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__13__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__13__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__13__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__14__name, VD_CACHE_tb__ConstPool__CONST_he450a8a4_0);
    __Vtask_D_CACHE_tb__DOT__check_data__14__actual 
        = vlSelfRef.D_CACHE_tb__DOT__mem_rd_count;
    __Vtask_D_CACHE_tb__DOT__check_data__14__expected = 1U;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__14__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__14__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__14__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__14__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__14__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__14__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__14__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__14__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_WRITEF_NX("\n--- Test 4: LW across sets ---\n",0);
    __Vtask_D_CACHE_tb__DOT__write_mem__15__word = 0x12345678U;
    __Vtask_D_CACHE_tb__DOT__write_mem__15__addr = 0U;
    vlSelfRef.D_CACHE_tb__DOT__mem[(0x00003fffU & (__Vtask_D_CACHE_tb__DOT__write_mem__15__addr 
                                                   >> 2U))] 
        = __Vtask_D_CACHE_tb__DOT__write_mem__15__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__16__word = 0xcafebabeU;
    __Vtask_D_CACHE_tb__DOT__write_mem__16__addr = 8U;
    vlSelfRef.D_CACHE_tb__DOT__mem[(0x00003fffU & (__Vtask_D_CACHE_tb__DOT__write_mem__16__addr 
                                                   >> 2U))] 
        = __Vtask_D_CACHE_tb__DOT__write_mem__16__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__17__word = 0x89abcdefU;
    __Vtask_D_CACHE_tb__DOT__write_mem__17__addr = 0x00000100U;
    vlSelfRef.D_CACHE_tb__DOT__mem[(0x00003fffU & (__Vtask_D_CACHE_tb__DOT__write_mem__17__addr 
                                                   >> 2U))] 
        = __Vtask_D_CACHE_tb__DOT__write_mem__17__word;
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__18__name, VD_CACHE_tb__ConstPool__CONST_h5ff31a4e_0);
    __Vtask_D_CACHE_tb__DOT__load__18__expect_miss = 1U;
    __Vtask_D_CACHE_tb__DOT__load__18__expected = 0x12345678U;
    __Vtask_D_CACHE_tb__DOT__load__18__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__18__addr = 0U;
    __Vtask_D_CACHE_tb__DOT__access__19__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__19__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__19__f3 = __Vtask_D_CACHE_tb__DOT__load__18__f3;
    __Vtask_D_CACHE_tb__DOT__access__19__addr = __Vtask_D_CACHE_tb__DOT__load__18__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__19__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__19__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__19__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__19__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp5 = 0U;
    while ((__Vilp5 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__20__name[__Vilp5] 
            = __Vtask_D_CACHE_tb__DOT__load__18__name
            [__Vilp5];
        __Vilp5 = ((IData)(1U) + __Vilp5);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__20__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__20__expected 
        = __Vtask_D_CACHE_tb__DOT__load__18__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__20__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__20__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__20__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__20__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__20__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__20__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__20__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__20__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp6 = 0U;
    while ((__Vilp6 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__21__name[__Vilp6] 
            = __Vtask_D_CACHE_tb__DOT__load__18__name
            [__Vilp6];
        __Vilp6 = ((IData)(1U) + __Vilp6);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__21__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__21__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__18__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__21__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__21__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__21__expect_miss) {
            __Vtemp_3[0U] = 0x20676f74U;
            __Vtemp_3[1U] = 0x20616e64U;
            __Vtemp_3[2U] = 0x63746564U;
            __Vtemp_3[3U] = 0x65787065U;
            __Vtemp_3[4U] = 0x49535320U;
            __Vtemp_3[5U] = 0x0000004dU;
        } else {
            __Vtemp_3[0U] = 0x20676f74U;
            __Vtemp_3[1U] = 0x20616e64U;
            __Vtemp_3[2U] = 0x63746564U;
            __Vtemp_3[3U] = 0x65787065U;
            __Vtemp_3[4U] = 0x48495420U;
            __Vtemp_3[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__21__name.data()
                     , '#',168,__Vtemp_3.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__21__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__21__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__21__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__22__name, VD_CACHE_tb__ConstPool__CONST_had322ff6_0);
    __Vtask_D_CACHE_tb__DOT__load__22__expect_miss = 1U;
    __Vtask_D_CACHE_tb__DOT__load__22__expected = 0xcafebabeU;
    __Vtask_D_CACHE_tb__DOT__load__22__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__22__addr = 8U;
    __Vtask_D_CACHE_tb__DOT__access__23__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__23__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__23__f3 = __Vtask_D_CACHE_tb__DOT__load__22__f3;
    __Vtask_D_CACHE_tb__DOT__access__23__addr = __Vtask_D_CACHE_tb__DOT__load__22__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__23__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__23__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__23__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__23__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp7 = 0U;
    while ((__Vilp7 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__24__name[__Vilp7] 
            = __Vtask_D_CACHE_tb__DOT__load__22__name
            [__Vilp7];
        __Vilp7 = ((IData)(1U) + __Vilp7);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__24__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__24__expected 
        = __Vtask_D_CACHE_tb__DOT__load__22__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__24__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__24__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__24__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__24__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__24__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__24__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__24__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__24__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp8 = 0U;
    while ((__Vilp8 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__25__name[__Vilp8] 
            = __Vtask_D_CACHE_tb__DOT__load__22__name
            [__Vilp8];
        __Vilp8 = ((IData)(1U) + __Vilp8);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__25__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__25__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__22__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__25__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__25__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__25__expect_miss) {
            __Vtemp_4[0U] = 0x20676f74U;
            __Vtemp_4[1U] = 0x20616e64U;
            __Vtemp_4[2U] = 0x63746564U;
            __Vtemp_4[3U] = 0x65787065U;
            __Vtemp_4[4U] = 0x49535320U;
            __Vtemp_4[5U] = 0x0000004dU;
        } else {
            __Vtemp_4[0U] = 0x20676f74U;
            __Vtemp_4[1U] = 0x20616e64U;
            __Vtemp_4[2U] = 0x63746564U;
            __Vtemp_4[3U] = 0x65787065U;
            __Vtemp_4[4U] = 0x48495420U;
            __Vtemp_4[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__25__name.data()
                     , '#',168,__Vtemp_4.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__25__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__25__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__25__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__26__name, VD_CACHE_tb__ConstPool__CONST_h9af0c437_0);
    __Vtask_D_CACHE_tb__DOT__load__26__expect_miss = 1U;
    __Vtask_D_CACHE_tb__DOT__load__26__expected = 0x89abcdefU;
    __Vtask_D_CACHE_tb__DOT__load__26__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__26__addr = 0x00000100U;
    __Vtask_D_CACHE_tb__DOT__access__27__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__27__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__27__f3 = __Vtask_D_CACHE_tb__DOT__load__26__f3;
    __Vtask_D_CACHE_tb__DOT__access__27__addr = __Vtask_D_CACHE_tb__DOT__load__26__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__27__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__27__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__27__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__27__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp9 = 0U;
    while ((__Vilp9 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__28__name[__Vilp9] 
            = __Vtask_D_CACHE_tb__DOT__load__26__name
            [__Vilp9];
        __Vilp9 = ((IData)(1U) + __Vilp9);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__28__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__28__expected 
        = __Vtask_D_CACHE_tb__DOT__load__26__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__28__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__28__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__28__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__28__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__28__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__28__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__28__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__28__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp10 = 0U;
    while ((__Vilp10 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__29__name[__Vilp10] 
            = __Vtask_D_CACHE_tb__DOT__load__26__name
            [__Vilp10];
        __Vilp10 = ((IData)(1U) + __Vilp10);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__29__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__29__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__26__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__29__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__29__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__29__expect_miss) {
            __Vtemp_5[0U] = 0x20676f74U;
            __Vtemp_5[1U] = 0x20616e64U;
            __Vtemp_5[2U] = 0x63746564U;
            __Vtemp_5[3U] = 0x65787065U;
            __Vtemp_5[4U] = 0x49535320U;
            __Vtemp_5[5U] = 0x0000004dU;
        } else {
            __Vtemp_5[0U] = 0x20676f74U;
            __Vtemp_5[1U] = 0x20616e64U;
            __Vtemp_5[2U] = 0x63746564U;
            __Vtemp_5[3U] = 0x65787065U;
            __Vtemp_5[4U] = 0x48495420U;
            __Vtemp_5[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__29__name.data()
                     , '#',168,__Vtemp_5.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__29__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__29__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__29__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__30__name, VD_CACHE_tb__ConstPool__CONST_he80b4162_0);
    __Vtask_D_CACHE_tb__DOT__load__30__expect_miss = 0U;
    __Vtask_D_CACHE_tb__DOT__load__30__expected = 0x89abcdefU;
    __Vtask_D_CACHE_tb__DOT__load__30__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__30__addr = 0x00000100U;
    __Vtask_D_CACHE_tb__DOT__access__31__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__31__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__31__f3 = __Vtask_D_CACHE_tb__DOT__load__30__f3;
    __Vtask_D_CACHE_tb__DOT__access__31__addr = __Vtask_D_CACHE_tb__DOT__load__30__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__31__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__31__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__31__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__31__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp11 = 0U;
    while ((__Vilp11 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__32__name[__Vilp11] 
            = __Vtask_D_CACHE_tb__DOT__load__30__name
            [__Vilp11];
        __Vilp11 = ((IData)(1U) + __Vilp11);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__32__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__32__expected 
        = __Vtask_D_CACHE_tb__DOT__load__30__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__32__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__32__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__32__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__32__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__32__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__32__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__32__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__32__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp12 = 0U;
    while ((__Vilp12 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__33__name[__Vilp12] 
            = __Vtask_D_CACHE_tb__DOT__load__30__name
            [__Vilp12];
        __Vilp12 = ((IData)(1U) + __Vilp12);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__33__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__33__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__30__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__33__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__33__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__33__expect_miss) {
            __Vtemp_6[0U] = 0x20676f74U;
            __Vtemp_6[1U] = 0x20616e64U;
            __Vtemp_6[2U] = 0x63746564U;
            __Vtemp_6[3U] = 0x65787065U;
            __Vtemp_6[4U] = 0x49535320U;
            __Vtemp_6[5U] = 0x0000004dU;
        } else {
            __Vtemp_6[0U] = 0x20676f74U;
            __Vtemp_6[1U] = 0x20616e64U;
            __Vtemp_6[2U] = 0x63746564U;
            __Vtemp_6[3U] = 0x65787065U;
            __Vtemp_6[4U] = 0x48495420U;
            __Vtemp_6[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__33__name.data()
                     , '#',168,__Vtemp_6.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__33__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__33__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__33__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_WRITEF_NX("\n--- Test 5: LB sign extension ---\n",0);
    __Vtask_D_CACHE_tb__DOT__write_mem__34__word = 0x807fff01U;
    __Vtask_D_CACHE_tb__DOT__write_mem__34__addr = 0x00000040U;
    vlSelfRef.D_CACHE_tb__DOT__mem[(0x00003fffU & (__Vtask_D_CACHE_tb__DOT__write_mem__34__addr 
                                                   >> 2U))] 
        = __Vtask_D_CACHE_tb__DOT__write_mem__34__word;
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__35__name, VD_CACHE_tb__ConstPool__CONST_h6b3bce4a_0);
    __Vtask_D_CACHE_tb__DOT__load__35__expect_miss = 1U;
    __Vtask_D_CACHE_tb__DOT__load__35__expected = 1U;
    __Vtask_D_CACHE_tb__DOT__load__35__f3 = 0U;
    __Vtask_D_CACHE_tb__DOT__load__35__addr = 0x00000040U;
    __Vtask_D_CACHE_tb__DOT__access__36__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__36__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__36__f3 = __Vtask_D_CACHE_tb__DOT__load__35__f3;
    __Vtask_D_CACHE_tb__DOT__access__36__addr = __Vtask_D_CACHE_tb__DOT__load__35__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__36__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__36__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__36__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__36__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp13 = 0U;
    while ((__Vilp13 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__37__name[__Vilp13] 
            = __Vtask_D_CACHE_tb__DOT__load__35__name
            [__Vilp13];
        __Vilp13 = ((IData)(1U) + __Vilp13);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__37__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__37__expected 
        = __Vtask_D_CACHE_tb__DOT__load__35__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__37__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__37__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__37__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__37__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__37__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__37__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__37__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__37__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp14 = 0U;
    while ((__Vilp14 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__38__name[__Vilp14] 
            = __Vtask_D_CACHE_tb__DOT__load__35__name
            [__Vilp14];
        __Vilp14 = ((IData)(1U) + __Vilp14);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__38__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__38__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__35__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__38__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__38__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__38__expect_miss) {
            __Vtemp_7[0U] = 0x20676f74U;
            __Vtemp_7[1U] = 0x20616e64U;
            __Vtemp_7[2U] = 0x63746564U;
            __Vtemp_7[3U] = 0x65787065U;
            __Vtemp_7[4U] = 0x49535320U;
            __Vtemp_7[5U] = 0x0000004dU;
        } else {
            __Vtemp_7[0U] = 0x20676f74U;
            __Vtemp_7[1U] = 0x20616e64U;
            __Vtemp_7[2U] = 0x63746564U;
            __Vtemp_7[3U] = 0x65787065U;
            __Vtemp_7[4U] = 0x48495420U;
            __Vtemp_7[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__38__name.data()
                     , '#',168,__Vtemp_7.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__38__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__38__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__38__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__39__name, VD_CACHE_tb__ConstPool__CONST_h93f055be_0);
    __Vtask_D_CACHE_tb__DOT__load__39__expect_miss = 0U;
    __Vtask_D_CACHE_tb__DOT__load__39__expected = 0xffffffffU;
    __Vtask_D_CACHE_tb__DOT__load__39__f3 = 0U;
    __Vtask_D_CACHE_tb__DOT__load__39__addr = 0x00000041U;
    __Vtask_D_CACHE_tb__DOT__access__40__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__40__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__40__f3 = __Vtask_D_CACHE_tb__DOT__load__39__f3;
    __Vtask_D_CACHE_tb__DOT__access__40__addr = __Vtask_D_CACHE_tb__DOT__load__39__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__40__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__40__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__40__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__40__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp15 = 0U;
    while ((__Vilp15 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__41__name[__Vilp15] 
            = __Vtask_D_CACHE_tb__DOT__load__39__name
            [__Vilp15];
        __Vilp15 = ((IData)(1U) + __Vilp15);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__41__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__41__expected 
        = __Vtask_D_CACHE_tb__DOT__load__39__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__41__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__41__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__41__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__41__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__41__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__41__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__41__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__41__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp16 = 0U;
    while ((__Vilp16 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__42__name[__Vilp16] 
            = __Vtask_D_CACHE_tb__DOT__load__39__name
            [__Vilp16];
        __Vilp16 = ((IData)(1U) + __Vilp16);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__42__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__42__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__39__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__42__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__42__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__42__expect_miss) {
            __Vtemp_8[0U] = 0x20676f74U;
            __Vtemp_8[1U] = 0x20616e64U;
            __Vtemp_8[2U] = 0x63746564U;
            __Vtemp_8[3U] = 0x65787065U;
            __Vtemp_8[4U] = 0x49535320U;
            __Vtemp_8[5U] = 0x0000004dU;
        } else {
            __Vtemp_8[0U] = 0x20676f74U;
            __Vtemp_8[1U] = 0x20616e64U;
            __Vtemp_8[2U] = 0x63746564U;
            __Vtemp_8[3U] = 0x65787065U;
            __Vtemp_8[4U] = 0x48495420U;
            __Vtemp_8[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__42__name.data()
                     , '#',168,__Vtemp_8.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__42__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__42__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__42__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__43__name, VD_CACHE_tb__ConstPool__CONST_h9d5d6592_0);
    __Vtask_D_CACHE_tb__DOT__load__43__expect_miss = 0U;
    __Vtask_D_CACHE_tb__DOT__load__43__expected = 0x0000007fU;
    __Vtask_D_CACHE_tb__DOT__load__43__f3 = 0U;
    __Vtask_D_CACHE_tb__DOT__load__43__addr = 0x00000042U;
    __Vtask_D_CACHE_tb__DOT__access__44__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__44__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__44__f3 = __Vtask_D_CACHE_tb__DOT__load__43__f3;
    __Vtask_D_CACHE_tb__DOT__access__44__addr = __Vtask_D_CACHE_tb__DOT__load__43__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__44__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__44__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__44__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__44__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp17 = 0U;
    while ((__Vilp17 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__45__name[__Vilp17] 
            = __Vtask_D_CACHE_tb__DOT__load__43__name
            [__Vilp17];
        __Vilp17 = ((IData)(1U) + __Vilp17);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__45__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__45__expected 
        = __Vtask_D_CACHE_tb__DOT__load__43__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__45__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__45__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__45__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__45__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__45__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__45__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__45__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__45__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp18 = 0U;
    while ((__Vilp18 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__46__name[__Vilp18] 
            = __Vtask_D_CACHE_tb__DOT__load__43__name
            [__Vilp18];
        __Vilp18 = ((IData)(1U) + __Vilp18);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__46__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__46__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__43__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__46__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__46__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__46__expect_miss) {
            __Vtemp_9[0U] = 0x20676f74U;
            __Vtemp_9[1U] = 0x20616e64U;
            __Vtemp_9[2U] = 0x63746564U;
            __Vtemp_9[3U] = 0x65787065U;
            __Vtemp_9[4U] = 0x49535320U;
            __Vtemp_9[5U] = 0x0000004dU;
        } else {
            __Vtemp_9[0U] = 0x20676f74U;
            __Vtemp_9[1U] = 0x20616e64U;
            __Vtemp_9[2U] = 0x63746564U;
            __Vtemp_9[3U] = 0x65787065U;
            __Vtemp_9[4U] = 0x48495420U;
            __Vtemp_9[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__46__name.data()
                     , '#',168,__Vtemp_9.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__46__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__46__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__46__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__47__name, VD_CACHE_tb__ConstPool__CONST_hddafe4b6_0);
    __Vtask_D_CACHE_tb__DOT__load__47__expect_miss = 0U;
    __Vtask_D_CACHE_tb__DOT__load__47__expected = 0xffffff80U;
    __Vtask_D_CACHE_tb__DOT__load__47__f3 = 0U;
    __Vtask_D_CACHE_tb__DOT__load__47__addr = 0x00000043U;
    __Vtask_D_CACHE_tb__DOT__access__48__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__48__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__48__f3 = __Vtask_D_CACHE_tb__DOT__load__47__f3;
    __Vtask_D_CACHE_tb__DOT__access__48__addr = __Vtask_D_CACHE_tb__DOT__load__47__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__48__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__48__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__48__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__48__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp19 = 0U;
    while ((__Vilp19 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__49__name[__Vilp19] 
            = __Vtask_D_CACHE_tb__DOT__load__47__name
            [__Vilp19];
        __Vilp19 = ((IData)(1U) + __Vilp19);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__49__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__49__expected 
        = __Vtask_D_CACHE_tb__DOT__load__47__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__49__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__49__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__49__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__49__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__49__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__49__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__49__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__49__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp20 = 0U;
    while ((__Vilp20 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__50__name[__Vilp20] 
            = __Vtask_D_CACHE_tb__DOT__load__47__name
            [__Vilp20];
        __Vilp20 = ((IData)(1U) + __Vilp20);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__50__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__50__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__47__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__50__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__50__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__50__expect_miss) {
            __Vtemp_10[0U] = 0x20676f74U;
            __Vtemp_10[1U] = 0x20616e64U;
            __Vtemp_10[2U] = 0x63746564U;
            __Vtemp_10[3U] = 0x65787065U;
            __Vtemp_10[4U] = 0x49535320U;
            __Vtemp_10[5U] = 0x0000004dU;
        } else {
            __Vtemp_10[0U] = 0x20676f74U;
            __Vtemp_10[1U] = 0x20616e64U;
            __Vtemp_10[2U] = 0x63746564U;
            __Vtemp_10[3U] = 0x65787065U;
            __Vtemp_10[4U] = 0x48495420U;
            __Vtemp_10[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__50__name.data()
                     , '#',168,__Vtemp_10.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__50__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__50__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__50__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_WRITEF_NX("\n--- Test 6: LBU zero extension ---\n",0);
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__51__name, VD_CACHE_tb__ConstPool__CONST_hb537c2ed_0);
    __Vtask_D_CACHE_tb__DOT__load__51__expect_miss = 0U;
    __Vtask_D_CACHE_tb__DOT__load__51__expected = 0x000000ffU;
    __Vtask_D_CACHE_tb__DOT__load__51__f3 = 4U;
    __Vtask_D_CACHE_tb__DOT__load__51__addr = 0x00000041U;
    __Vtask_D_CACHE_tb__DOT__access__52__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__52__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__52__f3 = __Vtask_D_CACHE_tb__DOT__load__51__f3;
    __Vtask_D_CACHE_tb__DOT__access__52__addr = __Vtask_D_CACHE_tb__DOT__load__51__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__52__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__52__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__52__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__52__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp21 = 0U;
    while ((__Vilp21 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__53__name[__Vilp21] 
            = __Vtask_D_CACHE_tb__DOT__load__51__name
            [__Vilp21];
        __Vilp21 = ((IData)(1U) + __Vilp21);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__53__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__53__expected 
        = __Vtask_D_CACHE_tb__DOT__load__51__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__53__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__53__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__53__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__53__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__53__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__53__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__53__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__53__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp22 = 0U;
    while ((__Vilp22 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__54__name[__Vilp22] 
            = __Vtask_D_CACHE_tb__DOT__load__51__name
            [__Vilp22];
        __Vilp22 = ((IData)(1U) + __Vilp22);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__54__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__54__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__51__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__54__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__54__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__54__expect_miss) {
            __Vtemp_11[0U] = 0x20676f74U;
            __Vtemp_11[1U] = 0x20616e64U;
            __Vtemp_11[2U] = 0x63746564U;
            __Vtemp_11[3U] = 0x65787065U;
            __Vtemp_11[4U] = 0x49535320U;
            __Vtemp_11[5U] = 0x0000004dU;
        } else {
            __Vtemp_11[0U] = 0x20676f74U;
            __Vtemp_11[1U] = 0x20616e64U;
            __Vtemp_11[2U] = 0x63746564U;
            __Vtemp_11[3U] = 0x65787065U;
            __Vtemp_11[4U] = 0x48495420U;
            __Vtemp_11[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__54__name.data()
                     , '#',168,__Vtemp_11.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__54__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__54__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__54__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__55__name, VD_CACHE_tb__ConstPool__CONST_h96405d94_0);
    __Vtask_D_CACHE_tb__DOT__load__55__expect_miss = 0U;
    __Vtask_D_CACHE_tb__DOT__load__55__expected = 0x00000080U;
    __Vtask_D_CACHE_tb__DOT__load__55__f3 = 4U;
    __Vtask_D_CACHE_tb__DOT__load__55__addr = 0x00000043U;
    __Vtask_D_CACHE_tb__DOT__access__56__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__56__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__56__f3 = __Vtask_D_CACHE_tb__DOT__load__55__f3;
    __Vtask_D_CACHE_tb__DOT__access__56__addr = __Vtask_D_CACHE_tb__DOT__load__55__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__56__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__56__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__56__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__56__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp23 = 0U;
    while ((__Vilp23 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__57__name[__Vilp23] 
            = __Vtask_D_CACHE_tb__DOT__load__55__name
            [__Vilp23];
        __Vilp23 = ((IData)(1U) + __Vilp23);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__57__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__57__expected 
        = __Vtask_D_CACHE_tb__DOT__load__55__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__57__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__57__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__57__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__57__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__57__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__57__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__57__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__57__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp24 = 0U;
    while ((__Vilp24 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__58__name[__Vilp24] 
            = __Vtask_D_CACHE_tb__DOT__load__55__name
            [__Vilp24];
        __Vilp24 = ((IData)(1U) + __Vilp24);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__58__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__58__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__55__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__58__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__58__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__58__expect_miss) {
            __Vtemp_12[0U] = 0x20676f74U;
            __Vtemp_12[1U] = 0x20616e64U;
            __Vtemp_12[2U] = 0x63746564U;
            __Vtemp_12[3U] = 0x65787065U;
            __Vtemp_12[4U] = 0x49535320U;
            __Vtemp_12[5U] = 0x0000004dU;
        } else {
            __Vtemp_12[0U] = 0x20676f74U;
            __Vtemp_12[1U] = 0x20616e64U;
            __Vtemp_12[2U] = 0x63746564U;
            __Vtemp_12[3U] = 0x65787065U;
            __Vtemp_12[4U] = 0x48495420U;
            __Vtemp_12[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__58__name.data()
                     , '#',168,__Vtemp_12.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__58__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__58__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__58__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_WRITEF_NX("\n--- Test 7: LH / LHU ---\n",0);
    __Vtask_D_CACHE_tb__DOT__write_mem__59__word = 0x80017fffU;
    __Vtask_D_CACHE_tb__DOT__write_mem__59__addr = 0x00000060U;
    vlSelfRef.D_CACHE_tb__DOT__mem[(0x00003fffU & (__Vtask_D_CACHE_tb__DOT__write_mem__59__addr 
                                                   >> 2U))] 
        = __Vtask_D_CACHE_tb__DOT__write_mem__59__word;
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__60__name, VD_CACHE_tb__ConstPool__CONST_h8dfa189f_0);
    __Vtask_D_CACHE_tb__DOT__load__60__expect_miss = 1U;
    __Vtask_D_CACHE_tb__DOT__load__60__expected = 0x00007fffU;
    __Vtask_D_CACHE_tb__DOT__load__60__f3 = 1U;
    __Vtask_D_CACHE_tb__DOT__load__60__addr = 0x00000060U;
    __Vtask_D_CACHE_tb__DOT__access__61__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__61__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__61__f3 = __Vtask_D_CACHE_tb__DOT__load__60__f3;
    __Vtask_D_CACHE_tb__DOT__access__61__addr = __Vtask_D_CACHE_tb__DOT__load__60__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__61__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__61__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__61__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__61__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp25 = 0U;
    while ((__Vilp25 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__62__name[__Vilp25] 
            = __Vtask_D_CACHE_tb__DOT__load__60__name
            [__Vilp25];
        __Vilp25 = ((IData)(1U) + __Vilp25);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__62__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__62__expected 
        = __Vtask_D_CACHE_tb__DOT__load__60__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__62__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__62__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__62__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__62__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__62__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__62__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__62__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__62__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp26 = 0U;
    while ((__Vilp26 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__63__name[__Vilp26] 
            = __Vtask_D_CACHE_tb__DOT__load__60__name
            [__Vilp26];
        __Vilp26 = ((IData)(1U) + __Vilp26);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__63__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__63__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__60__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__63__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__63__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__63__expect_miss) {
            __Vtemp_13[0U] = 0x20676f74U;
            __Vtemp_13[1U] = 0x20616e64U;
            __Vtemp_13[2U] = 0x63746564U;
            __Vtemp_13[3U] = 0x65787065U;
            __Vtemp_13[4U] = 0x49535320U;
            __Vtemp_13[5U] = 0x0000004dU;
        } else {
            __Vtemp_13[0U] = 0x20676f74U;
            __Vtemp_13[1U] = 0x20616e64U;
            __Vtemp_13[2U] = 0x63746564U;
            __Vtemp_13[3U] = 0x65787065U;
            __Vtemp_13[4U] = 0x48495420U;
            __Vtemp_13[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__63__name.data()
                     , '#',168,__Vtemp_13.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__63__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__63__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__63__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__64__name, VD_CACHE_tb__ConstPool__CONST_hca5c5548_0);
    __Vtask_D_CACHE_tb__DOT__load__64__expect_miss = 0U;
    __Vtask_D_CACHE_tb__DOT__load__64__expected = 0xffff8001U;
    __Vtask_D_CACHE_tb__DOT__load__64__f3 = 1U;
    __Vtask_D_CACHE_tb__DOT__load__64__addr = 0x00000062U;
    __Vtask_D_CACHE_tb__DOT__access__65__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__65__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__65__f3 = __Vtask_D_CACHE_tb__DOT__load__64__f3;
    __Vtask_D_CACHE_tb__DOT__access__65__addr = __Vtask_D_CACHE_tb__DOT__load__64__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__65__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__65__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__65__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__65__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp27 = 0U;
    while ((__Vilp27 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__66__name[__Vilp27] 
            = __Vtask_D_CACHE_tb__DOT__load__64__name
            [__Vilp27];
        __Vilp27 = ((IData)(1U) + __Vilp27);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__66__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__66__expected 
        = __Vtask_D_CACHE_tb__DOT__load__64__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__66__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__66__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__66__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__66__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__66__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__66__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__66__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__66__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp28 = 0U;
    while ((__Vilp28 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__67__name[__Vilp28] 
            = __Vtask_D_CACHE_tb__DOT__load__64__name
            [__Vilp28];
        __Vilp28 = ((IData)(1U) + __Vilp28);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__67__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__67__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__64__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__67__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__67__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__67__expect_miss) {
            __Vtemp_14[0U] = 0x20676f74U;
            __Vtemp_14[1U] = 0x20616e64U;
            __Vtemp_14[2U] = 0x63746564U;
            __Vtemp_14[3U] = 0x65787065U;
            __Vtemp_14[4U] = 0x49535320U;
            __Vtemp_14[5U] = 0x0000004dU;
        } else {
            __Vtemp_14[0U] = 0x20676f74U;
            __Vtemp_14[1U] = 0x20616e64U;
            __Vtemp_14[2U] = 0x63746564U;
            __Vtemp_14[3U] = 0x65787065U;
            __Vtemp_14[4U] = 0x48495420U;
            __Vtemp_14[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__67__name.data()
                     , '#',168,__Vtemp_14.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__67__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__67__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__67__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__68__name, VD_CACHE_tb__ConstPool__CONST_hd0c07945_0);
    __Vtask_D_CACHE_tb__DOT__load__68__expect_miss = 0U;
    __Vtask_D_CACHE_tb__DOT__load__68__expected = 0x00007fffU;
    __Vtask_D_CACHE_tb__DOT__load__68__f3 = 5U;
    __Vtask_D_CACHE_tb__DOT__load__68__addr = 0x00000060U;
    __Vtask_D_CACHE_tb__DOT__access__69__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__69__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__69__f3 = __Vtask_D_CACHE_tb__DOT__load__68__f3;
    __Vtask_D_CACHE_tb__DOT__access__69__addr = __Vtask_D_CACHE_tb__DOT__load__68__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__69__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__69__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__69__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__69__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp29 = 0U;
    while ((__Vilp29 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__70__name[__Vilp29] 
            = __Vtask_D_CACHE_tb__DOT__load__68__name
            [__Vilp29];
        __Vilp29 = ((IData)(1U) + __Vilp29);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__70__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__70__expected 
        = __Vtask_D_CACHE_tb__DOT__load__68__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__70__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__70__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__70__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__70__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__70__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__70__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__70__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__70__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp30 = 0U;
    while ((__Vilp30 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__71__name[__Vilp30] 
            = __Vtask_D_CACHE_tb__DOT__load__68__name
            [__Vilp30];
        __Vilp30 = ((IData)(1U) + __Vilp30);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__71__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__71__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__68__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__71__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__71__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__71__expect_miss) {
            __Vtemp_15[0U] = 0x20676f74U;
            __Vtemp_15[1U] = 0x20616e64U;
            __Vtemp_15[2U] = 0x63746564U;
            __Vtemp_15[3U] = 0x65787065U;
            __Vtemp_15[4U] = 0x49535320U;
            __Vtemp_15[5U] = 0x0000004dU;
        } else {
            __Vtemp_15[0U] = 0x20676f74U;
            __Vtemp_15[1U] = 0x20616e64U;
            __Vtemp_15[2U] = 0x63746564U;
            __Vtemp_15[3U] = 0x65787065U;
            __Vtemp_15[4U] = 0x48495420U;
            __Vtemp_15[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__71__name.data()
                     , '#',168,__Vtemp_15.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__71__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__71__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__71__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__72__name, VD_CACHE_tb__ConstPool__CONST_h55c4e4d6_0);
    __Vtask_D_CACHE_tb__DOT__load__72__expect_miss = 0U;
    __Vtask_D_CACHE_tb__DOT__load__72__expected = 0x00008001U;
    __Vtask_D_CACHE_tb__DOT__load__72__f3 = 5U;
    __Vtask_D_CACHE_tb__DOT__load__72__addr = 0x00000062U;
    __Vtask_D_CACHE_tb__DOT__access__73__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__73__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__73__f3 = __Vtask_D_CACHE_tb__DOT__load__72__f3;
    __Vtask_D_CACHE_tb__DOT__access__73__addr = __Vtask_D_CACHE_tb__DOT__load__72__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__73__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__73__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__73__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__73__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp31 = 0U;
    while ((__Vilp31 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__74__name[__Vilp31] 
            = __Vtask_D_CACHE_tb__DOT__load__72__name
            [__Vilp31];
        __Vilp31 = ((IData)(1U) + __Vilp31);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__74__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__74__expected 
        = __Vtask_D_CACHE_tb__DOT__load__72__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__74__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__74__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__74__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__74__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__74__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__74__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__74__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__74__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp32 = 0U;
    while ((__Vilp32 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__75__name[__Vilp32] 
            = __Vtask_D_CACHE_tb__DOT__load__72__name
            [__Vilp32];
        __Vilp32 = ((IData)(1U) + __Vilp32);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__75__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__75__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__72__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__75__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__75__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__75__expect_miss) {
            __Vtemp_16[0U] = 0x20676f74U;
            __Vtemp_16[1U] = 0x20616e64U;
            __Vtemp_16[2U] = 0x63746564U;
            __Vtemp_16[3U] = 0x65787065U;
            __Vtemp_16[4U] = 0x49535320U;
            __Vtemp_16[5U] = 0x0000004dU;
        } else {
            __Vtemp_16[0U] = 0x20676f74U;
            __Vtemp_16[1U] = 0x20616e64U;
            __Vtemp_16[2U] = 0x63746564U;
            __Vtemp_16[3U] = 0x65787065U;
            __Vtemp_16[4U] = 0x48495420U;
            __Vtemp_16[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__75__name.data()
                     , '#',168,__Vtemp_16.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__75__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__75__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__75__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_WRITEF_NX("\n--- Test 8: SW hit, write-back (memory not updated) ---\n",0);
    __Vtask_D_CACHE_tb__DOT__write_mem__76__word = 0xaaaaaaaaU;
    __Vtask_D_CACHE_tb__DOT__write_mem__76__addr = 0x00000080U;
    vlSelfRef.D_CACHE_tb__DOT__mem[(0x00003fffU & (__Vtask_D_CACHE_tb__DOT__write_mem__76__addr 
                                                   >> 2U))] 
        = __Vtask_D_CACHE_tb__DOT__write_mem__76__word;
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__77__name, VD_CACHE_tb__ConstPool__CONST_hd711b368_0);
    __Vtask_D_CACHE_tb__DOT__load__77__expect_miss = 1U;
    __Vtask_D_CACHE_tb__DOT__load__77__expected = 0xaaaaaaaaU;
    __Vtask_D_CACHE_tb__DOT__load__77__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__77__addr = 0x00000080U;
    __Vtask_D_CACHE_tb__DOT__access__78__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__78__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__78__f3 = __Vtask_D_CACHE_tb__DOT__load__77__f3;
    __Vtask_D_CACHE_tb__DOT__access__78__addr = __Vtask_D_CACHE_tb__DOT__load__77__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__78__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__78__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__78__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__78__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp33 = 0U;
    while ((__Vilp33 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__79__name[__Vilp33] 
            = __Vtask_D_CACHE_tb__DOT__load__77__name
            [__Vilp33];
        __Vilp33 = ((IData)(1U) + __Vilp33);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__79__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__79__expected 
        = __Vtask_D_CACHE_tb__DOT__load__77__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__79__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__79__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__79__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__79__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__79__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__79__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__79__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__79__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp34 = 0U;
    while ((__Vilp34 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__80__name[__Vilp34] 
            = __Vtask_D_CACHE_tb__DOT__load__77__name
            [__Vilp34];
        __Vilp34 = ((IData)(1U) + __Vilp34);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__80__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__80__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__77__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__80__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__80__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__80__expect_miss) {
            __Vtemp_17[0U] = 0x20676f74U;
            __Vtemp_17[1U] = 0x20616e64U;
            __Vtemp_17[2U] = 0x63746564U;
            __Vtemp_17[3U] = 0x65787065U;
            __Vtemp_17[4U] = 0x49535320U;
            __Vtemp_17[5U] = 0x0000004dU;
        } else {
            __Vtemp_17[0U] = 0x20676f74U;
            __Vtemp_17[1U] = 0x20616e64U;
            __Vtemp_17[2U] = 0x63746564U;
            __Vtemp_17[3U] = 0x65787065U;
            __Vtemp_17[4U] = 0x48495420U;
            __Vtemp_17[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__80__name.data()
                     , '#',168,__Vtemp_17.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__80__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__80__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__80__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__store__81__name, VD_CACHE_tb__ConstPool__CONST_h294b1dc1_0);
    __Vtask_D_CACHE_tb__DOT__store__81__expect_miss = 0U;
    __Vtask_D_CACHE_tb__DOT__store__81__value = 0x55555555U;
    __Vtask_D_CACHE_tb__DOT__store__81__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__store__81__addr = 0x00000080U;
    vlSelfRef.D_CACHE_tb__DOT__store__Vstatic__lane 
        = VL_SHIFTL_III(32,32,32, __Vtask_D_CACHE_tb__DOT__store__81__value, 
                        (0x00000018U & (__Vtask_D_CACHE_tb__DOT__store__81__addr 
                                        << 3U)));
    __Vtask_D_CACHE_tb__DOT__access__82__wdata = vlSelfRef.D_CACHE_tb__DOT__store__Vstatic__lane;
    __Vtask_D_CACHE_tb__DOT__access__82__we = 1U;
    __Vtask_D_CACHE_tb__DOT__access__82__f3 = __Vtask_D_CACHE_tb__DOT__store__81__f3;
    __Vtask_D_CACHE_tb__DOT__access__82__addr = __Vtask_D_CACHE_tb__DOT__store__81__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__82__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__82__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__82__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__82__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp35 = 0U;
    while ((__Vilp35 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__83__name[__Vilp35] 
            = __Vtask_D_CACHE_tb__DOT__store__81__name
            [__Vilp35];
        __Vilp35 = ((IData)(1U) + __Vilp35);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__83__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__83__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__store__81__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__83__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__83__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__83__expect_miss) {
            __Vtemp_18[0U] = 0x20676f74U;
            __Vtemp_18[1U] = 0x20616e64U;
            __Vtemp_18[2U] = 0x63746564U;
            __Vtemp_18[3U] = 0x65787065U;
            __Vtemp_18[4U] = 0x49535320U;
            __Vtemp_18[5U] = 0x0000004dU;
        } else {
            __Vtemp_18[0U] = 0x20676f74U;
            __Vtemp_18[1U] = 0x20616e64U;
            __Vtemp_18[2U] = 0x63746564U;
            __Vtemp_18[3U] = 0x65787065U;
            __Vtemp_18[4U] = 0x48495420U;
            __Vtemp_18[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__83__name.data()
                     , '#',168,__Vtemp_18.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__83__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__83__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__83__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__84__name, VD_CACHE_tb__ConstPool__CONST_he4371207_0);
    __Vtask_D_CACHE_tb__DOT__load__84__expect_miss = 0U;
    __Vtask_D_CACHE_tb__DOT__load__84__expected = 0x55555555U;
    __Vtask_D_CACHE_tb__DOT__load__84__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__84__addr = 0x00000080U;
    __Vtask_D_CACHE_tb__DOT__access__85__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__85__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__85__f3 = __Vtask_D_CACHE_tb__DOT__load__84__f3;
    __Vtask_D_CACHE_tb__DOT__access__85__addr = __Vtask_D_CACHE_tb__DOT__load__84__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__85__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__85__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__85__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__85__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp36 = 0U;
    while ((__Vilp36 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__86__name[__Vilp36] 
            = __Vtask_D_CACHE_tb__DOT__load__84__name
            [__Vilp36];
        __Vilp36 = ((IData)(1U) + __Vilp36);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__86__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__86__expected 
        = __Vtask_D_CACHE_tb__DOT__load__84__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__86__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__86__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__86__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__86__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__86__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__86__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__86__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__86__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp37 = 0U;
    while ((__Vilp37 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__87__name[__Vilp37] 
            = __Vtask_D_CACHE_tb__DOT__load__84__name
            [__Vilp37];
        __Vilp37 = ((IData)(1U) + __Vilp37);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__87__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__87__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__84__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__87__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__87__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__87__expect_miss) {
            __Vtemp_19[0U] = 0x20676f74U;
            __Vtemp_19[1U] = 0x20616e64U;
            __Vtemp_19[2U] = 0x63746564U;
            __Vtemp_19[3U] = 0x65787065U;
            __Vtemp_19[4U] = 0x49535320U;
            __Vtemp_19[5U] = 0x0000004dU;
        } else {
            __Vtemp_19[0U] = 0x20676f74U;
            __Vtemp_19[1U] = 0x20616e64U;
            __Vtemp_19[2U] = 0x63746564U;
            __Vtemp_19[3U] = 0x65787065U;
            __Vtemp_19[4U] = 0x48495420U;
            __Vtemp_19[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__87__name.data()
                     , '#',168,__Vtemp_19.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__87__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__87__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__87__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__88__name, VD_CACHE_tb__ConstPool__CONST_h2866433b_0);
    __Vtask_D_CACHE_tb__DOT__check_data__88__actual 
        = vlSelfRef.D_CACHE_tb__DOT__mem[32U];
    __Vtask_D_CACHE_tb__DOT__check_data__88__expected = 0xaaaaaaaaU;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__88__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__88__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__88__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__88__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__88__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__88__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__88__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__88__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_WRITEF_NX("\n--- Test 9: SB / SH merge ---\n",0);
    __Vtask_D_CACHE_tb__DOT__write_mem__89__word = 0U;
    __Vtask_D_CACHE_tb__DOT__write_mem__89__addr = 0x000000c0U;
    vlSelfRef.D_CACHE_tb__DOT__mem[(0x00003fffU & (__Vtask_D_CACHE_tb__DOT__write_mem__89__addr 
                                                   >> 2U))] 
        = __Vtask_D_CACHE_tb__DOT__write_mem__89__word;
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__90__name, VD_CACHE_tb__ConstPool__CONST_h6a025562_0);
    __Vtask_D_CACHE_tb__DOT__load__90__expect_miss = 1U;
    __Vtask_D_CACHE_tb__DOT__load__90__expected = 0U;
    __Vtask_D_CACHE_tb__DOT__load__90__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__90__addr = 0x000000c0U;
    __Vtask_D_CACHE_tb__DOT__access__91__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__91__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__91__f3 = __Vtask_D_CACHE_tb__DOT__load__90__f3;
    __Vtask_D_CACHE_tb__DOT__access__91__addr = __Vtask_D_CACHE_tb__DOT__load__90__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__91__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__91__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__91__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__91__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp38 = 0U;
    while ((__Vilp38 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__92__name[__Vilp38] 
            = __Vtask_D_CACHE_tb__DOT__load__90__name
            [__Vilp38];
        __Vilp38 = ((IData)(1U) + __Vilp38);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__92__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__92__expected 
        = __Vtask_D_CACHE_tb__DOT__load__90__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__92__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__92__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__92__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__92__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__92__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__92__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__92__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__92__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp39 = 0U;
    while ((__Vilp39 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__93__name[__Vilp39] 
            = __Vtask_D_CACHE_tb__DOT__load__90__name
            [__Vilp39];
        __Vilp39 = ((IData)(1U) + __Vilp39);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__93__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__93__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__90__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__93__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__93__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__93__expect_miss) {
            __Vtemp_20[0U] = 0x20676f74U;
            __Vtemp_20[1U] = 0x20616e64U;
            __Vtemp_20[2U] = 0x63746564U;
            __Vtemp_20[3U] = 0x65787065U;
            __Vtemp_20[4U] = 0x49535320U;
            __Vtemp_20[5U] = 0x0000004dU;
        } else {
            __Vtemp_20[0U] = 0x20676f74U;
            __Vtemp_20[1U] = 0x20616e64U;
            __Vtemp_20[2U] = 0x63746564U;
            __Vtemp_20[3U] = 0x65787065U;
            __Vtemp_20[4U] = 0x48495420U;
            __Vtemp_20[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__93__name.data()
                     , '#',168,__Vtemp_20.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__93__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__93__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__93__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__store__94__name, VD_CACHE_tb__ConstPool__CONST_h2dcce8d6_0);
    __Vtask_D_CACHE_tb__DOT__store__94__expect_miss = 0U;
    __Vtask_D_CACHE_tb__DOT__store__94__value = 0x000000aaU;
    __Vtask_D_CACHE_tb__DOT__store__94__f3 = 0U;
    __Vtask_D_CACHE_tb__DOT__store__94__addr = 0x000000c0U;
    vlSelfRef.D_CACHE_tb__DOT__store__Vstatic__lane 
        = VL_SHIFTL_III(32,32,32, __Vtask_D_CACHE_tb__DOT__store__94__value, 
                        (0x00000018U & (__Vtask_D_CACHE_tb__DOT__store__94__addr 
                                        << 3U)));
    __Vtask_D_CACHE_tb__DOT__access__95__wdata = vlSelfRef.D_CACHE_tb__DOT__store__Vstatic__lane;
    __Vtask_D_CACHE_tb__DOT__access__95__we = 1U;
    __Vtask_D_CACHE_tb__DOT__access__95__f3 = __Vtask_D_CACHE_tb__DOT__store__94__f3;
    __Vtask_D_CACHE_tb__DOT__access__95__addr = __Vtask_D_CACHE_tb__DOT__store__94__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__95__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__95__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__95__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__95__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp40 = 0U;
    while ((__Vilp40 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__96__name[__Vilp40] 
            = __Vtask_D_CACHE_tb__DOT__store__94__name
            [__Vilp40];
        __Vilp40 = ((IData)(1U) + __Vilp40);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__96__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__96__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__store__94__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__96__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__96__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__96__expect_miss) {
            __Vtemp_21[0U] = 0x20676f74U;
            __Vtemp_21[1U] = 0x20616e64U;
            __Vtemp_21[2U] = 0x63746564U;
            __Vtemp_21[3U] = 0x65787065U;
            __Vtemp_21[4U] = 0x49535320U;
            __Vtemp_21[5U] = 0x0000004dU;
        } else {
            __Vtemp_21[0U] = 0x20676f74U;
            __Vtemp_21[1U] = 0x20616e64U;
            __Vtemp_21[2U] = 0x63746564U;
            __Vtemp_21[3U] = 0x65787065U;
            __Vtemp_21[4U] = 0x48495420U;
            __Vtemp_21[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__96__name.data()
                     , '#',168,__Vtemp_21.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__96__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__96__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__96__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__store__97__name, VD_CACHE_tb__ConstPool__CONST_hc984ae36_0);
    __Vtask_D_CACHE_tb__DOT__store__97__expect_miss = 0U;
    __Vtask_D_CACHE_tb__DOT__store__97__value = 0x000000bbU;
    __Vtask_D_CACHE_tb__DOT__store__97__f3 = 0U;
    __Vtask_D_CACHE_tb__DOT__store__97__addr = 0x000000c1U;
    vlSelfRef.D_CACHE_tb__DOT__store__Vstatic__lane 
        = VL_SHIFTL_III(32,32,32, __Vtask_D_CACHE_tb__DOT__store__97__value, 
                        (0x00000018U & (__Vtask_D_CACHE_tb__DOT__store__97__addr 
                                        << 3U)));
    __Vtask_D_CACHE_tb__DOT__access__98__wdata = vlSelfRef.D_CACHE_tb__DOT__store__Vstatic__lane;
    __Vtask_D_CACHE_tb__DOT__access__98__we = 1U;
    __Vtask_D_CACHE_tb__DOT__access__98__f3 = __Vtask_D_CACHE_tb__DOT__store__97__f3;
    __Vtask_D_CACHE_tb__DOT__access__98__addr = __Vtask_D_CACHE_tb__DOT__store__97__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__98__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__98__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__98__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__98__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp41 = 0U;
    while ((__Vilp41 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__99__name[__Vilp41] 
            = __Vtask_D_CACHE_tb__DOT__store__97__name
            [__Vilp41];
        __Vilp41 = ((IData)(1U) + __Vilp41);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__99__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__99__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__store__97__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__99__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__99__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__99__expect_miss) {
            __Vtemp_22[0U] = 0x20676f74U;
            __Vtemp_22[1U] = 0x20616e64U;
            __Vtemp_22[2U] = 0x63746564U;
            __Vtemp_22[3U] = 0x65787065U;
            __Vtemp_22[4U] = 0x49535320U;
            __Vtemp_22[5U] = 0x0000004dU;
        } else {
            __Vtemp_22[0U] = 0x20676f74U;
            __Vtemp_22[1U] = 0x20616e64U;
            __Vtemp_22[2U] = 0x63746564U;
            __Vtemp_22[3U] = 0x65787065U;
            __Vtemp_22[4U] = 0x48495420U;
            __Vtemp_22[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__99__name.data()
                     , '#',168,__Vtemp_22.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__99__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__99__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__99__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__store__100__name, VD_CACHE_tb__ConstPool__CONST_h360dcc9f_0);
    __Vtask_D_CACHE_tb__DOT__store__100__expect_miss = 0U;
    __Vtask_D_CACHE_tb__DOT__store__100__value = 0x0000ccddU;
    __Vtask_D_CACHE_tb__DOT__store__100__f3 = 1U;
    __Vtask_D_CACHE_tb__DOT__store__100__addr = 0x000000c2U;
    vlSelfRef.D_CACHE_tb__DOT__store__Vstatic__lane 
        = VL_SHIFTL_III(32,32,32, __Vtask_D_CACHE_tb__DOT__store__100__value, 
                        (0x00000018U & (__Vtask_D_CACHE_tb__DOT__store__100__addr 
                                        << 3U)));
    __Vtask_D_CACHE_tb__DOT__access__101__wdata = vlSelfRef.D_CACHE_tb__DOT__store__Vstatic__lane;
    __Vtask_D_CACHE_tb__DOT__access__101__we = 1U;
    __Vtask_D_CACHE_tb__DOT__access__101__f3 = __Vtask_D_CACHE_tb__DOT__store__100__f3;
    __Vtask_D_CACHE_tb__DOT__access__101__addr = __Vtask_D_CACHE_tb__DOT__store__100__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__101__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__101__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__101__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__101__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp42 = 0U;
    while ((__Vilp42 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__102__name[__Vilp42] 
            = __Vtask_D_CACHE_tb__DOT__store__100__name
            [__Vilp42];
        __Vilp42 = ((IData)(1U) + __Vilp42);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__102__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__102__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__store__100__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__102__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__102__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__102__expect_miss) {
            __Vtemp_23[0U] = 0x20676f74U;
            __Vtemp_23[1U] = 0x20616e64U;
            __Vtemp_23[2U] = 0x63746564U;
            __Vtemp_23[3U] = 0x65787065U;
            __Vtemp_23[4U] = 0x49535320U;
            __Vtemp_23[5U] = 0x0000004dU;
        } else {
            __Vtemp_23[0U] = 0x20676f74U;
            __Vtemp_23[1U] = 0x20616e64U;
            __Vtemp_23[2U] = 0x63746564U;
            __Vtemp_23[3U] = 0x65787065U;
            __Vtemp_23[4U] = 0x48495420U;
            __Vtemp_23[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__102__name.data()
                     , '#',168,__Vtemp_23.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__102__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__102__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__102__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__103__name, VD_CACHE_tb__ConstPool__CONST_h68602cbd_0);
    __Vtask_D_CACHE_tb__DOT__load__103__expect_miss = 0U;
    __Vtask_D_CACHE_tb__DOT__load__103__expected = 0xccddbbaaU;
    __Vtask_D_CACHE_tb__DOT__load__103__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__103__addr = 0x000000c0U;
    __Vtask_D_CACHE_tb__DOT__access__104__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__104__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__104__f3 = __Vtask_D_CACHE_tb__DOT__load__103__f3;
    __Vtask_D_CACHE_tb__DOT__access__104__addr = __Vtask_D_CACHE_tb__DOT__load__103__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__104__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__104__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__104__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__104__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp43 = 0U;
    while ((__Vilp43 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__105__name[__Vilp43] 
            = __Vtask_D_CACHE_tb__DOT__load__103__name
            [__Vilp43];
        __Vilp43 = ((IData)(1U) + __Vilp43);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__105__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__105__expected 
        = __Vtask_D_CACHE_tb__DOT__load__103__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__105__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__105__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__105__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__105__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__105__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__105__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__105__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__105__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp44 = 0U;
    while ((__Vilp44 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__106__name[__Vilp44] 
            = __Vtask_D_CACHE_tb__DOT__load__103__name
            [__Vilp44];
        __Vilp44 = ((IData)(1U) + __Vilp44);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__106__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__106__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__103__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__106__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__106__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__106__expect_miss) {
            __Vtemp_24[0U] = 0x20676f74U;
            __Vtemp_24[1U] = 0x20616e64U;
            __Vtemp_24[2U] = 0x63746564U;
            __Vtemp_24[3U] = 0x65787065U;
            __Vtemp_24[4U] = 0x49535320U;
            __Vtemp_24[5U] = 0x0000004dU;
        } else {
            __Vtemp_24[0U] = 0x20676f74U;
            __Vtemp_24[1U] = 0x20616e64U;
            __Vtemp_24[2U] = 0x63746564U;
            __Vtemp_24[3U] = 0x65787065U;
            __Vtemp_24[4U] = 0x48495420U;
            __Vtemp_24[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__106__name.data()
                     , '#',168,__Vtemp_24.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__106__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__106__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__106__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_WRITEF_NX("\n--- Test 10: Boundary set ---\n",0);
    __Vtask_D_CACHE_tb__DOT__write_mem__107__word = 0xbaadf00dU;
    __Vtask_D_CACHE_tb__DOT__write_mem__107__addr = 0x000001fcU;
    vlSelfRef.D_CACHE_tb__DOT__mem[(0x00003fffU & (__Vtask_D_CACHE_tb__DOT__write_mem__107__addr 
                                                   >> 2U))] 
        = __Vtask_D_CACHE_tb__DOT__write_mem__107__word;
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__108__name, VD_CACHE_tb__ConstPool__CONST_h59e3c7a1_0);
    __Vtask_D_CACHE_tb__DOT__load__108__expect_miss = 1U;
    __Vtask_D_CACHE_tb__DOT__load__108__expected = 0xbaadf00dU;
    __Vtask_D_CACHE_tb__DOT__load__108__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__108__addr = 0x000001fcU;
    __Vtask_D_CACHE_tb__DOT__access__109__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__109__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__109__f3 = __Vtask_D_CACHE_tb__DOT__load__108__f3;
    __Vtask_D_CACHE_tb__DOT__access__109__addr = __Vtask_D_CACHE_tb__DOT__load__108__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__109__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__109__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__109__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__109__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp45 = 0U;
    while ((__Vilp45 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__110__name[__Vilp45] 
            = __Vtask_D_CACHE_tb__DOT__load__108__name
            [__Vilp45];
        __Vilp45 = ((IData)(1U) + __Vilp45);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__110__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__110__expected 
        = __Vtask_D_CACHE_tb__DOT__load__108__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__110__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__110__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__110__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__110__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__110__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__110__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__110__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__110__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp46 = 0U;
    while ((__Vilp46 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__111__name[__Vilp46] 
            = __Vtask_D_CACHE_tb__DOT__load__108__name
            [__Vilp46];
        __Vilp46 = ((IData)(1U) + __Vilp46);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__111__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__111__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__108__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__111__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__111__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__111__expect_miss) {
            __Vtemp_25[0U] = 0x20676f74U;
            __Vtemp_25[1U] = 0x20616e64U;
            __Vtemp_25[2U] = 0x63746564U;
            __Vtemp_25[3U] = 0x65787065U;
            __Vtemp_25[4U] = 0x49535320U;
            __Vtemp_25[5U] = 0x0000004dU;
        } else {
            __Vtemp_25[0U] = 0x20676f74U;
            __Vtemp_25[1U] = 0x20616e64U;
            __Vtemp_25[2U] = 0x63746564U;
            __Vtemp_25[3U] = 0x65787065U;
            __Vtemp_25[4U] = 0x48495420U;
            __Vtemp_25[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__111__name.data()
                     , '#',168,__Vtemp_25.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__111__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__111__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__111__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__112__name, VD_CACHE_tb__ConstPool__CONST_h4a3fce6c_0);
    __Vtask_D_CACHE_tb__DOT__load__112__expect_miss = 0U;
    __Vtask_D_CACHE_tb__DOT__load__112__expected = 0x0000000dU;
    __Vtask_D_CACHE_tb__DOT__load__112__f3 = 4U;
    __Vtask_D_CACHE_tb__DOT__load__112__addr = 0x000001fcU;
    __Vtask_D_CACHE_tb__DOT__access__113__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__113__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__113__f3 = __Vtask_D_CACHE_tb__DOT__load__112__f3;
    __Vtask_D_CACHE_tb__DOT__access__113__addr = __Vtask_D_CACHE_tb__DOT__load__112__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__113__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__113__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__113__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__113__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp47 = 0U;
    while ((__Vilp47 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__114__name[__Vilp47] 
            = __Vtask_D_CACHE_tb__DOT__load__112__name
            [__Vilp47];
        __Vilp47 = ((IData)(1U) + __Vilp47);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__114__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__114__expected 
        = __Vtask_D_CACHE_tb__DOT__load__112__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__114__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__114__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__114__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__114__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__114__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__114__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__114__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__114__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp48 = 0U;
    while ((__Vilp48 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__115__name[__Vilp48] 
            = __Vtask_D_CACHE_tb__DOT__load__112__name
            [__Vilp48];
        __Vilp48 = ((IData)(1U) + __Vilp48);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__115__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__115__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__112__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__115__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__115__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__115__expect_miss) {
            __Vtemp_26[0U] = 0x20676f74U;
            __Vtemp_26[1U] = 0x20616e64U;
            __Vtemp_26[2U] = 0x63746564U;
            __Vtemp_26[3U] = 0x65787065U;
            __Vtemp_26[4U] = 0x49535320U;
            __Vtemp_26[5U] = 0x0000004dU;
        } else {
            __Vtemp_26[0U] = 0x20676f74U;
            __Vtemp_26[1U] = 0x20616e64U;
            __Vtemp_26[2U] = 0x63746564U;
            __Vtemp_26[3U] = 0x65787065U;
            __Vtemp_26[4U] = 0x48495420U;
            __Vtemp_26[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__115__name.data()
                     , '#',168,__Vtemp_26.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__115__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__115__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__115__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_WRITEF_NX("\n--- Test 11: 2-way associativity ---\n",0);
    __Vtask_D_CACHE_tb__DOT__write_mem__116__word = 0x11111111U;
    __Vtask_D_CACHE_tb__DOT__write_mem__116__addr = 0x00003000U;
    vlSelfRef.D_CACHE_tb__DOT__mem[(0x00003fffU & (__Vtask_D_CACHE_tb__DOT__write_mem__116__addr 
                                                   >> 2U))] 
        = __Vtask_D_CACHE_tb__DOT__write_mem__116__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__117__word = 0x22222222U;
    __Vtask_D_CACHE_tb__DOT__write_mem__117__addr = 0x00003200U;
    vlSelfRef.D_CACHE_tb__DOT__mem[(0x00003fffU & (__Vtask_D_CACHE_tb__DOT__write_mem__117__addr 
                                                   >> 2U))] 
        = __Vtask_D_CACHE_tb__DOT__write_mem__117__word;
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__118__name, VD_CACHE_tb__ConstPool__CONST_h34c806d1_0);
    __Vtask_D_CACHE_tb__DOT__load__118__expect_miss = 1U;
    __Vtask_D_CACHE_tb__DOT__load__118__expected = 0x11111111U;
    __Vtask_D_CACHE_tb__DOT__load__118__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__118__addr = 0x00003000U;
    __Vtask_D_CACHE_tb__DOT__access__119__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__119__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__119__f3 = __Vtask_D_CACHE_tb__DOT__load__118__f3;
    __Vtask_D_CACHE_tb__DOT__access__119__addr = __Vtask_D_CACHE_tb__DOT__load__118__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__119__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__119__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__119__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__119__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp49 = 0U;
    while ((__Vilp49 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__120__name[__Vilp49] 
            = __Vtask_D_CACHE_tb__DOT__load__118__name
            [__Vilp49];
        __Vilp49 = ((IData)(1U) + __Vilp49);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__120__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__120__expected 
        = __Vtask_D_CACHE_tb__DOT__load__118__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__120__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__120__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__120__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__120__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__120__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__120__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__120__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__120__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp50 = 0U;
    while ((__Vilp50 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__121__name[__Vilp50] 
            = __Vtask_D_CACHE_tb__DOT__load__118__name
            [__Vilp50];
        __Vilp50 = ((IData)(1U) + __Vilp50);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__121__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__121__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__118__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__121__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__121__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__121__expect_miss) {
            __Vtemp_27[0U] = 0x20676f74U;
            __Vtemp_27[1U] = 0x20616e64U;
            __Vtemp_27[2U] = 0x63746564U;
            __Vtemp_27[3U] = 0x65787065U;
            __Vtemp_27[4U] = 0x49535320U;
            __Vtemp_27[5U] = 0x0000004dU;
        } else {
            __Vtemp_27[0U] = 0x20676f74U;
            __Vtemp_27[1U] = 0x20616e64U;
            __Vtemp_27[2U] = 0x63746564U;
            __Vtemp_27[3U] = 0x65787065U;
            __Vtemp_27[4U] = 0x48495420U;
            __Vtemp_27[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__121__name.data()
                     , '#',168,__Vtemp_27.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__121__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__121__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__121__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__122__name, VD_CACHE_tb__ConstPool__CONST_ha7acb184_0);
    __Vtask_D_CACHE_tb__DOT__load__122__expect_miss = 1U;
    __Vtask_D_CACHE_tb__DOT__load__122__expected = 0x22222222U;
    __Vtask_D_CACHE_tb__DOT__load__122__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__122__addr = 0x00003200U;
    __Vtask_D_CACHE_tb__DOT__access__123__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__123__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__123__f3 = __Vtask_D_CACHE_tb__DOT__load__122__f3;
    __Vtask_D_CACHE_tb__DOT__access__123__addr = __Vtask_D_CACHE_tb__DOT__load__122__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__123__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__123__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__123__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__123__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp51 = 0U;
    while ((__Vilp51 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__124__name[__Vilp51] 
            = __Vtask_D_CACHE_tb__DOT__load__122__name
            [__Vilp51];
        __Vilp51 = ((IData)(1U) + __Vilp51);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__124__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__124__expected 
        = __Vtask_D_CACHE_tb__DOT__load__122__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__124__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__124__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__124__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__124__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__124__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__124__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__124__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__124__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp52 = 0U;
    while ((__Vilp52 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__125__name[__Vilp52] 
            = __Vtask_D_CACHE_tb__DOT__load__122__name
            [__Vilp52];
        __Vilp52 = ((IData)(1U) + __Vilp52);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__125__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__125__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__122__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__125__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__125__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__125__expect_miss) {
            __Vtemp_28[0U] = 0x20676f74U;
            __Vtemp_28[1U] = 0x20616e64U;
            __Vtemp_28[2U] = 0x63746564U;
            __Vtemp_28[3U] = 0x65787065U;
            __Vtemp_28[4U] = 0x49535320U;
            __Vtemp_28[5U] = 0x0000004dU;
        } else {
            __Vtemp_28[0U] = 0x20676f74U;
            __Vtemp_28[1U] = 0x20616e64U;
            __Vtemp_28[2U] = 0x63746564U;
            __Vtemp_28[3U] = 0x65787065U;
            __Vtemp_28[4U] = 0x48495420U;
            __Vtemp_28[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__125__name.data()
                     , '#',168,__Vtemp_28.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__125__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__125__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__125__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__126__name, VD_CACHE_tb__ConstPool__CONST_hff4d6978_0);
    __Vtask_D_CACHE_tb__DOT__load__126__expect_miss = 0U;
    __Vtask_D_CACHE_tb__DOT__load__126__expected = 0x11111111U;
    __Vtask_D_CACHE_tb__DOT__load__126__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__126__addr = 0x00003000U;
    __Vtask_D_CACHE_tb__DOT__access__127__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__127__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__127__f3 = __Vtask_D_CACHE_tb__DOT__load__126__f3;
    __Vtask_D_CACHE_tb__DOT__access__127__addr = __Vtask_D_CACHE_tb__DOT__load__126__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__127__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__127__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__127__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__127__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp53 = 0U;
    while ((__Vilp53 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__128__name[__Vilp53] 
            = __Vtask_D_CACHE_tb__DOT__load__126__name
            [__Vilp53];
        __Vilp53 = ((IData)(1U) + __Vilp53);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__128__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__128__expected 
        = __Vtask_D_CACHE_tb__DOT__load__126__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__128__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__128__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__128__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__128__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__128__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__128__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__128__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__128__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp54 = 0U;
    while ((__Vilp54 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__129__name[__Vilp54] 
            = __Vtask_D_CACHE_tb__DOT__load__126__name
            [__Vilp54];
        __Vilp54 = ((IData)(1U) + __Vilp54);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__129__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__129__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__126__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__129__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__129__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__129__expect_miss) {
            __Vtemp_29[0U] = 0x20676f74U;
            __Vtemp_29[1U] = 0x20616e64U;
            __Vtemp_29[2U] = 0x63746564U;
            __Vtemp_29[3U] = 0x65787065U;
            __Vtemp_29[4U] = 0x49535320U;
            __Vtemp_29[5U] = 0x0000004dU;
        } else {
            __Vtemp_29[0U] = 0x20676f74U;
            __Vtemp_29[1U] = 0x20616e64U;
            __Vtemp_29[2U] = 0x63746564U;
            __Vtemp_29[3U] = 0x65787065U;
            __Vtemp_29[4U] = 0x48495420U;
            __Vtemp_29[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__129__name.data()
                     , '#',168,__Vtemp_29.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__129__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__129__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__129__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__130__name, VD_CACHE_tb__ConstPool__CONST_h338e056b_0);
    __Vtask_D_CACHE_tb__DOT__load__130__expect_miss = 0U;
    __Vtask_D_CACHE_tb__DOT__load__130__expected = 0x22222222U;
    __Vtask_D_CACHE_tb__DOT__load__130__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__130__addr = 0x00003200U;
    __Vtask_D_CACHE_tb__DOT__access__131__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__131__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__131__f3 = __Vtask_D_CACHE_tb__DOT__load__130__f3;
    __Vtask_D_CACHE_tb__DOT__access__131__addr = __Vtask_D_CACHE_tb__DOT__load__130__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__131__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__131__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__131__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__131__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp55 = 0U;
    while ((__Vilp55 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__132__name[__Vilp55] 
            = __Vtask_D_CACHE_tb__DOT__load__130__name
            [__Vilp55];
        __Vilp55 = ((IData)(1U) + __Vilp55);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__132__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__132__expected 
        = __Vtask_D_CACHE_tb__DOT__load__130__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__132__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__132__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__132__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__132__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__132__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__132__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__132__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__132__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp56 = 0U;
    while ((__Vilp56 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__133__name[__Vilp56] 
            = __Vtask_D_CACHE_tb__DOT__load__130__name
            [__Vilp56];
        __Vilp56 = ((IData)(1U) + __Vilp56);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__133__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__133__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__130__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__133__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__133__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__133__expect_miss) {
            __Vtemp_30[0U] = 0x20676f74U;
            __Vtemp_30[1U] = 0x20616e64U;
            __Vtemp_30[2U] = 0x63746564U;
            __Vtemp_30[3U] = 0x65787065U;
            __Vtemp_30[4U] = 0x49535320U;
            __Vtemp_30[5U] = 0x0000004dU;
        } else {
            __Vtemp_30[0U] = 0x20676f74U;
            __Vtemp_30[1U] = 0x20616e64U;
            __Vtemp_30[2U] = 0x63746564U;
            __Vtemp_30[3U] = 0x65787065U;
            __Vtemp_30[4U] = 0x48495420U;
            __Vtemp_30[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__133__name.data()
                     , '#',168,__Vtemp_30.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__133__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__133__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__133__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_WRITEF_NX("\n--- Test 12: Clean eviction ---\n",0);
    __Vtask_D_CACHE_tb__DOT__write_mem__134__word = 0x33333333U;
    __Vtask_D_CACHE_tb__DOT__write_mem__134__addr = 0x00003400U;
    vlSelfRef.D_CACHE_tb__DOT__mem[(0x00003fffU & (__Vtask_D_CACHE_tb__DOT__write_mem__134__addr 
                                                   >> 2U))] 
        = __Vtask_D_CACHE_tb__DOT__write_mem__134__word;
    vlSelfRef.D_CACHE_tb__DOT__clean_evict__DOT__wr_before 
        = vlSelfRef.D_CACHE_tb__DOT__mem_wr_count;
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__135__name, VD_CACHE_tb__ConstPool__CONST_h952d790b_0);
    __Vtask_D_CACHE_tb__DOT__load__135__expect_miss = 1U;
    __Vtask_D_CACHE_tb__DOT__load__135__expected = 0x33333333U;
    __Vtask_D_CACHE_tb__DOT__load__135__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__135__addr = 0x00003400U;
    __Vtask_D_CACHE_tb__DOT__access__136__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__136__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__136__f3 = __Vtask_D_CACHE_tb__DOT__load__135__f3;
    __Vtask_D_CACHE_tb__DOT__access__136__addr = __Vtask_D_CACHE_tb__DOT__load__135__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__136__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__136__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__136__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__136__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp57 = 0U;
    while ((__Vilp57 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__137__name[__Vilp57] 
            = __Vtask_D_CACHE_tb__DOT__load__135__name
            [__Vilp57];
        __Vilp57 = ((IData)(1U) + __Vilp57);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__137__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__137__expected 
        = __Vtask_D_CACHE_tb__DOT__load__135__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__137__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__137__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__137__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__137__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__137__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__137__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__137__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__137__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp58 = 0U;
    while ((__Vilp58 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__138__name[__Vilp58] 
            = __Vtask_D_CACHE_tb__DOT__load__135__name
            [__Vilp58];
        __Vilp58 = ((IData)(1U) + __Vilp58);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__138__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__138__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__135__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__138__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__138__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__138__expect_miss) {
            __Vtemp_31[0U] = 0x20676f74U;
            __Vtemp_31[1U] = 0x20616e64U;
            __Vtemp_31[2U] = 0x63746564U;
            __Vtemp_31[3U] = 0x65787065U;
            __Vtemp_31[4U] = 0x49535320U;
            __Vtemp_31[5U] = 0x0000004dU;
        } else {
            __Vtemp_31[0U] = 0x20676f74U;
            __Vtemp_31[1U] = 0x20616e64U;
            __Vtemp_31[2U] = 0x63746564U;
            __Vtemp_31[3U] = 0x65787065U;
            __Vtemp_31[4U] = 0x48495420U;
            __Vtemp_31[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__138__name.data()
                     , '#',168,__Vtemp_31.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__138__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__138__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__138__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__139__name, VD_CACHE_tb__ConstPool__CONST_h1031a607_0);
    __Vtask_D_CACHE_tb__DOT__check_data__139__actual 
        = vlSelfRef.D_CACHE_tb__DOT__mem_wr_count;
    __Vtask_D_CACHE_tb__DOT__check_data__139__expected 
        = vlSelfRef.D_CACHE_tb__DOT__clean_evict__DOT__wr_before;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__139__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__139__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__139__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__139__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__139__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__139__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__139__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__139__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__140__name, VD_CACHE_tb__ConstPool__CONST_ha442652b_0);
    __Vtask_D_CACHE_tb__DOT__load__140__expect_miss = 0U;
    __Vtask_D_CACHE_tb__DOT__load__140__expected = 0x33333333U;
    __Vtask_D_CACHE_tb__DOT__load__140__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__140__addr = 0x00003400U;
    __Vtask_D_CACHE_tb__DOT__access__141__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__141__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__141__f3 = __Vtask_D_CACHE_tb__DOT__load__140__f3;
    __Vtask_D_CACHE_tb__DOT__access__141__addr = __Vtask_D_CACHE_tb__DOT__load__140__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__141__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__141__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__141__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__141__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp59 = 0U;
    while ((__Vilp59 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__142__name[__Vilp59] 
            = __Vtask_D_CACHE_tb__DOT__load__140__name
            [__Vilp59];
        __Vilp59 = ((IData)(1U) + __Vilp59);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__142__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__142__expected 
        = __Vtask_D_CACHE_tb__DOT__load__140__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__142__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__142__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__142__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__142__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__142__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__142__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__142__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__142__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp60 = 0U;
    while ((__Vilp60 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__143__name[__Vilp60] 
            = __Vtask_D_CACHE_tb__DOT__load__140__name
            [__Vilp60];
        __Vilp60 = ((IData)(1U) + __Vilp60);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__143__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__143__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__140__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__143__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__143__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__143__expect_miss) {
            __Vtemp_32[0U] = 0x20676f74U;
            __Vtemp_32[1U] = 0x20616e64U;
            __Vtemp_32[2U] = 0x63746564U;
            __Vtemp_32[3U] = 0x65787065U;
            __Vtemp_32[4U] = 0x49535320U;
            __Vtemp_32[5U] = 0x0000004dU;
        } else {
            __Vtemp_32[0U] = 0x20676f74U;
            __Vtemp_32[1U] = 0x20616e64U;
            __Vtemp_32[2U] = 0x63746564U;
            __Vtemp_32[3U] = 0x65787065U;
            __Vtemp_32[4U] = 0x48495420U;
            __Vtemp_32[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__143__name.data()
                     , '#',168,__Vtemp_32.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__143__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__143__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__143__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_WRITEF_NX("\n--- Test 13: Dirty eviction / write-back ---\n",0);
    __Vtask_D_CACHE_tb__DOT__write_mem__144__word = 0x01010101U;
    __Vtask_D_CACHE_tb__DOT__write_mem__144__addr = 0x00005000U;
    vlSelfRef.D_CACHE_tb__DOT__mem[(0x00003fffU & (__Vtask_D_CACHE_tb__DOT__write_mem__144__addr 
                                                   >> 2U))] 
        = __Vtask_D_CACHE_tb__DOT__write_mem__144__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__145__word = 0x02020202U;
    __Vtask_D_CACHE_tb__DOT__write_mem__145__addr = 0x00005200U;
    vlSelfRef.D_CACHE_tb__DOT__mem[(0x00003fffU & (__Vtask_D_CACHE_tb__DOT__write_mem__145__addr 
                                                   >> 2U))] 
        = __Vtask_D_CACHE_tb__DOT__write_mem__145__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__146__word = 0x03030303U;
    __Vtask_D_CACHE_tb__DOT__write_mem__146__addr = 0x00005400U;
    vlSelfRef.D_CACHE_tb__DOT__mem[(0x00003fffU & (__Vtask_D_CACHE_tb__DOT__write_mem__146__addr 
                                                   >> 2U))] 
        = __Vtask_D_CACHE_tb__DOT__write_mem__146__word;
    __Vtask_D_CACHE_tb__DOT__write_mem__147__word = 0x04040404U;
    __Vtask_D_CACHE_tb__DOT__write_mem__147__addr = 0x00005600U;
    vlSelfRef.D_CACHE_tb__DOT__mem[(0x00003fffU & (__Vtask_D_CACHE_tb__DOT__write_mem__147__addr 
                                                   >> 2U))] 
        = __Vtask_D_CACHE_tb__DOT__write_mem__147__word;
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__148__name, VD_CACHE_tb__ConstPool__CONST_h1e1540f0_0);
    __Vtask_D_CACHE_tb__DOT__load__148__expect_miss = 1U;
    __Vtask_D_CACHE_tb__DOT__load__148__expected = 0x01010101U;
    __Vtask_D_CACHE_tb__DOT__load__148__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__148__addr = 0x00005000U;
    __Vtask_D_CACHE_tb__DOT__access__149__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__149__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__149__f3 = __Vtask_D_CACHE_tb__DOT__load__148__f3;
    __Vtask_D_CACHE_tb__DOT__access__149__addr = __Vtask_D_CACHE_tb__DOT__load__148__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__149__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__149__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__149__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__149__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp61 = 0U;
    while ((__Vilp61 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__150__name[__Vilp61] 
            = __Vtask_D_CACHE_tb__DOT__load__148__name
            [__Vilp61];
        __Vilp61 = ((IData)(1U) + __Vilp61);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__150__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__150__expected 
        = __Vtask_D_CACHE_tb__DOT__load__148__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__150__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__150__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__150__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__150__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__150__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__150__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__150__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__150__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp62 = 0U;
    while ((__Vilp62 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__151__name[__Vilp62] 
            = __Vtask_D_CACHE_tb__DOT__load__148__name
            [__Vilp62];
        __Vilp62 = ((IData)(1U) + __Vilp62);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__151__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__151__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__148__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__151__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__151__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__151__expect_miss) {
            __Vtemp_33[0U] = 0x20676f74U;
            __Vtemp_33[1U] = 0x20616e64U;
            __Vtemp_33[2U] = 0x63746564U;
            __Vtemp_33[3U] = 0x65787065U;
            __Vtemp_33[4U] = 0x49535320U;
            __Vtemp_33[5U] = 0x0000004dU;
        } else {
            __Vtemp_33[0U] = 0x20676f74U;
            __Vtemp_33[1U] = 0x20616e64U;
            __Vtemp_33[2U] = 0x63746564U;
            __Vtemp_33[3U] = 0x65787065U;
            __Vtemp_33[4U] = 0x48495420U;
            __Vtemp_33[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__151__name.data()
                     , '#',168,__Vtemp_33.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__151__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__151__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__151__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__store__152__name, VD_CACHE_tb__ConstPool__CONST_hebc43693_0);
    __Vtask_D_CACHE_tb__DOT__store__152__expect_miss = 0U;
    __Vtask_D_CACHE_tb__DOT__store__152__value = 0xfeedfaceU;
    __Vtask_D_CACHE_tb__DOT__store__152__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__store__152__addr = 0x00005000U;
    vlSelfRef.D_CACHE_tb__DOT__store__Vstatic__lane 
        = VL_SHIFTL_III(32,32,32, __Vtask_D_CACHE_tb__DOT__store__152__value, 
                        (0x00000018U & (__Vtask_D_CACHE_tb__DOT__store__152__addr 
                                        << 3U)));
    __Vtask_D_CACHE_tb__DOT__access__153__wdata = vlSelfRef.D_CACHE_tb__DOT__store__Vstatic__lane;
    __Vtask_D_CACHE_tb__DOT__access__153__we = 1U;
    __Vtask_D_CACHE_tb__DOT__access__153__f3 = __Vtask_D_CACHE_tb__DOT__store__152__f3;
    __Vtask_D_CACHE_tb__DOT__access__153__addr = __Vtask_D_CACHE_tb__DOT__store__152__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__153__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__153__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__153__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__153__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp63 = 0U;
    while ((__Vilp63 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__154__name[__Vilp63] 
            = __Vtask_D_CACHE_tb__DOT__store__152__name
            [__Vilp63];
        __Vilp63 = ((IData)(1U) + __Vilp63);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__154__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__154__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__store__152__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__154__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__154__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__154__expect_miss) {
            __Vtemp_34[0U] = 0x20676f74U;
            __Vtemp_34[1U] = 0x20616e64U;
            __Vtemp_34[2U] = 0x63746564U;
            __Vtemp_34[3U] = 0x65787065U;
            __Vtemp_34[4U] = 0x49535320U;
            __Vtemp_34[5U] = 0x0000004dU;
        } else {
            __Vtemp_34[0U] = 0x20676f74U;
            __Vtemp_34[1U] = 0x20616e64U;
            __Vtemp_34[2U] = 0x63746564U;
            __Vtemp_34[3U] = 0x65787065U;
            __Vtemp_34[4U] = 0x48495420U;
            __Vtemp_34[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__154__name.data()
                     , '#',168,__Vtemp_34.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__154__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__154__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__154__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__155__name, VD_CACHE_tb__ConstPool__CONST_h5853f4df_0);
    __Vtask_D_CACHE_tb__DOT__load__155__expect_miss = 1U;
    __Vtask_D_CACHE_tb__DOT__load__155__expected = 0x02020202U;
    __Vtask_D_CACHE_tb__DOT__load__155__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__155__addr = 0x00005200U;
    __Vtask_D_CACHE_tb__DOT__access__156__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__156__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__156__f3 = __Vtask_D_CACHE_tb__DOT__load__155__f3;
    __Vtask_D_CACHE_tb__DOT__access__156__addr = __Vtask_D_CACHE_tb__DOT__load__155__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__156__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__156__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__156__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__156__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp64 = 0U;
    while ((__Vilp64 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__157__name[__Vilp64] 
            = __Vtask_D_CACHE_tb__DOT__load__155__name
            [__Vilp64];
        __Vilp64 = ((IData)(1U) + __Vilp64);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__157__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__157__expected 
        = __Vtask_D_CACHE_tb__DOT__load__155__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__157__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__157__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__157__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__157__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__157__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__157__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__157__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__157__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp65 = 0U;
    while ((__Vilp65 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__158__name[__Vilp65] 
            = __Vtask_D_CACHE_tb__DOT__load__155__name
            [__Vilp65];
        __Vilp65 = ((IData)(1U) + __Vilp65);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__158__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__158__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__155__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__158__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__158__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__158__expect_miss) {
            __Vtemp_35[0U] = 0x20676f74U;
            __Vtemp_35[1U] = 0x20616e64U;
            __Vtemp_35[2U] = 0x63746564U;
            __Vtemp_35[3U] = 0x65787065U;
            __Vtemp_35[4U] = 0x49535320U;
            __Vtemp_35[5U] = 0x0000004dU;
        } else {
            __Vtemp_35[0U] = 0x20676f74U;
            __Vtemp_35[1U] = 0x20616e64U;
            __Vtemp_35[2U] = 0x63746564U;
            __Vtemp_35[3U] = 0x65787065U;
            __Vtemp_35[4U] = 0x48495420U;
            __Vtemp_35[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__158__name.data()
                     , '#',168,__Vtemp_35.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__158__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__158__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__158__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__159__name, VD_CACHE_tb__ConstPool__CONST_h367192a5_0);
    __Vtask_D_CACHE_tb__DOT__load__159__expect_miss = 1U;
    __Vtask_D_CACHE_tb__DOT__load__159__expected = 0x03030303U;
    __Vtask_D_CACHE_tb__DOT__load__159__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__159__addr = 0x00005400U;
    __Vtask_D_CACHE_tb__DOT__access__160__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__160__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__160__f3 = __Vtask_D_CACHE_tb__DOT__load__159__f3;
    __Vtask_D_CACHE_tb__DOT__access__160__addr = __Vtask_D_CACHE_tb__DOT__load__159__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__160__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__160__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__160__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__160__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp66 = 0U;
    while ((__Vilp66 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__161__name[__Vilp66] 
            = __Vtask_D_CACHE_tb__DOT__load__159__name
            [__Vilp66];
        __Vilp66 = ((IData)(1U) + __Vilp66);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__161__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__161__expected 
        = __Vtask_D_CACHE_tb__DOT__load__159__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__161__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__161__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__161__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__161__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__161__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__161__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__161__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__161__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp67 = 0U;
    while ((__Vilp67 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__162__name[__Vilp67] 
            = __Vtask_D_CACHE_tb__DOT__load__159__name
            [__Vilp67];
        __Vilp67 = ((IData)(1U) + __Vilp67);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__162__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__162__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__159__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__162__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__162__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__162__expect_miss) {
            __Vtemp_36[0U] = 0x20676f74U;
            __Vtemp_36[1U] = 0x20616e64U;
            __Vtemp_36[2U] = 0x63746564U;
            __Vtemp_36[3U] = 0x65787065U;
            __Vtemp_36[4U] = 0x49535320U;
            __Vtemp_36[5U] = 0x0000004dU;
        } else {
            __Vtemp_36[0U] = 0x20676f74U;
            __Vtemp_36[1U] = 0x20616e64U;
            __Vtemp_36[2U] = 0x63746564U;
            __Vtemp_36[3U] = 0x65787065U;
            __Vtemp_36[4U] = 0x48495420U;
            __Vtemp_36[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__162__name.data()
                     , '#',168,__Vtemp_36.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__162__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__162__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__162__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__163__name, VD_CACHE_tb__ConstPool__CONST_heba49680_0);
    __Vtask_D_CACHE_tb__DOT__load__163__expect_miss = 1U;
    __Vtask_D_CACHE_tb__DOT__load__163__expected = 0x04040404U;
    __Vtask_D_CACHE_tb__DOT__load__163__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__163__addr = 0x00005600U;
    __Vtask_D_CACHE_tb__DOT__access__164__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__164__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__164__f3 = __Vtask_D_CACHE_tb__DOT__load__163__f3;
    __Vtask_D_CACHE_tb__DOT__access__164__addr = __Vtask_D_CACHE_tb__DOT__load__163__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__164__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__164__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__164__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__164__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp68 = 0U;
    while ((__Vilp68 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__165__name[__Vilp68] 
            = __Vtask_D_CACHE_tb__DOT__load__163__name
            [__Vilp68];
        __Vilp68 = ((IData)(1U) + __Vilp68);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__165__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__165__expected 
        = __Vtask_D_CACHE_tb__DOT__load__163__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__165__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__165__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__165__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__165__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__165__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__165__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__165__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__165__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp69 = 0U;
    while ((__Vilp69 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__166__name[__Vilp69] 
            = __Vtask_D_CACHE_tb__DOT__load__163__name
            [__Vilp69];
        __Vilp69 = ((IData)(1U) + __Vilp69);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__166__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__166__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__163__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__166__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__166__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__166__expect_miss) {
            __Vtemp_37[0U] = 0x20676f74U;
            __Vtemp_37[1U] = 0x20616e64U;
            __Vtemp_37[2U] = 0x63746564U;
            __Vtemp_37[3U] = 0x65787065U;
            __Vtemp_37[4U] = 0x49535320U;
            __Vtemp_37[5U] = 0x0000004dU;
        } else {
            __Vtemp_37[0U] = 0x20676f74U;
            __Vtemp_37[1U] = 0x20616e64U;
            __Vtemp_37[2U] = 0x63746564U;
            __Vtemp_37[3U] = 0x65787065U;
            __Vtemp_37[4U] = 0x48495420U;
            __Vtemp_37[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__166__name.data()
                     , '#',168,__Vtemp_37.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__166__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__166__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__166__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__check_data__167__name, VD_CACHE_tb__ConstPool__CONST_hf379d909_0);
    __Vtask_D_CACHE_tb__DOT__check_data__167__actual 
        = vlSelfRef.D_CACHE_tb__DOT__mem[5120U];
    __Vtask_D_CACHE_tb__DOT__check_data__167__expected = 0xfeedfaceU;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__167__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__167__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__167__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__167__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__167__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__167__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__167__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__167__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    VL_ASSIGN_W(1601, __Vtask_D_CACHE_tb__DOT__load__168__name, VD_CACHE_tb__ConstPool__CONST_h745c521e_0);
    __Vtask_D_CACHE_tb__DOT__load__168__expect_miss = 1U;
    __Vtask_D_CACHE_tb__DOT__load__168__expected = 0xfeedfaceU;
    __Vtask_D_CACHE_tb__DOT__load__168__f3 = 2U;
    __Vtask_D_CACHE_tb__DOT__load__168__addr = 0x00005000U;
    __Vtask_D_CACHE_tb__DOT__access__169__wdata = 0U;
    __Vtask_D_CACHE_tb__DOT__access__169__we = 0U;
    __Vtask_D_CACHE_tb__DOT__access__169__f3 = __Vtask_D_CACHE_tb__DOT__load__168__f3;
    __Vtask_D_CACHE_tb__DOT__access__169__addr = __Vtask_D_CACHE_tb__DOT__load__168__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr 
        = __Vtask_D_CACHE_tb__DOT__access__169__addr;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3 
        = __Vtask_D_CACHE_tb__DOT__access__169__f3;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we 
        = __Vtask_D_CACHE_tb__DOT__access__169__we;
    vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata 
        = __Vtask_D_CACHE_tb__DOT__access__169__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_addr = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr;
    vlSelfRef.D_CACHE_tb__DOT__cpu_funct3 = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we;
    vlSelfRef.D_CACHE_tb__DOT__data_in_cpu = vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 1U;
    vlSelfRef.D_CACHE_tb__DOT__saw_miss = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         194);
    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        vlSelfRef.D_CACHE_tb__DOT__saw_miss = 1U;
    }
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    while (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall) {
        VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                          "@(posedge D_CACHE_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge D_CACHE_tb.clk)", 
                                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                             nullptr, 
                                             "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                             197);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         199);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.D_CACHE_tb__DOT__rdata = vlSelfRef.D_CACHE_tb__DOT__data_out_cpu;
    vlSelfRef.D_CACHE_tb__DOT__cpu_req = 0U;
    vlSelfRef.D_CACHE_tb__DOT__cpu_we = 0U;
    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(vlSelf, 
                                                      "@(posedge D_CACHE_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h883832f6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge D_CACHE_tb.clk)", 
                                                         "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         203);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    __Vilp70 = 0U;
    while ((__Vilp70 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_data__170__name[__Vilp70] 
            = __Vtask_D_CACHE_tb__DOT__load__168__name
            [__Vilp70];
        __Vilp70 = ((IData)(1U) + __Vilp70);
    }
    __Vtask_D_CACHE_tb__DOT__check_data__170__actual 
        = vlSelfRef.D_CACHE_tb__DOT__rdata;
    __Vtask_D_CACHE_tb__DOT__check_data__170__expected 
        = __Vtask_D_CACHE_tb__DOT__load__168__expected;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if ((__Vtask_D_CACHE_tb__DOT__check_data__170__expected 
         == __Vtask_D_CACHE_tb__DOT__check_data__170__actual)) {
        VL_WRITEF_NX("[PASS] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__170__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__170__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__170__actual);
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | Expected: 0x%08h Got: 0x%08h\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_data__170__name.data()
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__170__expected
                     , '#',32,__Vtask_D_CACHE_tb__DOT__check_data__170__actual);
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    __Vilp71 = 0U;
    while ((__Vilp71 <= 0x00000032U)) {
        __Vtask_D_CACHE_tb__DOT__check_hit_miss__171__name[__Vilp71] 
            = __Vtask_D_CACHE_tb__DOT__load__168__name
            [__Vilp71];
        __Vilp71 = ((IData)(1U) + __Vilp71);
    }
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__171__got_miss 
        = vlSelfRef.D_CACHE_tb__DOT__saw_miss;
    __Vtask_D_CACHE_tb__DOT__check_hit_miss__171__expect_miss 
        = __Vtask_D_CACHE_tb__DOT__load__168__expect_miss;
    vlSelfRef.D_CACHE_tb__DOT__test_count = ((IData)(1U) 
                                             + vlSelfRef.D_CACHE_tb__DOT__test_count);
    if (((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__171__expect_miss) 
         == (IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__171__got_miss))) {
        if (__Vtask_D_CACHE_tb__DOT__check_hit_miss__171__expect_miss) {
            __Vtemp_38[0U] = 0x20676f74U;
            __Vtemp_38[1U] = 0x20616e64U;
            __Vtemp_38[2U] = 0x63746564U;
            __Vtemp_38[3U] = 0x65787065U;
            __Vtemp_38[4U] = 0x49535320U;
            __Vtemp_38[5U] = 0x0000004dU;
        } else {
            __Vtemp_38[0U] = 0x20676f74U;
            __Vtemp_38[1U] = 0x20616e64U;
            __Vtemp_38[2U] = 0x63746564U;
            __Vtemp_38[3U] = 0x65787065U;
            __Vtemp_38[4U] = 0x48495420U;
            __Vtemp_38[5U] = 0U;
        }
        VL_WRITEF_NX("[PASS] %0d: %s | hit/miss OK (%s)\n",3
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__171__name.data()
                     , '#',168,__Vtemp_38.data());
        vlSelfRef.D_CACHE_tb__DOT__pass_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__pass_count);
    } else {
        VL_WRITEF_NX("[FAIL] %0d: %s | hit/miss WRONG (expected %s, got %s)\n",4
                     , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                     , '#',1601,__Vtask_D_CACHE_tb__DOT__check_hit_miss__171__name.data()
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__171__expect_miss)
                                ? 0x4d495353U : 0x00484954U)
                     , '#',32,((IData)(__Vtask_D_CACHE_tb__DOT__check_hit_miss__171__got_miss)
                                ? 0x4d495353U : 0x00484954U));
        vlSelfRef.D_CACHE_tb__DOT__fail_count = ((IData)(1U) 
                                                 + vlSelfRef.D_CACHE_tb__DOT__fail_count);
    }
    co_await vlSelfRef.__VdlySched.delay(0x0000000000004e20ULL, 
                                         nullptr, "/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 
                                         394);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    VL_WRITEF_NX("\n==============================================\n                Test Summary\n==============================================\nTotal Tests: %0d\nPassed:      %0d\nFailed:      %0d\n",3
                 , '~',32,vlSelfRef.D_CACHE_tb__DOT__test_count
                 , '~',32,vlSelfRef.D_CACHE_tb__DOT__pass_count
                 , '~',32,vlSelfRef.D_CACHE_tb__DOT__fail_count);
    if ((0U == vlSelfRef.D_CACHE_tb__DOT__fail_count)) {
        VL_WRITEF_NX("\n*** ALL TESTS PASSED ***\n",0);
    } else {
        VL_WRITEF_NX("\n*** SOME TESTS FAILED ***\n",0);
    }
    VL_WRITEF_NX("==============================================\n\n",0);
    VL_FINISH_MT("/Users/yatagaclapotk/Desktop/Genel_Calismalar/Mezuniyet/Mezuniyet_Projesi/CPU/TEST_BENCH/D_CACHE_TB/D_CACHE_TB.sv", 407, "");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_return;
}

bool VD_CACHE_tb___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___trigger_anySet__ico\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

bool VD_CACHE_tb___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void VD_CACHE_tb___024root___act_comb__TOP__0(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___act_comb__TOP__0\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_data 
        = (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_cache
                  [(0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                   >> 2U))]);
    vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_data 
        = (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache
                  [(0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                   >> 2U))]);
    vlSelfRef.D_CACHE_tb__DOT__uut__DOT__store_mask 
        = (0x0000000fU & ((0U == (IData)(vlSelfRef.D_CACHE_tb__DOT__cpu_funct3))
                           ? (0x8421U >> (0x0000000cU 
                                          & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                             << 2U)))
                           : ((1U == (IData)(vlSelfRef.D_CACHE_tb__DOT__cpu_funct3))
                               ? (0xc3U >> (4U & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                                  << 1U)))
                               : (- (IData)((2U == (IData)(vlSelfRef.D_CACHE_tb__DOT__cpu_funct3)))))));
    vlSelfRef.D_CACHE_tb__DOT__uut__DOT__lru = (1U 
                                                & (IData)(
                                                          (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache
                                                           [
                                                           (0x0000007fU 
                                                            & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                                               >> 2U))] 
                                                           >> 0x00000038U)));
    vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_tag = 
        (0x007fffffU & (IData)((vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache
                                [(0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                                 >> 2U))] 
                                >> 0x00000020U)));
    vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_valid 
        = (1U & (IData)((vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache
                         [(0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                          >> 2U))] 
                         >> 0x00000039U)));
    vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_tag = 
        (0x007fffffU & (IData)((vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_cache
                                [(0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                                 >> 2U))] 
                                >> 0x00000020U)));
    vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_valid 
        = (1U & (IData)((vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_cache
                         [(0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                          >> 2U))] 
                         >> 0x00000038U)));
    vlSelfRef.D_CACHE_tb__DOT__uut__DOT__victim_dirty 
        = (1U & ((IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__lru)
                  ? (IData)((vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache
                             [(0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                              >> 2U))] 
                             >> 0x00000037U)) : (IData)(
                                                        (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_cache
                                                         [
                                                         (0x0000007fU 
                                                          & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                                             >> 2U))] 
                                                         >> 0x00000037U))));
    vlSelfRef.D_CACHE_tb__DOT__uut__DOT__hit0 = ((IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_valid) 
                                                 & ((vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                                     >> 9U) 
                                                    == vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_tag));
    vlSelfRef.D_CACHE_tb__DOT__uut__DOT__hit = (((IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_valid) 
                                                 & ((vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                                     >> 9U) 
                                                    == vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_tag)) 
                                                | (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__hit0));
    vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall = ((~ 
                                                   ((0U 
                                                     == (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__state)) 
                                                    & (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__hit))) 
                                                  & (IData)(vlSelfRef.D_CACHE_tb__DOT__cpu_req));
}

void VD_CACHE_tb___024root___nba_sequent__TOP__0(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___nba_sequent__TOP__0\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__172__orig_word;
    __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__172__orig_word = 0;
    IData/*31:0*/ __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__172__new_payload;
    __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__172__new_payload = 0;
    CData/*3:0*/ __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__172__mask;
    __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__172__mask = 0;
    IData/*31:0*/ __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__173__orig_word;
    __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__173__orig_word = 0;
    IData/*31:0*/ __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__173__new_payload;
    __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__173__new_payload = 0;
    CData/*3:0*/ __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__173__mask;
    __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__173__mask = 0;
    IData/*31:0*/ __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__174__Vfuncout;
    __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__174__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__174__data_in;
    __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__174__data_in = 0;
    CData/*2:0*/ __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__174__funct;
    __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__174__funct = 0;
    IData/*31:0*/ __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__175__Vfuncout;
    __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__175__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__175__data_in;
    __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__175__data_in = 0;
    CData/*2:0*/ __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__175__funct;
    __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__175__funct = 0;
    CData/*0:0*/ __Vdly__D_CACHE_tb__DOT__mem_ack;
    __Vdly__D_CACHE_tb__DOT__mem_ack = 0;
    CData/*0:0*/ __Vdly__D_CACHE_tb__DOT__mem_ready;
    __Vdly__D_CACHE_tb__DOT__mem_ready = 0;
    IData/*31:0*/ __Vdly__D_CACHE_tb__DOT__mem_cnt;
    __Vdly__D_CACHE_tb__DOT__mem_cnt = 0;
    IData/*31:0*/ __Vdly__D_CACHE_tb__DOT__mem_rdata;
    __Vdly__D_CACHE_tb__DOT__mem_rdata = 0;
    CData/*1:0*/ __Vdly__D_CACHE_tb__DOT__uut__DOT__state;
    __Vdly__D_CACHE_tb__DOT__uut__DOT__state = 0;
    IData/*31:0*/ __VdlyVal__D_CACHE_tb__DOT__mem__v0;
    __VdlyVal__D_CACHE_tb__DOT__mem__v0 = 0;
    SData/*13:0*/ __VdlyDim0__D_CACHE_tb__DOT__mem__v0;
    __VdlyDim0__D_CACHE_tb__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__D_CACHE_tb__DOT__mem__v0;
    __VdlySet__D_CACHE_tb__DOT__mem__v0 = 0;
    CData/*7:0*/ __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v0;
    __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v0 = 0;
    CData/*0:0*/ __VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v0;
    __VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v0 = 0;
    IData/*31:0*/ __VdlyVal__D_CACHE_tb__DOT__uut__DOT__way0_cache__v0;
    __VdlyVal__D_CACHE_tb__DOT__uut__DOT__way0_cache__v0 = 0;
    CData/*7:0*/ __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way0_cache__v0;
    __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way0_cache__v0 = 0;
    CData/*0:0*/ __VdlySet__D_CACHE_tb__DOT__uut__DOT__way0_cache__v0;
    __VdlySet__D_CACHE_tb__DOT__uut__DOT__way0_cache__v0 = 0;
    CData/*7:0*/ __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way0_cache__v1;
    __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way0_cache__v1 = 0;
    IData/*31:0*/ __VdlyVal__D_CACHE_tb__DOT__uut__DOT__way1_cache__v1;
    __VdlyVal__D_CACHE_tb__DOT__uut__DOT__way1_cache__v1 = 0;
    CData/*7:0*/ __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v1;
    __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v1 = 0;
    CData/*0:0*/ __VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v1;
    __VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v1 = 0;
    CData/*7:0*/ __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v2;
    __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v2 = 0;
    CData/*7:0*/ __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v3;
    __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v3 = 0;
    CData/*7:0*/ __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v4;
    __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v4 = 0;
    CData/*0:0*/ __VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v4;
    __VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v4 = 0;
    CData/*7:0*/ __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v5;
    __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v5 = 0;
    CData/*0:0*/ __VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v5;
    __VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v5 = 0;
    QData/*57:0*/ __VdlyVal__D_CACHE_tb__DOT__uut__DOT__way1_cache__v6;
    __VdlyVal__D_CACHE_tb__DOT__uut__DOT__way1_cache__v6 = 0;
    CData/*7:0*/ __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v6;
    __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v6 = 0;
    CData/*0:0*/ __VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v6;
    __VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v6 = 0;
    QData/*56:0*/ __VdlyVal__D_CACHE_tb__DOT__uut__DOT__way0_cache__v2;
    __VdlyVal__D_CACHE_tb__DOT__uut__DOT__way0_cache__v2 = 0;
    CData/*7:0*/ __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way0_cache__v2;
    __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way0_cache__v2 = 0;
    CData/*0:0*/ __VdlySet__D_CACHE_tb__DOT__uut__DOT__way0_cache__v2;
    __VdlySet__D_CACHE_tb__DOT__uut__DOT__way0_cache__v2 = 0;
    CData/*7:0*/ __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v7;
    __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v7 = 0;
    // Body
    __Vdly__D_CACHE_tb__DOT__uut__DOT__state = vlSelfRef.D_CACHE_tb__DOT__uut__DOT__state;
    __VdlySet__D_CACHE_tb__DOT__uut__DOT__way0_cache__v0 = 0U;
    __VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v0 = 0U;
    __VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v1 = 0U;
    __VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v4 = 0U;
    __VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v5 = 0U;
    __VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v6 = 0U;
    __VdlySet__D_CACHE_tb__DOT__uut__DOT__way0_cache__v2 = 0U;
    __Vdly__D_CACHE_tb__DOT__mem_ack = vlSelfRef.D_CACHE_tb__DOT__mem_ack;
    __Vdly__D_CACHE_tb__DOT__mem_ready = vlSelfRef.D_CACHE_tb__DOT__mem_ready;
    __Vdly__D_CACHE_tb__DOT__mem_cnt = vlSelfRef.D_CACHE_tb__DOT__mem_cnt;
    __Vdly__D_CACHE_tb__DOT__mem_rdata = vlSelfRef.D_CACHE_tb__DOT__mem_rdata;
    __VdlySet__D_CACHE_tb__DOT__mem__v0 = 0U;
    __Vdly__D_CACHE_tb__DOT__mem_ack = 0U;
    __Vdly__D_CACHE_tb__DOT__mem_ready = 0U;
    if ((1U & ((IData)(vlSelfRef.D_CACHE_tb__DOT__reset) 
               | (~ (IData)(vlSelfRef.D_CACHE_tb__DOT__mem_req))))) {
        __Vdly__D_CACHE_tb__DOT__mem_cnt = 0U;
    } else {
        __Vdly__D_CACHE_tb__DOT__mem_cnt = ((IData)(1U) 
                                            + vlSelfRef.D_CACHE_tb__DOT__mem_cnt);
        if ((1U == vlSelfRef.D_CACHE_tb__DOT__mem_cnt)) {
            __Vdly__D_CACHE_tb__DOT__mem_cnt = 0U;
            if (vlSelfRef.D_CACHE_tb__DOT__mem_we) {
                vlSelfRef.D_CACHE_tb__DOT__mem_wr_count 
                    = ((IData)(1U) + vlSelfRef.D_CACHE_tb__DOT__mem_wr_count);
                __VdlyVal__D_CACHE_tb__DOT__mem__v0 
                    = vlSelfRef.D_CACHE_tb__DOT__mem_wdata;
                __VdlyDim0__D_CACHE_tb__DOT__mem__v0 
                    = (0x00003fffU & (vlSelfRef.D_CACHE_tb__DOT__memory_addr 
                                      >> 2U));
                __VdlySet__D_CACHE_tb__DOT__mem__v0 = 1U;
                __Vdly__D_CACHE_tb__DOT__mem_ack = 1U;
            } else {
                vlSelfRef.D_CACHE_tb__DOT__mem_rd_count 
                    = ((IData)(1U) + vlSelfRef.D_CACHE_tb__DOT__mem_rd_count);
                __Vdly__D_CACHE_tb__DOT__mem_rdata 
                    = vlSelfRef.D_CACHE_tb__DOT__mem
                    [(0x00003fffU & (vlSelfRef.D_CACHE_tb__DOT__memory_addr 
                                     >> 2U))];
                __Vdly__D_CACHE_tb__DOT__mem_ready = 1U;
            }
        }
    }
    vlSelfRef.D_CACHE_tb__DOT__mem_cnt = __Vdly__D_CACHE_tb__DOT__mem_cnt;
    if (__VdlySet__D_CACHE_tb__DOT__mem__v0) {
        vlSelfRef.D_CACHE_tb__DOT__mem[__VdlyDim0__D_CACHE_tb__DOT__mem__v0] 
            = __VdlyVal__D_CACHE_tb__DOT__mem__v0;
    }
    if (vlSelfRef.D_CACHE_tb__DOT__reset) {
        vlSelfRef.D_CACHE_tb__DOT__uut__DOT__miss = 0U;
        vlSelfRef.D_CACHE_tb__DOT__mem_we = 0U;
        vlSelfRef.D_CACHE_tb__DOT__mem_req = 0U;
        vlSelfRef.D_CACHE_tb__DOT__uut__DOT__cpu_bff_addr = 0U;
        __Vdly__D_CACHE_tb__DOT__uut__DOT__state = 0U;
    } else if ((0U == (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__state))) {
        if (vlSelfRef.D_CACHE_tb__DOT__cpu_req) {
            vlSelfRef.D_CACHE_tb__DOT__uut__DOT__cpu_bff_addr 
                = vlSelfRef.D_CACHE_tb__DOT__cpu_addr;
            if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__hit) {
                if (vlSelfRef.D_CACHE_tb__DOT__cpu_we) {
                    if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__hit0) {
                        __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__172__mask 
                            = vlSelfRef.D_CACHE_tb__DOT__uut__DOT__store_mask;
                        __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__172__new_payload 
                            = vlSelfRef.D_CACHE_tb__DOT__data_in_cpu;
                        __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v0 
                            = (0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                              >> 2U));
                        __VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v0 = 1U;
                        __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__172__orig_word 
                            = vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_data;
                        vlSelfRef.D_CACHE_tb__DOT__uut__DOT____VlemCall_0__apply_store 
                            = ((0xffff0000U & vlSelfRef.D_CACHE_tb__DOT__uut__DOT____VlemCall_0__apply_store) 
                               | ((0x0000ff00U & ((
                                                   (2U 
                                                    & (IData)(__Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__172__mask))
                                                    ? 
                                                   (__Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__172__new_payload 
                                                    >> 8U)
                                                    : 
                                                   (__Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__172__orig_word 
                                                    >> 8U)) 
                                                  << 8U)) 
                                  | (0x000000ffU & 
                                     ((1U & (IData)(__Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__172__mask))
                                       ? __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__172__new_payload
                                       : __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__172__orig_word))));
                        vlSelfRef.D_CACHE_tb__DOT__uut__DOT____VlemCall_0__apply_store 
                            = ((0x0000ffffU & vlSelfRef.D_CACHE_tb__DOT__uut__DOT____VlemCall_0__apply_store) 
                               | (((0x0000ff00U & (
                                                   ((8U 
                                                     & (IData)(__Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__172__mask))
                                                     ? 
                                                    (__Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__172__new_payload 
                                                     >> 0x18U)
                                                     : 
                                                    (__Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__172__orig_word 
                                                     >> 0x18U)) 
                                                   << 8U)) 
                                   | (0x000000ffU & 
                                      ((4U & (IData)(__Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__172__mask))
                                        ? (__Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__172__new_payload 
                                           >> 0x10U)
                                        : (__Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__172__orig_word 
                                           >> 0x10U)))) 
                                  << 0x00000010U));
                        __VdlyVal__D_CACHE_tb__DOT__uut__DOT__way0_cache__v0 
                            = vlSelfRef.D_CACHE_tb__DOT__uut__DOT____VlemCall_0__apply_store;
                        __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way0_cache__v0 
                            = (0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                              >> 2U));
                        __VdlySet__D_CACHE_tb__DOT__uut__DOT__way0_cache__v0 = 1U;
                        __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way0_cache__v1 
                            = (0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                              >> 2U));
                    } else {
                        __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__173__mask 
                            = vlSelfRef.D_CACHE_tb__DOT__uut__DOT__store_mask;
                        __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__173__new_payload 
                            = vlSelfRef.D_CACHE_tb__DOT__data_in_cpu;
                        __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__173__orig_word 
                            = vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_data;
                        vlSelfRef.D_CACHE_tb__DOT__uut__DOT____VlemCall_1__apply_store 
                            = ((0xffff0000U & vlSelfRef.D_CACHE_tb__DOT__uut__DOT____VlemCall_1__apply_store) 
                               | ((0x0000ff00U & ((
                                                   (2U 
                                                    & (IData)(__Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__173__mask))
                                                    ? 
                                                   (__Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__173__new_payload 
                                                    >> 8U)
                                                    : 
                                                   (__Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__173__orig_word 
                                                    >> 8U)) 
                                                  << 8U)) 
                                  | (0x000000ffU & 
                                     ((1U & (IData)(__Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__173__mask))
                                       ? __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__173__new_payload
                                       : __Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__173__orig_word))));
                        vlSelfRef.D_CACHE_tb__DOT__uut__DOT____VlemCall_1__apply_store 
                            = ((0x0000ffffU & vlSelfRef.D_CACHE_tb__DOT__uut__DOT____VlemCall_1__apply_store) 
                               | (((0x0000ff00U & (
                                                   ((8U 
                                                     & (IData)(__Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__173__mask))
                                                     ? 
                                                    (__Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__173__new_payload 
                                                     >> 0x18U)
                                                     : 
                                                    (__Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__173__orig_word 
                                                     >> 0x18U)) 
                                                   << 8U)) 
                                   | (0x000000ffU & 
                                      ((4U & (IData)(__Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__173__mask))
                                        ? (__Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__173__new_payload 
                                           >> 0x10U)
                                        : (__Vfunc_D_CACHE_tb__DOT__uut__DOT__apply_store__173__orig_word 
                                           >> 0x10U)))) 
                                  << 0x00000010U));
                        __VdlyVal__D_CACHE_tb__DOT__uut__DOT__way1_cache__v1 
                            = vlSelfRef.D_CACHE_tb__DOT__uut__DOT____VlemCall_1__apply_store;
                        __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v1 
                            = (0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                              >> 2U));
                        __VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v1 = 1U;
                        __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v2 
                            = (0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                              >> 2U));
                        __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v3 
                            = (0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                              >> 2U));
                    }
                } else if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__hit0) {
                    __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__174__funct 
                        = vlSelfRef.D_CACHE_tb__DOT__cpu_funct3;
                    __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__174__data_in 
                        = VL_SHIFTR_III(32,32,32, vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_data, 
                                        (0x00000018U 
                                         & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                            << 3U)));
                    vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__byte_payload 
                        = (0x000000ffU & __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__174__data_in);
                    __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v4 
                        = (0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                          >> 2U));
                    __VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v4 = 1U;
                    vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__half_payload 
                        = (0x0000ffffU & __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__174__data_in);
                    __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__174__Vfuncout 
                        = ((4U & (IData)(__Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__174__funct))
                            ? ((2U & (IData)(__Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__174__funct))
                                ? __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__174__data_in
                                : ((1U & (IData)(__Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__174__funct))
                                    ? (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__half_payload)
                                    : (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__byte_payload)))
                            : ((2U & (IData)(__Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__174__funct))
                                ? __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__174__data_in
                                : ((1U & (IData)(__Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__174__funct))
                                    ? (((- (IData)(
                                                   (1U 
                                                    & ((IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__half_payload) 
                                                       >> 0x0fU)))) 
                                        << 0x00000010U) 
                                       | (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__half_payload))
                                    : (((- (IData)(
                                                   (1U 
                                                    & ((IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__byte_payload) 
                                                       >> 7U)))) 
                                        << 8U) | (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__byte_payload)))));
                    vlSelfRef.D_CACHE_tb__DOT__data_out_cpu 
                        = __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__174__Vfuncout;
                } else {
                    __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__175__funct 
                        = vlSelfRef.D_CACHE_tb__DOT__cpu_funct3;
                    __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__175__data_in 
                        = VL_SHIFTR_III(32,32,32, vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_data, 
                                        (0x00000018U 
                                         & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                            << 3U)));
                    vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__byte_payload 
                        = (0x000000ffU & __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__175__data_in);
                    __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v5 
                        = (0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                          >> 2U));
                    __VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v5 = 1U;
                    vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__half_payload 
                        = (0x0000ffffU & __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__175__data_in);
                    __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__175__Vfuncout 
                        = ((4U & (IData)(__Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__175__funct))
                            ? ((2U & (IData)(__Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__175__funct))
                                ? __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__175__data_in
                                : ((1U & (IData)(__Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__175__funct))
                                    ? (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__half_payload)
                                    : (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__byte_payload)))
                            : ((2U & (IData)(__Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__175__funct))
                                ? __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__175__data_in
                                : ((1U & (IData)(__Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__175__funct))
                                    ? (((- (IData)(
                                                   (1U 
                                                    & ((IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__half_payload) 
                                                       >> 0x0fU)))) 
                                        << 0x00000010U) 
                                       | (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__half_payload))
                                    : (((- (IData)(
                                                   (1U 
                                                    & ((IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__byte_payload) 
                                                       >> 7U)))) 
                                        << 8U) | (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__byte_payload)))));
                    vlSelfRef.D_CACHE_tb__DOT__data_out_cpu 
                        = __Vfunc_D_CACHE_tb__DOT__uut__DOT__aligned_wdata__175__Vfuncout;
                }
            } else if (((IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__victim_dirty) 
                        & ((IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__lru)
                            ? (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_valid)
                            : (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_valid)))) {
                vlSelfRef.D_CACHE_tb__DOT__memory_addr 
                    = ((((IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__lru)
                          ? vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_tag
                          : vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_tag) 
                        << 9U) | (0x000001fcU & vlSelfRef.D_CACHE_tb__DOT__cpu_addr));
                __Vdly__D_CACHE_tb__DOT__uut__DOT__state = 3U;
                vlSelfRef.D_CACHE_tb__DOT__mem_req = 1U;
                vlSelfRef.D_CACHE_tb__DOT__mem_we = 1U;
                vlSelfRef.D_CACHE_tb__DOT__mem_wdata 
                    = ((IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__lru)
                        ? vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_data
                        : vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_data);
            } else {
                vlSelfRef.D_CACHE_tb__DOT__memory_addr 
                    = vlSelfRef.D_CACHE_tb__DOT__cpu_addr;
                __Vdly__D_CACHE_tb__DOT__uut__DOT__state = 1U;
                vlSelfRef.D_CACHE_tb__DOT__mem_req = 1U;
                vlSelfRef.D_CACHE_tb__DOT__mem_we = 0U;
            }
        }
    } else if ((3U == (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__state))) {
        if (vlSelfRef.D_CACHE_tb__DOT__mem_ack) {
            vlSelfRef.D_CACHE_tb__DOT__mem_we = 0U;
            vlSelfRef.D_CACHE_tb__DOT__memory_addr 
                = (0xfffffffcU & vlSelfRef.D_CACHE_tb__DOT__cpu_addr);
            __Vdly__D_CACHE_tb__DOT__uut__DOT__state = 1U;
        }
    } else if ((1U == (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__state))) {
        if (vlSelfRef.D_CACHE_tb__DOT__mem_ready) {
            __Vdly__D_CACHE_tb__DOT__uut__DOT__state = 2U;
            vlSelfRef.D_CACHE_tb__DOT__mem_req = 0U;
            if (vlSelfRef.D_CACHE_tb__DOT__uut__DOT__lru) {
                __VdlyVal__D_CACHE_tb__DOT__uut__DOT__way1_cache__v6 
                    = (0x0200000000000000ULL | (((QData)((IData)(
                                                                 (1U 
                                                                  & (~ (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__lru))))) 
                                                 << 0x00000038U) 
                                                | (((QData)((IData)(
                                                                    (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                                                     >> 9U))) 
                                                    << 0x00000020U) 
                                                   | (QData)((IData)(vlSelfRef.D_CACHE_tb__DOT__mem_rdata)))));
                __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v6 
                    = (0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                      >> 2U));
                __VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v6 = 1U;
            } else {
                __VdlyVal__D_CACHE_tb__DOT__uut__DOT__way0_cache__v2 
                    = (0x0100000000000000ULL | (((QData)((IData)(
                                                                 (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                                                  >> 9U))) 
                                                 << 0x00000020U) 
                                                | (QData)((IData)(vlSelfRef.D_CACHE_tb__DOT__mem_rdata))));
                __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way0_cache__v2 
                    = (0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                      >> 2U));
                __VdlySet__D_CACHE_tb__DOT__uut__DOT__way0_cache__v2 = 1U;
                __VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v7 
                    = (0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                      >> 2U));
            }
        }
    } else if ((2U == (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__state))) {
        vlSelfRef.D_CACHE_tb__DOT__uut__DOT__miss = 0U;
        vlSelfRef.D_CACHE_tb__DOT__mem_req = 0U;
        __Vdly__D_CACHE_tb__DOT__uut__DOT__state = 0U;
    }
    vlSelfRef.D_CACHE_tb__DOT__mem_ack = __Vdly__D_CACHE_tb__DOT__mem_ack;
    vlSelfRef.D_CACHE_tb__DOT__mem_ready = __Vdly__D_CACHE_tb__DOT__mem_ready;
    vlSelfRef.D_CACHE_tb__DOT__mem_rdata = __Vdly__D_CACHE_tb__DOT__mem_rdata;
    vlSelfRef.D_CACHE_tb__DOT__uut__DOT__state = __Vdly__D_CACHE_tb__DOT__uut__DOT__state;
    if (__VdlySet__D_CACHE_tb__DOT__uut__DOT__way0_cache__v0) {
        vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_cache[__VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way0_cache__v0] 
            = ((0x01ffffff00000000ULL & vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_cache
                [__VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way0_cache__v0]) 
               | (IData)((IData)(__VdlyVal__D_CACHE_tb__DOT__uut__DOT__way0_cache__v0)));
        vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_cache[__VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way0_cache__v1] 
            = (0x0080000000000000ULL | vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_cache
               [__VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way0_cache__v1]);
    }
    if (__VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v0) {
        vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache[__VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v0] 
            = (0x0100000000000000ULL | vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache
               [__VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v0]);
    }
    if (__VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v1) {
        vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache[__VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v1] 
            = ((0x03ffffff00000000ULL & vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache
                [__VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v1]) 
               | (IData)((IData)(__VdlyVal__D_CACHE_tb__DOT__uut__DOT__way1_cache__v1)));
        vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache[__VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v2] 
            = (0x0080000000000000ULL | vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache
               [__VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v2]);
        vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache[__VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v3] 
            = (0x02ffffffffffffffULL & vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache
               [__VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v3]);
    }
    if (__VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v4) {
        vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache[__VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v4] 
            = (0x0100000000000000ULL | vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache
               [__VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v4]);
    }
    if (__VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v5) {
        vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache[__VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v5] 
            = (0x02ffffffffffffffULL & vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache
               [__VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v5]);
    }
    if (__VdlySet__D_CACHE_tb__DOT__uut__DOT__way1_cache__v6) {
        vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache[__VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v6] 
            = __VdlyVal__D_CACHE_tb__DOT__uut__DOT__way1_cache__v6;
    }
    if (__VdlySet__D_CACHE_tb__DOT__uut__DOT__way0_cache__v2) {
        vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_cache[__VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way0_cache__v2] 
            = __VdlyVal__D_CACHE_tb__DOT__uut__DOT__way0_cache__v2;
        vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache[__VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v7] 
            = (0x0100000000000000ULL | vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache
               [__VdlyDim0__D_CACHE_tb__DOT__uut__DOT__way1_cache__v7]);
    }
}
