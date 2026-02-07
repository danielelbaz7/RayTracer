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

    SceneObject(const Vector3 &center, uint32_t color, float dif, float spec, int shiny)
        : center(center), color(color), diffuseCoefficient(dif), specularCoefficient(spec), shininess(shiny) {};

    virtual ~SceneObject() = default;
    virtual std::pair<bool, float> Intersects(const Ray& ray, float lowerDistance, float maxDistance) const = 0;
    virtual Vector3 GetNormal(const Vector3 &point) const = 0;
};


struct Sphere : SceneObject {
    double radius{};

    //max distance dictates the max size of the ray, lower is the initial
    std::pair<bool, float> Intersects(const Ray &ray, float lowerDistance, float maxDistance) const override {
        //calculate the discriminate and see if it can even be square rooted
        float dDotP = dot(ray.direction, ray.origin - this->center);
        float discriminant = dDotP * dDotP - dot(ray.origin - this->center, ray.origin - this->center) + (radius*radius);
        if (discriminant < 0) {
            return {false, -1};
        }

        float sqrtDisc = sqrt(discriminant);
        float t1 = -dDotP - sqrtDisc;
        float t2 = -dDotP + sqrtDisc;

        if (t1 >= lowerDistance && t1 <= maxDistance) {
            return {true, t1};
        }
        if (t2 >= lowerDistance && t2 <= maxDistance) {
            return {true, t2};
        }
        return {false, -1};
    }

    Vector3 GetNormal(const Vector3 &point) const override {
        return point - this->center;
    }

    Sphere(double r, const Vector3 &c, uint32_t co, float dif, float spec, int shiny) : SceneObject(c, co, dif, spec, shiny), radius(r) {};

};

struct Plane : SceneObject {
    Vector3 normalVector{0,0,1};
    Vector3 rightVector{1,0,0};
    Vector3 upVector{0,1,0};

    float length{};
    float width{};

    std::pair<bool, float> Intersects(const Ray &ray, float lowerDistance, float maxDistance) const override {
        //P is a possible point on the plane, P0 is a point already on the plane
        //formula = n dot (P0 - O) / n dot D
        //center is P0, origin of plane

        float numerator = dot(normalVector, center - ray.origin);
        float denominator = dot(normalVector, ray.direction);
        if (denominator == 0) {
            return {false, -1};
        }

        float t = numerator/denominator;
        if (t < lowerDistance || t > maxDistance) {
            return {false, -1};
        }

        Vector3 pointOnPlane = {ray.origin + t * ray.direction};

        if (abs(dot(pointOnPlane-center, upVector)) > length
            || abs(dot(pointOnPlane-center, rightVector)) > width) {
            return {false, -1};
        }

        return {true, t};
    }

    Vector3 GetNormal(const Vector3 &point) const override {
        return normalVector;
    }

    Plane(const Vector3 &c, const Vector3 &n, float length, float width, uint32_t co, float dif, float spec, int shiny)
        : SceneObject(c, co, dif, spec, shiny), normalVector(normalize(n)), length(length), width(width) {

        //0.99f is arbitrary, just means we aren't close to vertical. just checking to make sure it is less than 1
        Vector3 randomNonOrtho = (std::abs(normalVector.z) < 0.99f) ? Vector3{0, 0, 1} : Vector3{1, 0, 0};
        //cross of random non ortho will lie on plane, cross of that and normal will also lie on plane
        rightVector = normalize(cross(normalVector, randomNonOrtho));
        upVector = normalize(cross(normalVector, rightVector));
    };
};


#endif //RAYTRACER_SCENEOBJECT_H