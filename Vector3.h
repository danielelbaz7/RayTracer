#ifndef RAYTRACER_VECTOR3_H
#define RAYTRACER_VECTOR3_H

struct Vector3 {
    float x{}, y{}, z{};
};

inline Vector3 operator+(const Vector3& a, const Vector3& b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

inline Vector3 operator-(const Vector3& a) {
    return {-a.x, -a.y, -a.z};
}

inline Vector3 operator-(const Vector3& a, const Vector3& b) {
    return {a.x-b.x, a.y-b.y, a.z-b.z};
}

inline Vector3 operator*(const Vector3& a, float b) {
    return {a.x * b, a.y * b, a.z * b};
}

inline Vector3 operator*(float b, const Vector3& a) {
    return {a.x * b, a.y * b, a.z * b};
}

inline Vector3 operator/(const Vector3& a, float b) {
    return {a.x / b, a.y / b, a.z / b};
}

inline float dot(const Vector3& a, const Vector3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vector3 cross(const Vector3& a, const Vector3& b) {
    return Vector3{
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

inline Vector3 normalize(const Vector3& a) {
    float magnitude = std::sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
    return a / magnitude;
}

#endif // RAYTRACER_VECTOR3_H
