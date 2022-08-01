#pragma once
#include <vector>
#include <iostream>

#include "Color.h"

namespace PathTracer {
class Image
{  
  using Pixels = std::vector<Color>;
  Pixels pixels;
  int width;
  int height;

  void write_pixel_to_file(Color, std::ofstream &);

public:
  Image() = default; 
  Image(int inputWidth, int inputHeight, Pixels inputPixels) : width(inputWidth), height(inputHeight), pixels(std::move(inputPixels)) {} 

  void save();
  void save_as_png();
};


}// namespace PathTracer
