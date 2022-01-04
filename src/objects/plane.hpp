#ifndef PLANE_H
#define PLANE_H

#include <vecmath.h>
#include <cmath>
#include "core/object3d.hpp"
#include "constant.hpp"

// Implement Plane representing an infinite plane
// function: ax+by+cz=d
// choose your representation , add more fields and fill in the functions

class Plane : public Object3D {
public:
    Plane() {
        
    }
    Plane(const Vector3f &origin, const Vector3f &normal, Material *m) : Object3D(m) {
        n = normal.normalized();
        o = origin;
        mn = -1e10;
        mx = 1e10;
    }

    ~Plane() override = default;

    bool intersect(const Ray &ray, Hit &hit, double tmin) override {
        Vector3f a = ray.getOrigin(), d = ray.getDirection();
        double C = Vector3f::dot(n, d);
        if (fabs(C) < EPS_INT)
            return false;
        double A = Vector3f::dot(n, o), B = Vector3f::dot(n, a);
        double t = (A - B) / C;
        if (t < tmin + EPS_HIT)
            return false;
        Vector3f normal = C >= 0 ? -n : n;
        Vector2f texture_uv = Vector2f(0.0);
        if (hit.getT() > t) {
            hit.set(t, texture_uv[0], texture_uv[1], material, normal);
        }
        return true;
    }

    void get_all_faces(std::vector<Object3D*> &objects) override {
        objects.push_back(this);
    }

    Vector3f o, n;

};

#endif //PLANE_H
		

