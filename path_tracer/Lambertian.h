#pragma once

#include "Material.h"
namespace PathTracer {
class Lambertian : public Material
{
public:
  Lambertian(const Color &inputAlbedo) : albedo(inputAlbedo) {}

  virtual bool scatter(
    const Ray &r_in,
    const hit_record &rec,
    Color &attenuation,
    Ray &scattered) const override;


public:  
  Color albedo;
};
}// namespace PathTracer
