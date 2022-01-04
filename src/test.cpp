//
// Created by tom20 on 2020/12/21.
//

#include "objects/sphere.hpp"
#include "core/ray.hpp"

void sphere_test1() {
    Sphere s1(Vector3f(0, 0, 0), 1.0, nullptr);
    Hit hit;
    bool res = s1.intersect(Ray(Vector3f(1.0, 0.0, 0.0), Vector3f(1.0, 0.0, 0.0)), hit, 0.0);
    assert(!res);
}
void sphere_test() {
    sphere_test1();
}

void self_test() {
    sphere_test();
}
