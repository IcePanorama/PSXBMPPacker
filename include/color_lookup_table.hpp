/**
 *  ColorLookupTable
 *
 *  See: "TIM: Screen Image Data", pp. 182-6 in 'File Formats' for more
 *  details.
 *
 *  Clut entry:
 *  ---------------------------------------------------------------------------
 *  | Offset | Size (*) |     Value    |                 Notes                |
 *  ---------------------------------------------------------------------------
 *  |    0x0 |        1 |     Entry ID |                                      |
 *  ---------------------------------------------------------------------------
 *  |    0x1 |        1 |        Flags | Bit 0 (TYPE):                        |
 *  |        |          |              |   0: CLUT                            |
 *  |        |          |              |   1: Pixel array                     |
 *  ---------------------------------------------------------------------------
 *  |    0x2 |        2 |   CLUT width |                                      |
 *  ---------------------------------------------------------------------------
 *  |    0x4 |        2 |  CLUT height |                                      |
 *  ---------------------------------------------------------------------------
 *  |    0x6 |        ? | CLUT entry 0 |                                      |
 *  ---------------------------------------------------------------------------
 *  |    0x? |        ? |      ...     |                                      |
 *  ---------------------------------------------------------------------------
 *  |    0x? |        ? | CLUT entry n | Where n = (num entries - 1).         |
 *  ---------------------------------------------------------------------------
 *  * - in bytes.
 */
#ifndef _COLOR_LOOKUP_TABLE_HPP_
#define _COLOR_LOOKUP_TABLE_HPP_

#include "color.hpp"

#include <fstream>
#include <unordered_map>

class ColorLookupTable
{
  const std::unordered_map<Color, uint8_t, ColorHasher_s> &data_;

  const uint8_t entry_id_;
  const uint16_t width;
  const uint16_t height;

  uint16_t calculate_width (void) const noexcept;
  uint16_t calculate_height (void) const noexcept;

  void export_header (std::ofstream &fptr) const;
  void export_clut_entries (std::ofstream &fptr) const;

public:
  ColorLookupTable (
      const std::unordered_map<Color, uint8_t, ColorHasher_s> &data,
      uint8_t entry_id) noexcept;

  void export_data (std::ofstream &fptr) const;
};

#endif /* _COLOR_LOOKUP_TABLE_HPP_ */
