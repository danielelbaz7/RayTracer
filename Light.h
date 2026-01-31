//
// Created by Daniel Elbaz on 1/31/26.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H
#include "Vector3.h"

struct Light {
    Vector3 position{5, 5, 5};
    float intensity{1};
};

#endif //RAYTRACER_LIGHT_H