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

public:
    Camera(const std::vector<Sphere> &spheresVec) : spheres(spheresVec) {};
    uint8_t* RayTrace();


private:
    static constexpr int WIDTH{256};
    static constexpr int HEIGHT{256};
    static constexpr float PIXEL_DISTANCE{0.05};

    uint8_t frameBuffer[HEIGHT][WIDTH*3];

    cameraValues cv{};

    //this will create and return a ray based on how far we are inot the array
    Ray MakeRay(int xi, int yi) {
        return Ray(this->cv, xi, yi);
    }

};


#endif //RAYTRACER_CAMERA_H