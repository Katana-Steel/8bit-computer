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
  if (!memory.loadMemoryFromFile("core.mem")) {
    /// okay let's load a small add program
    memory.write(0xfe00, 0x50); /// jmp 0x0000
    memory.write(0x0000, 0x18); /// ld ax 0xfe00
    memory.write(0x0001, 0xfe); //// address for the load
    memory.write(0x0003, 0x19); /// ld bx 0xfe00
    memory.write(0x0004, 0xfe); //// address for the load
    memory.write(0x0006, 0x31); /// add ax bx
    memory.write(0x0007, 0x20); /// st ax 0xfe05
    memory.write(0x0008, 0xfe); //// high byte for the store address
    memory.write(0x0009, 0x05); //// low byte for the store address
  }
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