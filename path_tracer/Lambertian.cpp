#include "Lambertian.h"

using PathTracer::Lambertian;
using PathTracer::hit_record;

bool Lambertian::scatter(const Ray &r_in, const hit_record &rec, Color &attenuation, Ray &scattered) const
{

  attenuation = Color(1.0, 1.0, 1.0);
  double refraction_ratio = rec.front_face ? (1.0 / refractionIndex) : refractionIndex;

  glm::vec3 unit_direction = r_in.get_direction_length();
  glm::vec3 refracted = PathTracer::refract(unit_direction, rec.normal, refraction_ratio);

  scattered = Ray(rec.p, refracted);
  return true;
}
