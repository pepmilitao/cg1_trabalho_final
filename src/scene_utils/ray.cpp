#include "../../include/scene_utils/ray.hpp"

Ray::Ray(Vec3 origin, Vec3 direction) : origin{origin}, direction{direction} {}
Vec3 Ray::at(double t) {
    return origin + direction * t;
}
