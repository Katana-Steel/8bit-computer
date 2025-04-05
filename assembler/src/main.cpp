#include "assembler.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <input.asm> <output.mem>\n";
    return 1;
  }

  const std::string inputFile = argv[1];
  const std::string outputFile = argv[2];

  try {
    Assembler assembler;
    assembler.assemble(inputFile, outputFile);
    std::cout << "Assembly successful! Output written to " << outputFile
              << "\n";
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}