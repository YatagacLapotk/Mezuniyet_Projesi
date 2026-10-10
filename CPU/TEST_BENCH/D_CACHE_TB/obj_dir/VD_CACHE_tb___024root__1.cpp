// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VD_CACHE_tb.h for the primary calling header

#include "VD_CACHE_tb__pch.h"

void VD_CACHE_tb___024root___nba_sequent__TOP__0(VD_CACHE_tb___024root* vlSelf);

void VD_CACHE_tb___024root___eval_body__nba(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_body__nba\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        VD_CACHE_tb___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[4U] = 1U;
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        {
            // Inlined CFunc: _nba_comb__TOP__0
            vlSelfRef.D_CACHE_tb__DOT__uut__DOT__store_mask 
                = (0x0000000fU & ((0U == (IData)(vlSelfRef.D_CACHE_tb__DOT__cpu_funct3))
                                   ? (0x8421U >> (0x0000000cU 
                                                  & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                                     << 2U)))
                                   : ((1U == (IData)(vlSelfRef.D_CACHE_tb__DOT__cpu_funct3))
                                       ? (0xc3U >> 
                                          (4U & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                                 << 1U)))
                                       : (- (IData)(
                                                    (2U 
                                                     == (IData)(vlSelfRef.D_CACHE_tb__DOT__cpu_funct3)))))));
            vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_data 
                = (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_cache
                          [(0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                           >> 2U))]);
            vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_tag 
                = (0x007fffffU & (IData)((vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_cache
                                          [(0x0000007fU 
                                            & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                               >> 2U))] 
                                          >> 0x00000020U)));
            vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_valid 
                = (1U & (IData)((vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_cache
                                 [(0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                                  >> 2U))] 
                                 >> 0x00000038U)));
            vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_data 
                = (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache
                          [(0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                           >> 2U))]);
            vlSelfRef.D_CACHE_tb__DOT__uut__DOT__lru 
                = (1U & (IData)((vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache
                                 [(0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                                  >> 2U))] 
                                 >> 0x00000038U)));
            vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_tag 
                = (0x007fffffU & (IData)((vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache
                                          [(0x0000007fU 
                                            & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                               >> 2U))] 
                                          >> 0x00000020U)));
            vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_valid 
                = (1U & (IData)((vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache
                                 [(0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                                  >> 2U))] 
                                 >> 0x00000039U)));
            vlSelfRef.D_CACHE_tb__DOT__uut__DOT__hit0 
                = ((IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_valid) 
                   & ((vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                       >> 9U) == vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_tag));
            vlSelfRef.D_CACHE_tb__DOT__uut__DOT__victim_dirty 
                = (1U & ((IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__lru)
                          ? (IData)((vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache
                                     [(0x0000007fU 
                                       & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                          >> 2U))] 
                                     >> 0x00000037U))
                          : (IData)((vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_cache
                                     [(0x0000007fU 
                                       & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                          >> 2U))] 
                                     >> 0x00000037U))));
            vlSelfRef.D_CACHE_tb__DOT__uut__DOT__hit 
                = (((IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_valid) 
                    & ((vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                        >> 9U) == vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_tag)) 
                   | (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__hit0));
            vlSelfRef.D_CACHE_tb__DOT__uut__DOT__stall 
                = ((~ ((0U == (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__state)) 
                       & (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__hit))) 
                   & (IData)(vlSelfRef.D_CACHE_tb__DOT__cpu_req));
        }
        vlSelfRef.__Vm_traceActivity[5U] = 1U;
    }
}

void VD_CACHE_tb___024root___timing_ready(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___timing_ready\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h883832f6__0.ready("@(posedge D_CACHE_tb.clk)");
    }
}

void VD_CACHE_tb___024root___timing_resume(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___timing_resume\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_h883832f6__0.moveToResumeQueue(
                                                          "@(posedge D_CACHE_tb.clk)");
    vlSelfRef.__VtrigSched_h883832f6__0.resume("@(posedge D_CACHE_tb.clk)");
    if ((2ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void VD_CACHE_tb___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

void VD_CACHE_tb___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

void VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0(VD_CACHE_tb___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root____VbeforeTrig_h883832f6__0\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((IData)(vlSelfRef.D_CACHE_tb__DOT__clk) 
                                  & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__D_CACHE_tb__DOT__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__D_CACHE_tb__DOT__clk__0 
        = vlSelfRef.D_CACHE_tb__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h883832f6__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void VD_CACHE_tb___024root___eval_debug_assertions(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_debug_assertions\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
