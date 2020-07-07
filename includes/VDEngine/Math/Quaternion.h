//
// -- Some useful links --
//
// [Hands-On] [C++ Game Animation Programming] Learn modern animation techniques from theory to implementation with C++
// and OpenGL
// (P.75)
// https://gabormakesgames.com/quaternions.html
//
// SINGULARITE HANDLE :  Matrix4::GetAngle()
//
// Game engine exemple:
// https://github.com/mrdoob/three.js/blob/dev/src/math/Quaternion.js
// https://github.com/godotengine/godot/blob/master/core/math/quat.h
// https://github.com/ehsan/ogre/blob/master/OgreMain/src/OgreQuaternion.cpp
// http://irrlicht.sourceforge.net/docu/classirr_1_1core_1_1quaternion.html
//
// Euler -> Quaternion:
// (seq: all)
//            https://www.mathworks.com/matlabcentral/fileexchange/20696-function-to-convert-between-dcm-euler-angles-quaternions-and-euler-vectors
// (seq: all) https://ntrs.nasa.gov/archive/nasa/casi.ntrs.nasa.gov/19770024290.pdf
// (seq: YZX) https://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToQuaternion/index.htm
//
// Quaternion -> Euler:
// (seq: all)
//            https://www.mathworks.com/matlabcentral/fileexchange/20696-function-to-convert-between-dcm-euler-angles-quaternions-and-euler-vectors
// (seq: YZX) https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/index.htm
// (seq: all) http://bediyap.com/programming/convert-quaternion-to-euler-rotations/
//

#ifndef VDENGINE_QUATERNION_H_
#define VDENGINE_QUATERNION_H_

#include <iostream>

#include "VDEngine/Math/Core.hpp"
#include "VDEngine/Math/Vector3.h"

namespace VDEngine
{

class Quaternion
{

  public:
    float x;
    float y;
    float z;
    float w;

    // -- Constructors --

    Quaternion();
    Quaternion(float p_x, float p_y, float p_z, float p_w);
    Quaternion(const Vector3 & axis, const float & angle);
    Quaternion(const Vector3 & euler);
    Quaternion(const Quaternion & q);

    // -- static constructors

    static Quaternion CreateFromAngleAxis(const Vector3 & axis, const float & angle);

    static Quaternion LookRotation(const Vector3 & forward, const Vector3 & up = Vector3::CreateVecUp());
    static Quaternion FromTo(const Vector3 & from, const Vector3 & to);

    // -- Setters --

    void Set(float p_x, float p_y, float p_z, float p_w);

    void SetEuler(const Vector3 & p_euler);
    void SetEulerZXY(const Vector3 & p_euler);
    void SetEulerXYZ(const Vector3 & p_euler);

    void SetAngleAxis(const Vector3 & axis, float angle);

    // -- Getters --

    Vector3 GetEuler() const;
    Vector3 GetEulerZXY() const;
    Vector3 GetEulerXYZ() const;

    void GetAngleAxis(Vector3 & r_axis, float & r_angle) const;

    // Vector3 GetForward() const
    // {
    //     return Vector3::CreateVecForward() * (*this);
    // }

    // Vector3 GetRight() const
    // {
    //     return Vector3::CreateVecRight() * (*this);
    // }

    // Vector3 GetUp() const
    // {
    //     return Vector3::CreateVecUp() * (*this);
    // }

    // -- Functions --

    void Normalize();

    Quaternion GetNormalized() const;
    bool       IsNormalized() const;

    float GetMagnitude() const;

    // inline Quaternion inverse() const;
    // inline float dot(const Quaternion & q) const;

    // Quaternion slerp(const Quaternion & q, float t) const;
    // Quaternion slerpni(const Quaternion & q, float t) const;
    // Quaternion cubic_slerp(const Quaternion & q, const Quaternion & prep, const Quaternion & postq, float t) const;

    // -- operators --

    inline void operator+=(const Quaternion & rhs);
    inline void operator-=(const Quaternion & rhs);
    inline void operator*=(float rhs);
    void        operator*=(const Quaternion & rhs);
    inline void operator/=(float rhs);

    // -- operators --

    inline Quaternion operator+(const Quaternion & rhs) const;
    inline Quaternion operator-(const Quaternion & rhs) const;
    inline Quaternion operator*(float rhs) const;
    Quaternion        operator*(const Quaternion & rhs) const;
    // Quaternion        operator*(const Vector3 & rhs) const;
    inline Quaternion operator/(float rhs) const;

    // -- operators --

    inline Quaternion operator-() const;

    // -- operators --

    inline bool operator==(const Quaternion & p_quat) const;
    inline bool operator!=(const Quaternion & p_quat) const;

    // -- operators --

    Quaternion operator=(const Quaternion & q);
};

Vector3 operator*(const Vector3 & v, const Quaternion & q);

} // namespace VDEngine

#endif /* VDENGINE_QUATERNION_H_ */