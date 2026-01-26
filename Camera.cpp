//
// Created by Daniel Elbaz on 1/23/26.
//

#include "Camera.h"

std::array<std::array<uint8_t, Camera::WIDTH*3>, Camera::HEIGHT> Camera::RayTrace() {
    for (int i = 0; i < cv.WIDTH*cv.HEIGHT; i++) {
        Ray ray = this->MakeRay(i % cv.HEIGHT, i / cv.WIDTH);
        for (int j = 0; j < spheres.size(); j++) {
            const Sphere *currentSphere = &spheres[j];
            std::pair<bool, float> intersectValue = currentSphere->Intersects(ray, 0, INFINITY);
            if (intersectValue.first == false) {
                continue;
            }

            const uint32_t sphereColor = static_cast<uint32_t>(currentSphere->color);
            frameBuffer[i/cv.WIDTH][i%cv.HEIGHT*3] = (sphereColor & 0xFF0000) >> 16u;
            frameBuffer[i/cv.WIDTH][i%cv.HEIGHT*3 + 1] = (sphereColor & 0x00FF00) >> 8u;
            frameBuffer[i/cv.WIDTH][i%cv.HEIGHT*3 + 2] = (sphereColor & 0x0000FF);
        }
    }
    return frameBuffer;
}