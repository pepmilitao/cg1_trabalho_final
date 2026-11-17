#pragma once
#include "../general_utils/vec3.hpp"

class Color {
    public:
        Vec3 k_dif;
        Vec3 k_esp;
        Vec3 k_amb;
        double alpha;
        Color(Vec3 k_dif, Vec3 k_esp, Vec3 k_amb, double alpha);
};
