#pragma once
#include "../general_utils/vec3.hpp"
#include "../general_utils/mat3.hpp"
#include "../scene_utils/ray.hpp"
#include "shape.hpp"
#include "plane.hpp"
#include <cmath>

class Cilinder : public Shape{
    private:
        bool cilindric_surface(Ray& ray, Interseption& interseption);
        bool base(Ray& ray, Interseption& interseption);
        bool top(Ray& ray, Interseption& interseption);
    public:
        double radius;
        Vec3 center_base;
        Vec3 direction;
        Vec3 center_top;
        double height;
        bool is_base;
        bool is_top;
        Cilinder(double radius, Vec3 center_base, Vec3 direction, double height, bool is_base, bool is_top, Color color);
        bool intercepts(Ray& ray, Interseption& interseption) override;
};
