#include "bitmap_image.hpp"
#include "data_pack.hpp"

#include <format>
#include <fstream>
#include <iostream>
#include <stdexcept>

static void process_config_file (void);
static void process_entity_ids (std::ifstream &config_file);

int
main (void)
{
  constexpr const char *input_filename = "pipes.bmp";

  process_config_file ();

  try
    {
      BitmapImage input (input_filename);
      DataPack output (input.get_filename (), input.get_color_table (),
                       input.get_pixel_array (),
                       DataPack::entity_ids.at ("PIPE_TEXTURE"));
      std::cout << output.get_filename () << std::endl;
    }
  catch (const std::runtime_error &e)
    {
      std::cerr << e.what () << std::endl;
    }

  return 0;
}

void
process_config_file (void)
{
  constexpr const char *filename = "config.ini";
  const std::string entity_ids_section_heading = "[Entity IDs]";

  std::ifstream config_file (filename);
  if (!config_file.is_open ())
    {
      std::cerr << std::format ("WARNING: Failed to open config file, {}.\n",
                                filename);
      return;
    }

  do
    {
      std::string line (256, '\0');
      config_file.getline (line.data (), line.size ());

      if (line.empty () || config_file.fail ())
        break;
      else if (line.at (0) == ';') // ignore comments.
        continue;

      if (line.compare (0, entity_ids_section_heading.length (),
                        entity_ids_section_heading)
          == 0)
        {
          process_entity_ids (config_file);
        }
    }
  while (!config_file.eof ());
}

void
process_entity_ids (std::ifstream &config_file)
{
  while (true)
    {
      std::string entity_id (256, '\0');
      config_file.getline (entity_id.data (), entity_id.size ());
      if (entity_id.empty () || config_file.fail ())
        break;
      else if (entity_id.at (0) == ';') // ignore comments.
        continue;

      size_t delim = entity_id.find ('=');
      if (delim == std::string::npos) // skip malformed entity id lines.
        continue;

      std::string entity_name (entity_id.substr (0, delim));
      uint8_t id
          = static_cast<uint8_t> (std::stoi (entity_id.substr (delim + 1)));
      DataPack::entity_ids.insert (std::pair (entity_name, id));
    }
}
