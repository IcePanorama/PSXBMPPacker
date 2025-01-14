#include "bitmap_image.hpp"
#include "data_pack.hpp"
#include "packer_config.hpp"

#include <format>
#include <iostream>
#include <stdexcept>

int
main (void)
{
  constexpr const char *input_filename = "pipes.bmp";
  PackerConfig config;

  config.process_config_file ();

  try
    {
      std::cout << std::format ("Processing {}...\n", input_filename);
      BitmapImage input (input_filename);
      DataPack output (input.get_filename (), input.get_color_table (),
                       input.get_pixel_array ());
      std::cout << std::format ("Created {}.\n", output.get_filename ());
    }
  catch (const std::runtime_error &e)
    {
      std::cerr << e.what () << std::endl;
    }

  return 0;
}
