#ifndef SPHERE_H
#define SPHERE_H

#include <vecmath.h>
#include <cmath>

#include "core/object3d.hpp"
#include "constant.hpp"

// Implement functions and add more fields as necessary

class Sphere : public Object3D {
public:
    Sphere() {
        // unit ball at the center
    }

    Sphere(const Vector3f &center, double radius, Material *_material) : Object3D(_material) {
        o = center;
        r = radius;
        mn = center - Vector3f(radius);
        mx = center + Vector3f(radius);
    }

    ~Sphere() override = default;

    // smallpt implementation
    bool intersect(const Ray &ray, Hit &hit, double tmin) override {
        Vector3f op = o - ray.getOrigin();
        double b = Vector3f::dot(op, ray.getDirection());
        double det = b * b - Vector3f::dot(op, op) + r * r;
        if (det < EPS_INT) return false;
        det = sqrt(det);
        double t1 = b - det, t2 = b + det;
        if (t2 <= tmin + EPS_HIT) return false;
        double t = t1 > tmin + EPS_HIT ? t1 : t2;
        Vector3f N =  (ray.getOrigin() + t * ray.getDirection() - o).normalized();
        assert(fcmp(N.length(), 1.0) == 0);
        Vector2f texture_uv = Vector2f(0.0);
        if (t < hit.getT())
            hit.set(t, texture_uv[0], texture_uv[1], material, N);
        return true;
    }

    void get_all_faces(std::vector<Object3D*> &objects) override {
        objects.push_back(this);
    }

//    bool intersect(const Ray &ray, Hit &hit, double tmin) override {
//        Vector3f a = ray.getOrigin(), d = ray.getDirection();
////        std::cout << a[0] << ' ' << a[1] << ' ' << a[2] << ' ' << d[0] << ' ' << d[1] << ' '<< d[2] << "|";
//        Vector3f ao = o - a;
//        double l = Vector3f::dot(ao, d), ao2 = Vector3f::dot(ao, ao);
////        std::cout << l << ' ' << ao2 << "|";
//        double h2 = ao2 - l * l;
////        std::cout << h2 << ' ' << r * r << "|";
////        std::cout << std::endl;
//        if (fcmp(h2, r * r) >= 0)
//            return false;
//        double ll = sqrt(r * r - h2), t1 = l - ll, t2 = l + ll;
//        if (fcmp(t2, tmin) <= 0)
//            return false;
//        double t = fcmp(t1, tmin) > 0 ? t1 : t2;  // t1 <= t2
//        Vector3f point = a + t * d, normal = (point - o).normalized();
//        if (hit.getT() > t)
//            hit.set(t, material, normal);
//        return true;
//    }

protected:
    Vector3f o;
    double r;
};


#endif
