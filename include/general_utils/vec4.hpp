#pragma once
#include <cmath>
#include <stdexcept> 
#include "vec3.hpp"

class Vec4 {
      public:
        double x, y, z, w;
        Vec4(double x, double y, double z, double w);
        Vec4(Vec3 coords, double w);
        Vec4 operator+(const Vec4 &b);
        Vec4 operator-(const Vec4 &b);
        Vec4 operator*(const double &n);

        double dot(Vec4 &b);
        Vec3 to_point3();
        Vec3 to_direction3();
};
