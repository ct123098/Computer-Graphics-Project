//
// Created by tom20 on 2020/12/22.
//

#ifndef RENDER_SCENE_HPP
#define RENDER_SCENE_HPP

#include "core/light.hpp"
#include "core/camera.hpp"
#include "core/material.hpp"
#include "objects/group.hpp"

class Scene {
private:
    Camera *camera;
    std::vector<Object3D*> objects;
    std::vector<Material*> materials;
    std::vector<Light*> lights;

public:
    Scene();
    ~Scene();
    void clear();
    void destroy();
    Camera *setCamera(Camera *camera_);
    Camera *getCamera();
    Material *addMaterial(Material *material);
    Object3D *addObject(Object3D *object);
    std::vector<Object3D*> &getObjects();
    Light *addLight(Light *light);
    std::vector<Light *> &getLights();

//    static void buildCornellBox(Scene &scene);
//    static void buildCornellBoxPlaneGlassDragon(Scene &scene);
    static void buildCornellBoxPlaneHotBalloon(Scene &scene);
    static void buildCornellBoxPlane(Scene &scene);
    static void buildCornellBoxObjects(Scene &scene);

    static void buildScene(Scene &scene, int id = 0);

    static void buildGlassCups(Scene &scene);
    static void buildFountain(Scene &scene);

    static void buildCornellBoxTest(Scene &scene);
};

#endif //RENDER_SCENE_HPP
