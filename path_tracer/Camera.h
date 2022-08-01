#pragma once

#include <optional>

#include "Image.h"
#include "Scene.h"

#include "glm/glm.hpp"

#include "Ray.h"
//#include "Sphere.h"
//#include "Scene.h"
//#include "Color.h"
#include "ImageFile.h"
//#include "Ball.h"


namespace PathTracer {
struct CameraParams
{
  float viewport_height;
  float viewport_width;
  float focal_length;
  glm::vec3 origin;
  glm::vec3 horizontal;
  glm::vec3 vertical;
  glm::vec3 lower_left_corner;
};

struct CameraDataForPixelCalculation
{
  glm::vec3 origin;
  glm::vec3 horizontal;
  glm::vec3 vertical;
  glm::vec3 lower_left_corner;
  float red;
  float green;
  float blue;
};

class Camera
{
public:
  using Pixels = std::vector<Color>;

private:
  Scene scene;
  int width = 400;
  int height = 256;
  Pixels pixels;
  int aspect_ratio() const;
  Pixels generate_pixels();

public:
  Camera(Scene inputScene) : scene(std::move(inputScene)) {}
  Camera(int inputWidth, int inputHeight, Scene inputScene) : width(inputWidth), height(inputHeight), scene(std::move(inputScene)) {}
  Image make_image();
  const Scene &get_scene() const;
};

using Discriminants = std::tuple<float, float, float>;

// float check_collision(const Ray &, const Sphere &);
// float check_collision(const Ray &, const Ball & );
// bool hit(const Ray &, const Sphere &);

std::optional<hit_record> hit(const Ray &, const Ball &);
std::tuple<bool, float> calculate_the_closest_hit_point(const Scene &, const CameraDataForPixelCalculation &, const Ray &, int samplesPerPixel);
// float checkClosestPoint(const Scene &, const Ray &, int samplesPerPixel);
hit_record send_rays_into_scene(Ray ray, Ball sceneObject, int samplesPerPixel);
// Discriminants calculate_discriminant(const Ray &, const Sphere &);
Color calculate_color(float, const Ray &);
Color calc_normal(float, const Ray &);
Color does_ray_hit_anything(const Scene &, const CameraDataForPixelCalculation &, const Ray &, int samplesPerPixel);
Discriminants calculate_discriminant(const Ray &, const Ball &);
bool isRootInRange(float root, double min, double max);
Color calculate_pixel(const Scene &, const CameraDataForPixelCalculation &, int samplesPerPixel);
}// namespace PathTracer
