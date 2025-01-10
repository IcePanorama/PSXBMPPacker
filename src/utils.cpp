#include "utils.hpp"

#include <array>
#include <iosfwd>
#include <stdexcept>

uint32_t
read_uint32_from_file (std::ifstream &fptr)
{
  std::array<uint8_t, 4> bytes;
  fptr.read (reinterpret_cast<char *> (bytes.data ()), bytes.size ());
  if (fptr.fail ())
    throw std::runtime_error ("Error reading uint32_t from file.");

  return bytes.at (0) | static_cast<uint32_t> (bytes.at (1) << 8)
         | static_cast<uint32_t> (bytes.at (2) << 16)
         | static_cast<uint32_t> (bytes.at (3) << 24);
}

Color
read_color_from_file (std::ifstream &fptr)
{
  std::array<uint8_t, 3> bytes;
  fptr.read (reinterpret_cast<char *> (bytes.data ()), bytes.size ());
  if (fptr.fail ())
    throw std::runtime_error ("Error reading color from file.");

  return Color (bytes.at (2), bytes.at (1), bytes.at (0));
}

void
write_int16_to_file (std::ofstream &fptr, uint16_t x)
{
  const uint8_t LO = x & 0xFF;
  const uint8_t HI = (x & 0xFF00) >> 8;

  fptr.write (reinterpret_cast<const char *> (&LO), sizeof (uint8_t));
  fptr.write (reinterpret_cast<const char *> (&HI), sizeof (uint8_t));

  if (fptr.fail ())
    throw std::runtime_error ("ERROR: Error writing int16 to file.");
}

void
write_int32_to_file (std::ofstream &fptr, uint32_t x)
{
  const uint16_t LO = x & 0xFFFF;
  const uint16_t HI = (x & 0xFFFF0000) >> 16;

  write_int16_to_file (fptr, LO);
  write_int16_to_file (fptr, HI);
}

void
add_padding_to_file (std::ofstream &fptr)
{
  std::streampos current_pos = fptr.tellp ();

  size_t padding = 4 - (current_pos % 4);
  if (padding != 4)
    {
      fptr.write ("\0", padding);
      if (fptr.fail ())
        throw std::runtime_error (
            "ERROR: Error padding file to nearest word.");
    }
}
