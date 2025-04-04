#include "cpu.hpp"
#include "memory.hpp"
#include "utils/logger.hpp"
#include <fmt/format.h>

int main() {
  // setup logging framework
  Logger log{Logger::LogLevel::INFO};
  // Initialize CPU and Memory
  CPU cpu{};
  Memory memory{};
  // attaching main memory to the CPU
  cpu.mainMem = &memory;

  // Emulation loop
  while (true) {
    // Fetch the next instruction
    uint8_t instruction = memory.read(cpu.getProgramCounter());
    log.logInfo(fmt::format("Got instruction 0x{:x02} from memory at 0x{:x04}",
                            instruction, cpu.getProgramCounter()));
    // Execute the instruction
    cpu.executeInstruction(instruction);

    // Update the program counter

    // Add a condition to break the loop (for example, on a specific
    // instruction)
    if (instruction == 0x00) { // Assuming 0x00 is a halt instruction
      break;
    }
  }

  return 0;
}