#ifndef _UTILITIES_HPP_
#define _UTILITIES_HPP_

#include "color.hpp"

#include <cstdint>
#include <fstream>

uint32_t read_uint32_from_file (std::ifstream &fptr);
Color read_color_from_file (std::ifstream &fptr);
void write_int16_to_file (std::ofstream &fptr, uint16_t x);
void write_int32_to_file (std::ofstream &fptr, uint32_t x);
/** Pads the given file to the nearest word. */
void add_padding_to_file (std::ofstream &fptr);

inline uint8_t
u8_to_u5 (uint8_t x) noexcept
{
  return static_cast<uint8_t> ((x / 255.0) * 0x1F);
}

#endif /* _UTILITIES_HPP_ */
