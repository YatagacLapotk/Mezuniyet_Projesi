// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VD_CACHE_tb.h for the primary calling header

#include "VD_CACHE_tb__pch.h"

void VD_CACHE_tb___024root___ctor_var_reset(VD_CACHE_tb___024root* vlSelf);

VD_CACHE_tb___024root::VD_CACHE_tb___024root(VD_CACHE_tb__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    VD_CACHE_tb___024root___ctor_var_reset(this);
}

void VD_CACHE_tb___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

VD_CACHE_tb___024root::~VD_CACHE_tb___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
