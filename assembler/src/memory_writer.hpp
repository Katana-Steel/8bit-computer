#pragma once
#include "parser.hpp"
#include <string>
#include <vector>

class MemoryWriter {
public:
  void writeToFile(const std::vector<Instruction> &instructions,
                   const std::string &outputFile);
};
