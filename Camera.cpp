//
// Created by Daniel Elbaz on 1/23/26.
//

#include "Camera.h"

uint8_t* Camera::RayTrace(const std::vector<Sphere>& spheres) {
    for (int i = 0; i < WIDTH*HEIGHT*3; i++) {
        for (int j = 0; j < spheres.size(); j++) {

        }
    }
    return *frameBuffer;
}