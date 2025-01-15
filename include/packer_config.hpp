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
  void process_input_files (int argc, char **argv, int arg_pos);

public:
  PackerConfig ();
  PackerConfig (std::string filename);

  std::vector<std::string> input_filenames;

  void process_config_file (void);
  void process_command_line_args (int argc, char **argv);

  const std::string &get_output_filename (void) const noexcept;
};

#endif /* _PACKER_CONFIGURATION_HPP_ */
