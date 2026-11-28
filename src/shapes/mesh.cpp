#include "../../include/shapes/mesh.hpp"
#include <iostream>

Mesh::Mesh(ListMesh lm, Color color) : lm{lm}, Shape(color) {}

bool Mesh::intercepts(Ray &ray, Interseption &interseption) {
        // TODO: back face culling
        // TODO: iluminação interna
        Interseption closest;
        closest.t = INFINITY;
        for (auto face : this->lm.faces) {
                Interseption candidate;
                if (this->intercepts_triangle(ray, candidate, face) and
                    candidate.t < closest.t) {
                        closest = candidate;
                }
        }
        if (!std::isfinite(closest.t))
                return false;

        interseption = closest;
        return true;
}

bool Mesh::intercepts_triangle(Ray &ray, Interseption &interseption,
                               std::vector<int> face) {

        // Parte 1: intersecção com plano do triângulo
        // Cálculo do vetor normal do triângulo
        Vec3 r1 = this->lm.vertices[face[1]] - this->lm.vertices[face[0]];
        Vec3 r2 = this->lm.vertices[face[2]] - this->lm.vertices[face[0]];
        Vec3 n = r1.cross(r2);

        double area_triangulo = n.mag() * 0.5;
        n = n.norm();

        // Criação do plano e intersecção
        Plane plano(this->lm.vertices[face[0]], n, this->color);
        if (!plano.intercepts(ray, interseption))
                return false;

        // Parte 2: ponto dentro do plano
        // Vetor ponto de referência - ponto de intersecção
        Vec3 v = interseption.point - this->lm.vertices[face[0]];

        // Pesos
        Vec3 w1 = r2.cross(n) / (2.0 * area_triangulo);
        Vec3 w2 = n.cross(r1) / (2.0 * area_triangulo);

        // Coordenadas baricêntricas
        double c1 = v.dot(w1);
        double c2 = v.dot(w2);
        double c3 = 1 - (c1 + c2);

        // Requisitos para pertencimento do ponto
        if (c1 >= 0 and c2 >= 0 and c3 >= 0)
                return true;
        return false;
}
