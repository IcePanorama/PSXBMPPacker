#include "color_lookup_table.hpp"

ColorLookupTable::ColorLookupTable (
    const std::unordered_map<Color, uint8_t, ColorHasher_s> &data)
    : data_ (data), width (calculate_width ()), height (calculate_height ())
{
}

uint16_t
ColorLookupTable::calculate_width (void)
{
  return 16;
}

uint16_t
ColorLookupTable::calculate_height (void)
{
  return 1;
}
