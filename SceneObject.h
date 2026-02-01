//
// Created by Daniel Elbaz on 1/31/26.
//

#ifndef RAYTRACER_SCENEOBJECT_H
#define RAYTRACER_SCENEOBJECT_H

#include "Vector3.h"
#include "Ray.h"
#include <cstdint>
#include <utility>

struct SceneObject {
    protected:
        Vector3 center{0,0,0};
        uint32_t color{};
        float diffuseCoefficient{1};
        float specularCoefficient{0.5f};

        SceneObject(const Vector3 &c, uint32_t co, float dif, float spec)
            : center(c), color(co), diffuseCoefficient(dif), specularCoefficient(spec) {};
};


struct Sphere : SceneObject {
    double radius{};

    //max distance dictates the max size of the ray, lower is the initial
    std::pair<bool, float> Intersects(const Ray &ray, int lowerDistance, int maxDistance) const {
        //calculate the discriminate and see if it can even be square rooted
        float dDotP = dot(ray.direction, ray.origin - this->center);
        float discriminate = dDotP * dDotP - dot(ray.origin - this->center, ray.origin - this->center) + (radius*radius);
        if (discriminate < 0) {
            return {false, -1};
        }

        float sqrtDisc = sqrt(discriminate);
        float smallestT = std::min(-dDotP + sqrtDisc, -dDotP - sqrtDisc);
        return {true, smallestT};
    }

    Sphere(double r, const Vector3 &c, uint32_t co, float dif, float spec) : SceneObject(c, co, dif, spec), radius(r) {};

};

struct Plane : SceneObject {
    Vector3 normalVector{0,1,0};
    float length{};
    float width{};

    std::pair<bool, float> Intersects(const Ray &ray, int lowerDistance, int maxDistance) const {
        //P is a possible point on the plane, P0 is a point already on the plane
        //formula = n dot (P0 - O) / n dot D
        //center is P0, origin of plane
        float numerator = dot(normalVector, center - ray.origin);
        float denominator = dot(normalVector, ray.direction);
        if (denominator == 0) {
            return {false, -1};
        }
        return {true, numerator/denominator};
    }

    Plane(const Vector3 &n, const Vector3 &c, uint32_t co, float dif, float spec, float length, float width)
        : SceneObject(c, co, dif, spec), normalVector(n), length(length), width(width) {};
};


#endif //RAYTRACER_SCENEOBJECT_H