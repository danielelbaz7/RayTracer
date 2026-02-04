//
// Created by Daniel Elbaz on 1/23/26.
//

#ifndef RAYTRACER_WORLD_H
#define RAYTRACER_WORLD_H
#include <vector>

#include "SceneObject.h"
#include "Camera.h"
#include "Light.h"


class World {
public:
    void AddSceneObject(std::unique_ptr<SceneObject> s);

    void AddLight(const Light &l);

    World() : camera(sceneObjects, lights) {};
    Camera camera;

private:
    std::vector<std::unique_ptr<SceneObject>> sceneObjects{};
    std::vector<Light> lights{};
};


#endif //RAYTRACER_WORLD_H