# Assembly Language Documentation

This document provides an overview of the assembly language supported by the 8-bit Computer Emulator and its Assembly Compiler. It includes the list of supported instructions, their opcodes, and usage examples.

---

## Instruction Set

### 1. **JMP** - Jump to Address

- **Opcode:**`0x50`
- **Description:** Unconditionally jumps to the specified memory address.
- **Syntax:** `JMP <address>`
- **Example:**

```assembly
  JMP 0x1000
```

---

### 2. LDi - Load Immediate Value into Register

- **Opcode:** `0x10`
- **Description:** Loads an immediate value into the specified register.
- **Syntax:** `LDi <register> <value>`
- **Example:**

```assembly
LDi 0 0x42
```

---

### 3. LDm - Load Value from Memory into Register

- **Opcode:** `0x18`
- **Description:** Loads a value from the specified memory address into the specified register.
- **Syntax:** `LDm <register> <address>`
- **Example:**

```assembly
LDm 1 0x2000
```

---

### 4. ST - Store Register Value into Memory

- **Opcode:** `0x20`
- **Description:** Stores the value from the specified register into the specified memory address.
- **Syntax:** `ST <register> <address>`
- **Example:**

```assembly
ST 0 0x4300
```

---

### 5. ADD - Add Register to Accumulator

- **Opcode:** `0x30`
- **Description:** Adds the value of the specified register to the accumulator (AX).
- **Syntax:** `ADD <register>`
- **Example:**

```assembly
ADD 1
```

---

### 6. SUB - Subtract Register from Accumulator

- **Opcode:** `0x40`
- **Description:** Subtracts the value of the specified register from the accumulator (AX).
- **Syntax:** `SUB <register>`
- **Example:**

```assembly
SUB 3
```

---

### 7. JZ - Jump if Zero

- **Opcode:** `0x51`
- **Description:** Jumps to the specified address if the zero flag is set.
- **Syntax:** `JZ <address>`
- **Example:**

```assembly
JZ 0x4200
```

---

### 8. JC - Jump if Carry

- **Opcode:** `0x52`
- **Description:** Jumps to the specified address if the carry flag is set.
- **Syntax:** `JC <address>`
- **Example:**

```assembly
JC 0x4400
```

---

### 9. JZC - Jump if Zero and Carry

- **Opcode:** `0x53`
- **Description:** Jumps to the specified address if both the zero and carry flags are set.
- **Syntax:** `JZC <address>`
- **Example:**

```assembly
JZC 0x2900
```

---

### 10. NAND - Bitwise NAND Operation

- **Opcode:** `0x70`
- **Description:** Performs a bitwise NAND operation between the accumulator (AX) and the specified register, storing the result in the accumulator.
- **Syntax:** `NAND <register>`
- **Example:**

```assembly
NAND 3
```

---

### Directives

#### ORIGIN

- **Description:** Sets the starting address for the subsequent instructions.
- **Syntax:** `ORIGIN <address>`
- **Example:**

```assembly
ORIGIN 0xfe00
```

---

#### Notes

1. **Registers:** Registers are identified by numbers (e.g., `0`, `1`, `2`, etc.).
1. **Addresses:** Memory addresses are specified in hexadecimal format (e.g., `0x1000`).
1. **Immediate Values:** Immediate values are also specified in hexadecimal format (e.g., `0x42`).
1. **The Target CPU:** The target starts executing code at the initialization vector of address `0xfe00`

---

### Example Program

```assembly
ORIGIN     0x8000
LDi      0 0x42       ; Load immediate value 0x42 into register 0
LDm      1 0x2000     ; Load value from memory address 0x2000 into register 1
ADD      1            ; Add the value in register 1 to the accumulator
ST       0 0x3000     ; Store the value in register 0 to memory address 0x3000
JZ         0x8000     ; Jump to address 0x8000 if zero flag is set
```

This program demonstrates the use of various instructions and directives.

### Error Handling

- Invalid opcodes or syntax will result in an error during compilation.
- Ensure that all registers and memory addresses are valid and within range.
