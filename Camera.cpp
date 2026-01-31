//
// Created by Daniel Elbaz on 1/23/26.
//

#include "Camera.h"

#include <iostream>

std::array<std::array<uint8_t, Camera::WIDTH*3>, Camera::HEIGHT> Camera::RayTrace() {
    for (int i = 0; i < cv.WIDTH*cv.HEIGHT; i++) {
        //returns a ray in the form of P + tD
        Ray ray = this->MakeRay(i % cv.HEIGHT, i / cv.WIDTH);

        for (int j = 0; j < spheres.size(); j++) {
            const Sphere *currentSphere = &spheres[j];
            //first stores whether we intersect, second stores the t value
            std::pair<bool, float> intersectValue = currentSphere->Intersects(ray, 0, INFINITY);
            if (intersectValue.first == false) {
                continue;
            }

            uint32_t sphereColor = currentSphere->color;

            float lightPercentage{0.5f};

            for (const Light &l : lights) {
                //lighting calculation
                Vector3 intersectionPoint = ray.origin + (intersectValue.second * ray.direction);
                //normal vector of the tangent plane of the point on the sphere
                Vector3 normalVector = intersectionPoint - currentSphere->center;
                Vector3 lightVector = l.position - intersectionPoint;

                lightPercentage += currentSphere->diffuseCoefficient * l.intensity *
                    std::max(0.0f, dot(normalVector, lightVector));
            }

            sphereColor *= lightPercentage;


            frameBuffer[i/cv.WIDTH][i%cv.HEIGHT*3] = (sphereColor & 0xFF0000) >> 16u;
            frameBuffer[i/cv.WIDTH][i%cv.HEIGHT*3 + 1] = (sphereColor & 0x00FF00) >> 8u;
            frameBuffer[i/cv.WIDTH][i%cv.HEIGHT*3 + 2] = (sphereColor & 0x0000FF);
        }
    }
    return frameBuffer;
}
