#include "data_pack.hpp"

#include <algorithm>
#include <format>
#include <stdexcept>

DataPack::DataPack (
    const std::string &filename,
    const std::unordered_map<Color, uint8_t, ColorHasher_s> &clut_data)
    : filename_ (this->format_filename (filename)), file (), clut (clut_data)
{
  file.open (this->filename_, std::ios::binary);
  if (!file.is_open ())
    throw std::runtime_error (std::format (
        "ERROR: Error opening output file, {}.\n", this->filename_));
}

std::string
DataPack::format_filename (const std::string &filename) const noexcept
{
  std::string output (filename);

  if (output.length () > 8)
    output = output.substr (0, 8);

  size_t extension_loc = output.find ('.');
  if (extension_loc != std::string::npos)
    output = output.substr (0, extension_loc);

  std::transform (output.begin (), output.end (), output.begin (), ::toupper);

  output.append (".DAT");
  return output;
}

std::string
DataPack::get_filename (void) const noexcept
{
  return this->filename_;
}
