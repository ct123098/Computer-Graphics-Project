//
// Created by tom20 on 2020/12/20.
//

#include <random>
#include <vecmath.h>

#include "utils.hpp"
#include "constant.hpp"

double clip(double x, double mn, double mx) {
    return x > mx ? mx : x < mn ? mn : x;
}

Vector3f clip(const Vector3f &a, double mn, double mx) {
    Vector3f ret = a;
    for (int i = 0; i < 3; i++)
        ret[i] = clip(a[i], mn, mx);
    return ret;
}

double gamma_correction(double x, double gamma) {
    return pow(x, gamma);
}

Vector3f gamma_correction(const Vector3f &a, double gamma) {
    Vector3f ret = a;
    for (int i = 0; i < 3; i++)
        ret[i] = gamma_correction(a[i], gamma);
    return ret;
}

double frandom() {
    static thread_local std::mt19937 prng{ std::random_device{}() };
    static thread_local std::uniform_real_distribution<double> dist(0.0f, 1.0f);
    return dist(prng);
}

Vector2f random_inner_2d() {
    while (true) {
        double x = frandom() * 2 - 1, y = frandom() * 2 - 1;
        double r2 = x * x + y * y;
        if (r2 >= 1.0)
            continue;
        return Vector2f(x, y);
    }
}

Vector3f random_boundary_3d() {
    while (true) {
        double x = frandom() * 2 - 1, y = frandom() * 2 - 1, z = frandom() * 2 - 1;
        double r2 = x * x + y * y + z * z;
        if (r2 >= 1.0 || r2 <= EPS)
            continue;
        return Vector3f(x, y, z) / sqrt(r2);
    }
}

int fcmp(double x, double y) {
    if (fabs(y - x) <= EPS)
        return 0;
    return x > y ? 1 : -1;
}

Vector3f max(const Vector3f &a, const Vector3f &b) {
    Vector3f ret;
    for (int i = 0; i < 3; i++)
        ret[i] = std::max(a[i], b[i]);
    return ret;
}

Vector3f min(const Vector3f &a, const Vector3f &b) {
    Vector3f ret;
    for (int i = 0; i < 3; i++)
        ret[i] = std::min(a[i], b[i]);
    return ret;
}

bool operator < (const Vector3f &a, const Vector3f &b) {
    return a.x() < b.x() && a.y() < b.y() && a.z() < b.z();
}
bool operator <= (const Vector3f &a, const Vector3f &b) {
    return a.x() <= b.x() && a.y() <= b.y() && a.z() <= b.z();
}