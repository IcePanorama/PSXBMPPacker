#ifndef _DATA_PACK_HPP_
#define _DATA_PACK_HPP_

#include <fstream>
class DataPack
{
  std::string filename_;
  std::ofstream file;

public:
  DataPack (const std::string &filename);
};

#endif /* _DATA_PACK_HPP_ */
