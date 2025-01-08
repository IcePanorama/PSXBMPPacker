/**
 *  DataPack - Essentially the same this as the TIM image format used in the
 *  Sony Playstation's official PsyQ SDK, except without any of the positional
 *  information, and with support for multiple textures/sprites stored in a
 *  single pack.
 *
 *  All data is written in little endian form.
 *
 *  File structure:
 *  ---------------------------------------------------------------------------
 *  | Offset |  Size (*) |    Value    |                    Notes             |
 *  ---------------------------------------------------------------------------
 *  |    0x0 |         2 |     File ID |  0x0 = Sprite/Texture data           |
 *  |        |           |             |  TODO: add support for more things   |
 *  ---------------------------------------------------------------------------
 *  |    0x2 |         2 | Num entries | Number of files contained in this    |
 *  |        |           |             | pack.                                |
 *  ---------------------------------------------------------------------------
 *  (*) - in bytes.
 */
#ifndef _DATA_PACK_HPP_
#define _DATA_PACK_HPP_

#include "color_lookup_table.hpp"
#include "pixel_data.hpp"

#include <fstream>
#include <vector>

/**
 *  Essentially the same this as the TIM image format used in the Sony
 *  Playstation's official PsyQ SDK, except without any of the positional
 *  information, and with support for multiple textures/sprites stored in a
 *  single pack.
 */
class DataPack
{
  enum class FileID
  {
    FID_SPRITE_TEXTURE_DATA,
    FID_NUM_FILE_IDS
  };

  std::string filename_;
  std::ofstream file;

  FileID file_id;
  uint16_t num_entries;

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
  DataPack (const std::string &filename,
            const std::unordered_map<Color, uint8_t, ColorHasher_s> &clut_data,
            const std::vector<std::vector<uint8_t> > &pixel_data);
  std::string get_filename (void) const noexcept;
};

#endif /* _DATA_PACK_HPP_ */
