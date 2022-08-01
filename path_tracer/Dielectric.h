#pragma once

#include "Material.h"
namespace PathTracer {
class Dielectric : public Material
{
public:
  Dielectric(double index_of_refraction) : refractionIndex(index_of_refraction) {}

  virtual bool scatter(
    const Ray &r_in,
    const hit_record &rec,
    Color &attenuation,
    Ray &scattered) const override;


public:
  double refractionIndex;
};
}// namespace PathTracer
