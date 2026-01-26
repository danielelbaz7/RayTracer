//
// Created by Daniel Elbaz on 1/23/26.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H
#pragma once

#include <vector>
#include "Vector3.h"
#include "Sphere.h"



class Camera {
private:
    struct cameraValues {
        Vector3 pos{};
        Vector3 right{1,0,0};
        Vector3 up{0,1,0};
        Vector3 lookAt{0,0,1};
    };

    const std::vector<Sphere> &spheres;

public:
    Camera(const std::vector<Sphere> &spheresVec) : spheres(spheresVec) {};
    uint8_t* RayTrace();

    struct Ray {
        Vector3 origin;
        Vector3 direction;
        Ray(cameraValues &cv, int xi, int yi) :
        //resets position to 0,0 in world space, then adds the amount of pixels
        origin{
            cv.pos + (cv.right * -(((WIDTH/2) - xi) * PIXEL_DISTANCE)) + (cv.up * (((HEIGHT/2) - yi) * PIXEL_DISTANCE))
            },
        direction{cv.lookAt/sqrt(dot(cv.lookAt, cv.lookAt))} {};
    };

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