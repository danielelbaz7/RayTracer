//
// Created by Daniel Elbaz on 1/23/26.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H
#pragma once

#include <vector>
#include "Vector3.h"
#include "SceneObject.h"
#include "Ray.h"
#include "Light.h"


class Camera {
private:
    const std::vector<std::unique_ptr<SceneObject>> &sceneObjects;
    const std::vector<Light> &lights;
    static constexpr float PIXEL_DISTANCE{0.03};
    static constexpr int WIDTH{512};
    static constexpr int HEIGHT{512};

public:
    Camera(const std::vector<std::unique_ptr<SceneObject>> &sceneObjectsVec, const std::vector<Light> &lightVec) : sceneObjects(sceneObjectsVec), lights(lightVec) {}
    std::array<std::array<uint8_t, WIDTH*3>, HEIGHT> RayTrace();


private:
    std::array<std::array<uint8_t, WIDTH*3>, HEIGHT> frameBuffer{};

    cameraValues cv{
        {0,0,-10},
        {1,0,0}, {0,1,0}, {0,0,1}, WIDTH, HEIGHT, PIXEL_DISTANCE};

    //this will create and return a ray based on how far we are in the array
    Ray MakeRay(int xi, int yi) {
        return Ray(this->cv, xi, yi);
    }

};


#endif //RAYTRACER_CAMERA_H