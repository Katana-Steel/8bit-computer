#include "memory.hpp"
#include "utils/logger.hpp"
#include <filesystem>
#include <fstream>
#include <ios>
#include <string_view>

Memory::Memory() {
  std::fill(std::begin(memoryArray), std::end(memoryArray),
            0); // Initialize memory to zero
}

uint8_t Memory::read(uint16_t address) const { return memoryArray[address]; }

void Memory::write(uint16_t address, uint8_t value) {
  memoryArray[address] = value;
}

void Memory::loadMemoryFromFile(std::string_view filename) {
  Logger log{Logger::LogLevel::ERROR};
  // Ensure the file is in the current working directory
  std::filesystem::path filePath = std::filesystem::current_path() / filename;

  if (!std::filesystem::exists(filePath)) {
    log.logError("Memory File doesn't exist\nMemory untouched");
    return;
  }

  std::ifstream file(filePath, std::ios::binary);
  if (!file.is_open()) {
    log.logError("Can't open Memory File\nMemory untouched");
    return;
  }

  // Read up to 65KB (65536 bytes) into memoryArray
  file.read(reinterpret_cast<char *>(memoryArray.data()), sizeof(memoryArray));
}

void Memory::dumpMemoryToFile(std::string_view filename) const {
  Logger log{Logger::LogLevel::ERROR};
  // Ensure the file is in the current working directory
  std::filesystem::path filePath = std::filesystem::current_path() / filename;

  std::ofstream file(filePath, std::ios::binary);
  if (!file.is_open()) {
    log.logError("Can't create Memory Dump File");
    return;
  }

  // Write the entire memoryArray to the file
  file.write(reinterpret_cast<const char *>(memoryArray.data()),
             sizeof(memoryArray));

  if (!file) {
    log.logError("Error occurred while writing to Memory Dump File");
  }
}