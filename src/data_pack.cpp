#include "data_pack.hpp"
#include "utils.hpp"

#include <algorithm>
#include <format>
#include <iostream>

DataPack::DataPack (const PackerConfig &config, const BitmapImage &input,
                    uint8_t entry_id)
    : config_ (config), filename_ (), file (), num_entries (2)
{
  const std::string &given_filename = this->config_.get_output_filename ();
  if (given_filename.length () == 0)
    this->filename_ = this->format_filename (input.get_filename ());
  else
    this->filename_ = this->format_filename (given_filename);

  file.open (this->filename_, std::ios::binary);
  if (!file.is_open ())
    throw std::runtime_error (std::format (
        "ERROR: Error opening output file, {}.\n", this->filename_));

  this->cluts.push_back (
      ColorLookupTable (input.get_color_table (), entry_id));
  this->pixel_data_.push_back (PixelData (input.get_pixel_array (), entry_id));
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

void
DataPack::export_pack (void)
{
  std::cout << std::format ("Exporting {}.\n", this->filename_);
  this->export_header ();

  for (const auto &clut : this->cluts)
    clut.export_data (this->file);

  for (const auto &pixel_array : this->pixel_data_)
    pixel_array.export_data (this->file);
}

void
DataPack::export_header (void)
{
  write_int16_to_file (this->file, static_cast<uint16_t> (this->num_entries));
}

void
DataPack::append (const BitmapImage &input, uint8_t entry_id)
{
  this->num_entries += 2;

  this->cluts.push_back (
      ColorLookupTable (input.get_color_table (), entry_id));
  this->pixel_data_.push_back (PixelData (input.get_pixel_array (), entry_id));
}
