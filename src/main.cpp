#include "bitmap_image.hpp"
#include "data_pack.hpp"
#include "packer_config.hpp"

#include <iostream>
#include <stdexcept>

int
main (int argc, char **argv)
{
  try
    {
      PackerConfig config;
      config.process_config_file ();

      if (argc > 1)
        config.process_command_line_args (argc, argv);

      if (config.input_filenames.size () == 0)
        return 0;

      BitmapImage input (config.input_filenames.at (0));
      DataPack output (config, input);
      output.export_pack ();
      std::cout << "Done.\n";
    }
  catch (const std::runtime_error &e)
    {
      std::cerr << e.what () << std::endl;
    }

  return 0;
}
