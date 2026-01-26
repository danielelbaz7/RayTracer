//
// Created by Daniel Elbaz on 1/23/26.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H
#pragma once

#include <vector>
#include "Vector3.h"
#include "Sphere.h"
#include "Ray.h"


class Camera {
private:
    const std::vector<Sphere> &spheres;
    static constexpr float PIXEL_DISTANCE{0.05};
    static constexpr int WIDTH{256};
    static constexpr int HEIGHT{256};

public:
    Camera(const std::vector<Sphere> &spheresVec) : spheres(spheresVec) {}
    std::array<std::array<uint8_t, WIDTH*3>, HEIGHT> RayTrace();


private:
    std::array<std::array<uint8_t, WIDTH*3>, HEIGHT> frameBuffer{};

    cameraValues cv{
        {0,0,0},
        {1,0,0}, {0,1,0}, {0,0,1}, WIDTH, HEIGHT, PIXEL_DISTANCE};

    //this will create and return a ray based on how far we are inot the array
    Ray MakeRay(int xi, int yi) {
        return Ray(this->cv, xi, yi);
    }

};


#endif //RAYTRACER_CAMERA_H