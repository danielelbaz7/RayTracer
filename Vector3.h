#ifndef RAYTRACER_VECTOR3_H
#define RAYTRACER_VECTOR3_H

struct Vector3 {
    float x{}, y{}, z{};

    Vector3& operator+=(const Vector3& rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }
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

inline Vector3 operator*(const float b, const Vector3& a) {
    return {a.x * b, a.y * b, a.z * b};
}

inline Vector3 operator/(const Vector3& a, const float b) {
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

inline float length(const Vector3 &a) {
    return std::sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
};

inline Vector3 rotate(const Vector3 &vec, float angle) {

}

#endif // RAYTRACER_VECTOR3_H
