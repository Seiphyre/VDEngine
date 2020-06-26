#ifndef VDENGINE_VECTOR4_H_
#define VDENGINE_VECTOR4_H_

// // External libs
// #include "glm/glm.hpp"

// Internal headers
#include "VDEngine/Math/Core.hpp"

namespace VDEngine
{

struct Vector4
{

  public:
    float x;
    float y;
    float z;
    float w;

    // -- constructors --

    Vector4();
    Vector4(float x, float y, float z, float w);

    // -- static constructors --

    static Vector4 CreateVecZero();
    static Vector4 CreateVecOne();

    // -- convertion operators --

    // operator Vector3() const;
    // operator Vector2() const;

    // -- arithmetic operators --

    Vector4 operator+(const Vector4 & rhs) const;
    Vector4 operator-(const Vector4 & rhs) const;
    Vector4 operator*(float rhs) const;
    Vector4 operator/(float rhs) const;

    // -- comparison operators --

    bool operator==(const Vector4 & rhs) const;
    bool operator!=(const Vector4 & rhs) const;

    // -- glm compatibility --

    // glm::vec4 glm_vec4() const;
    // void      Set(const glm::vec4 & vec4);

    // -- Setters --

    void Set(float new_x, float new_y, float new_z, float new_w);

    void Scale(const Vector4 & scale);

    void Normalize();

    // -- Getters --

    Vector4 GetNormalized() const;

    float GetMagnitude() const;
    float GetSqrMagnitude() const;

    // -- Static functions --

    static float Dot(const Vector4 & lhs, const Vector4 & rhs);

    static float Distance(const Vector4 & vec_a, const Vector4 & vec_b);

    // -- TODO --

    // static Vector4 Lerp(Vector4 a, Vector4 b, float t);
    // static Vector4 LerpUnclamped(Vector4 a, Vector4 b, float t);

    // static Vector4 Project(Vector4 a, Vector4 b);
};

Vector4 operator*(float lhs, const Vector4 & rhs);
// Vector4 operator*(const Vector4 & lhs, float rhs);
Vector4 operator/(float lhs, const Vector4 & rhs);
// Vector4 operator/(const Vector4 & lhs, float rhs);

} // namespace VDEngine

#endif /* VDENGINE_VECTOR4_H_ */