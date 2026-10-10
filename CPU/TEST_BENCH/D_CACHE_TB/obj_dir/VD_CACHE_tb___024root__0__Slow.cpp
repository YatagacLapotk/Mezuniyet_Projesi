// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VD_CACHE_tb.h for the primary calling header

#include "VD_CACHE_tb__pch.h"

void VD_CACHE_tb___024root___timing_ready(VD_CACHE_tb___024root* vlSelf);

VL_ATTR_COLD void VD_CACHE_tb___024root___eval_static(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_static\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    {
        // Inlined CFunc: _eval_static__TOP
        vlSelfRef.D_CACHE_tb__DOT__pass_count = 0U;
        vlSelfRef.D_CACHE_tb__DOT__fail_count = 0U;
        vlSelfRef.D_CACHE_tb__DOT__test_count = 0U;
        const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
        vlSelfRef.D_CACHE_tb__DOT__init_cache__DOT__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11028004109948061237ull);
        vlSelfRef.D_CACHE_tb__DOT__store__Vstatic__lane = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1513411215528733224ull);
        vlSelfRef.D_CACHE_tb__DOT__clean_evict__DOT__wr_before = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11426066248604468234ull);
        vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__byte_payload = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5709912842140885198ull);
        vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__half_payload = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 2000559647190028546ull);
    }
    vlSelfRef.__Vtrigprevexpr___TOP__D_CACHE_tb__DOT__clk__0 
        = vlSelfRef.D_CACHE_tb__DOT__clk;
    VD_CACHE_tb___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VD_CACHE_tb___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool VD_CACHE_tb___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);
void VD_CACHE_tb___024root___act_comb__TOP__0(VD_CACHE_tb___024root* vlSelf);

VL_ATTR_COLD bool VD_CACHE_tb___024root___eval_stl(VD_CACHE_tb___024root* vlSelf, CData/*0:0*/ firstIteration) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_stl\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(firstIteration)));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VD_CACHE_tb___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = VD_CACHE_tb___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        {
            // Inlined CFunc: _eval_body__stl
            if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
                VD_CACHE_tb___024root___act_comb__TOP__0(vlSelf);
                {
                    // Inlined CFunc: __Vm_traceActivitySetAll
                    vlSelfRef.__Vm_traceActivity[0U] = 1U;
                    vlSelfRef.__Vm_traceActivity[1U] = 1U;
                    vlSelfRef.__Vm_traceActivity[2U] = 1U;
                    vlSelfRef.__Vm_traceActivity[3U] = 1U;
                    vlSelfRef.__Vm_traceActivity[4U] = 1U;
                    vlSelfRef.__Vm_traceActivity[5U] = 1U;
                }
            }
        }
    }
    return (__VstlExecute);
}

VL_ATTR_COLD void VD_CACHE_tb___024root___eval_dump_triggers__stl(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_dump_triggers__stl\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    VD_CACHE_tb___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VD_CACHE_tb___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

VL_ATTR_COLD void VD_CACHE_tb___024root___eval_dump_triggers__ico(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_dump_triggers__ico\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    VD_CACHE_tb___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VD_CACHE_tb___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

VL_ATTR_COLD void VD_CACHE_tb___024root___eval_dump_triggers__act(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_dump_triggers__act\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    VD_CACHE_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
}

VL_ATTR_COLD void VD_CACHE_tb___024root___eval_dump_triggers__nba(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_dump_triggers__nba\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    VD_CACHE_tb___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
}

VL_ATTR_COLD void VD_CACHE_tb___024root___eval_dump_triggers__obs(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_dump_triggers__obs\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void VD_CACHE_tb___024root___eval_dump_triggers__react(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_dump_triggers__react\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void VD_CACHE_tb___024root___eval_final(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___eval_final\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VD_CACHE_tb___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(VD_CACHE_tb___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool VD_CACHE_tb___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___trigger_anySet__stl\n"); );
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

bool VD_CACHE_tb___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void VD_CACHE_tb___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(VD_CACHE_tb___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool VD_CACHE_tb___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void VD_CACHE_tb___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(VD_CACHE_tb___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge D_CACHE_tb.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VD_CACHE_tb___024root___ctor_var_reset(VD_CACHE_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root___ctor_var_reset\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->D_CACHE_tb__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18010623300926121737ull);
    vlSelf->D_CACHE_tb__DOT__reset = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5739312832251884658ull);
    vlSelf->D_CACHE_tb__DOT__mem_ack = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6351293662811135700ull);
    vlSelf->D_CACHE_tb__DOT__mem_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15334855337480586052ull);
    vlSelf->D_CACHE_tb__DOT__mem_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2104949387723598026ull);
    vlSelf->D_CACHE_tb__DOT__memory_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9670840680068628270ull);
    vlSelf->D_CACHE_tb__DOT__mem_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9829892321548827128ull);
    vlSelf->D_CACHE_tb__DOT__mem_req = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16345874016260854546ull);
    vlSelf->D_CACHE_tb__DOT__mem_we = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8587728765638701299ull);
    vlSelf->D_CACHE_tb__DOT__data_in_cpu = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8579594975761747675ull);
    vlSelf->D_CACHE_tb__DOT__cpu_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10839518176674694752ull);
    vlSelf->D_CACHE_tb__DOT__cpu_funct3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 10438854252519066572ull);
    vlSelf->D_CACHE_tb__DOT__cpu_we = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8078021307322721319ull);
    vlSelf->D_CACHE_tb__DOT__cpu_req = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 534765894963127437ull);
    vlSelf->D_CACHE_tb__DOT__data_out_cpu = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15893597169522968954ull);
    for (int __Vi0 = 0; __Vi0 < 16384; ++__Vi0) {
        vlSelf->D_CACHE_tb__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15593811008168778986ull);
    }
    vlSelf->D_CACHE_tb__DOT__mem_cnt = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16894281899022343026ull);
    vlSelf->D_CACHE_tb__DOT__mem_rd_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1340570793744278043ull);
    vlSelf->D_CACHE_tb__DOT__mem_wr_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17718441759105146194ull);
    vlSelf->D_CACHE_tb__DOT__saw_miss = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2292976130495538731ull);
    vlSelf->D_CACHE_tb__DOT__rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17994251166263690921ull);
    vlSelf->D_CACHE_tb__DOT__access__Vstatic__addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12342959223236802187ull);
    vlSelf->D_CACHE_tb__DOT__access__Vstatic__f3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 11673915325136862958ull);
    vlSelf->D_CACHE_tb__DOT__access__Vstatic__we = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10227533350861572035ull);
    vlSelf->D_CACHE_tb__DOT__access__Vstatic__wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2177076687925154313ull);
    vlSelf->D_CACHE_tb__DOT__uut__DOT__stall = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15609734853488706549ull);
    vlSelf->D_CACHE_tb__DOT__uut__DOT__state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 7666706287642144399ull);
    vlSelf->D_CACHE_tb__DOT__uut__DOT__store_mask = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 2901815060138492042ull);
    for (int __Vi0 = 0; __Vi0 < 129; ++__Vi0) {
        vlSelf->D_CACHE_tb__DOT__uut__DOT__way0_cache[__Vi0] = VL_SCOPED_RAND_RESET_Q(57, __VscopeHash, 194063165712240864ull);
    }
    for (int __Vi0 = 0; __Vi0 < 129; ++__Vi0) {
        vlSelf->D_CACHE_tb__DOT__uut__DOT__way1_cache[__Vi0] = VL_SCOPED_RAND_RESET_Q(58, __VscopeHash, 17973380797032682957ull);
    }
    vlSelf->D_CACHE_tb__DOT__uut__DOT__way0_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11810794593711927221ull);
    vlSelf->D_CACHE_tb__DOT__uut__DOT__way1_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6498435343111329632ull);
    vlSelf->D_CACHE_tb__DOT__uut__DOT__way0_tag = VL_SCOPED_RAND_RESET_I(23, __VscopeHash, 14039885618905835264ull);
    vlSelf->D_CACHE_tb__DOT__uut__DOT__way1_tag = VL_SCOPED_RAND_RESET_I(23, __VscopeHash, 2920665171008724866ull);
    vlSelf->D_CACHE_tb__DOT__uut__DOT__lru = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17974273653977963765ull);
    vlSelf->D_CACHE_tb__DOT__uut__DOT__way0_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16361535379546537561ull);
    vlSelf->D_CACHE_tb__DOT__uut__DOT__way1_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16051942909807779685ull);
    vlSelf->D_CACHE_tb__DOT__uut__DOT__dirty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3805582011584528193ull);
    vlSelf->D_CACHE_tb__DOT__uut__DOT__hit0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6762394179204061128ull);
    vlSelf->D_CACHE_tb__DOT__uut__DOT__hit = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6783861668669267323ull);
    vlSelf->D_CACHE_tb__DOT__uut__DOT__miss = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12008622061065669970ull);
    vlSelf->D_CACHE_tb__DOT__uut__DOT__cpu_bff_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 110951159433722823ull);
    vlSelf->D_CACHE_tb__DOT__uut__DOT__data_temp = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16926586557271981980ull);
    vlSelf->D_CACHE_tb__DOT__uut__DOT__d_cache = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6943909214436024132ull);
    vlSelf->D_CACHE_tb__DOT__uut__DOT__victim_dirty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9510661623358079314ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__D_CACHE_tb__DOT__clk__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
    for (int __Vi0 = 0; __Vi0 < 6; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
