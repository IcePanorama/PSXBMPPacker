#include "pixel_data.hpp"

PixelData::PixelData (const std::vector<std::vector<uint8_t> > &data) noexcept
    : data_ (data),
      width (this->calculate_width ()),
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
