#ifndef _PACKER_CONFIGURATION_HPP_
#define _PACKER_CONFIGURATION_HPP_

#include "bitmap_image.hpp"

#include <cstdint>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

class PackerConfig
{
  static constexpr const char *default_filename = "config.ini";

  /**
   *  Contains entry ids listed in config file along with their related uint8
   *  value.
   */
  std::unordered_map<std::string, uint8_t> entry_id_lookup;
  std::string filename_;
  std::ifstream file;
  std::string output_filename;
  /**
   *  Entry ids optionally provided via command line arugment. Should
   *  correspond to keys in `entry_id_lookup`. Defaults to 0's if nothing is
   *  provided.
   */
  std::vector<uint8_t> entry_ids;

  void process_entry_ids (void);
  /**
   *  `arg_pos` is the index of the current argument being processed (in this
   *  case, the flag).
   *  @returns  index of the next command line argument - 1
   */
  int process_flags (int argc, char **argv, int arg_pos);
  /**
   *  `arg_pos` is the index of the current argument being processed (in this
   *  case, an input filename). File verification is NOT done here. The list of
   *  input files MUST come last in the list of command line arguments as input
   *  file processing is treated as the final step of the command line argument
   *  processing pipeline.
   *  @see BitmapImage::BitmapImage
   *  @see BitmapImage::validate_file
   */
  void process_input_files (int argc, char **argv, int arg_pos);
  void process_entry_id_associations (std::string list);
  void pad_entry_ids (size_t target_size) noexcept;

public:
  PackerConfig ();
  PackerConfig (std::string filename);

  std::vector<std::string> input_filenames;
  bool batch_processing;
  std::unordered_map<std::string, uint8_t> entry_id_register;
  bool sort_largest_first;

  void process_config_file (void);
  void process_command_line_args (int argc, char **argv);
  void register_entry_ids (const std::vector<BitmapImage> &images);

  const std::string &get_output_filename (void) const noexcept;
};

#endif /* _PACKER_CONFIGURATION_HPP_ */
