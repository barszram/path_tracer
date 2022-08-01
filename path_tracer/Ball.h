#pragma once

#include <memory>

#include "Sphere.h"
#include "Material.h"

namespace PathTracer {
class Ball
{  
  using MaterialImpl = std::shared_ptr<const Material>;
  Sphere sphere;
  MaterialImpl material;

public:
  Ball(const Sphere &inputSphere, const MaterialImpl &inputMaterial) : sphere{ inputSphere }, material{ inputMaterial } {}

  const Sphere &getSphere() const { return sphere; }
  const MaterialImpl &getMaterial() const { return material; }
};
}// namespace PathTracer