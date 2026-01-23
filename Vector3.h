//
// Created by Daniel Elbaz on 1/23/26.
//

#ifndef RAYTRACER_VECTOR3_H
#define RAYTRACER_VECTOR3_H

struct Vector3 {
    float x, y, z;
};

inline Vector3 operator+(Vector3 a, Vector3 b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

inline Vector3 operator*(Vector3 a, float b) {
    return {a.x * b, a.y * b, a.z * b};
}

inline Vector3 operator*(float b, Vector3 a) {
    return {a.x * b, a.y * b, a.z * b};
}


#endif //RAYTRACER_VECTOR3_H