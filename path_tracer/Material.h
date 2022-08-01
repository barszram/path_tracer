#pragma once

#include "Ray.h"
#include "Color.h"

#include "glm/gtx/norm.hpp"

//struct hit_record;
namespace PathTracer {
struct hit_record
{
  glm::vec3 p;
  glm::vec3 normal;
  float t;
  bool front_face;

  void set_face_normal(const Ray &ray, const glm::vec3 &outwardNormal)
  {
    front_face = glm::dot(ray.get_direction(), outwardNormal) < 0;
    normal = front_face ? outwardNormal : -outwardNormal;
  }
};


struct Material
{
  virtual bool scatter(
    const Ray &r_in,
    const hit_record &rec,
    Color &attenuation,
    Ray &scattered) const = 0;
  virtual ~Material() = default;
  // Material(const Material &) = default; // good?
  // Material(Material &&) = default;
  // Material &operator=(const Material &) = default;
  // Material &operator=(Material &&) = default;
};

glm::vec3 refract(const glm::vec3 &uv, const glm::vec3 &n, float etai_over_etat);
glm::vec3 reflect(const glm::vec3 &v, const glm::vec3 &n);
}


