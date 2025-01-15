#include "pixel_data.hpp"
#include "data_pack.hpp"
#include "utils.hpp"

PixelData::PixelData (const std::vector<std::vector<uint8_t> > &data,
                      uint8_t entry_id) noexcept
    : data_ (data),
      entry_id_ (entry_id),
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
PixelData::export_data (std::ofstream &fptr) const
{
  this->export_header (fptr);
  add_padding_to_file (fptr);
  this->export_pixel_data (fptr);
}

#include <format>
#include <iostream>

void
PixelData::export_header (std::ofstream &fptr) const
{
  uint16_t prefix = this->entry_id_ | ((1 << DataPack::FLAGS_TYPE_BIT) << 8);
  std::cout << std::format ("{:04X}\n", prefix);
  write_int16_to_file (fptr, prefix);

  write_int16_to_file (fptr, this->width);
  write_int16_to_file (fptr, this->height);
}

void
PixelData::export_pixel_data (std::ofstream &fptr) const
{
  for (const auto &row : this->data_)
    {
      for (size_t i = 0; i + 3 < row.size (); i += 4)
        {
          uint16_t value = row.at (i);
          value |= (row.at (i + 1) << 4);
          value |= (row.at (i + 2) << 8);
          value |= (row.at (i + 3) << 12);
          write_int16_to_file (fptr, value);
        }
    }
}
