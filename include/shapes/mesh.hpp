#pragma once
#include "../general_utils/listmesh.hpp"
#include "../general_utils/vec3.hpp"
#include "../scene_utils/ray.hpp"
#include "../shapes/plane.hpp"
#include "shape.hpp"
#include <cmath>

class Mesh : public Shape {
      public:
        ListMesh lm;
        Mesh(ListMesh lm, Color color);
        bool intercepts(Ray &ray, Interseption &interseption) override;

      private:
        bool intercepts_triangle(Ray &ray, Interseption &interseption, std::vector<int> face);
};
