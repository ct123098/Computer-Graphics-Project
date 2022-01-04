#ifndef CAMERA_H
#define CAMERA_H

#include "ray.hpp"

#include <vecmath.h>
#include <cmath>

#include "utils.hpp"
#include "objects/plane.hpp"

class Camera {
public:
    Camera(const Vector3f &center, const Vector3f &direction, const Vector3f &up, int imgW, int imgH) {
        this->center = center;
        this->direction = direction.normalized();
        this->horizontal = Vector3f::cross(this->direction, up);
        this->up = Vector3f::cross(this->horizontal, this->direction);
        this->width = imgW;
        this->height = imgH;
    }

    // Generate rays for each screen-space coordinate
    virtual Ray generateRay(const Vector2f &point) = 0;

    virtual ~Camera() = default;

    int getWidth() const { return width; }

    int getHeight() const { return height; }

    // Extrinsic parameters
    Vector3f center;
    Vector3f direction;
    Vector3f up;
    Vector3f horizontal;
    // Intrinsic parameters
    int width;
    int height;
};

// Implement Perspective camera
// You can add new functions or variables whenever needed.
class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(const Vector3f &center, const Vector3f &direction,
                      const Vector3f &up, int imgW, int imgH, float angle) : Camera(center, direction, up, imgW, imgH) {
        // angle is in radian.
        assert(0 <= angle && angle <= M_PI);
        double t = (2 * tan(angle / 2)), f = std::min(width, height) / t;
//        std::cerr << (angle / 2) << std::endl;
//        std::cerr << tan(M_PI / 180 * angle / 2) << std::endl;
//        exit(0);
        // fx = width / t, fy = height / t; // make both edge fit the angle
        fx = f, fy = f; // make the shorter edge fit the angle
        cx = width / 2.0, cy = height / 2.0;
    }

    Ray generateRay(const Vector2f &point) override {

//        printf("%lf %lf | ", r1, r2);
        double x = point.x(), y = point.y();
//        double x = point.x(), y = point.y();

        Vector3f d0((x - cx) / fx, (y - cy) / fy, -1.0);
        Matrix3f R(horizontal, up, -direction);
        Ray ret(center, (R * d0).normalized());
        return ret;
    }

protected:
    double cx, cy;
    double fx, fy;

};

// Implement Perspective camera
// You can add new functions or variables whenever needed.
class DOFCamera : public PerspectiveCamera {
public:
    DOFCamera(const Vector3f &center, const Vector3f &direction, const Vector3f &up, const Vector3f &focus_,
              double aperture_, int imgW, int imgH, float angle) : PerspectiveCamera(center, direction, up, imgW, imgH,
                                                                                     angle) {
        focus = focus_;
        aperture = aperture_;
        focus_plane = Plane(focus, -direction, nullptr);
    }

    Ray generateRay(const Vector2f &point) override {
        double x = point.x(), y = point.y();
        Vector3f d0((x - cx) / fx, (y - cy) / fy, -1.0);
        Matrix3f R(horizontal, up, -direction);
        Ray ray(center, (R * d0).normalized());
        Hit hit;
        bool _flag = focus_plane.intersect(ray, hit, 0.0);
        assert(_flag && hit.getT() <= 1e10);
        Vector3f focus_point = center + hit.getT() * ray.getDirection();
        assert(fcmp(Vector3f::dot(focus_point - focus_plane.o, direction), 0.0) == 0);
//        focus_point.print();
        Vector2f coef = aperture * random_inner_2d();
        Vector3f origin = center + coef.x() * horizontal + coef.y() * up;
        Ray ret(origin, (focus_point - origin).normalized());
        return ret;
    }

protected:
    Vector3f focus;
    Plane focus_plane;
    double aperture;

};

#endif //CAMERA_H
