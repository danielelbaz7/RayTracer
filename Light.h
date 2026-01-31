//
// Created by Daniel Elbaz on 1/31/26.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H
#include "Vector3.h"

struct Light {
    Vector3 position{};
    float intensity{1};

    Light(const Vector3 pos) : position(pos) {};
};

#endif //RAYTRACER_LIGHT_H