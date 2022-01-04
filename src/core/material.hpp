#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include <iostream>

#include <vecmath.h>
#include "core/ray.hpp"
#include "core/hit.hpp"
#include "utils.hpp"
#include "common/image.hpp"

enum MaterialType {
    DIFFUSION, SPECULAR, REFRACTION
};

class Material {
public:

    Material(double diffuse_, double specular_, double refraction_, const Vector3f &diffuse_color_,
             const Vector3f &specular_color_, double phong_s_, double ior_, const std::string &texture_filename_)
            : diffuse(diffuse_), specular(specular_), refraction(refraction_), diffuse_color(diffuse_color_),
              specular_color(specular_color_), phong_s(phong_s_), ior(ior_), diffuse_filename(texture_filename_),
              diffuse_texture(nullptr) {
//        std::cerr << "filename : " << diffuse_filename << std::endl;
        if (!diffuse_filename.empty()) {
            diffuse_texture = Image::LoadPPM(("mesh/" + diffuse_filename).c_str());
        }
//        std::cerr << "filename : " << diffuse_filename << std::endl;
    }

    ~Material() = default;

    Vector3f get_diffuse_color(double u = 0.0, double v = 0.0) const {
        assert(-10 * EPS <= u && u <= 1 + 10 * EPS);
        assert(-10 * EPS <= v && v <= 1 + 10 * EPS);
        if (!diffuse_texture)
            return diffuse_color;
//        return Vector3f(1.0);
        int W = diffuse_texture->Width(), H = diffuse_texture->Height();
        int x = std::max(std::min((int)(u * W), W - 1), 0);
        int y = std::max(std::min((int)(v * H), H - 1), 0);
//        std::cerr << diffuse_filename << ' ' << "(" << x << ' ' << y << ' ' << W << ' ' << H << ")" << std::endl;
        Vector3f color = diffuse_texture->GetPixel(x, y);
//        color.print();printf("\n");
        return color;
    }

//    Vector3f Shade(const Ray &ray, const Hit &hit, const Vector3f &dirToLight, const Vector3f &lightColor) {
////        const double INF = 1e300;
////        Vector3f shaded = Vector3f::ZERO;
////        Vector3f N = hit.getNormal(), L = dirToLight, V = -ray.getDirection();
//////        N = Vector3f::dot(N, L) > 0 ? N : -N;
////        Vector3f R = 2 * Vector3f::dot(N, L) * N - L;
////        shaded += lightColor * diffuseColor * clip(Vector3f::dot(N, L));
////        shaded += lightColor * specularColor * pow(clip(Vector3f::dot(V, R)), shininess);
//////        shaded.print();
//////        std::cout << (Vector3f::dot(N, L));
////        return shaded;
//        assert(false);
//    }

    double diffuse, specular, refraction;
    Vector3f diffuse_color, specular_color;
    double phong_s;
    double ior;
    std::string diffuse_filename;
    Image *diffuse_texture;
};


#endif // MATERIAL_H
