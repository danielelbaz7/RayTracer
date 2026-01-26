//
// Created by Daniel Elbaz on 1/23/26.
//

#ifndef RAYTRACER_WORLD_H
#define RAYTRACER_WORLD_H
#include <vector>

#include "Sphere.h"
#include "Camera.h"


class World {
public:
    void AddSphere(const Sphere &s);
    World() : camera(spheres) {};
    Camera camera;

private:
    std::vector<Sphere> spheres{};
};


#endif //RAYTRACER_WORLD_H