/**
 *  DataPack - Essentially the same thing as the TIM image format used in the
 *  Sony Playstation's official PsyQ SDK, except without any of the positional
 *  information, and with support for multiple textures/sprites stored in a
 *  single pack.
 *
 *  All data is written in little endian form.
 *
 *  File structure:
 *  ---------------------------------------------------------------------------
 *  | Offset |  Size (*) |     Value     |                Notes               |
 *  ---------------------------------------------------------------------------
 *  |    0x0 |         2 |   Num entries | Number of files contained in this  |
 *  |        |           |               | pack.                              |
 *  ---------------------------------------------------------------------------
 *  |    0x2 |         ? |  Pack entry 0 |                                    |
 *  ---------------------------------------------------------------------------
 *  |    0x? |         ? |      ...      |                                    |
 *  ---------------------------------------------------------------------------
 *  |    0x? |         ? |  Pack entry n | Where n = (num entries - 1).       |
 *  ---------------------------------------------------------------------------
 *  * - in bytes.
 *
 *  Pack entry:
 *  ---------------------------------------------------------------------------
 *  | Offset |  Size |    Value   |                   Notes                   |
 *  ---------------------------------------------------------------------------
 *  |    0x0 |     1 |   Entry ID |                                           |
 *  ---------------------------------------------------------------------------
 *  |    0x1 |     1 |      Flags | Bit 0 (TYPE):                             |
 *  |        |       |            |   0: CLUT                                 |
 *  |        |       |            |   1: Pixel array                          |
 *  ---------------------------------------------------------------------------
 *  |    0x2 |     ? |       Data | Exact details differs. See                |
 *  |        |       |            | ColorLookupTable or PixelData for more    |
 *  |        |       |            | info.                                     |
 *  ---------------------------------------------------------------------------
 */
#ifndef _DATA_PACK_HPP_
#define _DATA_PACK_HPP_

#include "color_lookup_table.hpp"
#include "pixel_data.hpp"

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

/**
 *  Essentially the same this as the TIM image format used in the Sony
 *  Playstation's official PsyQ SDK, except without any of the positional
 *  information, and with support for multiple textures/sprites stored in a
 *  single pack.
 */
class DataPack
{
  static constexpr uint8_t FLAGS_TYPE_BIT = 0;
  std::string filename_;
  std::ofstream file;

  uint16_t num_entries;
  uint8_t entry_id_;

  ColorLookupTable clut;
  PixelData pixel_data_;

  /**
   *  Conforms a given filename to the DOS 8.3 standard.
   *  @see: https://en.wikipedia.org/wiki/8.3_filename
   */
  std::string format_filename (const std::string &filename) const noexcept;

  void export_file (void);
  void export_header (void);

public:
  static std::unordered_map<std::string, uint8_t> entry_ids;

  DataPack (const std::string &filename,
            const std::unordered_map<Color, uint8_t, ColorHasher_s> &clut_data,
            const std::vector<std::vector<uint8_t> > &pixel_data,
            uint8_t entry_id = 0);
  std::string get_filename (void) const noexcept;
};

#endif /* _DATA_PACK_HPP_ */
