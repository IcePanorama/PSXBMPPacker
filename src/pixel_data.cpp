#include "pixel_data.hpp"

PixelData::PixelData (const std::vector<uint8_t> &data)
    : data_ (data), width (this->calculate_width ()),
      height (this->calculate_height ())
{
}

uint16_t
PixelData::calculate_width (void) const noexcept
{
  return 0;
}

uint16_t
PixelData::calculate_height (void) const noexcept
{
  return 0;
}
