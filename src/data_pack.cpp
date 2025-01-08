#include "data_pack.hpp"

DataPack::DataPack (const std::string &filename)
    : filename_ (filename), file ()
{
  file.open (this->filename_, std::ios::binary);
}
