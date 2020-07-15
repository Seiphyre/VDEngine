#include "VDEngine/Math/Vector3.h"

using namespace VDEngine;

/********************************************************
 *               -- Constructors --                     *
 ********************************************************/

Vector3::Vector3()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Vector3::Vector3(float p_x, float p_y, float p_z)
{
    x = p_x;
    y = p_y;
    z = p_z;
}

// -- static constructors --------------------------------

Vector3 Vector3::VecZero()
{
    return Vector3(0.0f, 0.0f, 0.0f);
}

Vector3 Vector3::VecOne()
{
    return Vector3(1.0f, 1.0f, 1.0f);
}

Vector3 Vector3::VecForward()
{
    return Vector3(0.0f, 0.0f, 1.0f);
}

Vector3 Vector3::VecBack()
{
    return Vector3(0.0f, 0.0f, -1.0f);
}

Vector3 Vector3::VecUp()
{
    return Vector3(0.0f, 1.0f, 0.0f);
}

Vector3 Vector3::VecDown()
{
    return Vector3(0.0f, -1.0f, 0.0f);
}

Vector3 Vector3::VecLeft()
{
    return Vector3(-1.0f, 0.0f, 0.0f);
}

Vector3 Vector3::VecRight()
{
    return Vector3(1.0f, 0.0f, 0.0f);
}

Vector3 Vector3::VecNan()
{
    return Vector3(NAN_FLOAT, NAN_FLOAT, NAN_FLOAT);
}

/********************************************************
 *                 -- Operators --                      *
 ********************************************************/

// -- unary minus operator ------------------------------

Vector3 Vector3::operator-() const
{
    return (*this * -1.0f);
}

// -- arithmetic operators ------------------------------

Vector3 Vector3::operator+(const Vector3 & rhs) const
{
    Vector3 res(x + rhs.x, y + rhs.y, z + rhs.z);
    return res;
}

Vector3 Vector3::operator-(const Vector3 & rhs) const
{
    Vector3 res(x - rhs.x, y - rhs.y, z - rhs.z);
    return res;
}

Vector3 Vector3::operator*(float rhs) const
{
    Vector3 res(x * rhs, y * rhs, z * rhs);
    return res;
}

Vector3 Vector3::operator/(float rhs) const
{
    Vector3 res(x / rhs, y / rhs, z / rhs);
    return res;
}

Vector3 VDEngine::operator*(float lhs, const Vector3 & rhs)
{
    Vector3 res(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs);
    return res;
}

Vector3 VDEngine::operator/(float lhs, const Vector3 & rhs)
{
    Vector3 res(rhs.x / lhs, rhs.y / lhs, rhs.z / lhs);
    return res;
}

// -- compound assignment --------------------------------

Vector3 & Vector3::operator+=(const Vector3 & rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;

    return *this;
}

Vector3 & Vector3::operator-=(const Vector3 & rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;

    return *this;
}

Vector3 & Vector3::operator*=(float rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;

    return *this;
}

Vector3 & Vector3::operator/=(float rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;

    return *this;
}

// -- comparison operators --------------------------------

bool Vector3::operator==(const Vector3 & rhs) const
{
    return ((double)Vector3::Distance(*this, rhs)) < EPSILON_DOUBLE;
}

bool Vector3::operator!=(const Vector3 & rhs) const
{
    return !(*this == rhs);
}

// -- insertion operators ---------------------------------

std::ostream & VDEngine::operator<<(std::ostream & os, const Vector3 & v)
{
    os << std::fixed << std::setprecision(5);

    os << "Vec3( " << v.x << "  " << v.y << "  " << v.z << " )";

    os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
    return os;
}

/********************************************************
 *                  -- Setters --                       *
 ********************************************************/

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

/********************************************************
 *                  -- Getters --                       *
 ********************************************************/

float Vector3::GetMagnitude() const
{
    double xx = (double)x * (double)x;
    double yy = (double)y * (double)y;
    double zz = (double)z * (double)z;

    return sqrt(xx + yy + zz);
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

    return Vector3::VecZero();
}

bool Vector3::IsNormalized() const
{
    float magnitude = GetMagnitude();

    return (abs(magnitude - 1.0f) < EPSILON_FLOAT);
}

/********************************************************
 *              -- Static functions --                  *
 ********************************************************/

Vector3 Vector3::Cross(const Vector3 & v1, const Vector3 & v2)
{
    return Vector3((float)((double)v1.y * (double)v2.z - (double)v1.z * (double)v2.y),
                   (float)((double)v1.z * (double)v2.x - (double)v1.x * (double)v2.z),
                   (float)((double)v1.x * (double)v2.y - (double)v1.y * (double)v2.x));
}

float Vector3::Dot(const Vector3 & v1, const Vector3 & v2)
{
    return (float)((double)v1.x * (double)v2.x + (double)v1.y * (double)v2.y + (double)v1.z * (double)v2.z);
}

float Vector3::Distance(const Vector3 & v1, const Vector3 & v2)
{
    Vector3 vector3 = v2 - v1;

    return vector3.GetMagnitude();
}

float Vector3::Angle(const Vector3 & p_from, const Vector3 & p_to)
{
    Vector3 from = p_from.GetNormalized();
    Vector3 to   = p_to.GetNormalized();

    if (from == Vector3::VecZero() || to == Vector3::VecZero())
    {
        std::cout << "[Warning][Vector3::Angle] Cannot calculate the angle between FROM and TO, because FROM or TO is "
                     "Vector3(0, 0, 0) or too small to be normalized."
                  << std::endl;
        return 0;
    }

    float dot_product         = Vector3::Dot(from.GetNormalized(), to.GetNormalized());
    float dot_product_clamped = clamp(dot_product, -1.0f, 1.0f);
    float result              = acos(dot_product_clamped);

    return to_degrees(result);
}

Vector3 Vector3::Lerp(const Vector3 & v1, const Vector3 & v2, float t)
{
    t = clamp(t, 0.0f, 1.0f);

    return Vector3(v1.x + (v2.x - v1.x) * t, v1.y + (v2.y - v1.y) * t, v1.z + (v2.z - v1.z) * t);
}

inline bool VDEngine::isnan(const Vector3 & vec)
{
    return std::isnan(vec.x) || std::isnan(vec.y) || std::isnan(vec.z);
}

/********************************************************
 *                    -- TODO --                        *
 ********************************************************/

// Vector3 Vector3::Reflect(const Vector3 & in_direction, const Vector3 & normal)
// {
//     return -2.0f * Vector3::Dot(normal, in_direction) * normal + in_direction;
// }

// Vector3 Vector3::ProjectOnVector(const Vector3 & v1, const Vector3 & v2)
// {
//     float num = Vector3::Dot(v2, v2);

//     if ((double)num < EPSILON_DOUBLE)
//         return Vector3::CreateVecZero();

//     return v2 * Vector3::Dot(v1, v2) / num;
// }

// Vector3 Vector3::ProjectOnPlane(Vector3 vector, Vector3 plane_normal)
// {
//     return vector - Vector3::Project(vector, plane_normal);
// }

// static Vector3 Slerp(const Vector3 & v1, const Vector3 & v2, float t)
// {
//     // https://gabormakesgames.com/blog_vectors_interpolate.html

//     Vector3 from = v1.GetNormalized();
//     Vector3 to   = v2.GetNormalized();

//     t = clamp(t, 0.0f, 1.0);

//     float theta     = to_radians(Vector3::Angle(from, to));
//     float sin_theta = sin(theta);

//     float a = sin((1.0 - t) * theta) / sin_theta;
//     float b = sin(t * theta) / sin_theta;

//     return (from * a) + (to * b);
// }

// static void OrthoNormalize(Vector3 & v1, Vector3 & v2)
// static void OrthoNormalize(Vector3 & v1, Vector3 & v2, Vector3 & v3)