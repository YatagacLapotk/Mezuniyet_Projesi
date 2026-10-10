# Run the D_CACHE testbench with Verilator.
#
# Usage (from anywhere):
#   tclsh run_sim.tcl            ;# native Verilator if installed, else Docker
#   tclsh run_sim.tcl docker     ;# force Docker (run_docker.sh)
#   tclsh run_sim.tcl clean      ;# remove build output and waveform

set here [file dirname [file normalize [info script]]]
set root [file normalize [file join $here .. .. ..]]
set mode [expr {$argc > 0 ? [lindex $argv 0] : "auto"}]

if {$mode eq "clean"} {
    file delete -force [file join $here obj_dir] [file join $here D_CACHE_tb.vcd]
    puts "cleaned"
    exit 0
}

proc run {args} {
    if {[catch {exec {*}$args >@ stdout 2>@ stderr} err]} {
        puts stderr "FAILED: $args\n$err"
        exit 1
    }
}

set have_verilator [expr {![catch {exec which verilator}]}]

if {$mode eq "docker" || ($mode eq "auto" && !$have_verilator)} {
    puts "== Verilator via Docker =="
    run bash [file join $here run_docker.sh]
} else {
    puts "== Verilator (native) =="
    cd $here
    run verilator --binary --timing --trace -Wno-fatal -Wno-lint -Wno-style \
        --top-module D_CACHE_tb -Mdir obj_dir \
        [file join $root CPU CACHE D_CACHE.v] [file join $here D_CACHE_TB.sv]
    run ./obj_dir/VD_CACHE_tb
}

puts "waveform: [file join $here D_CACHE_tb.vcd]"
