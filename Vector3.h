//
// Created by Daniel Elbaz on 1/23/26.
//

#ifndef RAYTRACER_VECTOR3_H
#define RAYTRACER_VECTOR3_H

struct Vector3 {
    float x, y, z;
};

inline Vec3 operator+(Vec3 a, Vec3 b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

#endif //RAYTRACER_VECTOR3_H