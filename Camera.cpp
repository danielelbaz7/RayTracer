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
        const SceneObject *currentSceneObject = nullptr;

        for (int j = 0; j < sceneObjects.size(); j++) {
            //first stores whether we intersect, second stores the t value
            const auto* tempSceneObject = sceneObjects[j].get();
            std::pair<bool, float> intersectValue = tempSceneObject->Intersects(ray, 0, INFINITY);
            if (intersectValue.first == false) {
                continue;
            }
            if (intersectValue.second >= 0  && intersectValue.second < smallest_t) {
                currentSceneObject = tempSceneObject;
                smallest_t = intersectValue.second;
            }
        }

        //if we didn't hit, next pixel
        if (!currentSceneObject) {
            continue;
        }

        uint32_t sceneObjectColor = currentSceneObject->color;

        //ambient
        float lightPercentage{0.3f};

        for (const Light &l : lights) {
            //diffuse lighting calculation
            Vector3 intersectionPoint = ray.origin + (smallest_t * ray.direction);
            //normal vector of the tangent plane of the point on the sphere
            Vector3 normalVector = normalize(intersectionPoint - currentSceneObject->center);
            Vector3 lightVector = l.position - intersectionPoint;

            float lightDistanceSquared = std::max(dot(lightVector, lightVector), 0.001f);

            lightVector = normalize(lightVector);

            lightPercentage += currentSceneObject->diffuseCoefficient * (l.intensity/lightDistanceSquared) *
                std::max(0.0f, dot(normalVector, lightVector));

            //specular (phong)
            Vector3 reflectionVector = normalize((2*dot(normalVector, lightVector))*normalVector - lightVector);
            Vector3 eyeVector = normalize(ray.origin - intersectionPoint);

            float specularLight = currentSceneObject->specularCoefficient * (l.intensity/lightDistanceSquared) *
                std::pow(std::max(0.0f, dot(eyeVector, reflectionVector)), currentSceneObject->shininess);

            lightPercentage += specularLight;
        }

        lightPercentage = std::clamp(lightPercentage, 0.0f, 1.0f);


        frameBuffer[i/cv.WIDTH][i%cv.HEIGHT*3] = ((sceneObjectColor & 0xFF0000) >> 16u)
            * lightPercentage;
        frameBuffer[i/cv.WIDTH][i%cv.HEIGHT*3 + 1] = ((sceneObjectColor & 0x00FF00) >> 8u)
            * lightPercentage;
        frameBuffer[i/cv.WIDTH][i%cv.HEIGHT*3 + 2] = ((sceneObjectColor & 0x0000FF))
            * lightPercentage;
    }
    return frameBuffer;
}
