#include "bitmap_image.hpp"

#include <iostream>
#include <stdexcept>

int
main (void)
{
  constexpr const char *input_filename = "pipes.bmp";

  try
    {
      BitmapImage input (input_filename);
      std::cout << input.get_filename () << std::endl;
    }
  catch (const std::runtime_error &e)
    {
      std::cerr << e.what () << std::endl;
    }

  return 0;
}
