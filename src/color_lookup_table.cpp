#include "color_lookup_table.hpp"
#include "data_pack.hpp"
#include "utils.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <numeric>
#include <vector>

ColorLookupTable::ColorLookupTable (
    const std::unordered_map<Color, uint8_t, ColorHasher_s> &data,
    uint8_t entry_id) noexcept : data_ (data),
                                 entry_id_ (entry_id),
                                 width (this->calculate_width ()),
                                 height (this->calculate_height ())
{
  assert (data.size () <= 16);
}

// TODO: expand to support more than just 4 bpp images.
uint16_t
ColorLookupTable::calculate_width (void) const noexcept
{
  return 16;
}

// TODO: expand to support more than just 4 bpp images.
uint16_t
ColorLookupTable::calculate_height (void) const noexcept
{
  return 1;
}

void
ColorLookupTable::export_data (std::ofstream &fptr) const
{
  this->export_header (fptr);
  add_padding_to_file (fptr);
  this->export_clut_entries (fptr);
}

void
ColorLookupTable::export_header (std::ofstream &fptr) const
{
  uint16_t prefix = this->entry_id_ & ~((1 << DataPack::FLAGS_TYPE_BIT) << 8);
  write_int16_to_file (fptr, prefix);

  write_int16_to_file (fptr, this->width);
  write_int16_to_file (fptr, this->height);
}

#include <cassert>

void
ColorLookupTable::export_clut_entries (std::ofstream &fptr) const
{
  static const Color TRANSPARENCY (0xFF, 0x00, 0xFF);
  constexpr const char *ERR_MSG = "ColorLookupTable::export_clut_entries: "
                                  "ERROR: Error exporting CLUT entries.";

  // Extract key-values from color table
  std::vector<Color> keys;
  std::vector<uint8_t> values;
  for (const auto &kv : this->data_)
    {
      keys.push_back (kv.first);
      values.push_back (kv.second);
    }

  // Sort colors based on their associated values.
  std::vector<size_t> indices (values.size ());
  std::iota (indices.begin (), indices.end (), 0);
  std::sort (indices.begin (), indices.end (), [&] (size_t a, size_t b) {
    return values.at (a) < values.at (b);
  });

  std::vector<Color> sorted_keys (keys);
  std::vector<uint8_t> sorted_values (values.size ());
  for (size_t i = 0; i < indices.size (); i++)
    {
      sorted_keys[i] = keys.at (indices.at (i));
      sorted_values[i] = values.at (indices.at (i));
    }

  /* Export clut entries. */
  uint8_t cnt;
  for (cnt = 0; cnt < sorted_keys.size (); cnt++)
    {
      const Color &color = sorted_keys.at (cnt);
      if (color == TRANSPARENCY)
        {
          fptr.write ("\0\0", 2);
          /*
              fptr.flush ();
              assert (fptr.good ());
              fptr.seekp (0x2, std::ios::cur);
           */
          if (fptr.fail ())
            throw std::runtime_error (ERR_MSG);
        }
      else
        {
          const uint8_t r = u8_to_u5 (color.get_red_value ());
          const uint8_t g = u8_to_u5 (color.get_green_value ());
          const uint8_t b = u8_to_u5 (color.get_blue_value ());
          const uint16_t entry = r | (g << 5) | (b << 10);
          write_int16_to_file (fptr, entry);
        }
    }

  fptr.seekp (0x2 * (0x10 - cnt), std::ios::cur);
  if (fptr.fail ())
    throw std::runtime_error (ERR_MSG);
}
