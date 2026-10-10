// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "VD_CACHE_tb__Syms.h"


void VD_CACHE_tb___024root__trace_chg_0_sub_0(VD_CACHE_tb___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void VD_CACHE_tb___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root__trace_chg_0\n"); );
    // Body
    VD_CACHE_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VD_CACHE_tb___024root*>(voidSelf);
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    VD_CACHE_tb___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void VD_CACHE_tb___024root__trace_chg_0_sub_0(VD_CACHE_tb___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root__trace_chg_0_sub_0\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 0);
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[1U] 
                      | vlSelfRef.__Vm_traceActivity[2U])))) {
        bufp->chgBit(oldp+0,(vlSelfRef.D_CACHE_tb__DOT__reset));
        bufp->chgIData(oldp+1,(vlSelfRef.D_CACHE_tb__DOT__data_in_cpu),32);
        bufp->chgIData(oldp+2,(vlSelfRef.D_CACHE_tb__DOT__cpu_addr),32);
        bufp->chgCData(oldp+3,(vlSelfRef.D_CACHE_tb__DOT__cpu_funct3),3);
        bufp->chgBit(oldp+4,(vlSelfRef.D_CACHE_tb__DOT__cpu_we));
        bufp->chgBit(oldp+5,(vlSelfRef.D_CACHE_tb__DOT__cpu_req));
        bufp->chgBit(oldp+6,(vlSelfRef.D_CACHE_tb__DOT__saw_miss));
        bufp->chgIData(oldp+7,(vlSelfRef.D_CACHE_tb__DOT__rdata),32);
        bufp->chgIData(oldp+8,(vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr),32);
        bufp->chgCData(oldp+9,(vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3),3);
        bufp->chgBit(oldp+10,(vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we));
        bufp->chgIData(oldp+11,(vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata),32);
        bufp->chgIData(oldp+12,((vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                 >> 9U)),23);
        bufp->chgCData(oldp+13,((0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                                >> 2U))),7);
    }
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[1U] 
                      | vlSelfRef.__Vm_traceActivity[4U])))) {
        bufp->chgBit(oldp+14,(vlSelfRef.D_CACHE_tb__DOT__mem_ack));
        bufp->chgBit(oldp+15,(vlSelfRef.D_CACHE_tb__DOT__mem_ready));
        bufp->chgIData(oldp+16,(vlSelfRef.D_CACHE_tb__DOT__mem_rdata),32);
        bufp->chgIData(oldp+17,(vlSelfRef.D_CACHE_tb__DOT__mem_cnt),32);
        bufp->chgIData(oldp+18,(vlSelfRef.D_CACHE_tb__DOT__mem_rd_count),32);
        bufp->chgIData(oldp+19,(vlSelfRef.D_CACHE_tb__DOT__mem_wr_count),32);
    }
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[3U] 
                      | vlSelfRef.__Vm_traceActivity[5U])))) {
        bufp->chgCData(oldp+20,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__store_mask),4);
        bufp->chgIData(oldp+21,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_data),32);
        bufp->chgIData(oldp+22,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_data),32);
        bufp->chgIData(oldp+23,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_tag),23);
        bufp->chgIData(oldp+24,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_tag),23);
        bufp->chgBit(oldp+25,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__lru));
        bufp->chgBit(oldp+26,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_valid));
        bufp->chgBit(oldp+27,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_valid));
        bufp->chgBit(oldp+28,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__hit0));
        bufp->chgBit(oldp+29,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__hit));
        bufp->chgBit(oldp+30,(((IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__lru)
                                ? (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_valid)
                                : (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_valid))));
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[4U]))) {
        bufp->chgIData(oldp+31,(vlSelfRef.D_CACHE_tb__DOT__memory_addr),32);
        bufp->chgIData(oldp+32,(vlSelfRef.D_CACHE_tb__DOT__mem_wdata),32);
        bufp->chgBit(oldp+33,(vlSelfRef.D_CACHE_tb__DOT__mem_req));
        bufp->chgBit(oldp+34,(vlSelfRef.D_CACHE_tb__DOT__mem_we));
        bufp->chgIData(oldp+35,(vlSelfRef.D_CACHE_tb__DOT__data_out_cpu),32);
        bufp->chgCData(oldp+36,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__state),2);
        bufp->chgBit(oldp+37,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__miss));
        bufp->chgIData(oldp+38,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__cpu_bff_addr),32);
    }
    bufp->chgBit(oldp+39,(vlSelfRef.D_CACHE_tb__DOT__clk));
    bufp->chgBit(oldp+40,(((~ ((0U == (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__state)) 
                               & (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__hit))) 
                           & (IData)(vlSelfRef.D_CACHE_tb__DOT__cpu_req))));
    bufp->chgIData(oldp+41,(vlSelfRef.D_CACHE_tb__DOT__pass_count),32);
    bufp->chgIData(oldp+42,(vlSelfRef.D_CACHE_tb__DOT__fail_count),32);
    bufp->chgIData(oldp+43,(vlSelfRef.D_CACHE_tb__DOT__test_count),32);
    bufp->chgIData(oldp+44,(vlSelfRef.D_CACHE_tb__DOT__store__Vstatic__lane),32);
    bufp->chgIData(oldp+45,(vlSelfRef.D_CACHE_tb__DOT__clean_evict__DOT__wr_before),32);
    bufp->chgIData(oldp+46,(vlSelfRef.D_CACHE_tb__DOT__init_cache__DOT__i),32);
    bufp->chgBit(oldp+47,((1U & (IData)((vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_cache
                                         [(0x0000007fU 
                                           & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                              >> 2U))] 
                                         >> 0x00000037U)))));
    bufp->chgBit(oldp+48,((1U & (IData)((vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache
                                         [(0x0000007fU 
                                           & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                              >> 2U))] 
                                         >> 0x00000037U)))));
    bufp->chgBit(oldp+49,(((IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_valid) 
                           & ((vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                               >> 9U) == vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_tag))));
    bufp->chgBit(oldp+50,((1U & ((IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__lru)
                                  ? (IData)((vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache
                                             [(0x0000007fU 
                                               & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                                  >> 2U))] 
                                             >> 0x00000037U))
                                  : (IData)((vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_cache
                                             [(0x0000007fU 
                                               & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                                  >> 2U))] 
                                             >> 0x00000037U))))));
    bufp->chgCData(oldp+51,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__byte_payload),8);
    bufp->chgSData(oldp+52,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__half_payload),16);
}

void VD_CACHE_tb___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root__trace_cleanup\n"); );
    // Body
    VD_CACHE_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VD_CACHE_tb___024root*>(voidSelf);
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[3U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[4U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[5U] = 0U;
}
