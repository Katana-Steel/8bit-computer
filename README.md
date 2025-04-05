# 8-bit Computer and Assembler

## Overview

This project consists of two main components:

1. **8-bit Computer Emulator**: A C++26 application that simulates the behavior of an 8-bit computer, including a CPU, memory, and logging utilities.
2. **Assembly Compiler**: A C++26 application that parses assembly code and compiles it into a binary format compatible with the 8-bit Computer Emulator. The compiled program is written to a `core.mem` file, which can be loaded into the emulator.

Together, these components provide a complete environment for writing, compiling, and running programs on a simulated 8-bit computer.

## Features

**CPU** features:

    * 7 basic instructions
    * 16bit addressing

**Memory** features:

    * 65Kb core memory

**Assembler** features:

    * builds core.mem from asm files
    * use ORIGIN to set instruction starting point

## Setup Instructions

**Clone the repository**:

**Build the project**:

```bash
mkdir build
cd build
cmake -G Ninja ..
cmake --build .
```

**Run the emulator**:

```bash
assembler/assembly_compiler ../samples/input.asm core.mem
computer/8bit_computer_emulator
hexdump -C core.mem
```

## Usage

Once the emulator is running, it will load the program from `core.mem` into memory and execute them. The emulator will simulate the execution of instructions and provide logging output for debugging and analysis.

**Note**: The emulator will load up to 65KB of data from the file `core.mem` and use it as the computer's memory. After execution halts, the memory will be dumped back to `core.mem`.

## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue for any enhancements or bug fixes.

## License

This project is licensed under the GNU GPLv3 or later License. See the LICENSE file for more details.
