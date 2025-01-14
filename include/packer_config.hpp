#ifndef _PACKER_CONFIGURATION_HPP_
#define _PACKER_CONFIGURATION_HPP_

#include <cstdint>
#include <fstream>
#include <string>
#include <unordered_map>

class PackerConfig
{
  static constexpr const char *default_filename = "config.ini";

  std::string filename_;
  std::ifstream file;
  std::unordered_map<std::string, uint8_t> entry_ids;
  std::string output_filename;

  void process_entry_ids (void);

public:
  PackerConfig ();
  PackerConfig (std::string filename);

  void process_config_file (void);
  void process_command_line_args (int argc, char **argv);

  const std::string &get_output_filename (void) const noexcept;
};

#endif /* _PACKER_CONFIGURATION_HPP_ */
