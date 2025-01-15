#ifndef _PACKER_CONFIGURATION_HPP_
#define _PACKER_CONFIGURATION_HPP_

#include <cstdint>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

class PackerConfig
{
  static constexpr const char *default_filename = "config.ini";

  std::string filename_;
  std::ifstream file;
  std::unordered_map<std::string, uint8_t> entry_ids;
  std::string output_filename;

  void process_entry_ids (void);
  /**
   *  `arg_pos` is the index of the current argument being processed (in this
   *  case, the flag).
   *  @returns  index of the next command line argument - 1
   */
  int process_flags (int argc, char **argv, int arg_pos);

  /**
   *  `arg_pos` is the index of the current argument being processed (in this
   *  case, an input filename). File verification is NOT done here.
   *  @returns  index of the next command line argument - 1
   *  @see BitmapImage::BitmapImage
   *  @see BitmapImage::validate_file
   */
  int process_input_files (int argc, char **argv, int arg_pos);

public:
  PackerConfig ();
  PackerConfig (std::string filename);

  std::vector<std::string> input_filenames;

  void process_config_file (void);
  void process_command_line_args (int argc, char **argv);

  const std::string &get_output_filename (void) const noexcept;
};

#endif /* _PACKER_CONFIGURATION_HPP_ */
