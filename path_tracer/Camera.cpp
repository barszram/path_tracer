#include "Camera.h"

#include <iostream>
#include <numeric>

// using namespace PathTracer;
namespace PathTracer {

int Camera::aspect_ratio() const
{
  return 16 / 9;
}

Camera::Pixels Camera::generate_pixels()
{
  for (int j = height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < width; ++i) {
      const auto r = float(i) / (width - 1);
      const auto g = float(j) / (height - 1);
      const auto b = 0.25;

      // camera parameters
      const auto viewport_height = 2.0f;
      const auto viewport_width = aspect_ratio() * viewport_height;
      const auto focal_length = 1.0f;
      const auto origin = glm::vec3(0, 0, 0);
      const auto horizontal = glm::vec3(viewport_width, 0, 0);
      const auto vertical = glm::vec3(0, viewport_height, 0);
      const auto lower_left_corner = origin - horizontal * 0.5f - vertical * 0.5f - glm::vec3(0, 0, focal_length);


      CameraParams cameraParams{
        .viewport_height = viewport_height,
        .viewport_width = viewport_width,
        .focal_length = focal_length,
        .origin = origin,
        .horizontal = horizontal,
        .vertical = vertical,
        .lower_left_corner = lower_left_corner
      };


      CameraDataForPixelCalculation cameraDataForPixelCalculation{
        .origin = origin,
        .horizontal = horizontal,
        .vertical = vertical,
        .lower_left_corner = lower_left_corner,
        .red = r,
        .green = g,
        .blue = b
      };

      const auto samplesPerPixel = 100;
      Color pixel = calculate_pixel(scene, cameraDataForPixelCalculation, samplesPerPixel);

      auto red = pixel.r;
      auto green = pixel.g;
      auto blue = pixel.b;
      const auto scale = 1.0f / samplesPerPixel;
      red *= scale;
      green *= scale;
      blue *= scale;

      Color newPixel = { red, green, blue };


      pixels.push_back(newPixel);
    }
  }
  return pixels;
}

Image Camera::make_image()
{
  auto pixels = generate_pixels();
  return Image(width, height, pixels);
}

const Scene &PathTracer::Camera::get_scene() const
{
  return scene;
}

Color calculate_color(float pointInRange, const Ray &ray)
{
  const auto n = glm::vec3{ ray.at(pointInRange) - glm::vec3{ 0, 0, -1 } };
  return 0.5f * glm::vec3{ n.x + 1, n.y + 1, n.z + 1 };
}

Color calc_normal(float pointInRange, const Ray &ray)
{
  const auto unitDirection = ray.get_direction_length();
  pointInRange = 0.5f * (unitDirection.y + 1.0f);
  return { (1.0f - pointInRange) * Color(1.0, 1.0, 1.0) + pointInRange * Color(0.5, 0.7, 1.0) };
}

Color does_ray_hit_anything(const Scene &scene, const CameraDataForPixelCalculation &cameraDataForPixelCalculation, const Ray &ray, int samplesPerPixel)
{
  auto [isHit, pointInRange] = calculate_the_closest_hit_point(scene, cameraDataForPixelCalculation, ray, samplesPerPixel);  
  return isHit ? calculate_color(pointInRange, ray) : calc_normal(pointInRange, ray);
}

Discriminants calculate_discriminant(const Ray &ray, const Ball &ball)
{
  glm::vec3 oc = ray.get_origin() - ball.getSphere().position;
  auto a = glm::dot(ray.get_direction(), ray.get_direction());// good?
  auto half_b = glm::dot(oc, ray.get_direction());
  float c = (oc.r * oc.r + oc.g * oc.g + oc.b * oc.b) - ball.getSphere().radius * ball.getSphere().radius;
  return std::make_tuple(half_b * half_b - a * c, half_b, a);
}

std::optional<hit_record> hit(const Ray &ray, const Ball &ball)
{
  auto [discriminant, half_b, a] = calculate_discriminant(ray, ball);
  if (discriminant < 0) {
    return std::nullopt;
  }
  const auto sqrtd = sqrt(discriminant);
  auto root = (-half_b - sqrtd) / a;
  const auto min = 0.f;
  constexpr auto max = std::numeric_limits<float>::infinity();
  if (isRootInRange(root, min, max)) {
    root = (-half_b + sqrtd) / a;
    if (isRootInRange(root, min, max)) {
      return std::nullopt;
    }
  }

  auto rec = hit_record();
  rec.t = root;
  rec.p = ray.at(rec.t);
  auto outwardNormal = rec.p - ball.getSphere().position;
  rec.set_face_normal(ray, outwardNormal);
  return rec;
}

std::tuple<bool, float> calculate_the_closest_hit_point(const Scene &scene, const CameraDataForPixelCalculation &cameraDataForPixelCalculation, const Ray &ray, int samplesPerPixel)
{
  bool isHit = false;
  auto max = std::numeric_limits<float>::infinity();
  for (const auto &sceneObject : scene.objects) {
    hit_record record = send_rays_into_scene(ray, sceneObject, samplesPerPixel);
    if (record.front_face) {
      isHit = true;
      max = record.t;
    }    
  }
  return { isHit, max };  
}

hit_record send_rays_into_scene(Ray ray, Ball sceneObject, int samplesPerPixel)
{
  auto results = std::vector<std::optional<hit_record>>();
  results.reserve(samplesPerPixel);
  for (int i = 0; i < samplesPerPixel; ++i) {
    results.push_back(hit(ray, sceneObject));
  }

  hit_record closestHit{};
  for (const auto &result : results) {
    if (result.has_value()) {
      closestHit.t += result->t;
    }
  }
  return closestHit;
}

bool PathTracer::isRootInRange(float root, double min, double max)
{
  return (root < min || max < root);
}

Color calculate_pixel(const Scene &scene, const CameraDataForPixelCalculation &cameraDataForPixelCalculation, int samplesPerPixel)
{
  auto ray = Ray{
    cameraDataForPixelCalculation.origin,
    cameraDataForPixelCalculation.lower_left_corner + cameraDataForPixelCalculation.red * cameraDataForPixelCalculation.horizontal + cameraDataForPixelCalculation.green * cameraDataForPixelCalculation.vertical - cameraDataForPixelCalculation.origin
  };
  return does_ray_hit_anything(scene, cameraDataForPixelCalculation, ray, samplesPerPixel);
}
}// namespace PathTracer
