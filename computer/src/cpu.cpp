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
  uint8_t regIndex = (instruction & 0x07);    // Extract the lower 3 bits
  bool memAddressing =
      (instruction & 0x08); // Check if the instruction is memory addressing
  uint16_t address = (mainMem->read(pc + 1) << 8) |
                     mainMem->read(pc + 2); // pre-fetch a 16-bit address

  switch (opcode) {
  case 0x1: // Load value into a register
    if (!memAddressing) {
      uint8_t value = mainMem->read(pc + 1); // Fetch the next byte as the value
      registers[regIndex] = value;
      pc++; // Increment program counter to account for the value byte
    } else {
      registers[regIndex] = mainMem->read(address);
      pc += 2; // Increment program counter to account for the 2-byte address
    }
    break;
  case 0x2: // Store value from a register to memory
    mainMem->write(
        address,
        registers[regIndex]); // Store the register value at the address
    pc += 2; // Increment program counter to account for the 2-byte address
    break;
  case 0x3: { // Add a register to register[0]
    int16_t tmp = 0;
    if (memAddressing) {
      tmp = (registers[regIndex] + mainMem->read(address));
      pc += 2; // Increment program counter to account for the 2-byte address
    } else {
      // Add the value of the specified register to register[0]
      tmp = registers[0] + registers[regIndex];
    }
    registers[0] = tmp & 0xFF; // Add the value of the specified
    // register to register[0]
    updateStatusFlags(tmp); // Update status flags (e.g., zero, carry, overflow)
    break;
  }
  case 0x4: { // Subtract a register from register[0]
    int16_t tmp = 0;
    if (memAddressing) {
      tmp = (registers[regIndex] - mainMem->read(address));
      pc += 2; // Increment program counter to account for the 2-byte address
    } else {
      // Add the value of the specified register to register[0]
      tmp = registers[0] - registers[regIndex];
    }
    registers[0] = tmp & 0xFF; // Add the value of the specified
    // register to register[0]
    updateStatusFlags(tmp); // Update status flags (e.g., zero, carry, overflow)
    break;
  }
  case 0x5: // Jump to a specific memory address
  {
    // Don't rely on unsigned wrap-around for address
    if (address == 0) {
      address = 0xFFFF; // Handle the case where address is 0
    } else {
      address--; // subtract 1 because pc will be incremented later if set.
    }
    pc += 2; // pre-Skip the address bytes if the jump is not taken
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
    case 4: // Jump on Not Zero
      if ((statusFlags & 0x01)==0)
        pc = address;
      break;
    }
    if (pc == address)
      statusFlags = 0; // Clear the status flags if the jump is taken
  } break;
  case 0x6: // OR two registers and store the result in register[0]
    if (!memAddressing) {
      registers[0] |= registers[regIndex]; // Perform OR operation
    } else {
      registers[0] = (registers[regIndex] | mainMem->read(address));
      pc += 2; // Increment program counter to account for the 2-byte address
    }
    updateStatusFlags(
        registers[0]); // Update status flags (e.g., zero, carry, overflow)
    break;
  case 0x7: // NAND two registers and store the result in register[0]
    if (!memAddressing) {
      registers[0] =
          ~(registers[0] & registers[regIndex]); // Perform NAND operation
    } else {
      registers[0] = ~(registers[regIndex] & mainMem->read(address));
      pc += 2; // Increment program counter to account for the 2-byte address
    }
    updateStatusFlags(
        registers[0]); // Update status flags (e.g., zero, carry, overflow)
    break;
  case 0x8: { // CMP two registers and set the status flags
    int16_t tmp = 0;
    if (!memAddressing) {
      tmp = registers[0] - registers[regIndex]; // Perform CMP operation
    } else {
      tmp = mainMem->read(address) - registers[regIndex];
      pc += 2; // Increment program counter to account for the 2-byte address
    }
    updateStatusFlags(tmp); // Update status flags (e.g., zero, carry, overflow)
    break;
  }
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