# Hazard Unit Implementation - Harris & Harris Approach

## Overview
This hazard unit implements hazard detection and resolution for a pipelined RISC-V processor based on "Digital Design and Computer Architecture" by Harris & Harris (Chapter 7).

## Three Types of Hazards Handled

### 1. DATA HAZARDS (Solved with Forwarding)

**Problem**: An instruction needs a value that hasn't been written back yet.

**Example**:
```assembly
ADD x1, x2, x3   # x1 = x2 + x3
SUB x4, x1, x5   # Uses x1 before it's written back!
```

**Solution**: Forward the result from later pipeline stages.

**Forwarding Paths**:
- `forwardA/B = 2'b10`: Forward from Memory stage (rdM)
- `forwardA/B = 2'b01`: Forward from Writeback stage (rdW)  
- `forwardA/B = 2'b00`: No forwarding (use register file value)

**Priority**: Memory stage has priority over Writeback (most recent value)

**Conditions** (Harris & Harris Table 7.5):
- Forward from Memory if: `(rs == rdM) && RegWriteM && (rdM != 0)`
- Forward from Writeback if: `(rs == rdW) && RegWriteW && (rdW != 0)`
- Special case: Never forward from x0 (always zero in RISC-V)

---

### 2. LOAD-USE HAZARDS (Solved with Stalling)

**Problem**: A load instruction is followed immediately by an instruction that uses the loaded value. Forwarding alone can't solve this because the data isn't available until Memory stage.

**Example**:
```assembly
LW  x1, 0(x2)    # Load from memory into x1
ADD x4, x1, x5   # Tries to use x1 immediately - TOO SOON!
```

**Solution**: Stall the pipeline for 1 cycle (insert a bubble/NOP).

**Detection**:
```verilog
lwStall = result_srcE_zer && reg_writeE && ((rdE == rs1D) || (rdE == rs2D))
```

Where:
- `result_srcE_zer`: Indicates load instruction in Execute stage
- `reg_writeE`: The load writes to a register
- `rdE == rs1D/rs2D`: Destination matches source operands in Decode

**Actions**:
- `stallF = 1`: Prevent Fetch from advancing
- `stallD = 1`: Prevent Decode from advancing  
- `flushE = 1`: Insert NOP (bubble) in Execute stage

---

### 3. CONTROL HAZARDS (Solved with Flushing)

**Problem**: Branch or jump changes the PC, but we've already fetched wrong instructions.

**Example**:
```assembly
BEQ x1, x2, LABEL   # If equal, jump to LABEL
ADD x3, x4, x5      # This might be wrong instruction!
SUB x6, x7, x8      # This too!
```

**Solution**: Flush (cancel) incorrectly fetched instructions.

**Detection**:
- `pcsrcE = 1`: Branch/jump taken (calculated in Execute stage)

**Actions**:
- `flushD = 1`: Clear Decode stage
- `flushE = 1`: Clear Execute stage
- `pc_src = 1`: Select new PC value (branch/jump target)

---

## Signal Descriptions

### Inputs

| Signal | Description |
|--------|-------------|
| `rs1D, rs2D` | Source registers in Decode stage |
| `rs1E, rs2E` | Source registers in Execute stage |
| `rdE` | Destination register in Execute stage |
| `rdM` | Destination register in Memory stage |
| `rdW` | Destination register in Writeback stage |
| `reg_writeM` | Memory stage writes to register |
| `reg_writeW` | Writeback stage writes to register |
| `reg_writeE` | Execute stage writes to register |
| `result_srcE_zer` | Load instruction indicator (1 = load from memory) |
| `pcsrcE` | Branch/jump taken signal |

### Outputs

| Signal | Description |
|--------|-------------|
| `forwardA[1:0]` | Forwarding control for operand A (rs1) |
| `forwardB[1:0]` | Forwarding control for operand B (rs2) |
| `stallF` | Stall Fetch stage |
| `stallD` | Stall Decode stage |
| `flushD` | Flush (clear) Decode stage |
| `flushE` | Flush (clear) Execute stage |
| `pc_src` | Select PC source (0=PC+4, 1=branch/jump target) |

---

## Forwarding MUX Usage (in Execute Stage)

```verilog
// Example for operand A (similar for operand B)
always @(*) begin
    case (forwardA)
        2'b00: srcA = rd1E;      // From register file
        2'b01: srcA = resultW;   // Forward from Writeback
        2'b10: srcA = aluResultM; // Forward from Memory
        default: srcA = rd1E;
    endcase
end
```

---

## Pipeline Behavior Examples

### Example 1: Data Hazard with Forwarding
```assembly
Instruction     | F | D | E | M | W |
----------------|---|---|---|---|---|
ADD x1, x2, x3  |   | F | D | E | M | W
SUB x4, x1, x5  |   |   | F | D*| E | M | W
                              ^
                              Forward from M stage
```
*At cycle when SUB is in Execute, forwardA=2'b10 provides x1 value from Memory stage*

### Example 2: Load-Use Hazard with Stall
```assembly
Instruction     | F | D | E | M | W |
----------------|---|---|---|---|---|
LW  x1, 0(x2)   |   | F | D | E | M | W
ADD x4, x1, x5  |   |   | F | D | D*| E | M | W
                            Stall ^
                              
```
*Pipeline stalled for 1 cycle, then forwarding handles the hazard*

### Example 3: Branch Taken (Control Hazard)
```assembly
Instruction     | F | D | E | M | W |
----------------|---|---|---|---|---|
BEQ x1, x2, 20  |   | F | D | E | M | W
ADD x3, x4, x5  |   |   | F | X |   |     (Flushed)
SUB x6, x7, x8  |   |   |   | X |   |     (Flushed)
TARGET_INST     |   |   |   | F | D | E
```
*When branch taken in E stage, wrong instructions in D and E are flushed*

---

## Integration Notes

1. **Connect to Execute Stage**: The forwarding MUXes should be in the Execute stage module to select between register file values and forwarded values.

2. **Connect to Pipeline Registers**: 
   - Stall signals prevent pipeline registers from updating
   - Flush signals clear pipeline registers to insert NOPs

3. **Additional Inputs Needed**: Make sure your CORE module provides:
   - `reg_writeE` signal from Execute stage
   - `pcsrcE` signal (branch/jump taken)
   - All register addresses at each stage

4. **Performance**: This implementation resolves most data hazards with forwarding (0 cycle penalty) and only stalls for load-use hazards (1 cycle penalty). Control hazards have a 2-cycle penalty with this basic branch resolution.

---

## References

- Harris, S. L., & Harris, D. (2021). *Digital Design and Computer Architecture: RISC-V Edition*. Morgan Kaufmann.
  - Chapter 7.5: Pipelined Processor
  - Section 7.5.3: Hazards
  - Figure 7.59: Hazard Unit Implementation
  - Table 7.5: Forwarding Logic
