#ifndef _COLOR_LOOKUP_TABLE_HPP_
#define _COLOR_LOOKUP_TABLE_HPP_

#include "color.hpp"

#include <unordered_map>

class ColorLookupTable
{
  const std::unordered_map<Color, uint8_t, ColorHasher_s> &data_;

  const uint16_t width;
  const uint16_t height;

  uint16_t calculate_width (void) const noexcept;
  uint16_t calculate_height (void) const noexcept;

public:
  ColorLookupTable (
      const std::unordered_map<Color, uint8_t, ColorHasher_s> &data) noexcept;
};

#endif /* _COLOR_LOOKUP_TABLE_HPP_ */
