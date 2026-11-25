#include "../../include/general_utils/vec3.hpp"

Vec3::Vec3() : x{0}, y{0}, z{0} {}
Vec3::Vec3(double x, double y, double z) : x{x}, y{y}, z{z} {}
Vec3 Vec3::operator+(const Vec3 &b) { return Vec3(x + b.x, y + b.y, z + b.z); }
Vec3 Vec3::operator-(const Vec3 &b) { return Vec3(x - b.x, y - b.y, z - b.z); }
Vec3 Vec3::operator*(const double &n) { return Vec3(x * n, y * n, z * n); }
Vec3 Vec3::operator/(const double &n) { return Vec3(x / n, y / n, z / n); }
bool Vec3::operator==(const Vec3 &b) {
        return x == b.x and y == b.y and z == b.z;
}
bool Vec3::operator!=(const Vec3 &b) { return !(*this == b); }
Vec3 Vec3::operator-() { return Vec3(-x, -y, -z); }
double Vec3::dot(Vec3 &b) { return x * b.x + y * b.y + z * b.z; }
Vec3 Vec3::cross(Vec3 &b) {
        return Vec3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
}
Vec3 Vec3::cross_at(Vec3 &b) { return Vec3(x * b.x, y * b.y, z * b.z); }
Vec3 Vec3::projection(Vec3 &b) {
        double a = this->dot(b);
        double c = b.dot(b);
        double l = a / c;
        return b * l;
}
Vec3 Vec3::projection_normalized(Vec3 &b) { return b * this->dot(b); }
double Vec3::mag() { return std::sqrt(x * x + y * y + z * z); }
Vec3 Vec3::norm() { return *this / this->mag(); }
