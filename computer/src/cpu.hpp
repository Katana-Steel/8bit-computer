#ifndef CPU_HPP
#define CPU_HPP

#include <array>
#include <cstdint>
class Memory;

class CPU {
public:
  CPU();
  void executeInstruction(uint8_t instruction);
  uint16_t getProgramCounter() const;
  void reset();

  std::array<uint8_t, 8> registers; // 8 general-purpose registers
  uint8_t statusFlags;              // Status flags register

  Memory *mainMem;

private:
  uint16_t pc;
  void handleInterrupts();
  void updateStatusFlags(const int16_t result);
  // Additional private methods and properties can be declared here
};

#endif // CPU_HPP