#include "packer_config.hpp"

#include <array>
#include <format>
#include <iostream>
#include <stdexcept>
#include <string>

PackerConfig::PackerConfig () : filename_ (PackerConfig::default_filename) {}

PackerConfig::PackerConfig (std::string filename) : filename_ (filename) {}

void
PackerConfig::process_config_file (void)
{
  const std::string entry_ids_section_heading = "[Entity IDs]";

  this->file.open (this->filename_);
  if (!this->file.is_open ())
    {
      std::cerr << std::format ("PackerConfig::process_config_file: WARNING: "
                                "Failed to open config file, {}.\n",
                                this->filename_);
      return;
    }

  do
    {
      std::string line (256, '\0');
      this->file.getline (line.data (), line.size ());

      if (line.empty () || this->file.fail ())
        break;
      else if (line.at (0) == ';') // ignore comments.
        continue;

      if (line.compare (0, entry_ids_section_heading.length (),
                        entry_ids_section_heading)
          == 0)
        {
          this->process_entry_ids ();
        }
    }
  while (!this->file.eof ());
}

void
PackerConfig::process_entry_ids (void)
{
  while (true)
    {
      std::string entry_id (256, '\0');
      this->file.getline (entry_id.data (), entry_id.size ());
      if (entry_id.empty () || this->file.fail ())
        break;
      else if (entry_id.at (0) == ';') // ignore comments.
        continue;

      size_t delim = entry_id.find ('=');
      if (delim == std::string::npos) // skip malformed entry id lines.
        continue;

      std::string entry_name (entry_id.substr (0, delim));
      uint8_t id
          = static_cast<uint8_t> (std::stoi (entry_id.substr (delim + 1)));
      this->entry_ids.insert (std::pair (entry_name, id));
    }
}

void
PackerConfig::process_command_line_args (int argc, char **argv)
{
  enum ARGS_e
  {
    ARG_OUTPUT_FILENAME,
    ARG_NUM_ARGS
  };

  std::array<std::string, 1> command_line_args = { "-o" };

  for (int i = 1; i < argc; i++) // skip executable name.
    {
      if (command_line_args.at (ARG_OUTPUT_FILENAME).compare (argv[i]) == 0)
        {
          if (i + 1 == argc)
            throw std::runtime_error (
                std::format ("PackerConfig::process_command_line_args: ERROR: "
                             "Invalid usage error."));
          this->output_filename = argv[++i];
        }
    }
}

const std::string &
PackerConfig::get_output_filename (void) const noexcept
{
  return this->output_filename;
}
