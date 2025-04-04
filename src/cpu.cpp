#include "cpu.hpp"
#include <cstdint>

CPU::CPU()
    : registers({0, 0, 0, 0, 0, 0, 0, 0}), statusFlags(0), pc(0xfe00),
      mainMem(nullptr) {}

void CPU::executeInstruction(uint8_t instruction) {
  // Implementation of instruction execution logic
  // This will include decoding the instruction and executing the corresponding
  // operation

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

void CPU::updateStatusFlags() {
  // Update the status flags based on the current state of the CPU
}