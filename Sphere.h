//
// Created by Daniel Elbaz on 1/23/26.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H
#pragma once
#include "Vector3.h"

struct Sphere {
    int radius;
    Vector3 center;

    enum class Color : int {
        RED = 0xFF0000, GREEN = 0x00FF00, BLUE = 0x0000FF
    };

    Color color{};

    //max distance dictates the max size of the ray, lower is the initial
    std::pair<bool, float> Intersects(const Camera::Ray &ray, int lowerDistance, int maxDistance) const {
        //calculate the discriminate and see if it can even be square rooted
        float dDotP = dot(ray.direction, ray.origin - this->center);
        float discriminate = dDotP * dDotP - dot(ray.origin - this->center, ray.origin - this->center) + 1;
        if (discriminate < 0) {
            return {false, -1};
        }

        float smallestT = std::min(-dDotP + sqrt(discriminate), -dDotP - sqrt(discriminate));
        return {true, smallestT};
    }

    Sphere(int r, const Vector3 &c, Color co) : radius(r), center(c), color(co) {};

};

#endif //RAYTRACER_SPHERE_H