#include "Material.h"

namespace PathTracer {
glm::vec3 refract(const glm::vec3 &uv, const glm::vec3 &n, float etai_over_etat)
{
  auto cos_theta = fminf(glm::dot(-uv, n), 1.0);
  auto r_out_perp = etai_over_etat * (uv + cos_theta * n);
  auto r_out_parallel = -sqrtf(fabs(1.0 - glm::length2(r_out_perp))) * n;
  return r_out_perp + r_out_parallel;
}
glm::vec3 reflect(const glm::vec3 &v, const glm::vec3 &n)
{ 
  return v - 2 * glm::dot(v, n) * n;
}
}// namespace PathTracer
