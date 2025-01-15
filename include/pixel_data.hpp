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
 *  |    0x0 |        1 |           Entry ID |                                |
 *  ---------------------------------------------------------------------------
 *  |    0x1 |        1 |              Flags | Bit 0 (TYPE):                  |
 *  |        |          |                    |   0: CLUT                      |
 *  |        |          |                    |   1: Pixel array               |
 *  ---------------------------------------------------------------------------
 *  |    0x2 |        2 |   Pixel data width | Not necessarily the original   |
 *  |        |          |                    | image's width.                 |
 *  ---------------------------------------------------------------------------
 *  |    0x4 |        2 |  Pixel data height |                                |
 *  ---------------------------------------------------------------------------
 *  |    0x6 |        ? | Pixel data entry 0 |                                |
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

  const uint8_t entry_id_;
  const uint16_t width;
  const uint16_t height;

  uint16_t calculate_width (void) const noexcept;
  uint16_t calculate_height (void) const noexcept;

  void export_header (std::ofstream &fptr) const;
  void export_pixel_data (std::ofstream &fptr) const;

public:
  PixelData (const std::vector<std::vector<uint8_t> > &data,
             uint8_t entry_id) noexcept;

  void export_data (std::ofstream &fptr) const;
};

#endif /* _PIXEL_DATA_HPP_ */
