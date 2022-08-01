#include "Metal.h"

namespace PathTracer {
bool Metal::scatter(const Ray &r_in, const hit_record &rec, Color &attenuation, Ray &scattered) const
{
  glm::vec3 reflected = reflect(r_in.get_direction_length(), rec.normal);
  scattered = Ray(rec.p, reflected);
  attenuation = albedo;
  return (glm::dot(scattered.get_direction(), rec.normal) > 0);
}
}

