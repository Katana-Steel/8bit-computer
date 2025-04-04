#include "memory.hpp"

Memory::Memory() {
  std::fill(std::begin(memoryArray), std::end(memoryArray),
            0); // Initialize memory to zero
}

uint8_t Memory::read(uint16_t address) const { return memoryArray[address]; }

void Memory::write(uint16_t address, uint8_t value) {
  memoryArray[address] = value;
}