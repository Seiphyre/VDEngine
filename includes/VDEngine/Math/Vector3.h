#ifndef VDENGINE_VECTOR3_H_
#define VDENGINE_VECTOR3_H_

// Standard c++ libs
#include <iostream>
#include <iomanip>

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

    /********************************************************
     *               -- Constructors --                     *
     ********************************************************/

    /**
     * @brief     Create `Vector3(0, 0, 0)`
     */
    Vector3();

    /**
     * @brief     Create `Vector3(x, y, z)`
     */
    Vector3(float x, float y, float z);

    // -- static constructors --

    /**
     * @brief     Return `Vector3(0, 0, 0)`.
     */
    static Vector3 VecZero();

    /**
     * @brief     Return `Vector3(1, 1, 1)`.
     */
    static Vector3 VecOne();

    /**
     * @brief     Return `Vector3(0, 0, 1)`.
     */
    static Vector3 VecPosZ();

    /**
     * @brief     Return `Vector3(0, 0, -1)`.
     */
    static Vector3 VecBack();

    /**
     * @brief     Return `Vector3(0, 1, 0)`.
     */
    static Vector3 VecPosY();

    /**
     * @brief     Return `Vector3(0, -1, 0)`.
     */
    static Vector3 VecDown();

    /**
     * @brief     Return `Vector3(-1, 0, 0)`.
     */
    static Vector3 VecLeft();

    /**
     * @brief     Return `Vector3(1, 0, 0)`.
     */
    static Vector3 VecPosX();

    /**
     * @brief     Return `Vector3(NAN_FLOAT, NAN_FLOAT, NAN_FLOAT)`. It can be used to handle vectors math errors.
     */
    static Vector3 VecNan();

    /********************************************************
     *                 -- Operators --                      *
     ********************************************************/

    // -- unary minus operator --

    Vector3 operator-() const;

    // -- arithmetic operators --

    Vector3 operator+(const Vector3 & rhs) const;
    Vector3 operator-(const Vector3 & rhs) const;
    Vector3 operator*(const Vector3 & rhs) const; // scale the vector
    Vector3 operator*(float rhs) const;
    Vector3 operator/(float rhs) const;

    // -- compound assignment --

    Vector3 & operator+=(const Vector3 & rhs);
    Vector3 & operator-=(const Vector3 & rhs);
    Vector3 & operator*=(float rhs);
    Vector3 & operator/=(float rhs);

    // -- comparison operators --

    bool operator==(const Vector3 & rhs) const;
    bool operator!=(const Vector3 & rhs) const;

    // -- member access, subscrip operators --

    float &       operator[](int index);
    const float & operator[](int index) const;

    // -- insertion operators --

    friend std::ostream & operator<<(std::ostream & os, const Vector3 & v);

    /********************************************************
     *                  -- Setters --                       *
     ********************************************************/

    /**
     * @brief     Set `x`, `y` and `z` components of this vector.
     */
    void Set(float x, float y, float z);

    /**
     * @brief     Multiplies this vector by `v1` component-wise.
     */
    void Scale(const Vector3 & v1);

    /**
     * @brief     Normalize this vector.
     *
     * @exception `if (vector.GetMagnitude == 0)` return Vector3(0, 0, 0).
     */
    void Normalize();

    /********************************************************
     *                  -- Getters --                       *
     ********************************************************/

    /**
     * @brief     Get the magnitude (length) of the vector.
     */
    float GetMagnitude() const;

    /**
     * @brief     Get the square magnitude (length) of the vector.
     */
    float GetSqrMagnitude() const;

    /**
     * @brief     Get a normalized copy of this vector.
     *
     * @exception `if (vector.GetMagnitude == 0)` return Vector3(0, 0, 0).
     */
    Vector3 GetNormalized() const;

    /**
     * @brief      Return `true` if the vector is normalized, `false` if it's not.
     * @exception  `if (vector.GetMagnitude == 0)` return false.
     */
    bool IsNormalized() const;

    /********************************************************
     *              -- Static functions --                  *
     ********************************************************/

    /**
     * @brief     Get the distance between `v1` and `v2`.
     */
    static float Distance(const Vector3 & v1, const Vector3 & v2);

    /**
     * @brief     Get the cross product of `v1` and `v2`.
     */
    static Vector3 Cross(const Vector3 & v1, const Vector3 & v2);

    /**
     * @brief     Get the dot product of `v1` and `v2`.
     */
    static float Dot(const Vector3 & v1, const Vector3 & v2);

    /**
     * @brief       Get the angle between `from` and `to`.
     *
     * @param from  (doesn't need to be normalized).
     * @param to    (doesn't need to be normalized).
     *
     * @return      Angle (in degrees).
     *
     * @exception   `if (from.GetMagnitude == 0)` return 0.
     * @exception   `if (to.GetMagnitude == 0)` return 0.
     */
    static float Angle(const Vector3 & from, const Vector3 & to);

    /**
     * @brief       Linear interpolation between `v1` and `v2` by the interpolant `t`.
     *
     * @param v1    a vector.
     * @param v2    a vector.
     * @param t     interpolation factor (it will be clamped to the range [0, 1]).
     */
    static Vector3 Lerp(const Vector3 & v1, const Vector3 & v2, float t);

    /********************************************************
     *                    -- TODO --                        *
     ********************************************************/

    // static Vector3 Reflect(const Vector3 & in_direction, const Vector3 & in_normal);

    // static Vector3 ProjectOnVector(const Vector3 & v1, const Vector3 & v2);
    // static Vector3 ProjectOnPlane(const Vector3 & vector, const Vector3 & plane_normal);

    // static Vector3 Slerp(const Vector3 & v1, const Vector3 & v2, float t);

    // static void OrthoNormalize(Vector3 & v1, Vector3 & v2);
    // static void OrthoNormalize(Vector3 & v1, Vector3 & v2, Vector3 & v3);
};

Vector3 operator*(float lhs, const Vector3 & rhs);
Vector3 operator/(float lhs, const Vector3 & rhs);

bool isnan(const Vector3 & vec);

} // namespace VDEngine

#endif /* VDENGINE_VECTOR3_H_ */