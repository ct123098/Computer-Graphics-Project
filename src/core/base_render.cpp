//
// Created by tom20 on 2020/12/20.
//

#include "base_render.hpp"

#include <thread>


BaseRender::BaseRender(Scene *scene_, Image *image_, int n_workers_) {
    scene = scene_;
    image = image_;
    n_workers = n_workers_;

    int W = scene->getCamera()->getWidth(), H = scene->getCamera()->getHeight();
    for (int x = 0, t = 0; x < W; x++)
        for (int y = 0; y < H; y++, t = (t + 1) % n_workers)
            tasks[t].emplace_back(x, y);

    n_progress = 0;
}

void BaseRender::render() {
    if (n_workers == 1) {
        render_id(0);
    }
    else {
        std::thread t[MAX_WORKERS];
        for (int i = 0; i < n_workers; i++) {
            t[i] = std::thread(&BaseRender::render_id, this, i);
        }
        for (int i = 0; i < n_workers; i++) {
            t[i].join();
        }
    }
}

void BaseRender::render_id(int worker_id) {
    assert(0 <= worker_id && worker_id < n_workers);
    int W = scene->getCamera()->getWidth(), H = scene->getCamera()->getHeight();
    auto task = tasks[worker_id];
    assert(!task.empty());
    for (auto & it : task) {
        int x = it.first, y = it.second;
//        std::cout << x << "," << y << ":";
        Vector3f color = render_pixel(x, y);
        image->SetPixel(x, y, color);
//        std::cout << std::endl;

        lock.lock();
        n_progress += 1;
        if (n_progress % (W * H / 10) == 0)
            std::cout << "Progress : " << 100.0 * n_progress / (W * H) << "% " << n_progress << '/' << W * H << std::endl;
        lock.unlock();
    }
}
