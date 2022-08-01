#pragma once

#include <vector>

#include "Ball.h"
namespace PathTracer {
class Scene
{

public:
  std::vector<Ball> objects; 
  void add_object(Ball);
};
}// namespace PathTracer