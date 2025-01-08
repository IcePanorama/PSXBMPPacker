#include "color_lookup_table.hpp"

ColorLookupTable::ColorLookupTable (
    const std::unordered_map<Color, uint8_t, ColorHasher_s> &data) noexcept
    : data_ (data),
      width (this->calculate_width ()),
      height (this->calculate_height ())
{
}

uint16_t
ColorLookupTable::calculate_width (void) const noexcept
{
  return 16;
}

uint16_t
ColorLookupTable::calculate_height (void) const noexcept
{
  return 1;
}
