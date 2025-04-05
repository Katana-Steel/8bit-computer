# 8-bit Computer Emulator

## Overview

The 8-bit Computer Emulator is a C++26 application that simulates the behavior of an 8-bit computer. It includes components such as a CPU, memory, and a logging utility to facilitate the emulation process. This project serves as an educational tool for understanding the architecture and operation of vintage computing systems.

## Features

* **CPU Simulation**: Emulates an 8-bit CPU with instruction execution, register management, and interrupt handling.
* **Memory Management**: Simulates memory operations, allowing for reading and writing to memory addresses.
* **Logging**: Provides a logging mechanism to track events and errors during emulation.

## Setup Instructions

**Clone the repository**:

**Build the project**:

**Run the emulator**:

## Usage

Once the emulator is running, you can load programs into memory and execute them. The emulator will simulate the execution of instructions and provide logging output for debugging and analysis.

**Note**: The emulator will load up to 65KB of data from the file `core.mem` and use it as the computer's memory. After execution halts, the memory will be dumped back to `core.mem`.

## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue for any enhancements or bug fixes.

## License

This project is licensed under the GNU GPLv3 or later License. See the LICENSE file for more details.

```plaintext
./8bit-computer-emulator
```

```plaintext
mkdir build
cd build
cmake -G Ninja ..
cmake --build .
```
