//
// Created by Daniel Elbaz on 1/23/26.
//

#include "Camera.h"

uint8_t* Camera::RayTrace(const std::vector<Sphere>& spheres) {
    for (int i = 0; i < WIDTH*HEIGHT; i++) {
        Ray ray = this->MakeRay(i % HEIGHT, i / WIDTH);
        for (int j = 0; j < spheres.size(); j++) {
            std::pair<bool, float> intersectValue = spheres[j].Intersects(ray, 0, INFINITY);

        }
    }
    return *frameBuffer;
}