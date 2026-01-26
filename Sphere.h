//
// Created by Daniel Elbaz on 1/23/26.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H
#pragma once
#include "Vector3.h"
#include "Ray.h"

struct Sphere {
    double radius;
    Vector3 center;

    uint32_t color{};

    //max distance dictates the max size of the ray, lower is the initial
    std::pair<bool, float> Intersects(const Ray &ray, int lowerDistance, int maxDistance) const {
        //calculate the discriminate and see if it can even be square rooted
        float dDotP = dot(ray.direction, ray.origin - this->center);
        float discriminate = dDotP * dDotP - dot(ray.origin - this->center, ray.origin - this->center) + (radius*radius);
        if (discriminate < 0) {
            return {false, -1};
        }

        float smallestT = std::min(-dDotP + sqrt(discriminate), -dDotP - sqrt(discriminate));
        return {true, smallestT};
    }

    Sphere(double r, const Vector3 &c, uint32_t co) : radius(r), center(c), color(co) {};

};

#endif //RAYTRACER_SPHERE_H