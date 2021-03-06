#pragma once
#include <math.h>
#include "Scalar.h"

union Vector3 {
    struct { float x, y, z; };
    float v[3];
    const float & operator[] (size_t idx) const { return v[idx]; }
    float & operator[] (size_t idx) { return v[idx]; }
    Vector3 & operator= (const Vector3 & other);
    Vector3 & operator+= (const Vector3 & other);
    Vector3 & operator-= (const Vector3 & other);
    Vector3 & operator/= (float scalar);
    Vector3 & operator*= (float scalar);
    Vector3 operator- ();
};

inline Vector3 Vector3::operator-() {
    return Vector3{ -x, -y, -z };
}

inline Vector3 & Vector3::operator= (const Vector3 & other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

inline Vector3 & Vector3::operator+= (const Vector3 & other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

inline Vector3 & Vector3::operator-= (const Vector3 & other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

inline Vector3 & Vector3::operator*= (float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

inline Vector3 & Vector3::operator/= (float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

inline Vector3 operator+ (Vector3 a, Vector3 b) {
    return Vector3{ a.x + b.x, a.y + b.y, a.z + b.z };
}

inline Vector3 operator- (Vector3 a, Vector3 b) {
    return Vector3{ a.x - b.x, a.y - b.y, a.z - b.z };
}

inline Vector3 operator* (Vector3 v, float f) {
    return Vector3{ v.x * f, v.y * f, v.z * f };
}

inline Vector3 operator* (float f, Vector3 v) {
    return v * f;
}

inline Vector3 operator/ (Vector3 v, float f) {
    return Vector3{ v.x / f, v.y / f, v.z / f };
}

inline bool operator== (Vector3 a, Vector3 & b) {
    return eq(a.x, b.x) && eq(a.y, b.y) && eq(a.z, b.z);
}

inline bool operator!= (Vector3 & a, Vector3 & b) {
    return !(a == b);
}

// magnitude
inline float magnitudeSq (Vector3 & v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

inline float magnitude (Vector3 & v) {
    return sqrtf(magnitudeSq(v));
}

// normalize
inline Vector3 normalize (Vector3 & v) {
    Scalar m = magnitude(v);
    if (m == Scalar{ 0 }) {
        return Vector3{ 0, 0, 0 };
    }
    return v / m;
}

// distance
inline float distSq (Vector3 & a, Vector3 & b) {
    float dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return dx * dx + dy * dy + dz * dz;
}

inline float dist (Vector3 & a, Vector3 & b) {
    return sqrtf(distSq(a, b));
}

//min
Vector3 min (Vector3 & a, Vector3 & b) {
    return Vector3{ min(a.x, b.x), min(a.y, b.y), min(a.z, b.z) };
}

template<typename... Args>
Vector3 min (Vector3 & a, Vector3 & b, Args... args) {
    return min(min(a, b), args...);
}

// max
Vector3 max (Vector3 & a, Vector3 & b) {
    return Vector3{ max(a.x, b.x), max(a.y, b.y), max(a.z, b.z) };
}

template<typename... Args>
Vector3 max (Vector3 & a, Vector3 b, Args... args) {
    return max(max(a, b), args...);
}

// Scalar product - dot product
float sprod (Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 cross (Vector3 a, Vector3 b) {
    return Vector3{
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

// projection
// project a onto b
Vector3 project (Vector3 & a, Vector3 & b) {
    float bb = sprod(b, b);
    if (eq(bb, 0.f)) {
        return Vector3{ 0, 0, 0 };
    }
    return (sprod(a, b) / bb) * b;
}

// deprojection -- vector rejection
// deproject a onto b
Vector3 deproject (Vector3 & a, Vector3 & b) {
    Vector3 p = project(a, b);
    return a - p;
}

//reflect
// n := normal vector
// i := incident vector
// Credit: HLSL documentation; GLSL spec documentation
Vector3 reflect (Vector3 & i, Vector3 & n) {
    return i - 2.f * sprod(i, n) * n;
}

// refract
// o := incident
// n := normal
// eta := refraction index
Vector3 refract (Vector3 & i, Vector3 & n, float eta) {
    float nDotI = sprod(n, i);
    float k = 1.f - eta * eta * (1.f - nDotI * nDotI);
    if (k < 0.f) {
        return Vector3{ 0, 0, 0 };
    }
    return eta * i - (eta * nDotI + sqrtf(k)) * n;
}

//clampM
// Constrains the magnitude of the vector to less than or
// equal to the passed in magnitude (maxLength).
Vector3 clamp (Vector3 & v, float maxLength) {
    // UNIMPLEMENTED
    return Vector3{};
}

//snap

//lerp
// Spherically interpolates between two vectors.
// Interpolates between a and b by amount t.
// The direction of the returned vector is interpolated by the angle
// and its magnitude is the interpolation beteen the magnitudes of a
// and b.

