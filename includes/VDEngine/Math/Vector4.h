#ifndef VDENGINE_VECTOR4_H_
#define VDENGINE_VECTOR4_H_

// Standard c++ libs
#include <iostream>
#include <iomanip>

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

    /********************************************************
     *               -- Constructors --                     *
     ********************************************************/

    /**
     * @brief     Create `Vector4(0, 0, 0, 0)`
     */
    Vector4();

    /**
     * @brief     Create `Vector4(x, y, z, w)`
     */
    Vector4(float x, float y, float z, float w);

    // -- static constructors --

    /**
     * @brief     Return `Vector4(1, 1, 1, 1)`
     */
    static Vector4 VecZero();

    /**
     * @brief     Return `Vector4(0, 0, 0, 0)`
     */
    static Vector4 VecOne();

    /**
     * @brief     Return `Vector4(NAN_FLOAT, NAN_FLOAT, NAN_FLOAT, NAN_FLOAT)`. It can be used to handle vectors math
     * errors.
     */
    static Vector4 VecNan();

    /********************************************************
     *                 -- Operators --                      *
     ********************************************************/

    // -- unary minus operator --

    Vector4 operator-() const;

    // -- arithmetic operators --

    Vector4 operator+(const Vector4 & rhs) const;
    Vector4 operator-(const Vector4 & rhs) const;
    Vector4 operator*(const Vector4 & rhs) const;
    Vector4 operator*(float rhs) const;
    Vector4 operator/(float rhs) const;

    // -- compound assignment --

    Vector4 & operator+=(const Vector4 & rhs);
    Vector4 & operator-=(const Vector4 & rhs);
    Vector4 & operator*=(float rhs);
    Vector4 & operator/=(float rhs);

    // -- comparison operators --

    bool operator==(const Vector4 & rhs) const;
    bool operator!=(const Vector4 & rhs) const;

    // -- member access, subscrip operators --

    float &       operator[](int index);
    const float & operator[](int index) const;

    // -- insertion operators --

    friend std::ostream & operator<<(std::ostream & os, const Vector4 & v);

    /********************************************************
     *                  -- Setters --                       *
     ********************************************************/

    /**
     * @brief     Set `x`, `y`, `z` and `w` components of this vector.
     */
    void Set(float x, float y, float z, float w);

    /**
     * @brief     Multiplies this vector by `v1` component-wise.
     */
    void Scale(const Vector4 & v1);

    /**
     * @brief     Normalize this vector.
     *
     * @exception `if (vector.GetMagnitude == 0)` return Vector4(0, 0, 0, 0).
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
     * @exception `if (vector.GetMagnitude == 0)` return Vector4(0, 0, 0, 0).
     */
    Vector4 GetNormalized() const;

    /********************************************************
     *              -- Static functions --                  *
     ********************************************************/

    /**
     * @brief     Get the dot product of `v1` and `v2`.
     */
    static float Dot(const Vector4 & v1, const Vector4 & v2);

    /**
     * @brief     Get the distance between `v1` and `v2`.
     */
    static float Distance(const Vector4 & v1, const Vector4 & v2);

    /**
     * @brief       Linear interpolation between `v1` and `v2` by the interpolant `t`.
     *
     * @param v1    a vector.
     * @param v2    a vector.
     * @param t     interpolation factor (it will be clamped to the range [0, 1]).
     */
    static Vector4 Lerp(const Vector4 & v1, const Vector4 & v2, float t);

    /********************************************************
     *                    -- TODO --                        *
     ********************************************************/

    // static Vector4 ProjectOnVector(const Vector4 & v1, const Vector4 & v2);
};

Vector4 operator*(float lhs, const Vector4 & rhs);
Vector4 operator/(float lhs, const Vector4 & rhs);

bool isnan(const Vector4 & vec);

} // namespace VDEngine

#endif /* VDENGINE_VECTOR4_H_ */