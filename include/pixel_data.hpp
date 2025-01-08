#ifndef _PIXEL_DATA_HPP_
#define _PIXEL_DATA_HPP_

#include <cstdint>
#include <vector>

class PixelData
{
  const std::vector<std::vector<uint8_t> > &data_;

  const uint16_t width;
  const uint16_t height;

  uint16_t calculate_width (void) const noexcept;
  uint16_t calculate_height (void) const noexcept;

public:
  PixelData (const std::vector<std::vector<uint8_t> > &data);
};

#endif /* _PIXEL_DATA_HPP_ */
