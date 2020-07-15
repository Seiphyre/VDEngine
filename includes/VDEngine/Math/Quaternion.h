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
// Compare convertioon results:
// https://www.andre-gaschler.com/rotationconverter/

#ifndef VDENGINE_QUATERNION_H_
#define VDENGINE_QUATERNION_H_

// Standard c++ libs
#include <iostream>
#include <iomanip>

// Internal headers
#include "VDEngine/Math/Core.hpp"
#include "VDEngine/Math/Vector3.h"
#include "VDEngine/Math/Vectors.hpp"

namespace VDEngine
{

class Quaternion
{

  public:
    float x;
    float y;
    float z;
    float w;

    /********************************************************
     *               -- Constructors --                     *
     ********************************************************/

    /**
     * @brief     Create `Quaternion(0, 0, 0, 1)`
     */
    Quaternion();

    /**
     * @brief     Create `Quaternion(x, y, z, w)`. The quaternion will be normalized.
     */
    Quaternion(float x, float y, float z, float w);

    /**
     * @brief     Copy Constructor
     */
    Quaternion(const Quaternion & q);

    // -- static constructors --

    /**
     * @brief         Create Quaternion from an axis-angle.
     * @param axis    Axis of the rotation (it doesn't need to be normalized).
     * @param angle   Angle of the rotation (in degrees).
     * @return        (normalized) Rotation.
     */
    static Quaternion CreateFromAxisAngle(const Vector3 & axis, const float & angle);

    /**
     * @brief         Create Quaternion from an euler angle.
     * @param euler   Euler angle (in degrees) (it doesn't need to be normalized).
     * @return        (normalized) Rotation.
     */
    static Quaternion CreateFromEuler(const Vector3 & euler);

    /**
     * @brief         Creates a rotation with the specified forward and upward directions.
     * @param forward Direction to look in (it will be normalized).
     * @param up      (optional) Vector that defines in which direction up is (it will be normalized).
     * @return        (normalized) Rotation.
     */
    static Quaternion LookRotation(const Vector3 & forward, const Vector3 & up = Vector3::VecUp());

    /**
     * @brief         Creates a rotation which rotates from `from` to `to`.
     * @param from    From direction (it will be normalized).
     * @param to      To direction (it will be normalized).
     * @return        (normalized) Rotation.
     */
    static Quaternion FromTo(const Vector3 & from, const Vector3 & to);

    /********************************************************
     *                  -- Setters --                       *
     ********************************************************/

    /**
     * @brief         Set `x`, `y`, `z` and `w` components of this quaternion. It will be normalized.
     */
    void Set(float x, float y, float z, float w);

    /**
     * @brief         Set this quaternion with an euler angle. It will be normalized.
     *                The rotation is performed around the Z axis, the X axis, and the the Y axis, in that order.
     * @param euler   Euler angle (in degrees) (it doesn't need to be normalized).
     */
    void SetEuler(const Vector3 & euler);

    /**
     * @brief         Set this quaternion with an axis-angle. The quaternion will be normalized.
     * @param axis    Axis of the rotation (it will be normalized).
     * @param angle   Angle of the rotation (in degrees).
     */
    void SetAngleAxis(const Vector3 & axis, float angle);

    /**
     * @brief     Normalize this quaternion.
     * @exception `if (vector.GetMagnitude == 0)` return Quaternion(0, 0, 0, 1).
     */
    void Normalize();

    /**
     * @brief     Inverse this quaternion.
     * @exception `if (Dot(vector, vector) == 0)` return Quaternion(0, 0, 0, 1).
     */
    void Inverse();

    /********************************************************
     *                  -- Getters --                       *
     ********************************************************/

    /**
     * @brief         Get the rotation as an euler angle.
     *                The rotation is performed around the Z axis, the X axis, and the the Y axis, in that order.
     * @return        Euler angle (in degrees) (range [0, 360]).
     * @exception     `if ( 90 <= euler.x <= 270 )` return wrong euler angle (singularity).
     */
    Vector3 GetEuler() const;

    /**
     * @brief         Get the rotation as an axis-angle (normalized).
     * @param axis    Axis of the rotation (normalized).
     * @param angle   Angle of the rotation (in degrees) (range [0,360]).
     */
    void GetAxisAngle(Vector3 & axis, float & angle) const;

    /**
     * @brief     Get the forward direction of the rotation (normalized).
     *            WRONG VALUE IF Quaternion(0,0,0,1)
     */
    Vector3 GetForward() const;

    /**
     * @brief     Get the right direction of the rotation (normalized).
     * WRONG VALUE IF Quaternion(0,0,0,1)
     */
    Vector3 GetRight() const;

    /**
     * @brief     Get the up direction of the rotation (normalized).
     * WRONG VALUE IF Quaternion(0,0,0,1)
     */
    Vector3 GetUp() const;

    /**
     * @brief     Get the magnitude (length) of this quaternion.
     */
    float GetMagnitude() const;

    /**
     * @brief     Get the square magnitude (length) of the quaternion.
     */
    float GetSqrMagnitude() const;

    /**
     * @brief     Get a normalized copy of this quaternion.
     *
     * @exception `if (quaternion.GetMagnitude == 0)` return Quaternion(0, 0, 0, 1).
     */
    Quaternion GetNormalized() const;

    /**
     * @brief      Return `true` if the quaternion is normalized, `false` if it's not.
     * @exception  `if (quaternion.GetMagnitude == 0)` return false.
     */
    bool IsNormalized() const;

    /**
     * @brief     Get an inversed copy of this quaternion.
     * @exception `if (Dot(vector, vector) == 0)` return Quaternion(0, 0, 0, 1).
     */
    Quaternion GetInversed() const;

    /********************************************************
     *              -- Static functions --                  *
     ********************************************************/

    /**
     * @brief     Get the dot product of `q1` and `q2`.
     */
    static float Dot(const Quaternion & q1, const Quaternion & q2);

    /********************************************************
     *                    -- TODO --                        *
     ********************************************************/

    // static Quaternion Lerp(const Quaternion & q1, const Quaternion & q2, float t);
    // static Quaternion Slerp(const Quaternion & q1, const Quaternion & q2, float t);

    // Slepni ?
    // Slep cubic ?

    /********************************************************
     *                 -- Operators --                      *
     ********************************************************/

    // -- unary minus operator --

    Quaternion operator-() const;

    // -- arithmetic operators --

    Quaternion operator+(const Quaternion & rhs) const;
    Quaternion operator-(const Quaternion & rhs) const;
    Quaternion operator*(const Quaternion & rhs) const; // Combine rotation between this quaternion and an other.

    Quaternion operator*(float rhs) const; // Scale this quaternion with a scalar.
    Quaternion operator/(float rhs) const; // Scale this quaternion with a scalar.

    // -- direct assignment operators --

    Quaternion operator=(const Quaternion & rhs);

    // -- compound assignment operators --

    Quaternion & operator+=(const Quaternion & rhs);
    Quaternion & operator-=(const Quaternion & rhs);
    Quaternion & operator*=(const Quaternion & rhs);

    Quaternion & operator*=(float rhs);
    Quaternion & operator/=(float rhs);

    // -- comparison operators --

    bool operator==(const Quaternion & rhs) const;
    bool operator!=(const Quaternion & rhs) const;

    // -- insertion operators --

    friend std::ostream & operator<<(std::ostream & os, const Quaternion & q);

  private:
    /**
     * @brief         Set this quaternion with an euler angle. It will be normalized.
     *                The rotation is performed around the Z axis, the X axis, and the the Y axis, in that order.
     * @param euler   Euler angle (in radians).
     */
    void SetEulerZXY(const Vector3 & euler);

    /**
     * @brief         Set this quaternion with an euler angle. It will be normalized.
     *                The rotation is performed around the X axis, the Y axis, and the the Z axis, in that order.
     * @param euler   Euler angle (in radians).
     */
    void SetEulerXYZ(const Vector3 & euler);

    /**
     * @brief         Get the rotation as an euler angle.
     *                The rotation is performed around the Z axis, the X axis, and the the Y axis, in that order.
     * @return        Euler angles (in degrees) (range [0, 360]).
     * @exception     `if ( 90 <= euler.x <= 270 )` return wrong euler angle (singularity).
     */
    Vector3 GetEulerZXY() const;

    /**
     * @brief         Get the rotation as an euler angle.
     *                The rotation is performed around the X axis, the Y axis, and the the Z axis, in that order.
     * @return        Euler angles (in degrees) (range [0, 360]).
     * @exception     `if ( 90 <= euler.y <= 270 )` return wrong euler angle (singularity).
     */
    Vector3 GetEulerXYZ() const;
};

Vector3 operator*(const Quaternion & q, const Vector3 & v); // Rotates a vector with this quaternion.

bool isnan(const Quaternion & quat);

} // namespace VDEngine

#endif /* VDENGINE_QUATERNION_H_ */