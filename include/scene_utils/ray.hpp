#pragma once
#include "../general_utils/vec3.hpp"

class Ray {
    public:
        Vec3 origin;
        Vec3 direction;
        Ray(Vec3 origin, Vec3 direction);
        Vec3 at(double t);
};
