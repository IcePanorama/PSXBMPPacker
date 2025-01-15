#include "bitmap_image.hpp"
#include "data_pack.hpp"
#include "packer_config.hpp"

#include <iostream>
#include <stdexcept>

int
main (int argc, char **argv)
{
  PackerConfig config;
  std::vector<BitmapImage> input_files;

  try
    {
      config.process_config_file ();

      if (argc > 1)
        config.process_command_line_args (argc, argv);

      if (config.input_filenames.size () == 0)
        return 0;

      for (const auto &filename : config.input_filenames)
        {
          input_files.push_back (BitmapImage (filename));
        }

      config.pad_entry_ids (input_files.size ());

      if (config.batch_processing)
        {
          DataPack output (config, input_files.at (0), config.entry_ids.at(0));

          for (size_t i = 1; i < input_files.size (); i++)
            output.append (input_files.at (i), config.entry_ids.at (i));

          output.export_pack ();
        }
      else
        {
          for (size_t i = 0; i < input_files.size (); i++)
            {
              DataPack output (config, input_files.at (i),
                               config.entry_ids.at (i));
              output.export_pack ();
            }
        }
    }
  catch (const std::runtime_error &e)
    {
      std::cerr << e.what ();
      return -1;
    }

  std::cout << "Done.\n";
  return 0;
}
