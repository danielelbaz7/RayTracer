//
// Created by Daniel Elbaz on 1/23/26.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H
#include "Vector3.h"
#include "Camera.h"

struct Sphere {
    int radius;
    Vector3 center;

    enum class Color : int {
        RED = 0xFF0000, GREEN = 0x00FF00, BLUE = 0x0000FF
    };

    //max distance dictates the max size of the ray, lower is the initial
    std::pair<bool, float> Intersects(const Camera::Ray &ray, int lowerDistance, int maxDistance) const {
        //calculate the discriminate and see if it can even be square rooted
        float dDotP = dot(ray.direction, ray.origin);
        float discriminate = dDotP * dDotP - dot(ray.origin, ray.origin) + 1;
        if (discriminate < 0) {
            return {false, -1};
        }

        float smallestT = std::min(-dDotP + sqrt(discriminate), -dDotP - sqrt(discriminate));
        return {true, smallestT};
    }

};

#endif //RAYTRACER_SPHERE_H