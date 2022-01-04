#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vecmath.h>
#include <cmath>
#include <iostream>

#include "core/object3d.hpp"
#include "constant.hpp"
#include "utils.hpp"

using namespace std;

// implement this class and add more fields as necessary,
class Triangle : public Object3D {

public:
    Triangle() = delete;

    // a b c are three vertex positions of the triangle
    Triangle(const Vector3f &a, const Vector3f &b, const Vector3f &c, Material *m) : Object3D(m) {
        v[0] = a, v[1] = b, v[2] = c;
        Vector3f normal = Vector3f::cross(b - a, c - a).normalized();
        vn[0] = vn[1] = vn[2] = normal;
        vt[0] = vt[1] = Vector2f(0);
        update_box();
    }

    // a b c are three vertex positions of the triangle
    Triangle(const Vector3f *v_, Material *m) : Triangle(v_[0], v_[1], v_[2], m) {

    }

    Triangle(const Vector3f *v_, const Vector3f *vn_, Material *m) : Object3D(m) {
        for (int i = 0; i < 3; i++)
            v[i] = v_[i], vn[i] = vn_[i];
        update_box();
    }

    // a b c are three vertex positions of the triangle
    Triangle(const Vector3f *v_, const Vector3f *vn_, const Vector2f *vt_, Material *m) : Object3D(m) {
        for (int i = 0; i < 3; i++)
            v[i] = v_[i], vn[i] = vn_[i], vt[i] = vt_[i];
        update_box();
    }

    void update_box() {
        mn = min(v[0], min(v[1], v[2]));
        mx = max(v[0], max(v[1], v[2]));
    }

    bool intersect(const Ray &ray, Hit &hit, double tmin) override {
        const Vector3f &o = ray.getOrigin(), &d = ray.getDirection();
        const Vector3f &v0 = v[0], &v1 = v[1], &v2 = v[2];
        Vector3f v0v1 = v1 - v0, v0v2 = v2 - v0;
        Vector3f pvec = Vector3f::cross(d, v0v2);
        double det = Vector3f::dot(v0v1, pvec);
        if (fabs(det) < EPS_INT)
            return false;
        double inv_det = 1 / det;
        Vector3f tvec = o - v0;
        double uu = Vector3f::dot(tvec, pvec) * inv_det;
        if (uu < EPS_INT || uu > 1 - EPS_INT)
            return false;
        Vector3f qvec = Vector3f::cross(tvec, v0v1);
        double vv = Vector3f::dot(d, qvec) * inv_det;
        if (vv < EPS_INT || uu + vv > 1 - EPS_INT)
            return false;
        double t = Vector3f::dot(v0v2, qvec) * inv_det;
        if (t < tmin + EPS_HIT)
            return false;

        Vector3f N = (uu * vn[1] + vv * vn[2] + (1 - uu - vv) * vn[0]).normalized();
        Vector3f plane_norm = Vector3f::cross(v[1] - v[0], v[2] - v[0]).normalized();
        Vector2f texture_uv = (uu * vt[1] + vv * vt[2] + (1 - uu - vv) * vt[0]);
//        std::cerr << uu << ' ' << vv << std::endl;
//        Vector2f texture_uv = Vector2f(0.5, 0.5);
        assert(fcmp(N.length(), 1.0) == 0);
//        if (fcmp(Vector3f::dot(o + t * d - v0, plane_norm), 0.0) != 0) {
//            std::cerr << Vector3f::dot(o + t * d - v0, plane_norm) << std::endl;
//        }
        assert(fcmp(Vector3f::dot(o + t * d - v0, plane_norm), 0.0) == 0);
        if (hit.getT() > t) {
            hit.set(t, texture_uv[0], texture_uv[1], material, N);
        }
        return true;
    }

    void get_all_faces(std::vector<Object3D *> &objects) override {
        objects.push_back(this);
    }

    Vector3f v[3], vn[3];
    Vector2f vt[3];
protected:
};

#endif //TRIANGLE_H
