#pragma once
#include "../general_utils/vec3.hpp"
#include "../scene_utils/ray.hpp"
#include "shape.hpp"
#include <cmath>

class Sphere : public Shape {
      public:
        double radius;
        Vec3 center;
        Sphere(double radius, Vec3 center, Color color);
        bool intercepts(Ray &ray, Interseption &interseption) override;
};
