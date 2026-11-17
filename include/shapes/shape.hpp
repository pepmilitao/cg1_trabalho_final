#pragma once
#include "../general_utils/vec3.hpp"
#include "../scene_utils/ray.hpp"
#include "../scene_utils/color.hpp"
#include "../scene_utils/interseption.hpp"

class Shape {
    public:
        Color color;
        Shape(Color color);
        virtual ~Shape();
        double lowerNotNegative(double t1, double t2);
        virtual bool intercepts(Ray& ray, Interseption& interseption) = 0;
};
