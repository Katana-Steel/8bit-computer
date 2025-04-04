#include <array>
#include <cstdint>
class Memory {
public:
  Memory();

  uint8_t read(uint16_t address) const;
  void write(uint16_t address, uint8_t value);

private:
  // max memory of 16bit addressing for the 8bit computer
  std::array<uint8_t, UINT16_MAX> memoryArray;
};