#include "color_lookup_table.hpp"
#include "utils.hpp"
#include <cstdint>

ColorLookupTable::ColorLookupTable (
    const std::unordered_map<Color, uint8_t, ColorHasher_s> &data) noexcept
    : data_ (data),
      width (this->calculate_width ()),
      height (this->calculate_height ())
{
}

// TODO: expand to support more than just 4 bpp images.
uint16_t
ColorLookupTable::calculate_width (void) const noexcept
{
  return 16;
}

// TODO: expand to support more than just 4 bpp images.
uint16_t
ColorLookupTable::calculate_height (void) const noexcept
{
  return 1;
}

void
ColorLookupTable::export_data (std::ofstream &fptr)
{
  // each clut entry = uint16_t
  uint32_t size
      = (this->width * sizeof (uint16_t)) * this->height + sizeof (uint32_t);
  write_int32_to_file (fptr, size);
}
