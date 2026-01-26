//
// Created by Daniel Elbaz on 1/23/26.
//

#include "Camera.h"

uint8_t* Camera::RayTrace() {
    for (int i = 0; i < WIDTH*HEIGHT; i++) {
        Ray ray = this->MakeRay(i % HEIGHT, i / WIDTH);
        for (int j = 0; j < spheres.size(); j++) {
            const Sphere *currentSphere = &spheres[j];
            std::pair<bool, float> intersectValue = currentSphere->Intersects(ray, 0, INFINITY);
            if (intersectValue.first == false) {
                continue;
            }

            const uint32_t sphereColor = static_cast<uint32_t>(currentSphere->color);
            frameBuffer[i/WIDTH][i%HEIGHT] = sphereColor & 0xFF0000 >> 16u;
            frameBuffer[i/WIDTH][i%HEIGHT + 1] = sphereColor & 0x00FF00 >> 8u;
            frameBuffer[i/WIDTH][i%HEIGHT + 2] = sphereColor & 0x0000FF;
        }
    }
    return *frameBuffer;
}