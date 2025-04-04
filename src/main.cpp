#include "cpu.hpp"
#include "memory.hpp"
#include "utils/logger.hpp"
#include <format>

int main() {
  // setup logging framework
  Logger log{Logger::LogLevel::INFO};
  // Initialize CPU and Memory
  CPU cpu{};
  Memory memory{};
  // attaching main memory to the CPU
  cpu.mainMem = &memory;
  memory.loadMemoryFromFile("core.mem");

  // Emulation loop
  while (true) {
    // Fetch the next instruction
    uint8_t instruction = memory.read(cpu.getProgramCounter());
    log.logInfo(std::format("Got instruction 0x{:02x} from memory at 0x{:04x}",
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

  // dump core memory
  memory.dumpMemoryToFile("core.mem");

  return 0;
}