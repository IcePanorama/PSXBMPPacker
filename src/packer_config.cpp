#include "packer_config.hpp"

#include <array>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <format>
#include <iostream>
#include <stdexcept>
#include <string>

PackerConfig::PackerConfig ()
    : filename_ (PackerConfig::default_filename), batch_processing (true)
{
}

PackerConfig::PackerConfig (std::string filename)
    : filename_ (filename), batch_processing (true)
{
}

void
PackerConfig::process_config_file (void)
{
  const std::string entry_ids_section_heading = "[Entity IDs]";

  this->file.open (this->filename_);
  if (!this->file.is_open ())
    {
      std::cerr << std::format (
          "{}: WARNING: Failed to open config file, {}.\n",
          __PRETTY_FUNCTION__, this->filename_);
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

// TODO: modify how we're doing this so that these are actually usable.
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
      this->entry_id_lookup.insert (std::pair (entry_name, id));
    }
}

const std::string &
PackerConfig::get_output_filename (void) const noexcept
{
  return this->output_filename;
}

void
PackerConfig::process_command_line_args (int argc, char **argv)
{

  for (int i = 1; i < argc; i++) // skip executable name.
    {
      if (!std::isalnum (argv[i][0]))
        {
          i = this->process_flags (argc, argv, i);
        }
      else
        {
          this->process_input_files (argc, argv, i);
          break;
        }
    }
}

int
PackerConfig::process_flags (int argc, char **argv, int arg_pos)
{
  static constexpr const char *invalid_usage_err_fmt
      = "{}: ERROR: Invalid usage error.\n\ttry: \t{} [-o output-filename] "
        "path/to/input.bmp ...";
  enum ARGS_e
  {
    ARG_OUTPUT_FILENAME,
    ARG_NO_BATCH_PROCESSING,
    ARG_ENTRY_IDS,
    ARG_NUM_ARGS
  };
  std::array<std::string, ARG_NUM_ARGS> command_line_args
      = { "-o", "-s", "-e" };

  int i;
  for (i = arg_pos; i < argc; i++)
    {
      if (command_line_args.at (ARG_OUTPUT_FILENAME).compare (argv[i]) == 0)
        {
          if (i + 1 == argc)
            throw std::runtime_error (std::format (
                invalid_usage_err_fmt, __PRETTY_FUNCTION__, argv[0]));

          this->output_filename = argv[++i];
        }
      else if (command_line_args.at (ARG_NO_BATCH_PROCESSING).compare (argv[i])
               == 0)
        {
          batch_processing = false;
        }
      else if (command_line_args.at (ARG_ENTRY_IDS).compare (argv[i]) == 0)
        {
          if (i + 1 == argc)
            throw std::runtime_error (std::format (
                invalid_usage_err_fmt, __PRETTY_FUNCTION__, argv[0]));

          this->process_entry_id_associations (argv[++i]);
        }
      else
        {
          if (!std::isalnum (argv[i][0]))
            throw std::runtime_error (std::format (
                invalid_usage_err_fmt, __PRETTY_FUNCTION__, argv[0]));

          return i - 1;
        }
    }

  return i;
}

void
PackerConfig::process_input_files (int argc, char **argv, int arg_pos)
{
  for (int i = arg_pos; i < argc; i++)
    {
      if (!std::isalnum (argv[i][0]))
        break;

      this->input_filenames.push_back (argv[i]);
    }
}

void
PackerConfig::process_entry_id_associations (std::string list)
{
  static constexpr const char *invalid_entry_id_err_fmt
      = "{}: ERROR: Invalid entry id, {}.\n";
  std::vector<std::string> given_ids;

  size_t delim = 0;
  while (true)
    {
      if (list.length () == 0 || delim == std::string::npos)
        break;

      delim = list.find (',');
      given_ids.push_back (std::string (list.substr (0, delim)));
      list = list.substr (delim + 1);
    }

  for (const auto &id : given_ids)
    {
      const auto &got = this->entry_id_lookup.find (id);
      if (got == this->entry_id_lookup.end ())
        throw std::runtime_error (
            std::format (invalid_entry_id_err_fmt, __PRETTY_FUNCTION__, id));

      this->entry_ids.push_back (this->entry_id_lookup.at (id));
    }
}

void
PackerConfig::pad_entry_ids (size_t target_size) noexcept
{
  if (this->entry_ids.size () >= target_size)
    return;

  uint8_t last_element;
  if (this->entry_ids.size () == 0)
    last_element = 0;
  else
    last_element = this->entry_ids.back ();
  this->entry_ids.resize (target_size, last_element);
}
