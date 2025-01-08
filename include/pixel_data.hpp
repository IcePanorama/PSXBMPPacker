#ifndef _PIXEL_DATA_HPP_
#define _PIXEL_DATA_HPP_

#include <cstdint>
#include <fstream>
#include <vector>

class PixelData
{
  const std::vector<std::vector<uint8_t> > &data_;

  const uint16_t width;
  const uint16_t height;

  uint16_t calculate_width (void) const noexcept;
  uint16_t calculate_height (void) const noexcept;

  void export_header (std::ofstream &fptr);
  void export_pixel_data (std::ofstream &fptr);

public:
  PixelData (const std::vector<std::vector<uint8_t> > &data) noexcept;

  void export_data (std::ofstream &fptr);
};

#endif /* _PIXEL_DATA_HPP_ */
