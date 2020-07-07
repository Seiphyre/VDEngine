#include "VDEngine/Math/Quaternion.h"

using namespace VDEngine;

Quaternion::Quaternion()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 1.0f;
}

Quaternion::Quaternion(float p_x, float p_y, float p_z, float p_w)
{
    Set(p_x, p_y, p_z, p_w);
}

Quaternion::Quaternion(const Quaternion & q)
{
    Set(q.x, q.y, q.z, q.w);
}

Quaternion::Quaternion(const Vector3 & axis, const float & angle)
{
    SetAngleAxis(axis, angle);
}

Quaternion::Quaternion(const Vector3 & euler)
{
    SetEuler(euler);
}

//////////////////////////////////////////////
//////////////////////////////////////////////

Quaternion Quaternion::CreateFromAngleAxis(const Vector3 & axis, const float & angle)
{
    Quaternion quat;
    quat.SetAngleAxis(axis, angle);

    return (quat);
}

//////////////////////////////////////////////
//////////////////////////////////////////////

inline void Quaternion::Set(float p_x, float p_y, float p_z, float p_w)
{
    x = p_x;
    y = p_y;
    z = p_z;
    w = p_w;

    if (!IsNormalized())
        Normalize();
}

void Quaternion::SetEuler(const Vector3 & p_euler)
{
    SetEulerZXY(p_euler);
};

// SetEulerXYZ expects a vector containing the Euler angles in the format
// (ax,ay,az), where ax is the angle of rotation around x axis,
// and similar for other axes.
// This implementation uses XYZ convention (X is the first rotation).
void Quaternion::SetEulerXYZ(const Vector3 & p_euler)
{
    float half_1 = p_euler.x * 0.5;
    float half_2 = p_euler.y * 0.5;
    float half_3 = p_euler.z * 0.5;

    // R = Rx(a1).Ry(a2).Rz(a3) convention for Euler angles.
    // Conversion to quaternion as listed in https://ntrs.nasa.gov/archive/nasa/casi.ntrs.nasa.gov/19770024290.pdf (page
    // A-2) a3 is the angle of the first rotation, following the notation in this reference.

    float c1 = cos(half_1);
    float s1 = sin(half_1);
    float c2 = cos(half_2);
    float s2 = sin(half_2);
    float c3 = cos(half_3);
    float s3 = sin(half_3);

    float x = s1 * c2 * c3 + c1 * s2 * s3;
    float y = -s1 * c2 * s3 + c1 * s2 * c3;
    float z = s1 * s2 * c3 + c1 * c2 * s3;
    float w = -s1 * s2 * s3 + c1 * c2 * c3;

    // Threejs      OK
    // Godot        OK
    // NASA         OK
    // Mathwork     OK
    // GLM          KO

    Set(x, y, z, w);

    // SOLUTION 2 -----

    // glm::quat QuatAroundX = glm::angleAxis(ofDegToRad(euler.x), glm::vec3(1.0, 0.0, 0.0));
    // glm::quat QuatAroundY = glm::angleAxis(ofDegToRad(euler.y), glm::vec3(0.0, 1.0, 0.0));
    // glm::quat QuatAroundZ = glm::angleAxis(ofDegToRad(euler.z), glm::vec3(0.0, 0.0, 1.0));
    // glm::quat orientation = QuatAroundX * QuatAroundY * QuatAroundZ;
}

void Quaternion::SetEulerZXY(const Vector3 & p_euler)
{
    float half_1 = p_euler.y * 0.5;
    float half_2 = p_euler.x * 0.5;
    float half_3 = p_euler.z * 0.5;

    // Conversion to quaternion as listed in https://ntrs.nasa.gov/archive/nasa/casi.ntrs.nasa.gov/19770024290.pdf (page
    // A-10)

    float c1 = cos(half_1);
    float s1 = sin(half_1);
    float c2 = cos(half_2);
    float s2 = sin(half_2);
    float c3 = cos(half_3);
    float s3 = sin(half_3);

    float x = -s1 * c2 * s3 + c1 * s2 * c3;
    float y = s1 * s2 * c3 + c1 * c2 * s3;
    float z = s1 * c2 * c3 + c1 * s2 * s3;
    float w = -s1 * s2 * s3 + c1 * c2 * c3;

    // Mathwork OK
    // NASA     OK
    // Threejs  KO

    Set(x, y, z, w);
}

// p_axis: no need to be normalized
// p_angle: must be in degree
void Quaternion::SetAngleAxis(const Vector3 & p_axis, float p_angle)
{
    Vector3 axis  = p_axis.GetNormalized();
    float   angle = to_radians(p_angle);

    // angle is divided by 2 BECAUSE quat range = 720° BUT sin/cos range = 0-360°
    float sin_angle = sinf(angle * 0.5f);
    float cos_angle = cosf(angle * 0.5f);

    Set(axis.x * sin_angle, axis.y * sin_angle, axis.z * sin_angle, cos_angle);

    // if (p_axis.GetMagnitude() != 1)
    // {
    //     std::cout << "[Quaternion::SetAngleAxis] The axis vector must be normalized." << std::endl;
    // }

    // float length = p_axis.GetMagnitude();

    // if (length == 0)
    // {
    //     Set(0, 0, 0, 0);
    // }
    // else
    // {
    //     float sin_angle = sin(p_angle * 0.5);
    //     float cos_angle = cos(p_angle * 0.5);
    //     float s         = sin_angle / length;

    //     Set(p_axis.x * s, p_axis.y * s, p_axis.z * s, cos_angle);
    // }
}

//////////////////////////////////////////////
//////////////////////////////////////////////

Vector3 Quaternion::GetEuler() const
{
    return GetEulerZXY();
}

Vector3 Quaternion::GetEulerZXY() const
{
    if (!IsNormalized())
    {
        std::cout << "[Quaternion::GetEulerZXY] The quaternion must be normalized." << std::endl;
    }

    float xy = x * y;
    float wz = w * z;
    float yz = y * z;
    float wx = w * x;
    float xz = x * z;
    float wy = w * y;

    float ww = w * w;
    float xx = x * x;
    float yy = y * y;
    float zz = z * z;

    float z = atan2(-2.0f * (xz - wy), ww - xx - yy + zz);
    float x = asin(2.0f * (yz + wx));
    float y = atan2(-2.0f * (xy - wz), ww - xx + yy - zz);

    return (Vector3(x, y, z));
}

Vector3 Quaternion::GetEulerXYZ() const
{
    if (!IsNormalized())
    {
        std::cout << "[Quaternion::GetEulerXYZ] The quaternion must be normalized." << std::endl;
    }

    float xy = x * y;
    float wz = w * z;
    float yz = y * z;
    float wx = w * x;
    float xz = x * z;
    float wy = w * y;

    float ww = w * w;
    float xx = x * x;
    float yy = y * y;
    float zz = z * z;

    float x = atan2(-2 * (yz - wx), ww - xx - yy + zz);
    float y = asin(2 * (xz + wy));
    float z = atan2(-2 * (xy - wz), ww + xx - yy - zz);

    // mathwork         OK
    // Birdy notebook   OK

    return (Vector3(x, y, z));
}

void Quaternion::GetAngleAxis(Vector3 & r_axis, float & r_angle) const
{
    // Get Angle
    r_angle = 2.0f * acos(w);

    // Get Axis
    float r  = 1.0f / sqrt(1.0f - w * w);
    r_axis.x = x * r;
    r_axis.y = y * r;
    r_axis.z = z * r;
}

//////////////////////////////////////////////
//////////////////////////////////////////////

void Quaternion::Normalize()
{
    *this /= GetMagnitude();
}

Quaternion Quaternion::GetNormalized() const
{
    return *this / GetMagnitude();
}

bool Quaternion::IsNormalized() const
{
    float length_squared = GetMagnitude() * GetMagnitude();

    return (abs(length_squared - 1.0f) < EPSILON_FLOAT);
}

float Quaternion::GetMagnitude() const
{
    return sqrt(x * x + y * y + z * z + w * w);
}

Quaternion Quaternion::LookRotation(const Vector3 & p_forward, const Vector3 & p_world_up)
{
    Vector3 look_forward = p_forward.GetNormalized();
    Vector3 look_up      = p_world_up.GetNormalized();

    // Calculate final orientation forward
    Quaternion rot_forward;

    rot_forward = Quaternion::FromTo(Vector3::CreateVecForward(), look_forward);

    // Calculate final orientation up
    Quaternion rot_up;

    Vector3 look_right = Vector3::Cross(look_up, look_forward);
    look_up            = Vector3::Cross(look_forward, look_right);

    Vector3 newUp = Vector3::CreateVecUp() * rot_forward;
    rot_up        = Quaternion::FromTo(newUp, look_up);

    // result
    Quaternion targetOrientation = rot_up * rot_forward;
    targetOrientation.Normalize();

    return (targetOrientation);
}

Quaternion Quaternion::FromTo(const Vector3 & p_from, const Vector3 & p_to)
{
    Vector3 from = p_from.GetNormalized();
    Vector3 to   = p_to.GetNormalized();

    // parallel direction (Cross product of from/to won't work ...)
    if (from == to)
    {
        return (Quaternion());
    }
    // Opposite direction (Cross product of from/to won't work ...)
    else if (from == (to * -1.0f))
    {
        // Find the closest orthogonal vector (world_forward, world_right, world_up)
        Vector3 ortho = Vector3::CreateVecRight();

        if (fabsf(from.y) < fabsf(from.x))
            ortho = Vector3::CreateVecUp();
        if ((fabsf(from.z) < fabsf(from.y)) && (fabsf(from.z) < fabsf(from.x)))
            ortho = Vector3::CreateVecForward();

        // Find axis
        Vector3 axis = Vector3::Cross(from, ortho).GetNormalized();

        // No angle (because cos(pi/2) = 0)
        return Quaternion(axis.x, axis.y, axis.z, 0);
    }

    // we can use the dot and cross products to create a quaternion that rotates two times the distance between the
    // given input vectors. So we need to find half that rotation.
    Vector3 half = (from + to).GetNormalized();

    // Find axis (with cross product) (cross(from, to) = sin(angle) * axis)
    Vector3 axis = Vector3::Cross(from, half);
    // find angle (with dot product) (from/to are normalized, so dot(from, to) = cos(angle))
    float angle = Vector3::Dot(from, half);

    return (Quaternion(axis.x, axis.y, axis.z, angle));
}

// Quaternion Quaternion::inverse() const
// {
//     if (!is_normalized())
//     {
//         std::cout << "[Quaternion::inverse] The quaternion must be normalized." << std::endl;
//     }

//     return Quaternion(-x, -y, -z, w);
// }

// float Quaternion::dot(const Quaternion & q) const
// {
//     return x * q.x + y * q.y + z * q.z + w * q.w;
// }

//////////////////////////////////////////////
//////////////////////////////////////////////

void Quaternion::operator+=(const Quaternion & rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
}

void Quaternion::operator-=(const Quaternion & rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
}

void Quaternion::operator*=(float rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
}

void Quaternion::operator*=(const Quaternion & rhs)
{
    float new_x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
    float new_y = w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z;
    float new_z = w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x;
    float new_w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;

    Set(new_x, new_y, new_z, new_w);
}

void Quaternion::operator/=(float rhs)
{
    *this *= 1.0f / rhs;
}

//////////////////////////////////////////////
//////////////////////////////////////////////

Quaternion Quaternion::operator+(const Quaternion & rhs) const
{
    const Quaternion & lhs = *this;

    return (Quaternion(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w));
}

Quaternion Quaternion::operator-(const Quaternion & rhs) const
{
    const Quaternion & lhs = *this;

    return (Quaternion(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w));
}

Quaternion Quaternion::operator*(const Quaternion & rhs) const
{
    Quaternion new_quat = *this;
    new_quat *= rhs;

    return (new_quat);
}

Quaternion Quaternion::operator*(float rhs) const
{
    return (Quaternion(x * rhs, y * rhs, z * rhs, w * rhs));
}

Vector3 VDEngine::operator*(const Vector3 & v, const Quaternion & q)
{
    Vector3 q_axis  = Vector3(q.x, q.y, q.z);
    float   q_angle = q.w;

    // formula : https://gabormakesgames.com/blog_quats_multiply_vec.html
    return 2.0f * Vector3::Dot(q_axis, v) * q_axis + (q_angle * q_angle - Vector3::Dot(q_axis, q_axis)) * v +
           2.0f * q_angle * Vector3::Cross(q_axis, v);
}

// Quaternion Quaternion::operator*(const Vector3 & rhs) const
// {
//     float new_x = w * rhs.x + y * rhs.z - z * rhs.y;
//     float new_y = w * w * rhs.y + z * rhs.x - x * rhs.z;
//     float new_z = w * rhs.z + x * rhs.y - y * rhs.x;
//     float new_w = -x * rhs.x - y * rhs.y - z * rhs.z;

//     return (Quaternion(new_x, new_y, new_z, new_w));
// }

Quaternion Quaternion::operator/(float rhs) const
{
    return (*this * (1.0f / rhs));
}

//////////////////////////////////////////////
//////////////////////////////////////////////

Quaternion Quaternion::operator-() const
{
    const Quaternion & new_quat = *this;

    return Quaternion(-new_quat.x, -new_quat.y, -new_quat.z, -new_quat.w);
}

//////////////////////////////////////////////
//////////////////////////////////////////////

bool Quaternion::operator==(const Quaternion & rhs) const
{
    // return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w);

    bool x_is_equal = abs(x - rhs.x) < EPSILON_FLOAT;
    bool y_is_equal = abs(y - rhs.y) < EPSILON_FLOAT;
    bool z_is_equal = abs(z - rhs.z) < EPSILON_FLOAT;
    bool w_is_equal = abs(w - rhs.w) < EPSILON_FLOAT;

    return (x_is_equal && y_is_equal && z_is_equal && w_is_equal);
}

bool Quaternion::operator!=(const Quaternion & rhs) const
{
    // return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;

    return (!(*this == rhs));
}

//////////////////////////////////////////////
//////////////////////////////////////////////

Quaternion Quaternion::operator=(const Quaternion & rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;

    return (*this);
}