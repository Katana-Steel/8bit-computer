#pragma once
#include <cstdint>
#include <string>
#include <vector>

struct Instruction {
  uint16_t address;
  uint8_t opcode;
  std::vector<uint8_t> operands;
};

class Parser {
public:
  std::vector<Instruction> parse(const std::string &inputFile);
};