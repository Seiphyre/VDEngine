#ifndef VDENGINE_VECTOR3_H_
#define VDENGINE_VECTOR3_H_

// // External libs
// #include "glm/glm.hpp"

// Internal headers
#include "VDEngine/Math/Core.hpp"

namespace VDEngine
{

struct Vector3
{

  public:
    float x;
    float y;
    float z;

    // -- constructors --

    Vector3();
    Vector3(float x, float y, float z);

    // -- static constructors --

    static Vector3 CreateVecZero();
    static Vector3 CreateVecOne();

    static Vector3 CreateVecForward();
    static Vector3 CreateVecBack();
    static Vector3 CreateVecUp();
    static Vector3 CreateVecDown();
    static Vector3 CreateVecLeft();
    static Vector3 CreateVecRight();

    // -- convertion operators --

    // operator Vector4() const;
    // operator Vector2() const;

    // -- arithmetic operators --

    Vector3 operator+(const Vector3 & rhs) const;
    Vector3 operator-(const Vector3 & rhs) const;
    Vector3 operator*(float rhs) const;
    Vector3 operator/(float rhs) const;

    // -- comparison operators --

    bool operator==(const Vector3 & rhs) const;
    bool operator!=(const Vector3 & rhs) const;

    // -- glm compatibility --

    // glm::vec3 glm_vec3() const;
    // void      Set(const glm::vec3 & vec3);

    // -- Setters --

    void Set(float new_x, float new_y, float new_z);

    void Scale(const Vector3 & scale);

    void Normalize();

    // -- Getters --

    float GetMagnitude() const;
    float GetSqrMagnitude() const;

    Vector3 GetNormalized() const;

    // -- Static functions --

    static float Distance(const Vector3 & vec_a, const Vector3 & vec_b);

    static Vector3 Cross(const Vector3 & lhs, const Vector3 & rhs);

    static float Dot(const Vector3 & lhs, const Vector3 & rhs);

    static float Angle(const Vector3 & from, const Vector3 & to);

    // -- TODO --

    // static Vector3 Reflect(Vector3 inDirection, Vector3 inNormal);

    // static Vector3 Project(Vector3 vector, Vector3 onNormal);
    // static Vector3 ProjectOnPlane(Vector3 vector, Vector3 planeNormal);

    // static Vector3 Lerp(Vector3 a, Vector3 b, float t);
    // static Vector3 LerpUnclamped(Vector3 a, Vector3 b, float t);
    // static Vector3 Slerp(Vector3 a, Vector3 b, float t);
    // static Vector3 SlerpUnclamped(Vector3 a, Vector3 b, float t);

    // static void OrthoNormalize(Vector3 & normal, Vector3 & tangent);
    // static void OrthoNormalize(Vector3 & normal, Vector3 & tangent, Vector3 & binormal);
};

Vector3 operator*(float lhs, const Vector3 & rhs);
// Vector3 operator*(const Vector3 & vector, float scalar);
Vector3 operator/(float lhs, const Vector3 & rhs);
// Vector3 operator/(const Vector3 & vector, float scalar);

} // namespace VDEngine

#endif /* VDENGINE_VECTOR3_H_ */