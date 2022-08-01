#pragma once

#include "Material.h"
namespace PathTracer {
class Metal : public Material
{
public:
  Metal(const Color &inputAlbedo, double inputFuzz) 
  : albedo(inputAlbedo)
  , fuzz(inputFuzz) 
  {    
  }

  virtual bool scatter(
    const Ray &r_in,
    const hit_record &rec,
    Color &attenuation,
    Ray &scattered) const override;


public:
  double fuzz;
  Color albedo;
};
}// namespace PathTracer