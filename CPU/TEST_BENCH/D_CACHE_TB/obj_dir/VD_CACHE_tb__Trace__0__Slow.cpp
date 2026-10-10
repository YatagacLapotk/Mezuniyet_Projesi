// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "VD_CACHE_tb__Syms.h"


VL_ATTR_COLD void VD_CACHE_tb___024root__trace_init_sub__TOP__0(VD_CACHE_tb___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root__trace_init_sub__TOP__0\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const int c = vlSymsp->__Vm_baseCode;
    VL_TRACE_PUSH_PREFIX(tracep, "D_CACHE_tb", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BIT(tracep,c+39,0,"clk",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+0,0,"reset",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+14,0,"mem_ack",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+15,0,"mem_ready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+16,0,"mem_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+31,0,"memory_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+32,0,"mem_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BIT(tracep,c+33,0,"mem_req",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+34,0,"mem_we",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+1,0,"data_in_cpu",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+2,0,"cpu_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+3,0,"cpu_funct3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 2,0);
    VL_TRACE_DECL_BIT(tracep,c+4,0,"cpu_we",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+5,0,"cpu_req",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+40,0,"stall",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+35,0,"data_out_cpu",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+53,0,"MEM_LAT",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+17,0,"mem_cnt",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+18,0,"mem_rd_count",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+19,0,"mem_wr_count",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+41,0,"pass_count",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+42,0,"fail_count",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+43,0,"test_count",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, 31,0);
    VL_TRACE_DECL_BIT(tracep,c+6,0,"saw_miss",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+7,0,"rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+54,0,"F3_B",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, 2,0);
    VL_TRACE_DECL_BUS(tracep,c+55,0,"F3_H",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, 2,0);
    VL_TRACE_DECL_BUS(tracep,c+56,0,"F3_W",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, 2,0);
    VL_TRACE_DECL_BUS(tracep,c+57,0,"F3_BU",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, 2,0);
    VL_TRACE_DECL_BUS(tracep,c+58,0,"F3_HU",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, 2,0);
    VL_TRACE_DECL_BUS(tracep,c+59,0,"CLK_PERIOD",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+8,0,"access__Vstatic__addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+9,0,"access__Vstatic__f3",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 2,0);
    VL_TRACE_DECL_BIT(tracep,c+10,0,"access__Vstatic__we",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+11,0,"access__Vstatic__wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+44,0,"store__Vstatic__lane",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_PUSH_PREFIX(tracep, "clean_evict", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BUS(tracep,c+45,0,"wr_before",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, 31,0);
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_PUSH_PREFIX(tracep, "init_cache", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BUS(tracep,c+46,0,"i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, 31,0);
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_PUSH_PREFIX(tracep, "uut", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BIT(tracep,c+39,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+0,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+14,0,"mem_ack",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+15,0,"mem_ready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+16,0,"mem_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+31,0,"memory_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+32,0,"mem_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BIT(tracep,c+33,0,"mem_req",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+34,0,"mem_we",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+1,0,"data_in_cpu",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+2,0,"cpu_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+3,0,"cpu_funct3",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 2,0);
    VL_TRACE_DECL_BIT(tracep,c+4,0,"cpu_we",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+5,0,"cpu_req",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+40,0,"stall",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+35,0,"data_out_cpu",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+60,0,"IDLE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+61,0,"START",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+53,0,"DONE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+62,0,"WRITEB",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+36,0,"state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 1,0);
    VL_TRACE_DECL_BUS(tracep,c+20,0,"store_mask",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BUS(tracep,c+21,0,"way0_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+22,0,"way1_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+12,0,"tag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 22,0);
    VL_TRACE_DECL_BUS(tracep,c+13,0,"set",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 6,0);
    VL_TRACE_DECL_BUS(tracep,c+23,0,"way0_tag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 22,0);
    VL_TRACE_DECL_BUS(tracep,c+24,0,"way1_tag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 22,0);
    VL_TRACE_DECL_BIT(tracep,c+25,0,"lru",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+26,0,"way0_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+27,0,"way1_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+47,0,"way0_dirty",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+48,0,"way1_dirty",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+63,0,"dirty",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+28,0,"hit0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+49,0,"hit1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+29,0,"hit",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+37,0,"miss",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+38,0,"cpu_bff_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+64,0,"data_temp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BUS(tracep,c+65,0,"d_cache",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 31,0);
    VL_TRACE_DECL_BIT(tracep,c+50,0,"victim_dirty",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+30,0,"victim_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+51,0,"aligned_wdata__Vstatic__byte_payload",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 7,0);
    VL_TRACE_DECL_BUS(tracep,c+52,0,"aligned_wdata__Vstatic__half_payload",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 15,0);
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_POP_PREFIX(tracep);
}

VL_ATTR_COLD void VD_CACHE_tb___024root__trace_init_top(VD_CACHE_tb___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root__trace_init_top\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VD_CACHE_tb___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void VD_CACHE_tb___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void VD_CACHE_tb___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void VD_CACHE_tb___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void VD_CACHE_tb___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void VD_CACHE_tb___024root__trace_register(VD_CACHE_tb___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root__trace_register\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&VD_CACHE_tb___024root__trace_const_0, 0, vlSelf);
    tracep->addFullCb(&VD_CACHE_tb___024root__trace_full_0, 0, vlSelf);
    tracep->addChgCb(&VD_CACHE_tb___024root__trace_chg_0, 0, vlSelf);
    tracep->addCleanupCb(&VD_CACHE_tb___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void VD_CACHE_tb___024root__trace_const_0_sub_0(VD_CACHE_tb___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void VD_CACHE_tb___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root__trace_const_0\n"); );
    // Body
    VD_CACHE_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VD_CACHE_tb___024root*>(voidSelf);
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VD_CACHE_tb___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void VD_CACHE_tb___024root__trace_const_0_sub_0(VD_CACHE_tb___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root__trace_const_0_sub_0\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullIData(oldp+53,(2U),32);
    bufp->fullCData(oldp+54,(0U),3);
    bufp->fullCData(oldp+55,(1U),3);
    bufp->fullCData(oldp+56,(2U),3);
    bufp->fullCData(oldp+57,(4U),3);
    bufp->fullCData(oldp+58,(5U),3);
    bufp->fullIData(oldp+59,(0x0000000aU),32);
    bufp->fullIData(oldp+60,(0U),32);
    bufp->fullIData(oldp+61,(1U),32);
    bufp->fullIData(oldp+62,(3U),32);
    bufp->fullBit(oldp+63,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__dirty));
    bufp->fullIData(oldp+64,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__data_temp),32);
    bufp->fullIData(oldp+65,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__d_cache),32);
}

VL_ATTR_COLD void VD_CACHE_tb___024root__trace_full_0_sub_0(VD_CACHE_tb___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void VD_CACHE_tb___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root__trace_full_0\n"); );
    // Body
    VD_CACHE_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VD_CACHE_tb___024root*>(voidSelf);
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VD_CACHE_tb___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void VD_CACHE_tb___024root__trace_full_0_sub_0(VD_CACHE_tb___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VD_CACHE_tb___024root__trace_full_0_sub_0\n"); );
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullBit(oldp+0,(vlSelfRef.D_CACHE_tb__DOT__reset));
    bufp->fullIData(oldp+1,(vlSelfRef.D_CACHE_tb__DOT__data_in_cpu),32);
    bufp->fullIData(oldp+2,(vlSelfRef.D_CACHE_tb__DOT__cpu_addr),32);
    bufp->fullCData(oldp+3,(vlSelfRef.D_CACHE_tb__DOT__cpu_funct3),3);
    bufp->fullBit(oldp+4,(vlSelfRef.D_CACHE_tb__DOT__cpu_we));
    bufp->fullBit(oldp+5,(vlSelfRef.D_CACHE_tb__DOT__cpu_req));
    bufp->fullBit(oldp+6,(vlSelfRef.D_CACHE_tb__DOT__saw_miss));
    bufp->fullIData(oldp+7,(vlSelfRef.D_CACHE_tb__DOT__rdata),32);
    bufp->fullIData(oldp+8,(vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__addr),32);
    bufp->fullCData(oldp+9,(vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__f3),3);
    bufp->fullBit(oldp+10,(vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__we));
    bufp->fullIData(oldp+11,(vlSelfRef.D_CACHE_tb__DOT__access__Vstatic__wdata),32);
    bufp->fullIData(oldp+12,((vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                              >> 9U)),23);
    bufp->fullCData(oldp+13,((0x0000007fU & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                             >> 2U))),7);
    bufp->fullBit(oldp+14,(vlSelfRef.D_CACHE_tb__DOT__mem_ack));
    bufp->fullBit(oldp+15,(vlSelfRef.D_CACHE_tb__DOT__mem_ready));
    bufp->fullIData(oldp+16,(vlSelfRef.D_CACHE_tb__DOT__mem_rdata),32);
    bufp->fullIData(oldp+17,(vlSelfRef.D_CACHE_tb__DOT__mem_cnt),32);
    bufp->fullIData(oldp+18,(vlSelfRef.D_CACHE_tb__DOT__mem_rd_count),32);
    bufp->fullIData(oldp+19,(vlSelfRef.D_CACHE_tb__DOT__mem_wr_count),32);
    bufp->fullCData(oldp+20,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__store_mask),4);
    bufp->fullIData(oldp+21,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_data),32);
    bufp->fullIData(oldp+22,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_data),32);
    bufp->fullIData(oldp+23,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_tag),23);
    bufp->fullIData(oldp+24,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_tag),23);
    bufp->fullBit(oldp+25,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__lru));
    bufp->fullBit(oldp+26,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_valid));
    bufp->fullBit(oldp+27,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_valid));
    bufp->fullBit(oldp+28,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__hit0));
    bufp->fullBit(oldp+29,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__hit));
    bufp->fullBit(oldp+30,(((IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__lru)
                             ? (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_valid)
                             : (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_valid))));
    bufp->fullIData(oldp+31,(vlSelfRef.D_CACHE_tb__DOT__memory_addr),32);
    bufp->fullIData(oldp+32,(vlSelfRef.D_CACHE_tb__DOT__mem_wdata),32);
    bufp->fullBit(oldp+33,(vlSelfRef.D_CACHE_tb__DOT__mem_req));
    bufp->fullBit(oldp+34,(vlSelfRef.D_CACHE_tb__DOT__mem_we));
    bufp->fullIData(oldp+35,(vlSelfRef.D_CACHE_tb__DOT__data_out_cpu),32);
    bufp->fullCData(oldp+36,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__state),2);
    bufp->fullBit(oldp+37,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__miss));
    bufp->fullIData(oldp+38,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__cpu_bff_addr),32);
    bufp->fullBit(oldp+39,(vlSelfRef.D_CACHE_tb__DOT__clk));
    bufp->fullBit(oldp+40,(((~ ((0U == (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__state)) 
                                & (IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__hit))) 
                            & (IData)(vlSelfRef.D_CACHE_tb__DOT__cpu_req))));
    bufp->fullIData(oldp+41,(vlSelfRef.D_CACHE_tb__DOT__pass_count),32);
    bufp->fullIData(oldp+42,(vlSelfRef.D_CACHE_tb__DOT__fail_count),32);
    bufp->fullIData(oldp+43,(vlSelfRef.D_CACHE_tb__DOT__test_count),32);
    bufp->fullIData(oldp+44,(vlSelfRef.D_CACHE_tb__DOT__store__Vstatic__lane),32);
    bufp->fullIData(oldp+45,(vlSelfRef.D_CACHE_tb__DOT__clean_evict__DOT__wr_before),32);
    bufp->fullIData(oldp+46,(vlSelfRef.D_CACHE_tb__DOT__init_cache__DOT__i),32);
    bufp->fullBit(oldp+47,((1U & (IData)((vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way0_cache
                                          [(0x0000007fU 
                                            & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                               >> 2U))] 
                                          >> 0x00000037U)))));
    bufp->fullBit(oldp+48,((1U & (IData)((vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_cache
                                          [(0x0000007fU 
                                            & (vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                               >> 2U))] 
                                          >> 0x00000037U)))));
    bufp->fullBit(oldp+49,(((IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_valid) 
                            & ((vlSelfRef.D_CACHE_tb__DOT__cpu_addr 
                                >> 9U) == vlSelfRef.D_CACHE_tb__DOT__uut__DOT__way1_tag))));
    bufp->fullBit(oldp+50,((1U & ((IData)(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__lru)
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
    bufp->fullCData(oldp+51,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__byte_payload),8);
    bufp->fullSData(oldp+52,(vlSelfRef.D_CACHE_tb__DOT__uut__DOT__aligned_wdata__Vstatic__half_payload),16);
}
