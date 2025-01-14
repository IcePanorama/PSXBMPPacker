#include "bitmap_image.hpp"
#include "data_pack.hpp"
#include "packer_config.hpp"

#include <iostream>
#include <stdexcept>

int
main (int argc, char **argv)
{
  constexpr const char *input_filename = "pipes.bmp";

  PackerConfig config;
  config.process_config_file ();

  if (argc > 2)
    config.process_command_line_args (argc, argv);

  try
    {
      BitmapImage input (input_filename);
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
