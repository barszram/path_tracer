#include <iostream>

#include "glm/glm.hpp"
#include "glm/ext.hpp"


#include "Camera.h"
#include "Dielectric.h"
#include "Metal.h"
#include "Lambertian.h"

int main()
{
  using namespace PathTracer;    
  
  auto sphere1 = Sphere(
    .position = glm::vec3(4, 1, 0),
    .radius = 0.5f
  );

  auto sphere2 = Sphere(
    .position = glm::vec3(-4, 1, 0),
    .radius = 0.5f
  );

  auto sphere3 = Sphere(
    .position = glm::vec3(0, 1, 0),
    .radius = 0.5f
  );
	
  using MaterialImpl = std::shared_ptr<Material>;
  const auto dielectric = MaterialImpl(std::make_shared<Dielectric>(1.5));
  const auto metal = MaterialImpl(std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0));
  const auto lambertian = MaterialImpl(std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1))); 

  auto scene = Scene();
  scene.add_object(Ball(sphere1, dielectric));
  scene.add_object(Ball(sphere2, metal));
  scene.add_object(Ball(sphere3, lambertian));

  const auto camera = Camera(scene);
  const auto image = camera.make_image();
  image.save();
}
