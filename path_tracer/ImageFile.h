#pragma once

#include <fstream>
#include <string>

class ImageFile
{

  std::ofstream imageFile = std::ofstream{ "image.ppm" };
public:
  ImageFile() = default;
  ImageFile(std::string inputFileName) : imageFile{ inputFileName }
  {
    imageFile = std::ofstream(inputFileName);
  }


  
};
