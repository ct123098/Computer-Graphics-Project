#ifndef LIGHT_H
#define LIGHT_H

#include <Vector3f.h>
#include "object3d.hpp"

class Light {
public:
    Light() = default;

    virtual ~Light() = default;

    virtual Ray generateRay() const = 0;
    virtual Vector3f getPower() const = 0;
};


//class DirectionalLight : public Light {
//public:
//    DirectionalLight() = delete;
//
//    DirectionalLight(const Vector3f &d, const Vector3f &c) {
//        direction = d.normalized();
//        color = c;
//    }
//
//    ~DirectionalLight() override = default;
//
//    ///@param p unsed in this function
//    ///@param distanceToLight not well defined because it's not a point light
//    void getIllumination(const Vector3f &p, Vector3f &dir, Vector3f &col) const override {
//        // the direction to the light is the opposite of the
//        // direction of the directional light source
//        dir = -direction;
//        col = color;
//    }
//
//private:
//
//    Vector3f direction;
//    Vector3f color;
//
//};

class PointLight : public Light {
public:
    PointLight() = delete;
    PointLight(const Vector3f &p, const Vector3f &c) {
        position = p;
        power = c;
    }
    ~PointLight() override = default;
    Ray generateRay() const override {
        return Ray(position, random_boundary_3d());
    }
    Vector3f getPower() const override {
        return power;
    }

private:
    Vector3f position;
    Vector3f power;
};

class DiskLight : public Light {
public:
    DiskLight() = delete;
    ~DiskLight() override = default;
    DiskLight(const Vector3f &p, const Vector3f &d, double r, const Vector3f &c)
            : position(p), direction(d.normalized()), radius(r), power(c) {
    }
    Ray generateRay() const override {
        Vector3f X = Vector3f::cross(fabs(direction.x()) >= 0.5 ? Vector3f(0, 1, 0) : Vector3f(1, 0, 0), direction).normalized();
        Vector3f Y = Vector3f::cross(direction, X);
        Vector2f coef = random_inner_2d();
        Vector3f D = random_boundary_3d();
        D = Vector3f::dot(D, direction) > 0 ? D : -D;
        return Ray(position + radius * coef.x() * X + radius * coef.y() * Y , D);
    }
    Vector3f getPower() const override {
        return power;
    }

private:
    Vector3f position, direction;
    double radius;
    Vector3f power;
};


class DiskParallelLight : public Light {
public:
    DiskParallelLight() = delete;
    ~DiskParallelLight() override = default;
    DiskParallelLight(const Vector3f &p, const Vector3f &d, double r, const Vector3f &c)
            : position(p), direction(d.normalized()), radius(r), power(c) {
    }
    Ray generateRay() const override {
        Vector3f X = Vector3f::cross(fabs(direction.x()) >= 0.5 ? Vector3f(0, 1, 0) : Vector3f(1, 0, 0), direction).normalized();
        Vector3f Y = Vector3f::cross(direction, X);
        Vector2f coef = random_inner_2d();
        return Ray(position + radius * coef.x() * X + radius * coef.y() * Y , direction);
    }
    Vector3f getPower() const override {
        return power;
    }

private:
    Vector3f position, direction;
    double radius;
    Vector3f power;
};

#endif // LIGHT_H
