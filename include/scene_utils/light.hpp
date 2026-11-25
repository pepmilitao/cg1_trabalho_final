#pragma once
#include "../general_utils/vec3.hpp"

class Light {
      public:
        Vec3 position;
        Vec3 intensity;
        Light();
        Light(Vec3 position);
        Light(Vec3 position, Vec3 intensity);
};
