#include "Image.h"


#include <iostream>
#include <limits>

#include "Camera.h"

using namespace PathTracer;


void Image::write_pixel_to_file(Color pixel, std::ofstream &imageFile)
{
  const auto max_value = 256;
  imageFile << static_cast<int>(max_value * glm::clamp(pixel.r, 0.0f, 0.999f)) << ' '
            << static_cast<int>(max_value * glm::clamp(pixel.g, 0.0f, 0.999f)) << ' '
            << static_cast<int>(max_value * glm::clamp(pixel.b, 0.0f, 0.999f)) << '\n';
}

void Image::save()
{
  // ImageFile imageFile;
  std::ofstream imageFile{ "image.ppm" };

  // write_image_header
  imageFile << "P3\n"
            << width << ' ' << height << "\n255\n";
  // write pixels
  for (const auto &pixel : pixels) {
    write_pixel_to_file(pixel, imageFile);
  }
  std::cerr << "\nDone.\n";
}

void Image::save_as_png()
{
  // ImageFile imageFile;
  std::ofstream imageFile{ "image.png" };

  // write_image_header
  imageFile << "137 80 78 71 13 10 26 10"
            << width << ' ' << height << "\n255\n";
  // write pixels
  for (const auto &pixel : pixels) {
    write_pixel_to_file(pixel, imageFile);
  }
  std::cerr << "\nDone.\n";
}
