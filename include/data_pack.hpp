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

#include "bitmap_image.hpp"
#include "color_lookup_table.hpp"
#include "packer_config.hpp"
#include "pixel_data.hpp"

#include <cstdint>
#include <fstream>
#include <string>

/**
 *  Essentially the same this as the TIM image format used in the Sony
 *  Playstation's official PsyQ SDK, except without any of the positional
 *  information, and with support for multiple textures/sprites stored in a
 *  single pack.
 */
class DataPack
{
  static constexpr uint8_t FLAGS_TYPE_BIT = 0;

  const PackerConfig &config_;
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

  std::string get_filename (void) const noexcept;
  void export_header (void);

public:
  DataPack (const PackerConfig &config, const BitmapImage &input,
            uint8_t entry_id = 0);

  void export_pack (void);
};

#endif /* _DATA_PACK_HPP_ */
