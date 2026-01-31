//
// Created by Daniel Elbaz on 1/23/26.
//

#include "Camera.h"

#include <iostream>
#include <algorithm>

std::array<std::array<uint8_t, Camera::WIDTH*3>, Camera::HEIGHT> Camera::RayTrace() {
    for (int i = 0; i < cv.WIDTH*cv.HEIGHT; i++) {
        //returns a ray in the form of P + tD
        Ray ray = this->MakeRay(i % cv.HEIGHT, i / cv.WIDTH);

        float smallest_t = INFINITY;
        const Sphere *currentSphere = nullptr;

        for (int j = 0; j < spheres.size(); j++) {
            //first stores whether we intersect, second stores the t value
            const Sphere *tempSphere = &spheres[j];
            std::pair<bool, float> intersectValue = tempSphere->Intersects(ray, 0, INFINITY);
            if (intersectValue.first == false) {
                continue;
            }
            if (intersectValue.second < smallest_t) {
                currentSphere = tempSphere;
                smallest_t = intersectValue.second;
            }
        }

        //if we didn't hit, next pixel
        if (!currentSphere) {
            continue;
        }

        uint32_t sphereColor = currentSphere->color;

        float lightPercentage{0.3f};

        for (const Light &l : lights) {
            //lighting calculation
            Vector3 intersectionPoint = ray.origin + (smallest_t * ray.direction);
            //normal vector of the tangent plane of the point on the sphere
            Vector3 normalVector = normalize(intersectionPoint - currentSphere->center);
            Vector3 lightVector = normalize(l.position - intersectionPoint);

            lightPercentage += currentSphere->diffuseCoefficient * l.intensity *
                std::max(0.0f, dot(normalVector, lightVector));

        frameBuffer[i/cv.WIDTH][i%cv.HEIGHT*3] = ((sphereColor & 0xFF0000) >> 16u)
            * std::clamp(lightPercentage, 0.0f, 1.0f);
        frameBuffer[i/cv.WIDTH][i%cv.HEIGHT*3 + 1] = ((sphereColor & 0x00FF00) >> 8u)
            * std::clamp(lightPercentage, 0.0f, 1.0f);
        frameBuffer[i/cv.WIDTH][i%cv.HEIGHT*3 + 2] = ((sphereColor & 0x0000FF))
            * std::clamp(lightPercentage, 0.0f, 1.0f);
        }
    }
    return frameBuffer;
}
