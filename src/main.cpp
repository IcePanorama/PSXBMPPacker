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

      DataPack output (config, input_files.at (0), 0);

      // TODO: handle different entry ids for different sections of the pack.
      for (size_t i = 1; i < input_files.size (); i++)
        output.append (input_files.at (i), 1);

      output.export_pack ();
    }
  catch (const std::runtime_error &e)
    {
      std::cerr << e.what () << std::endl;
      return -1;
    }

  std::cout << "Done.\n";
  return 0;
}
