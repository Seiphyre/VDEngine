#ifndef VDENGINE_VECTOR2_H_
#define VDENGINE_VECTOR2_H_

// // External libs
// #include "glm/glm.hpp"

// Internal headers
#include "VDEngine/Math/Core.hpp"

namespace VDEngine
{

struct Vector2
{

  public:
    float x;
    float y;

    // -- constructors --

    Vector2();
    Vector2(float x, float y);

    // -- static constructors --

    static Vector2 CreateVecZero();
    static Vector2 CreateVecOne();

    static Vector2 CreateVecUp();
    static Vector2 CreateVecDown();
    static Vector2 CreateVecLeft();
    static Vector2 CreateVecRight();

    // -- convertion operators --

    // operator Vector4() const;
    // operator Vector3() const;

    // -- arithmetic operators --

    Vector2 operator+(const Vector2 & rhs) const;
    Vector2 operator-(const Vector2 & rhs) const;
    Vector2 operator*(float rhs) const;
    Vector2 operator/(float rhs) const;

    // -- comparison operators --

    bool operator==(const Vector2 & rhs) const;
    bool operator!=(const Vector2 & rhs) const;

    // -- glm compatibility --

    // glm::vec2 glm_vec2() const;
    // void      Set(const glm::vec2 & vec2);

    // -- Setters --

    void Set(float new_x, float new_y);

    void Scale(const Vector2 & scale);

    void Normalize();

    // -- Getters --

    float GetMagnitude() const;
    float GetSqrMagnitude() const;

    Vector2 GetNormalized() const;

    // -- Static functions --

    static float Distance(const Vector2 & vec_a, const Vector2 & vec_b);

    static float Dot(const Vector2 & lhs, const Vector2 & rhs);

    static float Angle(const Vector2 & from, const Vector2 & to);

    // -- TODO --

    // static Vector2 Reflect(Vector2 inDirection, Vector2 inNormal);

    // static Vector2 Lerp(Vector2 a, Vector2 b, float t);
    // static Vector2 LerpUnclamped(Vector2 a, Vector2 b, float t);
};

Vector2 operator*(float lhs, const Vector2 & rhs);
// Vector2 operator*(const Vector2 & vector, float scalar);
Vector2 operator/(float lhs, const Vector2 & rhs);
// Vector2 operator/(const Vector2 & vector, float scalar);

} // namespace VDEngine

#endif /* VDENGINE_VECTOR2_H_ */