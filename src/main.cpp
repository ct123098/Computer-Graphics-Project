#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <ctime>
#include <string>
#include <thread>
//#include "common/scene_parser.hpp"

//#include "core/ray_casting.hpp"
#include "common/scene.hpp"

#include "common/image.hpp"
#include "core/camera.hpp"
#include "objects/group.hpp"
#include "core/light.hpp"
#include "constant.hpp"
#include "core/sppm_render.hpp"


void self_test();

using namespace std;

struct ArgumentsConfig {
    string cwd;
    int id;
};

ArgumentsConfig parse_args(int argc, char *argv[]) {
    ArgumentsConfig args;
    for (int argNum = 1; argNum < argc; ++argNum) {
        std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
    }
    if (argc != 2 && argc != 3) {
        cout << "Usage: ./bin/PA1 <input scene file> <output bmp file>" << endl;
        exit(1);
    }
    args.cwd = argv[1];
    args.id = argc == 3 ? atoi(argv[2]) : 0;
    return args;
}

int main(int argc, char *argv[]) {

    self_test();

    ArgumentsConfig args = parse_args(argc, argv);

    cout << "Rendering started." << endl;
    std::clock_t c_start = std::clock();

//    SceneParser sceneParser(args.inputFile.c_str());
//    SceneParser sceneParser;
    Scene scene;
    Scene::buildScene(scene, args.id);

    int W = scene.getCamera()->getWidth(), H = scene.getCamera()->getHeight();
    Image image(W, H);

//    RayCasting render(&sceneParser, &image, 1);
//    RayTracing render(&scene, &image, N_WORKERS, N_SAMPLES);
    SPPMRender render(&scene, &image, N_ROUNDS, N_PHOTONS, N_WORKERS, args.cwd);
    render.render();

    image.SaveBMP((args.cwd + "/final.bmp").c_str());

    std::clock_t c_end = std::clock();
    cout << "Rendering finished. ";
    cout << "(CPU time used: " << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << "ms)" << endl;
    return 0;
}

