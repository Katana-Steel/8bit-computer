## 8-bit Computer Emulator

### Overview

The 8-bit Computer Emulator is a C++26 application that simulates the behavior of an 8-bit computer. It includes components such as a CPU, memory, and a logging utility to facilitate the emulation process. This project serves as an educational tool for understanding the architecture and operation of vintage computing systems.

### Features

* **CPU Simulation**: Emulates an 8-bit CPU with instruction execution, register management, and interrupt handling.
* **Memory Management**: Simulates memory operations, allowing for reading and writing to memory addresses.
* **Logging**: Provides a logging mechanism to track events and errors during emulation.

### Project Structure

```plaintext
8bit-computer-emulator
├── src
│   ├── main.cpp          # Entry point of the application
│   ├── cpu.cpp           # Implementation of the CPU class
│   ├── cpu.hpp           # Declaration of the CPU class
│   ├── memory.cpp        # Implementation of the Memory class
│   ├── memory.hpp        # Declaration of the Memory class
│   └── utils
│       ├── logger.cpp    # Implementation of the Logger class
│       └── logger.hpp    # Declaration of the Logger class
├── CMakeLists.txt        # CMake configuration file
└── README.md             # Project documentation
```

### Setup Instructions

**Clone the repository**:

**Build the project**:

**Run the emulator**:

### Usage

Once the emulator is running, you can load programs into memory and execute them. The emulator will simulate the execution of instructions and provide logging output for debugging and analysis.

### Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue for any enhancements or bug fixes.

### License

This project is licensed under the GNU GPLv3 or later License. See the LICENSE file for more details.

```plaintext
./8bit-computer-emulator
```

```plaintext
mkdir build
cd build
cmake ..
make
```

```plaintext
git clone <repository-url>
cd 8bit-computer-emulator
```
