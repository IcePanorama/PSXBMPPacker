#include "pixel_data.hpp"

PixelData::PixelData (const std::vector<std::vector<uint8_t> > &data) noexcept
    : data_ (data),
      width (this->calculate_width ()),
      height (this->calculate_height ())
{
}

/**
 *  Currently assumes that all images are 4 bpp.
 *  TODO: expand support for other types of images.
 */
uint16_t
PixelData::calculate_width (void) const noexcept
{
  if (this->data_.size () == 0)
    return 0;

  return (this->data_.at (0).size () >> 2);
}

uint16_t
PixelData::calculate_height (void) const noexcept
{
  return this->data_.size ();
}

void
PixelData::export_header (std::ofstream &fptr)
{
  if (fptr.fail ())
    return;
}
