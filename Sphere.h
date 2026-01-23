//
// Created by Daniel Elbaz on 1/23/26.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H
#include "Vector3.h"

struct Sphere {
    int radius;
    Vector3 center;

    enum class Color : int {
        RED = 0xFF0000, GREEN = 0x00FF00, BLUE = 0x0000FF
    };

};

#endif //RAYTRACER_SPHERE_H