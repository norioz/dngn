#pragma once

#include <math.h>
#include "Scalar.h"

// ---------
// Vector
// ----------
// convert to a float pointer (implicit conversion?) -- doc this
// scalar projection - (dot product, maybe don't call it this)
//cross product     `
//projection   `
//deproject -- vector rejection `
//reflect   `
//lerp      `
//min / max   `
//clamp     `
//snap      `

union Vector2 {
    struct { float x, y; };
    float v[2];
    const float & operator[] (size_t idx) const { return v[idx]; }
    float & operator[] (size_t idx) { return v[idx]; }
    Vector2 & operator= (Vector2 & other);
    Vector2 operator- ();
    Vector2 & operator+= (const Vector2 & other);
    Vector2 & operator-= (const Vector2 & other);
    Vector2 & operator/= (float scalar);
    Vector2 & operator*= (float scalar);
};

inline Vector2 & Vector2::operator= (Vector2 & other) {
    x = other.x;
    y = other.y;
    return *this;
}

inline Vector2 Vector2::operator-() {
    Vector2 v;
    v.x = -x;
    v.y = -y;
    return v;
}

inline Vector2 & Vector2::operator+= (const Vector2 & other) {
    x += other.x;
    y += other.y;
    return *this;
}

inline Vector2 & Vector2::operator-= (const Vector2 & other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

inline Vector2 & Vector2::operator*= (float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

inline Vector2 & Vector2::operator/= (float scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

inline Vector2 operator+ (Vector2 a, Vector2 b) {
    Vector2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

inline Vector2 operator- (Vector2 a, Vector2 b) {
    Vector2 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

inline Vector2 operator* (Vector2 v, float f) {
    Vector2 result;
    result.x = v.x * f;
    result.y = v.y * f;
    return result;
}

inline Vector2 operator* (float f, Vector2 v) {
    Vector2 result;
    result.x = v.x * f;
    result.y = v.y * f;
    return result;
}

inline Vector2 operator/ (Vector2 v, float f) {
    Vector2 result;
    result.x = v.x / f;
    result.y = v.y / f;
    return result;
}

inline bool operator== (Vector2 a, Vector2 & b) {
    return Scalar(a.x) == Scalar(b.x) && Scalar(a.y) == Scalar(b.y);
}

inline bool operator!= (Vector2 & a, Vector2 & b) {
    return !(a == b);
}

inline float magnitude (Vector2 & v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

inline Vector2 normalize (Vector2 & v) {
    Scalar m = magnitude(v);
    if (m == Scalar{ 0 }) {
        return Vector2{ 0, 0 };
    }
    return Vector2{ v.x / m, v.y / m };
}

inline float distSq (Vector2 & a, Vector2 & b) {
    float dx = a.x - b.x, dy = a.y - b.y;
    return (dx * dx + dy * dy);
}

inline float dist (Vector2 & a, Vector2 & b) {
    return sqrt(distSq(a, b));
}

// ----------

union Vector3 {
    struct { float x, y, z; };
    const float & operator[] (size_t idx) const { }
    float & operator[] (size_t idx) { }
    Vector3 & operator+= (const Vector3 & other);
    Vector3 & operator-= (const Vector3 & other);
    Vector3 & operator/= (float scalar);
    Vector3 & operator*= (float scalar);
};

inline Vector3 & Vector3::operator+= (const Vector3 & other) {
    // UNIMPLEMENTED
    return *this;
}

inline Vector3 & Vector3::operator-= (const Vector3 & other) {
    // UNIMPLEMENTED
    return *this;
}

inline Vector3 & Vector3::operator*= (float scalar) {
    // UNIMPLEMENTED
    return *this;
}

inline Vector3 & Vector3::operator/= (float scalar) {
    // UNIMPLEMENTED
    return *this;
}
