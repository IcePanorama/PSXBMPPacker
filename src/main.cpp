#include "bitmap_image.hpp"
#include "data_pack.hpp"

#include <iostream>
#include <stdexcept>

int
main (void)
{
  constexpr const char *input_filename = "pipes.bmp";

  try
    {
      BitmapImage input (input_filename);
      DataPack output (input.get_filename (), input.get_color_table (),
                       input.get_pixel_array ());
      std::cout << output.get_filename () << std::endl;
    }
  catch (const std::runtime_error &e)
    {
      std::cerr << e.what () << std::endl;
    }

  return 0;
}
