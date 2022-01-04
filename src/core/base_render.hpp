//
// Created by tom20 on 2020/12/20.
//

#ifndef RENDER_BASE_RENDER_HPP
#define RENDER_BASE_RENDER_HPP

#include <Vector3f.h>
#include <utility>
#include <vector>
#include <mutex>

#include "common/scene.hpp"
#include "common/image.hpp"
#include "core/ray.hpp"

class BaseRender {
public:
    static const int MAX_WORKERS = 128;

protected:
    Scene *scene;
    Image *image;
    int n_workers;
    int n_progress;
    std::mutex lock;
    std::vector<std::pair<int, int> > tasks[MAX_WORKERS];

public:
    BaseRender(Scene *scene, Image *image_, int n_workers_ = 1);
    virtual void render();

protected:
    virtual void render_id(int worker_id);
    virtual Vector3f render_pixel(int x, int y) { assert(false); }
};

#endif //RENDER_BASE_RENDER_HPP
