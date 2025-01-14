#include "packer_config.hpp"

#include <format>
#include <iostream>

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
