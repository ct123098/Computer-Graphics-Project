//
// Created by tom20 on 2020/12/22.
//

#include "common/scene.hpp"
#include "objects/sphere.hpp"
#include "objects/plane.hpp"
#include "objects/mesh.hpp"

//void Scene::buildCornellBox(Scene &scene) {
////    printf("build conell box\n");
//    scene.clear();
//
//    scene.setCamera(new PerspectiveCamera(Vector3f(50, 52, 295.6 - 130.0), Vector3f(0, -0.042612, -1).normalized(), Vector3f(0, 1, 0), IMG_WIDTH, IMG_HEIGHT, M_PI / 180 * 60 /* 0.502643 */));
//
//    Material *m1 = scene.addMaterial(new Material(DIFFUSION, Vector3f(255 / 255.0, 175 / 255.0, 204 / 255.0), Vector3f(0.0, 0.0, 0.0)));
//    Material *m2 = scene.addMaterial(new Material(DIFFUSION, Vector3f(162 / 255.0, 210 / 255.0, 255 / 255.0), Vector3f(0.0, 0.0, 0.0)));
//    Material *m3 = scene.addMaterial(new Material(DIFFUSION, Vector3f(248 / 255.0, 237 / 255.0, 235 / 255.0), Vector3f(0.0, 0.0, 0.0)));
//    Material *m4 = scene.addMaterial(new Material(DIFFUSION, Vector3f(0.0, 0.0, 0.0), Vector3f(0.0, 0.0, 0.0)));
//    Material *m5 = scene.addMaterial(new Material(SPECULAR, Vector3f(0.99, 0.99, 0.99), Vector3f(0.0, 0.0, 0.0)));
//    Material *m6 = scene.addMaterial(new Material(REFRACTION, Vector3f(0.99, 0.99, 0.99), Vector3f(0.0, 0.0, 0.0)));
//    Material *m7 = scene.addMaterial(new Material(DIFFUSION, Vector3f(0.0, 0.0, 0.0), Vector3f(12, 12, 12)));
//
//    scene.addObject(new Sphere(Vector3f(1e5 + 1, 40.8, 81.6), 1e5, m1));
//    scene.addObject(new Sphere(Vector3f(-1e5 + 99, 40.8, 81.6), 1e5, m2));
//    scene.addObject(new Sphere(Vector3f(50, 40.8, 1e5), 1e5, m3));
//    scene.addObject(new Sphere(Vector3f(50, 40.8, -1e5 + 170), 1e5, m4));
//    scene.addObject(new Sphere(Vector3f(50, 1e5, 81.6), 1e5, m3));
//    scene.addObject(new Sphere(Vector3f(50, -1e5 + 81.6, 81.6), 1e5, m3));
//    scene.addObject(new Sphere(Vector3f(27, 16.5, 47), 16.5, m5));
//    scene.addObject(new Sphere(Vector3f(73, 16.5, 78), 16.5, m6));
//    scene.addObject(new Sphere(Vector3f(50, 681.6 - .27, 81.6), 600, m7));
//}
//
//void Scene::buildCornellBoxPlaneGlassDragon(Scene &scene) {
////    printf("build conell box\n");
//    scene.clear();
//
//    scene.setCamera(new PerspectiveCamera(Vector3f(50, 52, 165), Vector3f(0, -0.05, -1).normalized(), Vector3f(0, 1, 0), IMG_WIDTH, IMG_HEIGHT, M_PI / 180 * 50));
//
////    Material *m1 = scene.addMaterial(new Material(DIFFUSION, Vector3f(255 / 255.0, 175 / 255.0, 204 / 255.0), Vector3f(0.0, 0.0, 0.0)));
////    Material *m2 = scene.addMaterial(new Material(DIFFUSION, Vector3f(162 / 255.0, 210 / 255.0, 255 / 255.0), Vector3f(0.0, 0.0, 0.0)));
//    Material *m1 = scene.addMaterial(new Material(DIFFUSION, Vector3f(255 / 255.0, 181 / 255.0, 167 / 255.0), Vector3f(0.0, 0.0, 0.0)));
//    Material *m2 = scene.addMaterial(new Material(DIFFUSION, Vector3f(254 / 255.0, 200 / 255.0, 154 / 255.0), Vector3f(0.0, 0.0, 0.0)));
//    Material *m3 = scene.addMaterial(new Material(DIFFUSION, Vector3f(248 / 255.0, 237 / 255.0, 235 / 255.0), Vector3f(0.0, 0.0, 0.0)));
//    Material *m4 = scene.addMaterial(new Material(DIFFUSION, Vector3f(0.3, 0.3, 0.3), Vector3f(0.0, 0.0, 0.0)));
//    Material *m5 = scene.addMaterial(new Material(SPECULAR, Vector3f(0.99, 0.99, 0.99), Vector3f(0.0, 0.0, 0.0)));
//    Material *m6 = scene.addMaterial(new Material(REFRACTION, Vector3f(0.99, 0.99, 0.99), Vector3f(0.0, 0.0, 0.0)));
////    Material *m7 = scene.addMaterial(new Material(DIFFUSION, Vector3f(0.0, 0.0, 0.0), Vector3f(1.0, 1.0, 1.0)));
//
//    scene.addObject(new Plane(Vector3f(1.0, 40.8, 81.6), Vector3f(1.0, 0.0, 0.0), m1));
//    scene.addObject(new Plane(Vector3f(99.0, 40.8, 81.6), Vector3f(-1.0, 0.0, 0.0), m2));
//    scene.addObject(new Plane(Vector3f(50, 40.8, 0), Vector3f(0.0, 0.0, 1.0), m4));
//    scene.addObject(new Plane(Vector3f(50, 40.8, 170), Vector3f(0.0, 0.0, -1.0), m4));
//    scene.addObject(new Plane(Vector3f(50, 0.0, 81.6), Vector3f(0.0, 1., 0.0), m4));
//    scene.addObject(new Plane(Vector3f(50, 81.6, 81.6), Vector3f(0.0, -1.0, 0.0), m4));
////    scene.addObject(new Sphere(Vector3f(27, 16.5, 47), 16.5, m5));
////    scene.addObject(new Sphere(Vector3f(73, 16.5, 78), 16.5, m6));
////    scene.addObject(new Sphere(Vector3f(50, 681.6 - .27, 81.6), 600, m7));
////    scene.addObject(new Mesh("mesh/cube.obj", 73, 20, 30, 20, 20, 20, m3));
////    scene.addObject(new Mesh("mesh/normalized_bunny_100.obj", 73, 40, 30, 20, 20, 20, m3));
//
//    scene.addObject(new Mesh("mesh/normalized_dragon_100k.obj", 50, 0, 30, 50, 50, 50, m6));
////    scene.addObject(new Mesh("mesh/fixed.perfect.dragon.100K.0.07.obj", 50, 25, 60, 50, 50, 50, m3));
////    scene.addObject(new Mesh("mesh/bunny_200.obj", 50, 0, 60, 200, 200, 200, m3));
////    scene.addObject(new Mesh("mesh/bunny_1k.obj", 50, -10, 60, 200, 200, 200, m3));
//
////    scene.addLight(new PointLight(Vector3f(50, 81, 81.6), Vector3f(6000.0, 6000.0, 6000.0)));
////    scene.addLight(new PointLight(Vector3f(50, 52, 169), Vector3f(30000.0, 30000.0, 30000.0)));
//    scene.addLight(new PointLight(Vector3f(90, 70, 70), Vector3f(6000.0, 6000.0, 6000.0)));
//    scene.addLight(new PointLight(Vector3f(10, 70, 70), Vector3f(6000.0, 6000.0, 6000.0)));
//    scene.addLight(new PointLight(Vector3f(50, 70, 10), Vector3f(15000.0, 15000.0, 15000.0)));
//}

void Scene::buildCornellBoxPlane(Scene &scene) {
//    printf("build conell box\n");
    scene.clear();

    scene.setCamera(new PerspectiveCamera(Vector3f(50, 52, 165), Vector3f(0, -0.042612, -1).normalized(), Vector3f(0, 1, 0),IMG_WIDTH, IMG_HEIGHT, M_PI / 180 * 45 /* 0.502643 */));

    Material *m1 = scene.addMaterial(new Material(1.0, 0.0, 0.0, Vector3f(255 / 255.0, 175 / 255.0, 204 / 255.0), Vector3f(0.0, 0.0, 0.0), 0.0,0.0, ""));
//    Material *m2 = scene.addMaterial(new Material(1.0, 0.0, 0.0, Vector3f(162 / 255.0, 210 / 255.0, 255 / 255.0), Vector3f(0.0, 0.0, 0.0), 0.0,0.0, ""));
    Material *m3 = scene.addMaterial(new Material(1.0, 0.0, 0.0, Vector3f(248 / 255.0, 237 / 255.0, 235 / 255.0), Vector3f(0.0, 0.0, 0.0), 0.0,0.0, ""));
    Material *m4 = scene.addMaterial(new Material(1.0, 0.0, 0.0, Vector3f(0.0, 0.0, 0.0), Vector3f(0.0, 0.0, 0.0), 0.0, 0.0, ""));
//    Material *m5 = scene.addMaterial(new Material(0.0, 1.0, 0.0, Vector3f(0.99, 0.99, 0.99), Vector3f(0.0, 0.0, 0.0), 0.0, 0.0, ""));
    Material *m6 = scene.addMaterial(new Material(0.0, 0.0, 1.0, Vector3f(0.99, 0.99, 0.99), Vector3f(0.0, 0.0, 0.0), 0.0, 1.33, ""));
//    Material *m7 = scene.addMaterial(new Material(DIFFUSION, Vector3f(0.0, 0.0, 0.0), Vector3f(1.0, 1.0, 1.0)));

    scene.addObject(new Plane(Vector3f(1.0, 40.8, 81.6), Vector3f(1.0, 0.0, 0.0), m1));
//    scene.addObject(new Plane(Vector3f(99.0, 40.8, 81.6), Vector3f(-1.0, 0.0, 0.0), m2));
    scene.addObject(new Plane(Vector3f(50, 40.8, 0), Vector3f(0.0, 0.0, 1.0), m3));
    scene.addObject(new Plane(Vector3f(50, 40.8, 170), Vector3f(0.0, 0.0, -1.0), m4));
    scene.addObject(new Plane(Vector3f(50, 0.0, 81.6), Vector3f(0.0, 1., 0.0), m3));
//    scene.addObject(new Plane(Vector3f(50, 81.6, 81.6), Vector3f(0.0, -1.0, 0.0), m3));
//    scene.addObject(new Sphere(Vector3f(27, 16.5, 47), 16.5, m5));
//    scene.addObject(new Sphere(Vector3f(73, 16.5, 78), 16.5, m6));
//    scene.addObject(new Sphere(Vector3f(50, 681.6 - .27, 81.6), 600, m7));
//    scene.addObject(new Mesh("mesh/cube.obj", 73, 20, 30, 20, 20, 20, m3));
//    scene.addObject(new Mesh("mesh/normalized_bunny_100.obj", 73, 40, 30, 20, 20, 20, m3));

//    scene.addObject(new Mesh("mesh/normalized_dragon_100k.obj", 50, 0, 60, 50, 50, 50, m5));
//    scene.addObject(new Mesh("mesh/fixed.perfect.dragon.100K.0.07.obj", 50, 25, 60, 50, 50, 50, m3));
//    scene.addObject(new Mesh("mesh/bunny_200.obj", 50, 0, 60, 200, 200, 200, m3));
//    scene.addObject(new Mesh("mesh/bunny_1k.obj", 50, -10, 60, 200, 200, 200, m3));
//    scene.addObject(new Mesh("mesh/normalized_bunny_100.obj", 50, 30, 30, 20, 20, 20, m3));
//    scene.addObject(new Mesh("mesh/cube.obj", 50, 0, 30, 30, 30, 30, m6));
//    scene.addObject(new Mesh("mesh/normalized_bunny_1k.obj", 50, 30, 30, 20, 20, 20, nullptr));
//    scene.addObject(new Mesh("mesh/cube.obj", 50, 0, 30, 30, 30, 30, m6));
    scene.addObject(new Mesh("mesh/balon.obj", 30, 20, 30, 50, 50, 50, nullptr));

//    scene.addLight(new PointLight(Vector3f(50, 81, 81.6), Vector3f(6000.0, 6000.0, 6000.0)));
//    scene.addLight(new PointLight(Vector3f(90, 70, 90), Vector3f(6000.0, 6000.0, 6000.0)));
//    scene.addLight(new PointLight(Vector3f(10, 70, 90), Vector3f(6000.0, 6000.0, 6000.0)));
//    scene.addLight(new PointLight(Vector3f(50, 70, 10), Vector3f(6000.0, 6000.0, 6000.0)));
//    scene.addLight(new PointLight(Vector3f(50, 15, 30), Vector3f(6000.0, 6000.0, 6000.0)));
//    scene.addObject(new Mesh("mesh/cube.obj", 94, 71.6, 5, 10, 10, 10, m6));
    scene.addObject(new Sphere(Vector3f(94, 76.6, 5), 10, m6));
    scene.addLight(new PointLight(Vector3f(94, 76.6, 5), Vector3f(4000.0, 4000.0, 4000.0)));
}

void Scene::buildCornellBoxObjects(Scene &scene) {
//    printf("build conell box\n");
    scene.clear();

    scene.setCamera(
            new PerspectiveCamera(Vector3f(50, 52, 165), Vector3f(0, -0.22, -1).normalized(), Vector3f(0, 1, 0),IMG_WIDTH, IMG_HEIGHT, M_PI / 180 * 35 /* 0.502643 */));

    Material *m1 = scene.addMaterial(new Material(1.0, 0.0, 0.0, Vector3f(255 / 255.0, 175 / 255.0, 204 / 255.0), Vector3f(0.0, 0.0, 0.0), 0.0,0.0, ""));
    Material *m2 = scene.addMaterial(new Material(1.0, 0.0, 0.0, Vector3f(162 / 255.0, 210 / 255.0, 255 / 255.0), Vector3f(0.0, 0.0, 0.0), 0.0,0.0, ""));
//    Material *m1 = scene.addMaterial(new Material(1.0, 0.0, 0.0, Vector3f(255 / 255.0, 181 / 255.0, 167 / 255.0), Vector3f(0.0, 0.0, 0.0), 0.0,0.0, ""));
//    Material *m2 = scene.addMaterial(new Material(1.0, 0.0, 0.0, Vector3f(254 / 255.0, 200 / 255.0, 154 / 255.0), Vector3f(0.0, 0.0, 0.0), 0.0,0.0, ""));
    Material *m3 = scene.addMaterial(new Material(1.0, 0.0, 0.0, Vector3f(248 / 255.0, 237 / 255.0, 235 / 255.0), Vector3f(0.0, 0.0, 0.0), 0.0,0.0, ""));
//    Material *m4 = scene.addMaterial(new Material(1.0, 0.0, 0.0, Vector3f(0.0, 0.0, 0.0), Vector3f(0.0, 0.0, 0.0), 0.0, 0.0, ""));
//    Material *m5 = scene.addMaterial(new Material(0.0, 1.0, 0.0, Vector3f(0.99, 0.99, 0.99), Vector3f(0.0, 0.0, 0.0), 0.0, 0.0, ""));
    Material *m6 = scene.addMaterial(new Material(0.0, 0.0, 1.0, Vector3f(0.99, 0.99, 0.99), Vector3f(0.0, 0.0, 0.0), 0.0, 1.33, ""));

    Material *m_refr_yellow = scene.addMaterial(new Material(0.0, 0.0, 1.0, 0 * Vector3f(1, 1, 1) + 1 * Vector3f(255, 242, 148) / 255, Vector3f(0.0, 0.0, 0.0), 0.0, 1.5, ""));
    Material *m_refl_yellow = scene.addMaterial(new Material(0.4, 0.6, 0.0, 0 * Vector3f(1, 1, 1) + 1 *  Vector3f(218,165,32) / 255, Vector3f(0.0, 0.0, 0.0), 0.0, 1.5, ""));

    scene.addObject(new Plane(Vector3f(1.0, 40.8, 81.6), Vector3f(1.0, 0.0, 0.0), m1));
    scene.addObject(new Plane(Vector3f(99.0, 40.8, 81.6), Vector3f(-1.0, 0.0, 0.0), m2));
    scene.addObject(new Plane(Vector3f(50, 40.8, 0), Vector3f(0.0, 0.0, 1.0), m3));
    scene.addObject(new Plane(Vector3f(50, 40.8, 170), Vector3f(0.0, 0.0, -1.0), m3));
    scene.addObject(new Plane(Vector3f(50, 0.0, 81.6), Vector3f(0.0, 1., 0.0), m3));
    scene.addObject(new Plane(Vector3f(50, 81.6, 81.6), Vector3f(0.0, -1.0, 0.0), m3));


    scene.addObject(new Mesh("mesh/cube.obj", 50, 0, 30, 30, 30, 30, m6));
    scene.addObject(new Mesh("mesh/cube.obj", 30, 0, 60, 20, 20, 20, m6));
    scene.addObject(new Mesh("mesh/cube.obj", 70, 0, 60, 20, 20, 20, m6));
//
    scene.addObject(new Mesh("mesh/normalized_dragon_100k.obj", 50, 30, 30, 25, 25, 25, m_refr_yellow));
    scene.addObject(new Mesh("mesh/normalized_bunny_1k.obj", 30, 20, 60, 15, 15, 15, m_refl_yellow));
    scene.addObject(new Mesh("mesh/cat_texture.obj", 70, 20, 60, 25, 25, 25, nullptr));

    scene.addLight(new PointLight(Vector3f(50, 10, 30), 8e3 * Vector3f(255, 161, 72) / 255));
    scene.addLight(new PointLight(Vector3f(30, 10, 60), 8e3 * Vector3f(255, 161, 72) / 255));
    scene.addLight(new PointLight(Vector3f(70, 10, 60), 8e3 * Vector3f(255, 161, 72) / 255));
    scene.addLight(new DiskLight(Vector3f(50, 60, 80), Vector3f(0, -1, -1), 10, 2e4 * Vector3f(1.0, 1.0, 1.0)));

}

void Scene::buildCornellBoxPlaneHotBalloon(Scene &scene) {
//    printf("build conell box\n");
    scene.clear();

    scene.setCamera(new PerspectiveCamera(Vector3f(60, 52, 165), Vector3f(0, -0.042612, -1).normalized(), Vector3f(0, 1, 0),IMG_WIDTH, IMG_HEIGHT, M_PI / 180 * 45 /* 0.502643 */));

    Material *m1 = scene.addMaterial(new Material(1.0, 0.0, 0.0, Vector3f(135, 206, 235) / 255, Vector3f(1.0, 1.0, 1.0), 5.0,0.0, ""));
    Material *m2 = scene.addMaterial(new Material(1.0, 0.0, 0.0, Vector3f(150, 205, 50) / 255, Vector3f(1.0, 1.0, 1.0), 5.0,0.0, ""));
    Material *m3 = scene.addMaterial(new Material(0.7, 0.3, 0.0, Vector3f(248 / 255.0, 237 / 255.0, 235 / 255.0), Vector3f(0.0, 0.0, 0.0), 0.0,0.0, ""));
//    Material *m4 = scene.addMaterial(new Material(1.0, 0.0, 0.0, Vector3f(0.0, 0.0, 0.0), Vector3f(0.0, 0.0, 0.0), 0.0, 0.0, ""));
//    Material *m5 = scene.addMaterial(new Material(0.0, 1.0, 0.0, Vector3f(0.99, 0.99, 0.99), Vector3f(0.0, 0.0, 0.0), 0.0, 0.0, ""));
//    Material *m6 = scene.addMaterial(new Material(0.0, 0.0, 1.0, Vector3f(0.99, 0.99, 0.99), Vector3f(0.0, 0.0, 0.0), 0.0, 1.33, ""));
    Material *m7 = scene.addMaterial(new Material(0.3, 0.2, 0.5, Vector3f(0.99, 0.99, 0.99), Vector3f(0.0, 0.0, 0.0), 0.0, 1.33, ""));

    scene.addObject(new Plane(Vector3f(1.0, 40.8, 81.6), Vector3f(1.0, 0.0, 0.0), m1));
    scene.addObject(new Plane(Vector3f(50, 40.8, 0), Vector3f(0.0, 0.0, 1.0), m2));
    scene.addObject(new Plane(Vector3f(50, 0.0, 81.6), Vector3f(0.0, 1., 0.0), m3));


    scene.addObject(new Mesh("mesh/balloon.obj", 45, 35, 25, 50, 50, 50, nullptr));

    double x = 100, z = 40, d = 14, sqrt3 = sqrt(3), sqrt6 = sqrt(6);

    scene.addObject(new Sphere(Vector3f(x, (0.5 + sqrt6 / 3) * d, z), d / 2, m7));
    scene.addLight(new PointLight(Vector3f(x, (0.5 + sqrt6 / 3) * d, z), 3e3 * Vector3f(1.0, 1.0, 0.5)));

    scene.addObject(new Sphere(Vector3f(x - 0.5 * d, 0.5 * d, z - sqrt3 / 6 * d), d / 2, m7));
    scene.addLight(new PointLight(Vector3f(x - 0.5 * d, 0.5 * d, z - sqrt3 / 6 * d), 3e3 * Vector3f(0.5, 0.5, 1.0)));

    scene.addObject(new Sphere(Vector3f(x + 0.5 * d, 0.5 * d, z - sqrt3 / 6 * d), d / 2, m7));
    scene.addLight(new PointLight(Vector3f(x + 0.5 * d, 0.5 * d, z - sqrt3 / 6 * d), 3e3 * Vector3f(0.5, 1.0, 0.5)));

    scene.addObject(new Sphere(Vector3f(x, 0.5 * d, z + sqrt3 / 3 * d), d / 2, m7));
    scene.addLight(new PointLight(Vector3f(x, 0.5 * d, z + sqrt3 / 3 * d), 3e3 * Vector3f(1.0, 0.5, 0.5)));

//    scene.addLight(new DiskLight(Vector3f(100, 100, 100), Vector3f(-1, -1, -1), 40, 1e5 * Vector3f(1.0, 1.0, 1.0)));
    scene.addLight(new DiskParallelLight(Vector3f(100, 0, 70), Vector3f(-1, 1, 0), 10, 2e5 * Vector3f(1.0, 1.0, 1.0)));
}

void Scene::buildGlassCups(Scene &scene) {
    scene.clear();

//    Camera *camera = scene.setCamera(new PerspectiveCamera(1e2 * Vector3f(-0.465929239988327, 0.3516400158405304, 0.17683753371238708),-Vector3f(-0.08583881705999374, 0.04929906874895096,0.01418816763907671).normalized(),Vector3f(0.04863884672522545, 0.08700348436832428, -0.0080411983653903).normalized(),IMG_WIDTH, IMG_HEIGHT, M_PI / 180 * 30 /* 0.502643 */));
//    camera->center.print();
//    camera->direction.print();
//    camera->up.print();
    scene.setCamera(new DOFCamera(1e2 * Vector3f(-0.465929239988327, 0.3516400158405304, 0.17683753371238708),-Vector3f(-0.08583881705999374, 0.04929906874895096,0.01418816763907671).normalized(), Vector3f(0.04863884672522545, 0.08700348436832428, -0.0080411983653903).normalized(), 100 * Vector3f(0, 0, 0), 0.6, IMG_WIDTH, IMG_HEIGHT, M_PI / 180 * 30 /* 0.502643 */));

    Material *m0 = scene.addMaterial(new Material(1.0, 0.0, 0.0, Vector3f(248 / 255.0, 237 / 255.0, 235 / 255.0), Vector3f(1.0, 1.0, 1.0), 10,0.0, ""));
    Material *m1 = scene.addMaterial(new Material(0.05, 0.1, 0.85, Vector3f(1, 1, 1), Vector3f(0.0, 0.0, 0.0), 0.0, 1.5, ""));

    scene.addObject(new Plane(Vector3f(0.0, 0.0, 0.0), Vector3f(0.0, 1.0, 0.0), m0));
    scene.addObject(new Mesh("mesh/whiskey_glass.obj", 0, 0, 0, 100, 100, 100, m1));

    scene.addLight(new DiskParallelLight(Vector3f(40, 40, -20), Vector3f(-1, -1, 1), 20, 5e3 * Vector3f(1.0, 1.0, 1.0)));

    scene.addLight(new DiskLight(Vector3f(0, 100, 0), Vector3f(0, -1, 0), 10, 4e3 * Vector3f(0.84, 1.0, 0.20)));
    scene.addLight(new DiskLight(Vector3f(25, 100, 0), Vector3f(0, -1, 0), 10, 4e3 * Vector3f(0.84, 1.0, 0.20)));
    scene.addLight(new DiskLight(Vector3f(0, 100, 25), Vector3f(0, -1, 0), 10, 4e3 * Vector3f(0.84, 1.0, 0.20)));
    scene.addLight(new DiskLight(Vector3f(25, 100, 25), Vector3f(0, -1, 0), 10, 4e3 * Vector3f(0.84, 1.0, 0.20)));

    scene.addLight(new DiskLight(Vector3f(45, 50, -68), -Vector3f(0.17, 0.21, -0.40), 14,3e4 * Vector3f(1, 0.61, 0.91)));
    scene.addLight(new DiskLight(Vector3f(46, 79, -59), -Vector3f(0.13, 0.32, -0.32), 20,2e4 * Vector3f(1, 0.40, 0.85)));
    scene.addLight(new DiskLight(Vector3f(-21, 89, -31), -Vector3f(-0.29, 0.80, -0.38), 40,4e4 * Vector3f(0.70, 1, 0.89)));
//    scene.addLight(new DiskLight(Vector3f(-32, 34, 104), -Vector3f(-0.08, 0.06, 0.22), 40,3e4 * Vector3f(0.42, 0.47, 1)));
}

void Scene::buildFountain(Scene &scene) {
    scene.clear();

    scene.setCamera(new PerspectiveCamera(10 * Vector3f( -1.5577569007873535, 1.367582678794860, 1.4860734939575195) + 2 * Vector3f(0.608250737190246, 1.8235139577882364e-05, 0.793745219707489),-Vector3f(-0.7926756143569946,  -0.05187712982296944, 0.6074323058128357 ).normalized(),Vector3f(  -0.04118828848004341,  0.9986534118652344,  0.03153984248638153).normalized(),IMG_WIDTH, IMG_HEIGHT, M_PI / 180 * 50 /* 0.502643 */));
//    camera->center.print();
//    camera->direction.print();
//    camera->up.print();
//    Vector3f::cross(camera->direction, camera->up).print();
//    + v + 5 * -Vector3f(-0.79, -0.05,0.60).normalized()
//    Camera *camera = scene.setCamera(new DOFCamera(Vector3f(-14.3611, 13.6759, 16.4482), Vector3f(0.7927, 0.0519, -0.6074), Vector3f(-0.0412, 0.9987, 0.0315), 10 * Vector3f(0.43078, 2.0040, 0.67962), 2e-1, IMG_WIDTH, IMG_HEIGHT, M_PI / 180 * 50 /* 0.502643 */));


    Material *m1 = scene.addMaterial(new Material(0.1, 0.0, 0.9, Vector3f(1, 1, 1), Vector3f(1.0, 1.0, 1.0), 2.0, 1.3, ""));

    scene.addObject(new Mesh("mesh/fountain_solid.obj", 0, 0, 0, 10, 10, 10, nullptr));
    scene.addObject(new Mesh("mesh/fountain_fluid.obj", 0, 0, 0, 10, 10, 10, m1));

    scene.addLight(new DiskLight(10 * Vector3f(0.72, 5, -0.43), -Vector3f( 0.02094241790473461,  0.992747724056243,  -0.11837799102067947), 20, 2e2 * Vector3f(235, 238, 255) / 255.0));
    scene.addLight(new DiskParallelLight(10 * Vector3f(2.0322399139404297, 7.067582607269287,  2.506073474884033), -Vector3f( 0.3338068425655365,  0.8812054991722107,  0.334738552570343), 5, 2e3 * Vector3f(1, 1, 1)));
}

void Scene::buildCornellBoxTest(Scene &scene) {
//    printf("build conell box\n");
    scene.clear();
    scene.setCamera(new PerspectiveCamera(Vector3f(50, 52, 165), Vector3f(0, -0.22, -1).normalized(), Vector3f(0, 1, 0),IMG_WIDTH, IMG_HEIGHT, M_PI / 180 * 60 /* 0.502643 */));

    Material *m3 = scene.addMaterial(new Material(1.0, 0.0, 0.0, Vector3f(248 / 255.0, 237 / 255.0, 235 / 255.0), Vector3f(0.0, 0.0, 0.0), 0.0,0.0, ""));
    Material *m6 = scene.addMaterial(new Material(0.0, 0.0, 1., Vector3f(0.99, 0.99, 0.99), Vector3f(0.0, 0.0, 0.0), 0.0, 1.1, ""));
    Material *m7 = scene.addMaterial(new Material(0.0, 0.0, 1.0, Vector3f(0.99, 0.99, 0.99), Vector3f(0.0, 0.0, 0.0), 0.0, 1.5, ""));

    Material *m_refr_yellow = scene.addMaterial(new Material(0.0, 0.0, 1.0, 0 * Vector3f(1, 1, 1) + 1 * Vector3f(255, 242, 148) / 255, Vector3f(0.0, 0.0, 0.0), 0.0, 1.5, ""));
    Material *m_refl_yellow = scene.addMaterial(new Material(0.4, 0.6, 0.0, 0 * Vector3f(1, 1, 1) + 1 *  Vector3f(218,165,32) / 255, Vector3f(0.0, 0.0, 0.0), 0.0, 1.5, ""));

//    scene.addObject(new Plane(Vector3f(1.0, 40.8, 81.6), Vector3f(1.0, 0.0, 0.0), m3));
    scene.addObject(new Plane(Vector3f(99.0, 40.8, 81.6), Vector3f(-1.0, 0.0, 0.0), m3));
    scene.addObject(new Plane(Vector3f(50, 40.8, 0), Vector3f(0.0, 0.0, 1.0), m3));
    scene.addObject(new Plane(Vector3f(50, 40.8, 170), Vector3f(0.0, 0.0, -1.0), m3));
    scene.addObject(new Plane(Vector3f(50, 0.0, 81.6), Vector3f(0.0, 1., 0.0), m3));
//    scene.addObject(new Plane(Vector3f(50, 81.6, 81.6), Vector3f(0.0, -1.0, 0.0), m3));

//    scene.addObject(new Mesh("mesh/cube.obj", 70, 0, 60, 20, 20, 20, m6));

//    scene.addObject(new Triangle(Vector3f(80, 0, 50), Vector3f(80, 20, 50), Vector3f(80, 0, 70), m6));
//    scene.addObject(new Triangle(Vector3f(80, 20, 70), Vector3f(80, 0, 70), Vector3f(80, 20, 50), m6));
//
//    scene.addObject(new Triangle(Vector3f(80, 20, 50), Vector3f(60, 20, 50), Vector3f(80, 20, 70), m6));
//    scene.addObject(new Triangle(Vector3f(60, 20, 70), Vector3f(80, 20, 70), Vector3f(60, 20, 50), m6));

//    scene.addObject(new Triangle(Vector3f(80, 0, 50), Vector3f(80, 0, 70), Vector3f(60, 0, 50), m6));
//    scene.addObject(new Triangle(Vector3f(60, 0, 70), Vector3f(60, 0, 50), Vector3f(80, 0, 70), m6));

//    scene.addLight(new PointLight(Vector3f(70, 10, 60), 4e3 * Vector3f(1, 1, 1)));

    scene.addObject(new Sphere(Vector3f(30, 10, 60), 10, m7));
    scene.addLight(new PointLight(Vector3f(10, 10, 60), 1e3 * Vector3f(1, 1, 1)));
//
//    scene.addLight(new PointLight(Vector3f(50, 10, 30), 8e3 * Vector3f(255, 161, 72) / 255));
//    scene.addLight(new PointLight(Vector3f(30, 10, 60), 8e3 * Vector3f(255, 161, 72) / 255));
//    scene.addLight(new DiskLight(Vector3f(50, 60, 80), Vector3f(0, -1, -1), 10, 2e4 * Vector3f(1.0, 1.0, 1.0)));

}
void Scene::buildScene(Scene &scene, int id) {
    switch (id) {
        case 0: break;
        case 1: buildCornellBoxObjects(scene); return ;
        case 2: buildCornellBoxPlaneHotBalloon(scene); return ;
        case 3: buildGlassCups(scene); return ;
        case 4: buildFountain(scene); return ;
        default: assert(false);
    }
    // else do
    buildCornellBoxTest(scene);
}

Scene::Scene() : camera(nullptr) {
    clear();
}

Scene::~Scene() {
    destroy();
}

void Scene::clear() {
    destroy();
}

void Scene::destroy() {
    delete camera;
    for (auto object : objects) {
        delete object;
    }
    for (auto material : materials) {
        delete material;
    }
    for (auto light : lights) {
        delete light;
    }
}

Camera *Scene::setCamera(Camera *camera_) {
    assert(camera == nullptr);
    camera = camera_;
    return camera;
}

Camera *Scene::getCamera() {
    return camera;
}

Material *Scene::addMaterial(Material *material) {
    materials.push_back(material);
    return material;
}

Object3D *Scene::addObject(Object3D *object) {
    objects.push_back(object);
    return object;
}


Light *Scene::addLight(Light *light) {
    lights.push_back(light);
    return light;
}

std::vector<Light *> &Scene::getLights() {
    return lights;
}

std::vector<Object3D *> &Scene::getObjects() {
    return objects;
}


