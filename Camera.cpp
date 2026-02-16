//
// Created by Daniel Elbaz on 1/23/26.
//

#include "Camera.h"

#include <iostream>
#include <algorithm>

std::array<std::array<uint8_t, Camera::WIDTH*3>, Camera::HEIGHT> Camera::RayTrace() {
    for (int i = 0; i < cv.WIDTH*cv.HEIGHT; i++) {
        //returns a ray in the form of P + tD
        Ray ray = orthogonal ? this->MakeRay(i % cv.WIDTH, i / cv.WIDTH, false)
        : this->MakeRay(i % cv.WIDTH, i / cv.WIDTH, true);


        uint32_t finalColor = CastRay(ray);

        frameBuffer[i/cv.WIDTH][i%cv.HEIGHT*3] = ((finalColor & 0xFF0000) >> 16u);
        frameBuffer[i/cv.WIDTH][i%cv.HEIGHT*3 + 1] = ((finalColor & 0x00FF00) >> 8u);
        frameBuffer[i/cv.WIDTH][i%cv.HEIGHT*3 + 2] = ((finalColor & 0x0000FF));
    }
    return frameBuffer;
}

uint32_t Camera::CastRay(const Ray &ray, int depth) {
    float smallest_t = INFINITY;
    const SceneObject *currentSceneObject = nullptr;

    for (int j = 0; j < sceneObjects.size(); j++) {
        //first stores whether we intersect, second stores the t value
        const auto* tempSceneObject = sceneObjects[j].get();
        std::pair<bool, float> intersectValue = tempSceneObject->Intersects(ray, 0.001f, INFINITY);
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
        return 0x000000;
    }

    uint32_t sceneObjectColor = currentSceneObject->color;

    Vector3 intersectionPoint = ray.origin + (smallest_t * ray.direction);

    //ambient
    float lightPercentage{0.3f};

    for (const Light &l : lights) {
        //diffuse lighting calculation

        //direction vector going from the light source to the point of intersection
        Vector3 lightToIntersect = (l.position - intersectionPoint);
        Vector3 lightToIntersectNormalized = normalize(lightToIntersect);
        //ray made from this vector
        Ray lightToIntersectRay{intersectionPoint, lightToIntersectNormalized};

        bool lightBlocked = false;

        //check to see if we hit any objects
        for (int j = 0; j < sceneObjects.size(); j++) {

            //first stores whether we intersect, second stores the t value
            const auto* tempSceneObject = sceneObjects[j].get();

            if (tempSceneObject == currentSceneObject) {
                continue;
            }

            if (tempSceneObject->Intersects(lightToIntersectRay, 0.001f, length(lightToIntersect)).first) {
                lightBlocked = true;
                break;
            }

        }

        if (!lightBlocked) {
            AddLight(intersectionPoint, currentSceneObject, l, ray, lightPercentage);
        }

    }

    uint32_t additionalColor = 0x000000;
    float refl = currentSceneObject->reflectivity;

    if (refl > 0.0f && depth > 0) {
        Vector3 sceneObjectNormal = currentSceneObject->GetNormal(intersectionPoint);
        Vector3 reflectedRayDirection = ray.direction - (2*dot(ray.direction, sceneObjectNormal) * sceneObjectNormal);
        Ray reflectedRay{intersectionPoint, normalize(reflectedRayDirection)};

        additionalColor = CastRay(reflectedRay, depth - 1);
    }

    lightPercentage = std::clamp(lightPercentage, 0.0f, 1.0f);

    uint32_t noReflectionColor = static_cast<uint8_t>((((sceneObjectColor & 0x0000FF)) * lightPercentage));
    noReflectionColor += static_cast<uint8_t>(((sceneObjectColor & 0x00FF00) >> 8u) * lightPercentage) << 8u;
    noReflectionColor += static_cast<uint8_t>(((sceneObjectColor & 0xFF0000) >> 16u) * lightPercentage) << 16u;

    uint32_t finalColor = static_cast<uint8_t>((additionalColor & 0x0000FF) * refl + ((1.0f-refl) * (noReflectionColor & 0x0000FF)));
    finalColor += static_cast<uint8_t>(((additionalColor & 0x00FF00) >> 8u) * refl + ((1.0f-refl) * ((noReflectionColor & 0x00FF00) >> 8u))) << 8u;
    finalColor += static_cast<uint8_t>(((additionalColor & 0xFF0000) >> 16u) * refl + ((1.0f-refl) * ((noReflectionColor & 0xFF0000) >> 16u))) << 16u;

    return finalColor;

}

void Camera::AddLight(const Vector3 intersectionPoint, const SceneObject *currentSceneObject, const Light &l, const Ray &ray, float &lightPercentage) {
    //normal vector of the tangent plane of the point on the sphere
    Vector3 normalVector = normalize(currentSceneObject->GetNormal(intersectionPoint));
    if (dot(ray.direction, normalVector) > 0.0f) {
        normalVector = -normalVector;
    }
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
