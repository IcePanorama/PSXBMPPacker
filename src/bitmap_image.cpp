#include "bitmap_image.hpp"
#include "utils.hpp"

#include <format>
#include <iostream>
#include <stdexcept>

BitmapImage::BitmapImage (const std::string &filename)
    : filename_ (filename), file (filename, std::ios::binary)
{
  if (!file.is_open ())
    throw std::runtime_error (
        std::format ("Error opening file, {}", filename));

  std::cout << std::format ("Processing {}.\n", this->filename_);

  this->validate_file ();

  this->file.seekg (BitmapImage::DATA_START_OFFSET_LOC);
  if (this->file.fail () || this->file.eof ())
    throw std::runtime_error (
        "Failed to seek to location of input file's data start offset.");

  this->data_start = read_uint32_from_file (this->file);

  this->file.seekg (BitmapImage::BITMAP_DIMENSIONS_LOC);
  if (this->file.fail () || this->file.eof ())
    throw std::runtime_error (
        "Failed to seek to location of input file dimensions.");

  this->width = read_uint32_from_file (this->file);
  this->height = read_uint32_from_file (this->file);

  this->row_size = ((BitmapImage::BYTES_PER_PIXEL * this->width + 3) / 4) * 4;

  this->pixel_array.resize (this->height);
  this->process_pixel_array ();
}

void
BitmapImage::validate_file ()
{
  std::string identifier (2, '\0');
  this->file.read (identifier.data (), identifier.size ());
  if (this->file.fail ())
    throw std::runtime_error (
        std::format ("Error reading from file, {}\n", this->filename_));

  if (identifier != "BM")
    throw std::runtime_error (std::format (
        "Error: The file, {}, is not a bitmap image.", this->filename_));
}

void
BitmapImage::process_pixel_array (void)
{
  this->file.seekg (this->data_start);
  if (this->file.fail () || this->file.eof ())
    throw std::runtime_error (
        "Failed to seek to location of pixel data array.");

  const uint32_t PADDING
      = this->row_size - (this->width * BitmapImage::BYTES_PER_PIXEL);

  // Bitmaps start from bottom left corner so we're doing this in reverse.
  for (auto it = this->pixel_array.rbegin (); it != this->pixel_array.rend ();
       it++)
    {
      for (uint32_t x = 0; x < this->width; x++)
        {
          Color c = read_color_from_file (this->file);

          auto got = this->color_table.find (c);
          if (got == this->color_table.end ())
            this->color_table.insert (
                std::make_pair (c, this->color_table.size ()));

          it->push_back (this->color_table.at (c));
        }

      this->file.seekg (PADDING, std::ios_base::cur);
      if (this->file.fail () || this->file.eof ())
        throw std::runtime_error ("Error seeking through pixel array data.");
    }
}

const std::string &
BitmapImage::get_filename (void) const noexcept
{
  return this->filename_;
}

const std::unordered_map<Color, uint8_t, ColorHasher_s> &
BitmapImage::get_color_table (void) const noexcept
{
  return this->color_table;
}

const std::vector<std::vector<uint8_t> > &
BitmapImage::get_pixel_array (void) const noexcept
{
  return this->pixel_array;
}

uint32_t
BitmapImage::get_width (void) const noexcept
{
  return this->width;
}

uint32_t
BitmapImage::get_height (void) const noexcept
{
  return this->height;
}

bool
BitmapImage::operator< (const BitmapImage &other) const noexcept
{
  return this->get_size () < other.get_size ();
}

/*
 *  FIXME: gonna have to change this when we support multiple output modes.
 *  i.e., a 1-bpp img of a given width and height will end up being smaller
 *  than a 4-bpp img of the same width/height.
 */
uint32_t
BitmapImage::get_size (void) const noexcept
{
  return this->color_table.size () * this->pixel_array.size ();
}
