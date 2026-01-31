//
// Created by Daniel Elbaz on 1/23/26.
//

#include "World.h"

void World::AddSphere(const Sphere &s) {
    spheres.push_back(s);
}

void World::AddLight(const Light &l) {
    lights.push_back(l);
}