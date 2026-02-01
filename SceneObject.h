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
    Vector3 center{0,0,0};
    uint32_t color{};
    float diffuseCoefficient{1};
    float specularCoefficient{0.5f};

    SceneObject(const Vector3 &c, uint32_t co, float dif, float spec)
        : center(c), color(co), diffuseCoefficient(dif), specularCoefficient(spec) {};

    virtual ~SceneObject() = default;
    virtual std::pair<bool, float> Intersects(const Ray& ray, float lowerDistance, float maxDistance) const = 0;
};


struct Sphere : SceneObject {
    double radius{};

    //max distance dictates the max size of the ray, lower is the initial
    std::pair<bool, float> Intersects(const Ray &ray, float lowerDistance, float maxDistance) const {
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
    Vector3 rightVector{1,0,0};
    Vector3 upVector{0,0,1};

    float length{};
    float width{};

    std::pair<bool, float> Intersects(const Ray &ray, float lowerDistance, float maxDistance) const {
        //P is a possible point on the plane, P0 is a point already on the plane
        //formula = n dot (P0 - O) / n dot D
        //center is P0, origin of plane


        float numerator = dot(normalVector, center - ray.origin);
        float denominator = dot(normalVector, ray.direction);
        if (denominator == 0) {
            return {false, -1};
        }

        float t = numerator/denominator;
        return {true, t};
    }

    Plane(const Vector3 &n, const Vector3 &c, uint32_t co, float dif, float spec, float length, float width)
        : SceneObject(c, co, dif, spec), normalVector(normalize(n)), length(length), width(width) {

        //0.99f is arbitrary, just means we aren't close to vertical. just checking to make sure it is less than 1
        Vector3 randomNonOrtho = (std::abs(normalVector.y) < 0.99f) ? Vector3{0, 1, 0} : Vector3{1, 0, 0};
        //cross of random non ortho will lie on plane, cross of that and normal will also lie on plane
        rightVector = normalize(cross(normalVector, randomNonOrtho));
        upVector = normalize(cross(normalVector, rightVector));
    };
};


#endif //RAYTRACER_SCENEOBJECT_H