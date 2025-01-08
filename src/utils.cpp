#include "utils.hpp"

#include <array>
#include <stdexcept>

uint32_t
read_uint32_from_file (std::ifstream &f)
{
  std::array<uint8_t, 4> bytes;
  f.read (reinterpret_cast<char *> (bytes.data ()), bytes.size ());
  if (f.fail ())
    throw std::runtime_error ("Error reading uint32_t from file.");

  return bytes.at (0) | static_cast<uint32_t> (bytes.at (1) << 8)
         | static_cast<uint32_t> (bytes.at (2) << 16)
         | static_cast<uint32_t> (bytes.at (3) << 24);
}

Color
read_color_from_file (std::ifstream &f)
{
  std::array<uint8_t, 3> bytes;
  f.read (reinterpret_cast<char *> (bytes.data ()), bytes.size ());
  if (f.fail ())
    throw std::runtime_error ("Error reading color from file.");

  return Color (bytes.at (2), bytes.at (1), bytes.at (0));
}

void
write_int16_to_file (std::ofstream &f, uint16_t x)
{
  const uint8_t LO = x & 0xFF;
  const uint8_t HI = (x & 0xFF00) >> 8;

  f.write (reinterpret_cast<const char *> (&LO), sizeof (uint8_t));
  f.write (reinterpret_cast<const char *> (&HI), sizeof (uint8_t));

  if (f.fail ())
    throw std::runtime_error ("ERROR: Error writing int16 to file.");
}
