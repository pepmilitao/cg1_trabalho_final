#include "../../include/general_utils/listmesh.hpp"

ListMesh::ListMesh(std::vector<Vec3> &vertices, std::vector<std::vector<int>> &faces)
    : vertices{vertices}, faces{faces} {}
