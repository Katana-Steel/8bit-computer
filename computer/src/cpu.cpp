// copyright Rene Kjellerup 2025
// released under the GNU GPL version 3 or later
#include "cpu.hpp"
#include "memory.hpp"
#include <cstdint>

CPU::CPU()
    : registers({0, 0, 0, 0, 0, 0, 0, 0}), statusFlags(0), pc(0xfe00),
      mainMem(nullptr) {}

void CPU::executeInstruction(uint8_t instruction) {
  // Decode the instruction
  uint8_t opcode = (instruction & 0xF0) >> 4; // Extract the upper 4 bits
  uint8_t regIndex = (instruction & 0x0F);    // Extract the lower 4 bits

  switch (opcode) {
  case 0x1: // Load value into a register
    if (regIndex < 8) {
      uint8_t value = mainMem->read(pc + 1); // Fetch the next byte as the value
      registers[regIndex] = value;
      pc++; // Increment program counter to account for the value byte
    } else {
      uint16_t address = (mainMem->read(pc + 1) << 8) | mainMem->read(pc + 2);
      registers[regIndex & 0x7] = mainMem->read(address);
      pc += 2; // Increment program counter to account for the 2-byte address
    }
    break;
  case 0x2: // Store value from a register to memory
    if (regIndex < 8) {
      uint16_t address = (mainMem->read(pc + 1) << 8) |
                         mainMem->read(pc + 2); // Fetch 16-bit address
      mainMem->write(
          address,
          registers[regIndex]); // Store the register value at the address
      pc += 2; // Increment program counter to account for the 2-byte address
    }
    break;
  case 0x3: // Add a register to register[0]
    if (regIndex < 8) {
      int16_t tmp = registers[0] + registers[regIndex];
      registers[0] = tmp & 0xFF; // Add the value of the specified
                                 // register to register[0]
      updateStatusFlags(
          tmp); // Update status flags (e.g., zero, carry, overflow)
    }
    break;
  case 0x4: // Subtract a register from register[0]
    if (regIndex < 8) {
      int16_t tmp = registers[0] - registers[regIndex];
      registers[0] -= tmp & 0xFF;
      // from register[0]
      updateStatusFlags(
          tmp); // Update status flags (e.g., zero, carry, overflow)
    }
    break;
  case 0x5: // Jump to a specific memory address
  {
    uint16_t address = (mainMem->read(pc + 1) << 8) |
                       mainMem->read(pc + 2); // Fetch 16-bit address
    address--; // subtract 1 because pc will be incremented later if set.
    pc += 2;   // pre-Skip the address bytes if the jump is not taken
    switch (regIndex) {
    default: // Unconditional jump
      pc = address;
      break;
    case 1: // Jump if zero
      if (statusFlags & 0x01)
        pc = address;
      break;
    case 2: // Jump on Carry
      if (statusFlags & 0x02)
        pc = address;
      break;
    case 3: // Jump on Zero and Carry
      if (statusFlags & 0x03)
        pc = address;
      break;
    }

  } break;
  case 0x6: // Jump if Zero (JZ)
  {
    uint16_t address = (mainMem->read(pc + 1) << 8) |
                       mainMem->read(pc + 2); // Fetch 16-bit address
    if (statusFlags & 0x01) { // Check if the zero flag (bit 0) is set
      pc = address - 1; // Set the program counter to the address (subtract 1
                        // because pc will be incremented later)
    } else {
      pc += 2; // Skip the address bytes if the jump is not taken
    }
    statusFlags = 0;
  } break;

  case 0x7: // NAND two registers and store the result in register[0]
    if (regIndex < 8) {
      registers[0] =
          ~(registers[0] & registers[regIndex]); // Perform NAND operation
      updateStatusFlags(
          registers[0]); // Update status flags (e.g., zero, carry, overflow)
    }
    break;

  default:
    // Handle unknown opcode
    break;
  }

  // update the program counter
  if (pc == (0xffff)) {
    pc = 0;
  } else {
    pc++;
  }
}

void CPU::reset() {
  // Reset all registers and status flags
  for (int i = 0; i < 8; ++i) {
    registers[i] = 0;
  }
  statusFlags = 0;
  pc = 0xfe00;
}

uint16_t CPU::getProgramCounter() const { return pc; }

void CPU::handleInterrupts() {
  // Handle CPU interrupts
}

void CPU::updateStatusFlags(const int16_t result) {
  // Update the status flags based on the current state of the CPU
  if (registers[0] == 0) {
    statusFlags |= 0x01; // Set the zero flag (bit 0) to 1
  } else {
    statusFlags &= ~0x01; // Clear the zero flag (bit 0)
  }

  if (result > 0xFF ||
      result < 0) {      // Check for overflow (carry) or underflow (borrow)
    statusFlags |= 0x02; // Set the carry flag (bit 1) to 1
  } else {
    statusFlags &= ~0x02; // Clear the carry flag (bit 1)
  }
}