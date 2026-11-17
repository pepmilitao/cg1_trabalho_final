#pragma once
#include "../general_utils/vec3.hpp"
#include "../scene_utils/ray.hpp"
#include "shape.hpp"
#include <cmath>

class Plane : public Shape{
    private:
        Vec3 normal;
    public:
        Vec3 known_point;
        Plane(Vec3 known_point, Vec3 normal, Color color);
        bool intercepts(Ray& ray, Interseption& interseption) override;
};
