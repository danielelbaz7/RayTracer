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
    int shininess{100};

    SceneObject(const Vector3 &c, uint32_t co, float dif, float spec, int shiny)
        : center(c), color(co), diffuseCoefficient(dif), specularCoefficient(spec), shininess(shiny) {};

    virtual ~SceneObject() = default;
    virtual std::pair<bool, float> Intersects(const Ray& ray, float lowerDistance, float maxDistance) const = 0;
};


struct Sphere : SceneObject {
    double radius{};

    //max distance dictates the max size of the ray, lower is the initial
    std::pair<bool, float> Intersects(const Ray &ray, float lowerDistance, float maxDistance) const {
        //calculate the discriminate and see if it can even be square rooted
        float dDotP = dot(ray.direction, ray.origin - this->center);
        float discriminant = dDotP * dDotP - dot(ray.origin - this->center, ray.origin - this->center) + (radius*radius);
        if (discriminant < 0) {
            return {false, -1};
        }

        float sqrtDisc = sqrt(discriminant);
        float smallestT = std::min(-dDotP + sqrtDisc, -dDotP - sqrtDisc);
        return {true, smallestT};
    }

    Sphere(double r, const Vector3 &c, uint32_t co, float dif, float spec, int shiny) : SceneObject(c, co, dif, spec, shiny), radius(r) {};

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
        Vector3 pointOnPlane = {ray.origin + t * ray.direction};

        if (abs(dot(pointOnPlane-center, upVector)) > length
            || abs(dot(pointOnPlane-center, rightVector)) > width) {
            return {false, -1};
        }

        return {true, t};
    }

    Plane(const Vector3 &n, const Vector3 &c, uint32_t co, float dif, float spec, float length, float width, int shiny)
        : SceneObject(c, co, dif, spec, shiny), normalVector(normalize(n)), length(length), width(width) {

        //0.99f is arbitrary, just means we aren't close to vertical. just checking to make sure it is less than 1
        Vector3 randomNonOrtho = (std::abs(normalVector.y) < 0.99f) ? Vector3{0, 1, 0} : Vector3{1, 0, 0};
        //cross of random non ortho will lie on plane, cross of that and normal will also lie on plane
        rightVector = normalize(cross(normalVector, randomNonOrtho));
        upVector = normalize(cross(normalVector, rightVector));
    };
};


#endif //RAYTRACER_SCENEOBJECT_H