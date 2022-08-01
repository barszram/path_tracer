#pragma once

#include "glm/glm.hpp"

namespace PathTracer {
class Ray
{
  glm::vec3 origin;
  glm::vec3 direction;

public:
  Ray(glm::vec3 inputOrigin, glm::vec3 inputDirection) : origin(inputOrigin), direction(inputDirection)
  {}
  glm::vec3 get_origin() const { return origin; }
  glm::vec3 get_direction() const { return direction; }
  glm::vec3 get_direction_length() const { return glm::normalize(direction); }
  glm::vec3 at(float t) const { return origin + t * direction; }
};
}// namespace PathTracer
