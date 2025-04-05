#include "assembler.hpp"
#include "memory_writer.hpp"
#include "parser.hpp"
#include <fstream>
#include <iostream>

void Assembler::assemble(const std::string &inputFile,
                         const std::string &outputFile) {
  Parser parser;
  auto instructions = parser.parse(inputFile);

  MemoryWriter writer;
  writer.writeToFile(instructions, outputFile);
}