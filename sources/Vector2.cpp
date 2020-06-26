#include "VDEngine/Math/Vector2.h"

using namespace VDEngine;

Vector2::Vector2()
{
    x = 0.0f;
    y = 0.0f;
}

Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

Vector2 Vector2::CreateVecZero()
{
    return Vector2(0.0f, 0.0f);
}

Vector2 Vector2::CreateVecOne()
{
    return Vector2(1.0f, 1.0f);
}

Vector2 Vector2::CreateVecUp()
{
    return Vector2(0.0f, 1.0f);
}

Vector2 Vector2::CreateVecDown()
{
    return Vector2(0.0f, -1.0f);
}

Vector2 Vector2::CreateVecLeft()
{
    return Vector2(-1.0f, 0.0f);
}

Vector2 Vector2::CreateVecRight()
{
    return Vector2(1.0f, 0.0f);
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

// Vector2::operator Vector4() const
// {
//     return Vector4(x, y, 0.0f, 0.0f);
// }

// Vector2::operator Vector3() const
// {
//     return Vector3(x, y, 0.0f);
// }

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

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

// Vector2 operator*(const Vector2 & vector, float scalar)
// {
//     Vector2 res(vector.x * scalar, vector.y * scalar);
//     return res;
// }

Vector2 operator*(float lhs, const Vector2 & rhs)
{
    Vector2 res(rhs.x * lhs, rhs.y * lhs);
    return res;
}

Vector2 Vector2::operator/(float rhs) const
{
    return Vector2(x / rhs, y / rhs);
}

// Vector2 operator/(const Vector2 & vector, float scalar)
// {
//     Vector2 res(vector.x * scalar, vector.y * scalar);
//     return res;
// }

Vector2 operator/(float lhs, const Vector2 & rhs)
{
    Vector2 res(rhs.x * lhs, rhs.y * lhs);
    return res;
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

bool Vector2::operator==(const Vector2 & rhs) const
{
    return (double)Vector2::Distance(*this, rhs) < EPSILON_DOUBLE;
}

bool Vector2::operator!=(const Vector2 & rhs) const
{
    return !(*this == rhs);
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

// glm::vec2 Vector2::glm_vec2() const
// {
//     return glm::vec2(x, y);
// }

// void Vector2::Set(const glm::vec2 & vec2)
// {
//     x = vec2.x;
//     y = vec2.y;
// }

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

void Vector2::Set(float new_x, float new_y)
{
    x = new_x;
    y = new_y;
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

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

Vector2 Vector2::GetNormalized() const
{
    float magnitude = this->GetMagnitude();

    if ((double)magnitude > EPSILON_DOUBLE)
        return *this / magnitude;

    return Vector2::CreateVecZero();
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

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

float Vector2::Dot(const Vector2 & lhs, const Vector2 & rhs)
{
    return (float)((double)lhs.x * (double)rhs.x + (double)lhs.y * (double)rhs.y);
}

float Vector2::Angle(const Vector2 & from, const Vector2 & to)
{
    float dot_product         = Vector2::Dot(from.GetNormalized(), to.GetNormalized());
    float dot_product_clamped = clamp(dot_product, -1.0f, 1.0f);
    float result              = acos(dot_product_clamped);

    return to_degrees(result);
}

float Vector2::Distance(const Vector2 & vec_a, const Vector2 & vec_b)
{
    Vector2 vector2 = vec_a - vec_b;

    return vector2.GetMagnitude();
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

// static Vector2 Lerp(Vector2 a, Vector2 b, float t)
// {
//   t = Mathf.Clamp01(t);
//   return new Vector2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
// }

// static Vector2 LerpUnclamped(Vector2 a, Vector2 b, float t)
// {
//   return new Vector2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
// }

// Vector2 Vector2::Reflect(Vector2 inDirection, Vector2 inNormal)
// {
//     return -2f * Vector2.Dot(inNormal, inDirection) * inNormal + inDirection;
// }