// copyright Rene Kjellerup 2025
// released under the GNU GPL version 3 or later
#include "parser.hpp"
#include "utils/logger.hpp"
#include <cstdint>
#include <format>
#include <fstream>
#include <sstream>
#include <stdexcept>

std::vector<Instruction> Parser::parse(const std::string &inputFile) {
  Logger log{Logger::LogLevel::INFO};
  std::ifstream file(inputFile);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open input file: " + inputFile);
  }

  std::vector<Instruction> instructions;
  std::string line;
  uint16_t address = 0;

  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string opcode;
    iss >> opcode;

    // Handle ORIGIN directive
    if (opcode == "ORIGIN") {
      uint16_t newAddress;
      iss >> std::hex >> newAddress;
      address =
          newAddress; // Update the starting address for the next instructions
      continue;       // Skip to the next line
    }
    Instruction instr;
    instr.address = address;

    if (opcode == "JMP") {
      instr.opcode = 0x50;
      uint16_t target;
      iss >> std::hex >> target;
      instr.operands.push_back((target >> 8) & 0xFF); // High byte
      instr.operands.push_back(target & 0xFF);        // Low byte
    } else if (opcode == "LDi") {
      instr.opcode = 0x10;
      uint8_t reg;
      uint16_t value;
      iss >> reg;
      iss >> value;
      instr.opcode |= reg & 0x0F; // store the dest register in the lower 4bits
      instr.operands.push_back(value & 0xFF);
      log.logInfo(std::format("LDi found load value 0x{:02x}", value));
    } else if (opcode == "LDm") {
      instr.opcode = 0x10;
      uint16_t target;
      uint8_t reg;
      iss >> reg >> std::hex >> target;
      instr.opcode |=
          (reg | 0x08) & 0x0F; // store the dest register in the lower 4bits
      instr.operands.push_back((target >> 8) & 0xFF);
      instr.operands.push_back(target & 0xFF);
      log.logInfo(std::format("LDm found load target 0x{:04x}", target));
    } else if (opcode == "ST") {
      instr.opcode = 0x20;
      uint8_t reg;
      uint16_t memAddr;
      iss >> reg >> std::hex >> memAddr;
      instr.opcode |= (reg & 0x0F); // store the src register in the lower 4bits
      instr.operands.push_back((memAddr >> 8) & 0xFF); // High byte
      instr.operands.push_back(memAddr & 0xFF);        // Low byte
    } else if (opcode == "ADD") {
      instr.opcode = 0x30;
      uint8_t reg;
      iss >> reg;
      instr.opcode |= (reg & 0x0F); // store the src register in the lower 4bits
    } else if (opcode == "SUB") {
      instr.opcode = 0x40;
      uint8_t reg;
      iss >> reg;
      instr.opcode |= (reg & 0x0F); // store the src register in the lower 4bits
    } else if (opcode == "JZ") {
      instr.opcode = 0x51;
      uint16_t target;
      iss >> std::hex >> target;
      instr.operands.push_back((target >> 8) & 0xFF); // High byte
      instr.operands.push_back(target & 0xFF);        // Low byte
    } else if (opcode == "JC") {
      instr.opcode = 0x52;
      uint16_t target;
      iss >> std::hex >> target;
      instr.operands.push_back((target >> 8) & 0xFF); // High byte
      instr.operands.push_back(target & 0xFF);        // Low byte
    } else if (opcode == "JZC") {
      instr.opcode = 0x53;
      uint16_t target;
      iss >> std::hex >> target;
      instr.operands.push_back((target >> 8) & 0xFF); // High byte
      instr.operands.push_back(target & 0xFF);        // Low byte
    } else if (opcode == "NAND") {
      instr.opcode = 0x70;
      uint8_t reg;
      iss >> reg;
      instr.opcode |= (reg & 0x0F); // store the src register in the lower 4bits
    } else if (opcode == "RAW") {   // write upto 4 bytes of raw data
      uint16_t rawData = 0;
      iss >> std::hex >> rawData;
      instr.opcode = (rawData >> 8) & 0xFF; // Store the raw data in the opcode
      if (instr.opcode == 0x00)
        instr.opcode = rawData & 0xFF;
      else
        instr.operands.push_back(rawData & 0xFF);
      rawData = 0;
      iss >> std::hex >> rawData;
      if (rawData != 0x00) {
        instr.operands.push_back((rawData >> 8) &
                                 0xFF); // Store the raw data in the opcode
        instr.operands.push_back(rawData & 0xFF);
      }
    } else {
      throw std::runtime_error("Unknown opcode: " + opcode);
    }

    instructions.push_back(instr);
    address += 1 + instr.operands.size(); // Increment address
  }

  return instructions;
}