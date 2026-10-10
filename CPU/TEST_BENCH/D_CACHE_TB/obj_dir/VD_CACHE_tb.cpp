// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VD_CACHE_tb__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

VD_CACHE_tb::VD_CACHE_tb(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new VD_CACHE_tb__Syms(contextp(), _vcname__, this)}
    , m_evalLoop{*this, /*convergeLimit:*/ 10000}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

VD_CACHE_tb::VD_CACHE_tb(const char* _vcname__)
    : VD_CACHE_tb(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

VD_CACHE_tb::~VD_CACHE_tb() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void VD_CACHE_tb___024root___eval_debug_assertions(VD_CACHE_tb___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD void VD_CACHE_tb___024root___eval_static(VD_CACHE_tb___024root* vlSelf);
void VD_CACHE_tb___024root___eval_initial(VD_CACHE_tb___024root* vlSelf);
VL_ATTR_COLD bool VD_CACHE_tb___024root___eval_stl(VD_CACHE_tb___024root* vlSelf, CData/*0:0*/ firstIteration);
void VD_CACHE_tb___024root___eval_sample(VD_CACHE_tb___024root* vlSelf);
bool VD_CACHE_tb___024root___eval_ico(VD_CACHE_tb___024root* vlSelf, CData/*0:0*/ firstIteration);
bool VD_CACHE_tb___024root___eval_act(VD_CACHE_tb___024root* vlSelf);
bool VD_CACHE_tb___024root___eval_inact(VD_CACHE_tb___024root* vlSelf);
bool VD_CACHE_tb___024root___eval_nba(VD_CACHE_tb___024root* vlSelf);
bool VD_CACHE_tb___024root___eval_obs(VD_CACHE_tb___024root* vlSelf);
bool VD_CACHE_tb___024root___eval_react(VD_CACHE_tb___024root* vlSelf);
void VD_CACHE_tb___024root___eval_postponed(VD_CACHE_tb___024root* vlSelf);
VL_ATTR_COLD void VD_CACHE_tb___024root___eval_final(VD_CACHE_tb___024root* vlSelf);
VL_ATTR_COLD void VD_CACHE_tb___024root___eval_dump_triggers__stl(VD_CACHE_tb___024root* vlSelf);
VL_ATTR_COLD void VD_CACHE_tb___024root___eval_dump_triggers__ico(VD_CACHE_tb___024root* vlSelf);
VL_ATTR_COLD void VD_CACHE_tb___024root___eval_dump_triggers__act(VD_CACHE_tb___024root* vlSelf);
VL_ATTR_COLD void VD_CACHE_tb___024root___eval_dump_triggers__nba(VD_CACHE_tb___024root* vlSelf);
VL_ATTR_COLD void VD_CACHE_tb___024root___eval_dump_triggers__obs(VD_CACHE_tb___024root* vlSelf);
VL_ATTR_COLD void VD_CACHE_tb___024root___eval_dump_triggers__react(VD_CACHE_tb___024root* vlSelf);

void VD_CACHE_tb::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VD_CACHE_tb::eval_step\n"); );
    m_evalLoop.eval();
}

void VD_CACHE_tb::evalBegin() {
#ifdef VL_DEBUG
    // Debug assertions
    VD_CACHE_tb___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
}

void VD_CACHE_tb::evalEnd() {
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
    vlSymsp->TOP.__VdlySched.cleanupForevered();
}

void VD_CACHE_tb::evalStatic() {
    VD_CACHE_tb___024root___eval_static(&(vlSymsp->TOP));
}

void VD_CACHE_tb::evalInitial() {
    VD_CACHE_tb___024root___eval_initial(&(vlSymsp->TOP));
}

bool VD_CACHE_tb::evalStl(bool firstIteration) {
    return VD_CACHE_tb___024root___eval_stl(&(vlSymsp->TOP), firstIteration);
}

void VD_CACHE_tb::evalSample() {
    VD_CACHE_tb___024root___eval_sample(&(vlSymsp->TOP));
}

bool VD_CACHE_tb::evalIco(bool firstIteration) {
    return VD_CACHE_tb___024root___eval_ico(&(vlSymsp->TOP), firstIteration);
}

bool VD_CACHE_tb::evalAct() {
    return VD_CACHE_tb___024root___eval_act(&(vlSymsp->TOP));
}

bool VD_CACHE_tb::evalInact() {
    return VD_CACHE_tb___024root___eval_inact(&(vlSymsp->TOP));
}

bool VD_CACHE_tb::evalNba() {
    return VD_CACHE_tb___024root___eval_nba(&(vlSymsp->TOP));
}

bool VD_CACHE_tb::evalObs() {
    return VD_CACHE_tb___024root___eval_obs(&(vlSymsp->TOP));
}

bool VD_CACHE_tb::evalReact() {
    return VD_CACHE_tb___024root___eval_react(&(vlSymsp->TOP));
}

void VD_CACHE_tb::evalPostponed() {
    VD_CACHE_tb___024root___eval_postponed(&(vlSymsp->TOP));
}

void VD_CACHE_tb::evalFinal() {
    VD_CACHE_tb___024root___eval_final(&(vlSymsp->TOP));
}

VL_ATTR_COLD void VD_CACHE_tb::dumpTriggersStl() {
    VD_CACHE_tb___024root___eval_dump_triggers__stl(&(vlSymsp->TOP));
}

VL_ATTR_COLD void VD_CACHE_tb::dumpTriggersIco() {
    VD_CACHE_tb___024root___eval_dump_triggers__ico(&(vlSymsp->TOP));
}

VL_ATTR_COLD void VD_CACHE_tb::dumpTriggersAct() {
    VD_CACHE_tb___024root___eval_dump_triggers__act(&(vlSymsp->TOP));
}

VL_ATTR_COLD void VD_CACHE_tb::dumpTriggersNba() {
    VD_CACHE_tb___024root___eval_dump_triggers__nba(&(vlSymsp->TOP));
}

VL_ATTR_COLD void VD_CACHE_tb::dumpTriggersObs() {
    VD_CACHE_tb___024root___eval_dump_triggers__obs(&(vlSymsp->TOP));
}

VL_ATTR_COLD void VD_CACHE_tb::dumpTriggersReact() {
    VD_CACHE_tb___024root___eval_dump_triggers__react(&(vlSymsp->TOP));
}

void VD_CACHE_tb::eval_end_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+eval_end_step VD_CACHE_tb::eval_end_step\n"); );
#ifdef VM_TRACE
    // Tracing
    if (VL_UNLIKELY(vlSymsp->__Vm_dumping)) vlSymsp->_traceDump();
#endif  // VM_TRACE
}

//============================================================
// Events and timing
bool VD_CACHE_tb::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t VD_CACHE_tb::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* VD_CACHE_tb::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

VL_ATTR_COLD void VD_CACHE_tb::final() {
    contextp()->executingFinal(true);
    evalFinal();
    contextp()->executingFinal(false);
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* VD_CACHE_tb::hierName() const { return vlSymsp->name(); }
const char* VD_CACHE_tb::modelName() const { return "VD_CACHE_tb"; }
unsigned VD_CACHE_tb::threads() const { return 1; }
void VD_CACHE_tb::prepareClone() const { contextp()->prepareClone(); }
void VD_CACHE_tb::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> VD_CACHE_tb::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false}};
};

//============================================================
// Trace configuration

void VD_CACHE_tb___024root__trace_decl_types(VerilatedVcd* tracep);

void VD_CACHE_tb___024root__trace_init_top(VD_CACHE_tb___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    VD_CACHE_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VD_CACHE_tb___024root*>(voidSelf);
    VD_CACHE_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(vlSymsp->name(), VerilatedTracePrefixType::SCOPE_MODULE);
    VD_CACHE_tb___024root__trace_decl_types(tracep);
    VD_CACHE_tb___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void VD_CACHE_tb___024root__trace_register(VD_CACHE_tb___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void VD_CACHE_tb::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'VD_CACHE_tb::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP), name(), false, 66);
    VD_CACHE_tb___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
