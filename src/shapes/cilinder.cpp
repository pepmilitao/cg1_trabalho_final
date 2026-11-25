#include "../../include/shapes/cilinder.hpp"
#include <cmath>

Cilinder::Cilinder(double radius, Vec3 center_base, Vec3 direction,
                   double height, bool is_base, bool is_top, Color color)
    : radius{radius}, center_base{center_base}, direction{direction},
      center_top{center_base + direction * height}, height{height},
      is_base{is_base}, is_top{is_top}, Shape(color) {}

bool Cilinder::cilindric_surface(Ray &ray, Interseption &interseption) {
        Vec3 s = ray.origin - center_base;
        Vec3 v = s - s.projection_normalized(direction);
        Vec3 w = ray.direction - ray.direction.projection_normalized(direction);
        double a = w.dot(w);
        double b = v.dot(w) * 2.0;
        double c = v.dot(v) - radius * radius;

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
                Vec3 projection =
                    (p1 - center_base).projection_normalized(direction);
                double dir = projection.norm().dot(direction);
                if (not(dir < -0.999 and dir > -1.001)) {
                        double height_p1 = (projection).mag();
                        p1_in_surface = height_p1 >= 0 and height_p1 <= height;
                }
        }
        if (t2_possible) {
                p2 = ray.at(t2);
                Vec3 projection =
                    (p2 - center_base).projection_normalized(direction);
                double dir = projection.norm().dot(direction);
                if (not(dir < -0.999 and dir > -1.001)) {
                        double height_p2 = (projection).mag();
                        p2_in_surface = height_p2 >= 0 and height_p2 <= height;
                }
        }

        if (!p1_in_surface and !p2_in_surface)
                return false;
        if (p1_in_surface and p2_in_surface) {
                double t = lowerNotNegative(t1, t2);
                interseption.t = t;
                if (t == t1) {
                        interseption.point = p1;
                } else {
                        interseption.point = p2;
                }
                Vec3 sub = interseption.point - center_base;
                interseption.normal =
                    (sub - sub.projection_normalized(direction)).norm();
        } else if (p1_in_surface) {
                interseption.t = t1;
                interseption.point = p1;
                Vec3 sub = interseption.point - center_base;
                interseption.normal =
                    (sub - sub.projection_normalized(direction)).norm();
        } else {
                interseption.t = t2;
                interseption.point = p2;
                Vec3 sub = interseption.point - center_base;
                interseption.normal =
                    (sub - sub.projection_normalized(direction)).norm();
        }
        return true;
}
bool Cilinder::base(Ray &ray, Interseption &interseption) {
        Plane base_plane(center_base, -direction, color);
        if (base_plane.intercepts(ray, interseption) and
            (ray.at(interseption.t) - center_base).mag() <= radius)
                return true;
        return false;
}
bool Cilinder::top(Ray &ray, Interseption &interseption) {
        Plane top_plane(center_top, direction, color);
        if (top_plane.intercepts(ray, interseption) and
            (ray.at(interseption.t) - center_top).mag() <= radius)
                return true;
        return false;
}
bool Cilinder::intercepts(Ray &ray, Interseption &interseption) {
        Interseption int_sup;
        Interseption int_bas;
        Interseption int_top;
        if (not cilindric_surface(ray, int_sup))
                int_sup.t = INFINITY;
        if (not is_base or not base(ray, int_bas))
                int_bas.t = INFINITY;
        if (not is_top or not top(ray, int_top))
                int_top.t = INFINITY;
        double t =
            lowerNotNegative(int_sup.t, lowerNotNegative(int_bas.t, int_top.t));
        if (t == int_sup.t)
                interseption = int_sup;
        if (t == int_bas.t)
                interseption = int_bas;
        if (t == int_top.t)
                interseption = int_top;
        if (interseption.t == INFINITY)
                return false;
        return true;
        // Check da superfície cilíndrica

        // TODO: fazer bases também
}
