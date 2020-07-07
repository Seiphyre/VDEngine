#include "VDEngine/Math/Vector4.h"

using namespace VDEngine;

Vector4::Vector4()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 0.0f;
}

Vector4::Vector4(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

Vector4 Vector4::CreateVecZero()
{
    return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
}

Vector4 Vector4::CreateVecOne()
{
    return Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

// Vector4::operator Vector3() const
// {
//      return Vector3(x, y, z);
// }
// Vector4::operator Vector2() const
// {
//      return Vector2(x, y);
// }

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

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

Vector4 VDEngine::operator*(float lhs, const Vector4 & rhs)
{
    return Vector4(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs, rhs.w * lhs);
}

// Vector4 operator*(const Vector4 & lhs, float rhs)
// {
//     return Vector4(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
// }

Vector4 Vector4::operator/(float rhs) const
{
    return Vector4(x / rhs, y / rhs, z / rhs, w / rhs);
}

Vector4 VDEngine::operator/(float lhs, const Vector4 & rhs)
{
    return Vector4(rhs.x / lhs, rhs.y / lhs, rhs.z / lhs, rhs.w / lhs);
}

// Vector4 operator/(const Vector4 & lhs, float rhs)
// {
//     return Vector4(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs);
// }

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

bool Vector4::operator==(const Vector4 & rhs) const
{
    return (double)Vector4::Distance(*this, rhs) < EPSILON_DOUBLE;
}

bool Vector4::operator!=(const Vector4 & rhs) const
{
    return !(*this == rhs);
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

// glm::vec4 Vector4::glm_vec4() const
// {
//     return glm::vec4(x, y, z, w);
// }

// void Vector4::Set(const glm::vec4 & vec4)
// {
//     x = vec4.x;
//     y = vec4.y;
//     z = vec4.z;
//     w = vec4.w;
// }

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

void Vector4::Set(float new_x, float new_y, float new_z, float new_w)
{
    x = new_x;
    y = new_y;
    z = new_z;
    w = new_w;
}

void Vector4::Scale(const Vector4 & scale)
{
    x *= scale.x;
    y *= scale.y;
    z *= scale.z;
    w *= scale.w;
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
        x /= 0.0f;
        y /= 0.0f;
        z /= 0.0f;
        w /= 0.0f;
    }
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

Vector4 Vector4::GetNormalized() const
{
    float magnitude = GetMagnitude();

    if ((double)magnitude > EPSILON_DOUBLE)
        return *this / magnitude;

    return Vector4::CreateVecZero();
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

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

float Vector4::Dot(const Vector4 & lhs, const Vector4 & rhs)
{
    return (float)((double)lhs.x * (double)rhs.x + (double)lhs.y * (double)rhs.y + (double)lhs.z * (double)rhs.z +
                   (double)lhs.w * (double)rhs.w);
}

float Vector4::Distance(const Vector4 & vec_a, const Vector4 & vec_b)
{
    Vector4 vector = vec_a - vec_b;

    return vector.GetMagnitude();
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

// Vector4 Vector4::Lerp(Vector4 a, Vector4 b, float t)
// {
//     t = clamp(t, 0.0f, 1.0f);
//     return Vector4(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t, a.w + (b.w - a.w) * t);
// }

// Vector4 Vector4::LerpUnclamped(Vector4 a, Vector4 b, float t)
// {
//     return Vector4(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t, a.w + (b.w - a.w) * t);
// }

// Vector4 Vector4::Project(Vector4 a, Vector4 b)
// {
//     return b * Vector4::Dot(a, b) / Vector4::Dot(b, b);
// }