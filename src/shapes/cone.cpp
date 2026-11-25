#include "../../include/shapes/cone.hpp"
#include <cmath>

Cone::Cone(double radius, Vec3 center_base, Vec3 direction, double height,
           bool is_base, Color color)
    : radius{radius}, center_base{center_base}, direction{direction},
      vertice{center_base + direction * height}, height{height},
      is_base{is_base}, Shape(color) {}

bool Cone::conic_surface(Ray &ray, Interseption &interseption) {
        double tan_theta = radius / height;
        double cos_theta2 = 1.0 / (1.0 + tan_theta * tan_theta);
        Vec3 v = vertice - ray.origin;
        double dn = ray.direction.dot(direction);
        double dd = ray.direction.dot(ray.direction);
        double vd = v.dot(ray.direction);
        double vn = v.dot(direction);
        double vv = v.dot(v);

        double a = dn * dn - dd * cos_theta2;
        double b = 2.0 * (vd * cos_theta2 - vn * dn);
        double c = vn * vn - vv * cos_theta2;

        double delta = b * b - 4 * a * c;
        if (delta < 0.0)
                return false;
        double sqrt_delta = sqrt(delta);
        double t1 = (-b - sqrt_delta) / (2.0 * a);
        double t2 = (-b + sqrt_delta) / (2.0 * a);

        bool t1_possible = true;
        bool t2_possible = true;
        bool p1_in_surface = false;
        bool p2_in_surface = false;
        if (t1 < 0)
                t1_possible = false;
        if (t2 < 0)
                t2_possible = false;
        if (!t1_possible and !t2_possible)
                return false;

        Vec3 p1(0, 0, 0);
        Vec3 p2(0, 0, 0);
        if (t1_possible) {
                p1 = ray.at(t1);
                double height_p1 = (p1 - center_base).dot(direction);
                p1_in_surface = height_p1 >= 0 and height_p1 <= height;
        }
        if (t2_possible) {
                p2 = ray.at(t2);
                double height_p2 = (p2 - center_base).dot(direction);
                p2_in_surface = height_p2 >= 0 and height_p2 <= height;
        }

        if (!p1_in_surface and !p2_in_surface)
                return false;
        if (p1_in_surface and p2_in_surface) {
                double t = lowerNotNegative(t1, t2);
                interseption.t = t;
                if (t == t1)
                        interseption.point = p1;
                else
                        interseption.point = p2;
        } else if (p1_in_surface) {
                interseption.t = t1;
                interseption.point = p1;
        } else {
                interseption.t = t2;
                interseption.point = p2;
        }
        Vec3 q = interseption.point - vertice;
        Vec3 n = direction * q.dot(direction) - q * cos_theta2;
        interseption.normal = (-n).norm();
        return true;
}
bool Cone::base(Ray &ray, Interseption &interseption) {
        Plane base_plane(center_base, -direction, color);
        if (base_plane.intercepts(ray, interseption) and
            (ray.at(interseption.t) - center_base).mag() <= radius)
                return true;
        return false;
}
bool Cone::intercepts(Ray &ray, Interseption &interseption) {
        Interseption int_sup;
        Interseption int_bas;
        if (not conic_surface(ray, int_sup))
                int_sup.t = INFINITY;
        if (not is_base or not base(ray, int_bas))
                int_bas.t = INFINITY;
        double t = lowerNotNegative(int_sup.t, int_bas.t);
        if (t == int_sup.t)
                interseption = int_sup;
        if (t == int_bas.t)
                interseption = int_bas;
        if (interseption.t == INFINITY)
                return false;
        return true;
}
