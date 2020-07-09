#ifndef VDENGINE_VECTOR2_H_
#define VDENGINE_VECTOR2_H_

// Standard c++ libs
#include <iostream>
#include <iomanip>

// Internal headers
#include "VDEngine/Math/Core.hpp"

namespace VDEngine
{

struct Vector2
{

  public:
    float x;
    float y;

    /********************************************************
     *               -- Constructors --                     *
     ********************************************************/

    /**
     * @brief     Create `Vector2(0, 0)`
     */
    Vector2();

    /**
     * @brief     Create `Vector2(x, y)`
     */
    Vector2(float x, float y);

    // -- static constructors --

    /**
     * @brief     Return `Vector2(0, 0)`.
     */
    static Vector2 VecZero();

    /**
     * @brief     Return `Vector2(1, 1)`.
     */
    static Vector2 VecOne();

    /**
     * @brief     Return `Vector2(0, 1)`.
     */
    static Vector2 VecUp();

    /**
     * @brief     Return `Vector2(0, -1)`.
     */
    static Vector2 VecDown();

    /**
     * @brief     Return `Vector2(-1, 0)`.
     */
    static Vector2 VecLeft();

    /**
     * @brief     Return `Vector2(0, 1)`.
     */
    static Vector2 VecRight();

    /**
     * @brief     Return `Vector2(NAN_FLOAT, NAN_FLOAT)`. It can be used to handle vectors math errors.
     */
    static Vector2 VecNan();

    /********************************************************
     *                 -- Operators --                      *
     ********************************************************/

    // -- unary minus operator --

    Vector2 operator-() const;

    // -- arithmetic operators --

    Vector2 operator+(const Vector2 & rhs) const;
    Vector2 operator-(const Vector2 & rhs) const;
    Vector2 operator*(float rhs) const;
    Vector2 operator/(float rhs) const;

    // -- compound assignment --

    Vector2 & operator+=(const Vector2 & rhs);
    Vector2 & operator-=(const Vector2 & rhs);
    Vector2 & operator*=(float rhs);
    Vector2 & operator/=(float rhs);

    // -- comparison operators --

    bool operator==(const Vector2 & rhs) const;
    bool operator!=(const Vector2 & rhs) const;

    // -- insertion operators --

    friend std::ostream & operator<<(std::ostream & os, const Vector2 & v);

    /********************************************************
     *                  -- Setters --                       *
     ********************************************************/

    /**
     * @brief     Set `x` and `y` components of this vector.
     */
    void Set(float x, float y);

    /**
     * @brief     Multiplies this vector by `v1` component-wise.
     */
    void Scale(const Vector2 & scalar);

    /**
     * @brief     Normalize this vector.
     *
     * @exception `if (vector.GetMagnitude == 0)` return Vector2(0, 0).
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
     * @exception `if (vector.GetMagnitude == 0)` return Vector2(0, 0).
     */
    Vector2 GetNormalized() const;

    /********************************************************
     *              -- Static functions --                  *
     ********************************************************/

    /**
     * @brief     Get the distance between `v1` and `v2`.
     */
    static float Distance(const Vector2 & v1, const Vector2 & v2);

    /**
     * @brief     Get the dot product of `v1` and `v2`.
     */
    static float Dot(const Vector2 & v1, const Vector2 & v2);

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
    static float Angle(const Vector2 & from, const Vector2 & to);

    /**
     * @brief       Linear interpolation between `v1` and `v2` by the interpolant `t`.
     *
     * @param v1    a vector.
     * @param v2    a vector.
     * @param t     interpolation factor (it will be clamped to the range [0, 1]).
     */
    static Vector2 Lerp(const Vector2 & v1, const Vector2 & v2, float t);

    /********************************************************
     *                    -- TODO --                        *
     ********************************************************/

    // static Vector2 Reflect(const Vector2 & in_direction, const Vector2 & normal);

    // static Vector2 ProjectOnVector(const Vector2 & v1, const Vector2 & v2);
};

Vector2 operator*(float lhs, const Vector2 & rhs);
Vector2 operator/(float lhs, const Vector2 & rhs);

bool isnan(const Vector2 & vec);

} // namespace VDEngine

#endif /* VDENGINE_VECTOR2_H_ */