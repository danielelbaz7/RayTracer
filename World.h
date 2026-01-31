//
// Created by Daniel Elbaz on 1/23/26.
//

#ifndef RAYTRACER_WORLD_H
#define RAYTRACER_WORLD_H
#include <vector>

#include "Sphere.h"
#include "Camera.h"
#include "Light.h"


class World {
public:
    void AddSphere(const Sphere &s);

    void AddLight(const Light &l);

    World() : camera(spheres, lights) {};
    Camera camera;

private:
    std::vector<Sphere> spheres{};
    std::vector<Light> lights{};
};


#endif //RAYTRACER_WORLD_H