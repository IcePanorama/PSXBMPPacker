/**
 *  PixelData
 *
 *  See: "TIM: Screen Image Data", pp. 182-6 in 'File Formats' for more
 *  details.
 *
 *  Pixel data entry:
 *  ---------------------------------------------------------------------------
 *  | Offset | Size (*) |        Value       |             Notes              |
 *  ---------------------------------------------------------------------------
 *  |    0x0 |        1 |         Entry ID   |                                |
 *  ---------------------------------------------------------------------------
 *  |    0x1 |        4 |        Entry size  | In bytes, of the remainder of  |
 *  |        |          |                    | this entry (excluding this     |
 *  |        |          |                    | value).                        |
 *  ---------------------------------------------------------------------------
 *  |    0x5 |        2 |   Pixel data width | Not necessarily the original   |
 *  |        |          |                    | image's width.                 |
 *  ---------------------------------------------------------------------------
 *  |    0x7 |        2 |  Pixel data height |                                |
 *  ---------------------------------------------------------------------------
 *  |    0x9 |        ? | Pixel data entry 0 |                                |
 *  ---------------------------------------------------------------------------
 *  |    0x? |        ? |         ...        |                                |
 *  ---------------------------------------------------------------------------
 *  |    0x? |        ? | Pixel data entry n | Where n = (num entries - 1).   |
 *  ---------------------------------------------------------------------------
 *  * - in bytes.
 */
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
