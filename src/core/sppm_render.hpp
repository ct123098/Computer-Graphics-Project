//
// Created by tom20 on 2021/1/4.
//

#ifndef RENDER_SPPM_RENDER_HPP
#define RENDER_SPPM_RENDER_HPP

#include "base_render.hpp"

struct HitPoint {
public:
    Vector3f pos, dir, norm;
    Vector3f weight, flux, flux_light;
    int n;
    double r2;
    Material *mat;
    bool valid;
    void init() {
        pos = dir = norm = 0;
        mat = nullptr;

        weight = 1.0;
        flux = flux_light = 0;
        n = 0;
        r2 = -1e100;

        valid = false;
    }
    void init_r2(double r2_) {
        r2 = r2_;
    }
    void invalidate() {
        pos = dir = norm = 0;
        mat = nullptr;
        weight = 1.0;
        valid = false;
    }
    void update(const Vector3f &rho) {
        double factor = (n * ALPHA + ALPHA) / (n * ALPHA + 1);
        n += 1;
        r2 *= factor;
        flux = (flux + weight * rho) * factor;
    }
};

struct HitPointGroup {
public:
    HitPointGroup();
    void build(std::vector<HitPoint*> hit_points);
    void update(const Vector3f &X, const Vector3f &V, const Vector3f &weight, const Hit &hit);

private:
    static const int MAX_BUCKET_NUM = 10000000;
    std::vector<HitPoint*> *bucket;
    double bucket_rad;
    int n_bucket;
    void init_hash_table(int n, double bucket_rad);
    int hash(const Vector3f &X);
    int hash(int ix, int iy, int iz);

};

class SPPMRender : public BaseRender  {
public:
    SPPMRender(Scene *scene_, Image *image_, int n_rounds_, int n_photons_, int n_workers_, std::string cwd_);

    ~SPPMRender();
    void render() override;

private:
    void trace(int depth, const Ray &ray, const Vector3f &weight, HitPoint *hp);

    int n_rounds, n_photons, n_workers;
    int W, H;
    Camera *camera;
    ObjectGroup object_group;
    std::vector<HitPoint*> hit_points;
    HitPointGroup hit_point_group;
    std::string cwd;


    void render_step1(int r);
    void render_step2(int r);
    void render_save_img(int r);
};


#endif //RENDER_SPPM_RENDER_HPP
