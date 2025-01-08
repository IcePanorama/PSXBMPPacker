#ifndef _DATA_PACK_HPP_
#define _DATA_PACK_HPP_

#include "color_lookup_table.hpp"

#include <fstream>

class DataPack
{
  std::string filename_;
  std::ofstream file;

  ColorLookupTable clut;

  /**
   *  Conforms a given filename to the DOS 8.3 standard.
   *  @see: https://en.wikipedia.org/wiki/8.3_filename
   */
  std::string format_filename (const std::string &filename) const noexcept;

public:
  DataPack (
      const std::string &filename,
      const std::unordered_map<Color, uint8_t, ColorHasher_s> &clut_data);
  std::string get_filename (void) const noexcept;
};

#endif /* _DATA_PACK_HPP_ */
