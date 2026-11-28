#include "../../include/general_utils/vec4.hpp"

Vec4::Vec4(double x, double y, double z, double w) : x{x}, y{y}, z{z}, w{w} {}
Vec4::Vec4(Vec3 coords, double w)
    : x{coords.x}, y{coords.y}, z{coords.z}, w{w} {}
Vec4 Vec4::operator+(const Vec4 &b) {
        return {x + b.x, y + b.y, z + b.z, w + b.w};
}
Vec4 Vec4::operator-(const Vec4 &b) {
        return {x - b.x, y - b.y, z - b.z, w - b.w};
}
Vec4 Vec4::operator*(const double &n) { return {x * n, y * n, z * n, w * n}; }
double Vec4::dot(Vec4 &b) { return x * b.x + y * b.y + z * b.z + w * b.w; }
Vec3 Vec4::to_point3() {
        if (w < 1e-12) {
                throw std::runtime_error(
                    "Não é possível converter Vec4 para ponto: w é zero");
        }
        return {x / w, y / w, z / w};
}
Vec3 Vec4::to_direction3() {
	return {x, y, z};
}
