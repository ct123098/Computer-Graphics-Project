#ifndef HIT_H
#define HIT_H

#include <cstring>
#include <vecmath.h>
#include "ray.hpp"

class Material;

class Hit {
public:

    // constructors
    Hit() {
        material = nullptr;
        t = 1e38;
    }

    Hit(double t_, double u_, double v_, Material *m, const Vector3f &n) : t(t_), u(u_), v(v_), material(m), normal(n) {

    }

    // destructor
    ~Hit() = default;

    double getT() const {
        return t;
    }
    double getU() const {
        return u;
    }
    double getV() const {
        return v;
    }

    Material *getMaterial() const {
        return material;
    }

    const Vector3f &getNormal() const {
        return normal;
    }

    void set(double t_, double u_, double v_, Material *m, const Vector3f &n) {
        t = t_, u = u_, v = v_;
        material = m;
        normal = n;
    }

private:
    double t, u, v;
    Material *material;
    Vector3f normal;

};

inline std::ostream &operator<<(std::ostream &os, const Hit &h) {
    os << "Hit <" << h.getT() << ", " << h.getNormal() << ">";
    return os;
}

#endif // HIT_H
