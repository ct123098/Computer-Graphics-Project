//
// Created by tom20 on 2020/12/20.
//

#ifndef RENDER_UTILS_HPP
#define RENDER_UTILS_HPP

#include <random>
#include <vecmath.h>

#include "constant.hpp"

double clip(double x, double mn, double mx);

Vector3f clip(const Vector3f &a, double mn, double mx);

double gamma_correction(double x, double gamma);

Vector3f gamma_correction(const Vector3f &a, double gamma);

double frandom();

Vector2f random_inner_2d();
Vector3f random_boundary_3d();

int fcmp(double x, double y);

Vector3f max(const Vector3f &a, const Vector3f &b);

Vector3f min(const Vector3f &a, const Vector3f &b);

bool operator < (const Vector3f &a, const Vector3f &b);
bool operator <= (const Vector3f &a, const Vector3f &b);

#endif //RENDER_UTILS_HPP
