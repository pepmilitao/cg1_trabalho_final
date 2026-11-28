#pragma once
#include "vec3.hpp"
#include <vector>

class ListMesh {
      public:
        std::vector<Vec3> vertices;
        std::vector<std::vector<int>> faces;
        ListMesh(std::vector<Vec3> &vertices, std::vector<std::vector<int>> &faces);
};