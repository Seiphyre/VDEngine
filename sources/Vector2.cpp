#include "VDEngine/Math/Vector2.h"

using namespace VDEngine;

/********************************************************
 *               -- Constructors --                     *
 ********************************************************/

Vector2::Vector2()
{
    x = 0.0f;
    y = 0.0f;
}

Vector2::Vector2(float p_x, float p_y)
{
    x = p_x;
    y = p_y;
}

// -- static constructors ---------------------------------

Vector2 Vector2::VecNan()
{
    return Vector2(NAN_FLOAT, NAN_FLOAT);
}

Vector2 Vector2::VecZero()
{
    return Vector2(0.0f, 0.0f);
}

Vector2 Vector2::VecOne()
{
    return Vector2(1.0f, 1.0f);
}

Vector2 Vector2::VecUp()
{
    return Vector2(0.0f, 1.0f);
}

Vector2 Vector2::VecDown()
{
    return Vector2(0.0f, -1.0f);
}

Vector2 Vector2::VecLeft()
{
    return Vector2(-1.0f, 0.0f);
}

Vector2 Vector2::VecRight()
{
    return Vector2(1.0f, 0.0f);
}

/********************************************************
 *                 -- Operators --                      *
 ********************************************************/

// -- unary minus operator --------------------------------

Vector2 Vector2::operator-() const
{
    return (*this * -1.0f);
}

// -- arithmetic operators --------------------------------

Vector2 Vector2::operator+(const Vector2 & rhs) const
{
    return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2 & rhs) const
{
    return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator*(float rhs) const
{
    return Vector2(x * rhs, y * rhs);
}

Vector2 Vector2::operator/(float rhs) const
{
    return Vector2(x / rhs, y / rhs);
}

Vector2 VDEngine::operator*(float lhs, const Vector2 & rhs)
{
    Vector2 res(rhs.x * lhs, rhs.y * lhs);
    return res;
}

Vector2 VDEngine::operator/(float lhs, const Vector2 & rhs)
{
    Vector2 res(rhs.x / lhs, rhs.y / lhs);
    return res;
}

// -- compound assignment ---------------------------------

Vector2 & Vector2::operator+=(const Vector2 & rhs)
{
    x += rhs.x;
    y += rhs.y;

    return *this;
}

Vector2 & Vector2::operator-=(const Vector2 & rhs)
{
    x -= rhs.x;
    y -= rhs.y;

    return *this;
}

Vector2 & Vector2::operator*=(float rhs)
{
    x *= rhs;
    y *= rhs;

    return *this;
}

Vector2 & Vector2::operator/=(float rhs)
{
    x /= rhs;
    y /= rhs;

    return *this;
}

// -- comparison operators ---------------------------------

bool Vector2::operator==(const Vector2 & rhs) const
{
    return ((double)Vector2::Distance(*this, rhs)) < EPSILON_DOUBLE;
}

bool Vector2::operator!=(const Vector2 & rhs) const
{
    return !(*this == rhs);
}

// -- insertion operators ---------------------------------

std::ostream & VDEngine::operator<<(std::ostream & os, const Vector2 & v)
{
    os << std::fixed << std::setprecision(5);

    os << "Vec2( " << v.x << "  " << v.y << " )";

    os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
    return os;
}

/********************************************************
 *                  -- Setters --                       *
 ********************************************************/

void Vector2::Set(float p_x, float p_y)
{
    x = p_x;
    y = p_y;
}

void Vector2::Scale(const Vector2 & scale)
{
    x *= scale.x;
    y *= scale.y;
}

void Vector2::Normalize()
{
    float magnitude = this->GetMagnitude();

    if ((double)magnitude > EPSILON_DOUBLE)
    {
        x /= magnitude;
        y /= magnitude;
    }
    else
    {
        x = 0;
        y = 0;
    }
}

/********************************************************
 *                  -- Getters --                       *
 ********************************************************/

Vector2 Vector2::GetNormalized() const
{
    float magnitude = this->GetMagnitude();

    if ((double)magnitude > EPSILON_DOUBLE)
        return *this / magnitude;

    return Vector2::VecZero();
}

float Vector2::GetMagnitude() const
{
    double xx = (double)x * (double)x;
    double yy = (double)y * (double)y;

    return sqrt((float)(xx + yy));
}

float Vector2::GetSqrMagnitude() const
{
    double xx = (double)x * (double)x;
    double yy = (double)y * (double)y;

    return (float)(xx + yy);
}

/********************************************************
 *              -- Static functions --                  *
 ********************************************************/

float Vector2::Dot(const Vector2 & v1, const Vector2 & v2)
{
    return (float)((double)v1.x * (double)v2.x + (double)v1.y * (double)v2.y);
}

float Vector2::Angle(const Vector2 & p_from, const Vector2 & p_to)
{
    Vector2 from = p_from.GetNormalized();
    Vector2 to   = p_to.GetNormalized();

    if (from == Vector2::VecZero() || to == Vector2::VecZero())
    {
        std::cout << "[Warning][Vector2::Angle] Cannot calculate the angle between FROM and TO, because FROM or TO is "
                     "Vector2(0, 0) or too small to be normalized."
                  << std::endl;
        return 0;
    }

    float dot_product         = Vector2::Dot(from, to);
    float dot_product_clamped = clamp(dot_product, -1.0f, 1.0f);

    float result = acos(dot_product_clamped);

    return to_degrees(result);
}

float Vector2::Distance(const Vector2 & v1, const Vector2 & v2)
{
    Vector2 vector2 = v1 - v2;

    return vector2.GetMagnitude();
}

Vector2 Vector2::Lerp(const Vector2 & v1, const Vector2 & v2, float t)
{
    t = clamp(t, 0.0f, 1.0f);
    return Vector2(v1.x + (v2.x - v1.x) * t, v1.y + (v2.y - v1.y) * t);
}

inline bool VDEngine::isnan(const Vector2 & vec)
{
    return std::isnan(vec.x) || std::isnan(vec.y);
}

/********************************************************
 *                    -- TODO --                        *
 ********************************************************/

// Vector2 Vector2::Reflect(const Vector2 & in_direction, const Vector2 & normal)
// {
//     return -2f * Vector2.Dot(normal, in_direction) * normal + in_direction;
// }

// Vector2 Vector2::ProjectOnVector(const Vector2 & v1, const Vector2 & v2);