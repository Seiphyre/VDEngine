#include "VDEngine/Math/Vector3.h"

using namespace VDEngine;

Vector3::Vector3()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

Vector3 Vector3::CreateVecZero()
{
    return Vector3(0.0f, 0.0f, 0.0f);
}

Vector3 Vector3::CreateVecOne()
{
    return Vector3(1.0f, 1.0f, 1.0f);
}

Vector3 Vector3::CreateVecForward()
{
    return Vector3(0.0f, 0.0f, 1.0f);
}

Vector3 Vector3::CreateVecBack()
{
    return Vector3(0.0f, 0.0f, -1.0f);
}

Vector3 Vector3::CreateVecUp()
{
    return Vector3(0.0f, 1.0f, 0.0f);
}

Vector3 Vector3::CreateVecDown()
{
    return Vector3(0.0f, -1.0f, 0.0f);
}

Vector3 Vector3::CreateVecLeft()
{
    return Vector3(-1.0f, 0.0f, 0.0f);
}

Vector3 Vector3::CreateVecRight()
{
    return Vector3(1.0f, 0.0f, 0.0f);
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

// Vector3::operator Vector4() const
// {
//     return Vector4(x, y, z, 0.0f);
// }

// Vector3::operator Vector2() const
// {
//     return Vector2(x, y);
// }

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

Vector3 Vector3::operator+(const Vector3 & rhs) const
{
    Vector3 res(x + rhs.x, y + rhs.y, z + rhs.z);
    return res;
}

Vector3 Vector3::operator-(const Vector3 & rhs) const
{
    Vector3 res(x + rhs.x, y + rhs.y, z + rhs.z);
    return res;
}

Vector3 Vector3::operator*(float rhs) const
{
    Vector3 res(x * rhs, y * rhs, z * rhs);
    return res;
}

// Vector3 operator*(const Vector3 & vector, float scalar)
// {
//     Vector3 res(vector.x * scalar, vector.y * scalar, vector.z * scalar);
//     return res;
// }

Vector3 VDEngine::operator*(float lhs, const Vector3 & rhs)
{
    Vector3 res(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs);
    return res;
}

Vector3 Vector3::operator/(float rhs) const
{
    Vector3 res(x / rhs, y / rhs, z / rhs);
    return res;
}

// Vector3 operator/(const Vector3 & vector, float scalar)
// {
//     Vector3 res(vector.x * scalar, vector.y * scalar, vector.z * scalar);
//     return res;
// }

Vector3 VDEngine::operator/(float lhs, const Vector3 & rhs)
{
    Vector3 res(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs);
    return res;
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

bool Vector3::operator==(const Vector3 & rhs) const
{
    return (double)Vector3::Distance(*this, rhs) < EPSILON_DOUBLE;
}

bool Vector3::operator!=(const Vector3 & rhs) const
{
    return !(*this == rhs);
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

// glm::vec3 Vector3::glm_vec3() const
// {
//     return glm::vec3(x, y, z);
// }

// void Vector3::Set(const glm::vec3 & vec3)
// {
//     x = vec3.x;
//     y = vec3.y;
//     z = vec3.z;
// }

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

void Vector3::Set(float new_x, float new_y, float new_z)
{
    this->x = new_x;
    this->y = new_y;
    this->z = new_z;
}

void Vector3::Scale(const Vector3 & scale)
{
    this->x *= scale.x;
    this->y *= scale.y;
    this->z *= scale.z;
}

void Vector3::Normalize()
{
    float magnitude = this->GetMagnitude();

    if ((double)magnitude > EPSILON_DOUBLE)
    {
        x /= magnitude;
        y /= magnitude;
        z /= magnitude;
    }
    else
    {
        x = 0;
        y = 0;
        z = 0;
    }
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

float Vector3::GetMagnitude() const
{
    double xx = (double)x * (double)x;
    double yy = (double)y * (double)y;
    double zz = (double)z * (double)z;

    return sqrt((float)(xx + yy + zz));
}

float Vector3::GetSqrMagnitude() const
{
    double xx = (double)x * (double)x;
    double yy = (double)y * (double)y;
    double zz = (double)z * (double)z;

    return (float)(xx + yy + zz);
}

Vector3 Vector3::GetNormalized() const
{
    float magnitude = GetMagnitude();

    if ((double)magnitude > EPSILON_DOUBLE)
        return *this / magnitude;

    return Vector3::CreateVecZero();
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

Vector3 Vector3::Cross(const Vector3 & lhs, const Vector3 & rhs)
{
    return Vector3((float)((double)lhs.y * (double)rhs.z - (double)lhs.z * (double)rhs.y),
                   (float)((double)lhs.z * (double)rhs.x - (double)lhs.x * (double)rhs.z),
                   (float)((double)lhs.x * (double)rhs.y - (double)lhs.y * (double)rhs.x));
}

float Vector3::Dot(const Vector3 & lhs, const Vector3 & rhs)
{
    return (float)((double)lhs.x * (double)rhs.x + (double)lhs.y * (double)rhs.y + (double)lhs.z * (double)rhs.z);
}

float Vector3::Distance(const Vector3 & vec_a, const Vector3 & vec_b)
{
    Vector3 vector3 = vec_a - vec_b;

    return vector3.GetMagnitude();
}

float Vector3::Angle(const Vector3 & from, const Vector3 & to)
{
    float dot_product         = Vector3::Dot(from.GetNormalized(), to.GetNormalized());
    float dot_product_clamped = clamp(dot_product, -1.0f, 1.0f);
    float result              = acos(dot_product_clamped);

    return to_degrees(result);
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

// Vector3 Vector3::Reflect(Vector3 inDirection, Vector3 inNormal)
// {
//     return -2.0f * Vector3::Dot(inNormal, inDirection) * inNormal + inDirection;
// }

// Vector3 Vector3::Project(Vector3 vector, Vector3 onNormal)
// {
//     float num = Vector3::Dot(onNormal, onNormal);

//     if ((double)num < EPSILON_DOUBLE)
//         return Vector3::CreateVecZero();

//     return onNormal * Vector3::Dot(vector, onNormal) / num;
// }

// Vector3 Vector3::ProjectOnPlane(Vector3 vector, Vector3 planeNormal)
// {
//     return vector - Vector3::Project(vector, planeNormal);
// }

// static Vector3 Lerp(Vector3 a, Vector3 b, float t)
// {
//   t = Mathf.Clamp01(t);
//   return Vector3(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t);
// }

// static Vector3 LerpUnclamped(Vector3 a, Vector3 b, float t)
// {
//   return Vector3(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t);
// }

// static Vector3 Slerp(Vector3 a, Vector3 b, float t)
// static Vector3 SlerpUnclamped(Vector3 a, Vector3 b, float t)
// static void OrthoNormalize(Vector3 & normal, Vector3 & tangent)
// static void OrthoNormalize(Vector3 & normal, Vector3 & tangent, Vector3 & binormal)