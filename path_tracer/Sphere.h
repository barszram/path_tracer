#pragma once

#include "glm/glm.hpp"

namespace PathTracer {
struct Sphere
{
  glm::vec3 position;
  float radius;
};
}// namespace PathTracer