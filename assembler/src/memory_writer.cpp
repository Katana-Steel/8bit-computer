#include "memory_writer.hpp"
#include <fstream>
#include <stdexcept>

void MemoryWriter::writeToFile(const std::vector<Instruction> &instructions,
                               const std::string &outputFile) {
  std::ofstream file(outputFile, std::ios::binary);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open output file: " + outputFile);
  }

  std::vector<uint8_t> memory(65536, 0); // Initialize 64KB memory with zeros

  for (const auto &instr : instructions) {
    memory[instr.address] = instr.opcode;
    for (size_t i = 0; i < instr.operands.size(); ++i) {
      memory[instr.address + 1 + i] = instr.operands[i];
    }
  }

  file.write(reinterpret_cast<const char *>(memory.data()), memory.size());
}