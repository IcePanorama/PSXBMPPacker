#include "data_pack.hpp"
#include "pixel_data.hpp"
#include "utils.hpp"

#include <algorithm>
#include <format>
#include <stdexcept>

std::unordered_map<std::string, uint8_t> DataPack::entry_ids;

DataPack::DataPack (
    const std::string &filename,
    const std::unordered_map<Color, uint8_t, ColorHasher_s> &clut_data,
    const std::vector<std::vector<uint8_t> > &pixel_data, uint8_t entry_id)
    : filename_ (this->format_filename (filename)), file (), num_entries (2),
      entry_id_ (entry_id), clut (clut_data), pixel_data_ (pixel_data)
{
  file.open (this->filename_, std::ios::binary);
  if (!file.is_open ())
    throw std::runtime_error (std::format (
        "ERROR: Error opening output file, {}.\n", this->filename_));

  this->export_file ();
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

#include <format>
#include <iostream>

void
DataPack::export_file (void)
{
  this->export_header ();

  uint16_t prefix = this->entry_id_ & ~((1 << DataPack::FLAGS_TYPE_BIT) << 8);
  write_int16_to_file (this->file, prefix);
  this->clut.export_data (this->file);

  prefix = this->entry_id_ | ((1 << DataPack::FLAGS_TYPE_BIT) << 8);
  write_int16_to_file (this->file, prefix);
  this->pixel_data_.export_data (this->file);
}

void
DataPack::export_header (void)
{
  write_int16_to_file (this->file, static_cast<uint16_t> (this->num_entries));
}
