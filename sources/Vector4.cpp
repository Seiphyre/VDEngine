#include "VDEngine/Math/Vector4.h"

using namespace VDEngine;

/********************************************************
 *               -- Constructors --                     *
 ********************************************************/

Vector4::Vector4()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 0.0f;
}

Vector4::Vector4(float p_x, float p_y, float p_z, float p_w)
{
    x = p_x;
    y = p_y;
    z = p_z;
    w = p_w;
}

// -- static constructors --------------------------------

Vector4 Vector4::VecZero()
{
    return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
}

Vector4 Vector4::VecOne()
{
    return Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}

Vector4 Vector4::VecNan()
{
    return Vector4(NAN_FLOAT, NAN_FLOAT, NAN_FLOAT, NAN_FLOAT);
}

/********************************************************
 *                 -- Operators --                      *
 ********************************************************/

// -- unary minus operator ------------------------------

Vector4 Vector4::operator-() const
{
    return (*this * -1.0f);
}

// -- arithmetic operators ------------------------------

Vector4 Vector4::operator+(const Vector4 & rhs) const
{
    return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

Vector4 Vector4::operator-(const Vector4 & rhs) const
{
    return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

Vector4 Vector4::operator*(float rhs) const
{
    return Vector4(x * rhs, y * rhs, z * rhs, w * rhs);
}

Vector4 Vector4::operator/(float rhs) const
{
    return Vector4(x / rhs, y / rhs, z / rhs, w / rhs);
}

Vector4 VDEngine::operator*(float lhs, const Vector4 & rhs)
{
    return Vector4(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs, rhs.w * lhs);
}

Vector4 VDEngine::operator/(float lhs, const Vector4 & rhs)
{
    return Vector4(rhs.x / lhs, rhs.y / lhs, rhs.z / lhs, rhs.w / lhs);
}

// -- compound assignment --------------------------------

Vector4 & Vector4::operator+=(const Vector4 & rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;

    return *this;
}

Vector4 & Vector4::operator-=(const Vector4 & rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;

    return *this;
}

Vector4 & Vector4::operator*=(float rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;

    return *this;
}

Vector4 & Vector4::operator/=(float rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    w /= rhs;

    return *this;
}

// -- comparison operators --------------------------------

bool Vector4::operator==(const Vector4 & rhs) const
{
    return ((double)Vector4::Distance(*this, rhs)) < EPSILON_DOUBLE;
}

bool Vector4::operator!=(const Vector4 & rhs) const
{
    return !(*this == rhs);
}

// -- insertion operators -----------------------------------

std::ostream & VDEngine::operator<<(std::ostream & os, const Vector4 & v)
{
    os << std::fixed << std::setprecision(5);

    os << "Vec4( " << v.x << "  " << v.y << "  " << v.z << "  " << v.w << " )";

    os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
    return os;
}

/********************************************************
 *                  -- Setters --                       *
 ********************************************************/

void Vector4::Set(float p_x, float p_y, float p_z, float p_w)
{
    x = p_x;
    y = p_y;
    z = p_z;
    w = p_w;
}

void Vector4::Scale(const Vector4 & v1)
{
    x *= v1.x;
    y *= v1.y;
    z *= v1.z;
    w *= v1.w;
}

void Vector4::Normalize()
{
    float magnitude = this->GetMagnitude();

    if ((double)magnitude > EPSILON_DOUBLE)
    {
        x /= magnitude;
        y /= magnitude;
        z /= magnitude;
        w /= magnitude;
    }
    else
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
        w = 0.0f;
    }
}

/********************************************************
 *                  -- Getters --                       *
 ********************************************************/

Vector4 Vector4::GetNormalized() const
{
    float magnitude = GetMagnitude();

    if ((double)magnitude > EPSILON_DOUBLE)
        return *this / magnitude;

    return Vector4::VecZero();
}

float Vector4::GetMagnitude() const
{
    double xx = (double)x * (double)x;
    double yy = (double)y * (double)y;
    double zz = (double)z * (double)z;
    double ww = (double)w * (double)w;

    return sqrt((float)(xx + yy + zz + ww));
}

float Vector4::GetSqrMagnitude() const
{
    double xx = (double)x * (double)x;
    double yy = (double)y * (double)y;
    double zz = (double)z * (double)z;
    double ww = (double)w * (double)w;

    return (float)(xx + yy + zz + ww);
}

/********************************************************
 *              -- Static functions --                  *
 ********************************************************/

float Vector4::Dot(const Vector4 & v1, const Vector4 & v2)
{
    return (float)((double)v1.x * (double)v2.x + (double)v1.y * (double)v2.y + (double)v1.z * (double)v2.z +
                   (double)v1.w * (double)v2.w);
}

float Vector4::Distance(const Vector4 & v1, const Vector4 & v2)
{
    Vector4 vector = v1 - v2;

    return vector.GetMagnitude();
}

Vector4 Vector4::Lerp(const Vector4 & v1, const Vector4 & v2, float t)
{
    t = clamp(t, 0.0f, 1.0f);

    return Vector4(v1.x + (v2.x - v1.x) * t, v1.y + (v2.y - v1.y) * t, v1.z + (v2.z - v1.z) * t,
                   v1.w + (v2.w - v1.w) * t);
}

inline bool VDEngine::isnan(const Vector4 & vec)
{
    return std::isnan(vec.x) || std::isnan(vec.y) || std::isnan(vec.z) || std::isnan(vec.w);
}

/********************************************************
 *                    -- TODO --                        *
 ********************************************************/

// Vector4 Vector4::ProjectOnVector(const Vector4 & v1, const Vector4 & v2)
// {
//     return v2 * Vector4::Dot(v1, v2) / Vector4::Dot(v2, v2);
// }