#include "VDEngine/Math/Quaternion.h"

using namespace VDEngine;

/********************************************************
 *               -- Constructors --                     *
 ********************************************************/

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

// -- static constructors -------------------------------

Quaternion Quaternion::CreateFromEuler(const Vector3 & euler)
{
    Quaternion quat;
    quat.SetEuler(euler);

    return (quat);
}

Quaternion Quaternion::CreateFromAxisAngle(const Vector3 & axis, const float & angle)
{
    Quaternion quat;
    quat.SetAngleAxis(axis, angle);

    return (quat);
}

Quaternion Quaternion::LookRotation(const Vector3 & p_forward, const Vector3 & p_up)
{
    // http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/#i-need-an-equivalent-of-glulookat-how-do-i-orient-an-object-towards-a-point-
    // https://gabormakesgames.com/blog_quats_create.html (go to : Look At)

    Vector3 forward = p_forward.GetNormalized();
    Vector3 up      = p_up.GetNormalized();

    std::cout << up << std::endl;

    // Calculate final orientation forward
    Quaternion rot1;

    rot1 = Quaternion::FromTo(Vector3::VecForward(), forward);
    std::cout << rot1 << std::endl;

    // Calculate final orientation up
    Quaternion rot2;

    Vector3 right = Vector3::Cross(up, forward);
    up            = Vector3::Cross(forward, right);

    Vector3 new_up = rot1 * Vector3::VecUp();
    rot2           = Quaternion::FromTo(new_up, up);

    std::cout << rot2 << std::endl;

    // result
    Quaternion targetOrientation = rot2 * rot1;

    std::cout << targetOrientation << std::endl;
    targetOrientation.Normalize();

    return (targetOrientation);

    ///////////////////////////////////////////////////

    // if (p_forward == Vector3::VecZero())
    // {
    //     std::cout << "[Quaternion::LookRotation] direction not valid." << std::endl;
    //     return Quaternion();
    // }

    // // Vector3 forward = p_forward.GetNormalized();
    // Vector3 up = p_up.GetNormalized();

    // if (p_up != p_forward)
    // {

    //     Vector3    v = p_forward + up * -Vector3::Dot(up, p_forward);
    //     Quaternion q = Quaternion::FromTo(Vector3::VecForward(), v);

    //     return q * Quaternion::FromTo(v, p_forward);
    // }
    // else
    // {
    //     return Quaternion::FromTo(Vector3::VecForward(), p_forward);
    // }

    ///////////////////////////////////////////////////

    // Vector3 forward = p_forward.GetNormalized();
    // Vector3 right   = (Vector3::Cross(p_up, forward)).GetNormalized();
    // Vector3 up      = Vector3::Cross(forward, right);

    // float m00 = right.x;
    // float m01 = right.y;
    // float m02 = right.z;
    // float m10 = up.x;
    // float m11 = up.y;
    // float m12 = up.z;
    // float m20 = forward.x;
    // float m21 = forward.y;
    // float m22 = forward.z;

    // float      num8 = (m00 + m11) + m22;
    // Quaternion quaternion;
    // if (num8 > 0.0f)
    // {
    //     float num    = sqrt(num8 + 1.0f);
    //     quaternion.w = num * 0.5f;
    //     num          = 0.5f / num;
    //     quaternion.x = (m12 - m21) * num;
    //     quaternion.y = (m20 - m02) * num;
    //     quaternion.z = (m01 - m10) * num;
    //     return quaternion;
    // }
    // if ((m00 >= m11) && (m00 >= m22))
    // {
    //     float num7   = sqrt(((1.0f + m00) - m11) - m22);
    //     float num4   = 0.5f / num7;
    //     quaternion.x = 0.5f * num7;
    //     quaternion.y = (m01 + m10) * num4;
    //     quaternion.z = (m02 + m20) * num4;
    //     quaternion.w = (m12 - m21) * num4;
    //     return quaternion;
    // }
    // if (m11 > m22)
    // {
    //     float num6   = sqrt(((1.0f + m11) - m00) - m22);
    //     float num3   = 0.5f / num6;
    //     quaternion.x = (m10 + m01) * num3;
    //     quaternion.y = 0.5f * num6;
    //     quaternion.z = (m21 + m12) * num3;
    //     quaternion.w = (m20 - m02) * num3;
    //     return quaternion;
    // }
    // float num5   = sqrt(((1.0f + m22) - m00) - m11);
    // float num2   = 0.5f / num5;
    // quaternion.x = (m20 + m02) * num2;
    // quaternion.y = (m21 + m12) * num2;
    // quaternion.z = 0.5f * num5;
    // quaternion.w = (m01 - m10) * num2;

    // return quaternion;
}

Quaternion Quaternion::FromTo(const Vector3 & p_from, const Vector3 & p_to)
{
    // http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/#how-do-i-find-the-rotation-between-2-vectors-
    // https://gabormakesgames.com/blog_quats_create.html (go to : Shortest Arc (from to rotation))

    // Using Half-Way Vector Solution -------

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
        Vector3 ortho = Vector3::VecRight();

        if (fabsf(from.y) < fabsf(from.x))
            ortho = Vector3::VecUp();
        if ((fabsf(from.z) < fabsf(from.y)) && (fabsf(from.z) < fabsf(from.x)))
            ortho = Vector3::VecForward();

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

    Quaternion result = Quaternion(axis.x, axis.y, axis.z, angle);

    // -- UNITY ? --
    // Vector3 axis  = Vector3::Cross(from, to);
    // float   angle = Vector3::Angle(from, to);
    //
    // Quaternion result = Quaternion::CreateFromAxisAngle(axis.GetNormalized(), angle);
    // -----------

    result.Normalize();

    return (result);
}

/********************************************************
 *                  -- Setters --                       *
 ********************************************************/

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
    // https://www.mathworks.com/matlabcentral/fileexchange/20696-function-to-convert-between-dcm-euler-angles-quaternions-and-euler-vectors
    // (in "Functions" tab -> line "switch INPUT_TYPE" -> line "case 'EA' ")
    // https://ntrs.nasa.gov/archive/nasa/casi.ntrs.nasa.gov/19770024290.pdf (page A-10)
    //
    // with mathworks/NASA : 1 = Z, 2 = X, 3 = Y
    //
    // https://github.com/mrdoob/three.js/blob/master/src/math/Quaternion.js (func : setFromEuler())
    //
    // with threejs : 1 = X, 2 = Y, 3 = Z

    Vector3 euler = Vector3(to_radians(p_euler.x), to_radians(p_euler.y), to_radians(p_euler.z));

    SetEulerZXY(euler);
};

void Quaternion::SetEulerXYZ(const Vector3 & p_euler)
{
    float half_1 = p_euler.x * 0.5f;
    float half_2 = p_euler.y * 0.5f;
    float half_3 = p_euler.z * 0.5f;

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

    Set(x, y, z, w);

    // -- OTHER METHODE -----

    // Quaternion QuatAroundX = Quaternion::CreateFromAxisAngle(Vector3::VecRight(), euler.x);
    // Quaternion QuatAroundY = Quaternion::CreateFromAxisAngle(Vector3::VecUp(), euler.y);
    // Quaternion QuatAroundZ = Quaternion::CreateFromAxisAngle(Vector3::VecForward(), euler.z);

    // Quaternion orientation = QuatAroundX * QuatAroundY * QuatAroundZ;
}

void Quaternion::SetEulerZXY(const Vector3 & p_euler)
{
    float half_1 = p_euler.z * 0.5; // first rotation angle
    float half_2 = p_euler.x * 0.5; // second rotation angle
    float half_3 = p_euler.y * 0.5; // third rotation angle

    float c1 = cos(half_1);
    float s1 = sin(half_1);
    float c2 = cos(half_2);
    float s2 = sin(half_2);
    float c3 = cos(half_3);
    float s3 = sin(half_3);

    float new_x = -s1 * c2 * s3 + c1 * s2 * c3;
    float new_y = s1 * s2 * c3 + c1 * c2 * s3;
    float new_z = c1 * s2 * s3 + s1 * c2 * c3;
    float new_w = -s1 * s2 * s3 + c1 * c2 * c3;

    Set(new_x, new_y, new_z, new_w);
}

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

void Quaternion::Normalize()
{
    float magnitude = this->GetMagnitude();

    if (magnitude > EPSILON_FLOAT)
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
        w = 1.0f;
    }
}

void Quaternion::Inverse()
{
    float norm = Dot(*this, *this);

    if (abs(norm) > EPSILON_FLOAT)
    {
        x /= (-1.0f * norm);
        y /= (-1.0f * norm);
        z /= (-1.0f * norm);
        w /= norm;
    }
    else
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
        w = 1.0f;
    }
}

/********************************************************
 *                  -- Getters --                       *
 ********************************************************/

Vector3 Quaternion::GetEuler() const
{
    // http://bediyap.com/programming/convert-quaternion-to-euler-rotations/
    // https://www.mathworks.com/matlabcentral/fileexchange/20696-function-to-convert-between-dcm-euler-angles-quaternions-and-euler-vectors
    // (in "Functions" tab -> line "switch OUTPUT_TYPE" -> line "case 'EA' ")

    return GetEulerZXY();
}

Vector3 Quaternion::GetEulerZXY() const
{
    if (!IsNormalized())
    {
        std::cout << "[Warning] [Quaternion::GetEulerZXY] The quaternion must be normalized." << std::endl;
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

    float z = atan2(-2.0f * (xy - wz), ww - xx + yy - zz);
    float x = asin(clamp(2.0f * (yz + wx), -1, 1)); // -1/1 are dangerous because of float precision
    float y = atan2(-2.0f * (xz - wy), ww - xx - yy + zz);

    Vector3 result = Vector3(to_degrees(x), to_degrees(y), to_degrees(z));

    result.x = fmod((fmod(result.x, 360.0f) + 360.0f), 360.0f);
    result.y = fmod((fmod(result.y, 360.0f) + 360.0f), 360.0f);
    result.z = fmod((fmod(result.z, 360.0f) + 360.0f), 360.0f);

    // if (!result.IsNormalized())
    //     result.Normalize();

    return (result);
}

Vector3 Quaternion::GetEulerXYZ() const
{
    if (!IsNormalized())
    {
        std::cout << "[Warning] [Quaternion::GetEulerXYZ] The quaternion must be normalized." << std::endl;
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

    Vector3 result = Vector3(to_degrees(x), to_degrees(y), to_degrees(z));

    // if (!result.IsNormalized())
    //     result.Normalize();

    return (result);
}

void Quaternion::GetAxisAngle(Vector3 & r_axis, float & r_angle) const
{
    // Get Angle
    r_angle = 2.0f * acos(w);
    r_angle = to_degrees(r_angle);

    // Get Axis
    r_axis = Vector3(x, y, z);
    r_axis.Normalize();
}

Vector3 Quaternion::GetForward() const
{
    Vector3 forward = (*this) * Vector3::VecForward();

    if (!forward.IsNormalized())
        forward.Normalize();

    return (forward);
}

Vector3 Quaternion::GetRight() const
{
    Vector3 right = (*this) * Vector3::VecRight();

    if (!right.IsNormalized())
        right.Normalize();

    return (right);
}

Vector3 Quaternion::GetUp() const
{
    Vector3 up = (*this) * Vector3::VecUp();

    if (!up.IsNormalized())
        up.Normalize();

    return (up);
}

float Quaternion::GetMagnitude() const
{
    return sqrt(Dot(*this, *this));
}

float Quaternion::GetSqrMagnitude() const
{
    return Dot(*this, *this);
}

Quaternion Quaternion::GetNormalized() const
{
    Quaternion quat = *this;

    quat.Normalize();

    return quat;
}

bool Quaternion::IsNormalized() const
{
    float magnitude = GetMagnitude();

    return (abs(magnitude - 1.0f) < EPSILON_FLOAT);
}

Quaternion Quaternion::GetInversed() const
{
    Quaternion quat = *this;

    quat.Inverse();

    return quat;
}

/********************************************************
 *              -- Static functions --                  *
 ********************************************************/

inline float Quaternion::Dot(const Quaternion & q1, const Quaternion & q2)
{
    return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
}

inline bool VDEngine::isnan(const Quaternion & quat)
{
    return std::isnan(quat.x) || std::isnan(quat.y) || std::isnan(quat.z) || std::isnan(quat.w);
}

// inline Quaternion Quaternion::Inverse() const
// {
//     if (!is_normalized())
//     {
//         std::cout << "[Quaternion::inverse] The quaternion must be normalized." << std::endl;
//     }

//     return Quaternion(-x, -y, -z, w);
// }

// Quaternion Lerp(const Quaternion & q1, const Quaternion & q2, float t) const
// {
// }

// Quaternion Slerp(const Quaternion & q1, const Quaternion & q2, float t) const
// {
// }

/********************************************************
 *                 -- Operators --                      *
 ********************************************************/

// -- unary minus operator ------------------------------

inline Quaternion Quaternion::operator-() const
{
    return (*this * -1.0f);
}

// -- arithmetic operators ------------------------------

inline Quaternion Quaternion::operator+(const Quaternion & rhs) const
{
    const Quaternion & lhs = *this;

    return (Quaternion(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w));
}

inline Quaternion Quaternion::operator-(const Quaternion & rhs) const
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

inline Quaternion Quaternion::operator*(float rhs) const
{
    return (Quaternion(x * rhs, y * rhs, z * rhs, w * rhs));
}

inline Quaternion Quaternion::operator/(float rhs) const
{
    return (*this * (1.0f / rhs));
}

Vector3 VDEngine::operator*(const Quaternion & q, const Vector3 & v)
{
    // -- GABOR -----------------------------------------

    // Vector3 q_axis  = Vector3(q.x, q.y, q.z);
    // float   q_angle = q.w;

    // // formula : https://gabormakesgames.com/blog_quats_multiply_vec.html
    // return 2.0f * Vector3::Dot(q_axis, v) * q_axis + (q_angle * q_angle - Vector3::Dot(q_axis, q_axis)) * v +
    //        2.0f * q_angle * Vector3::Cross(q_axis, v);

    // -- GLM -----------------------------------------

    Vector3 q_vector(q.x, q.y, q.z);
    Vector3 qv_cross_v  = Vector3::Cross(q_vector, v);
    Vector3 qv_cross_uv = Vector3::Cross(q_vector, qv_cross_v);

    return v + ((qv_cross_v * q.w) + qv_cross_uv) * 2.0f;

    // ------------------------

    // glm::vec3 QuatVector(q.x, q.y, q.z);
    // glm::vec3 uv(glm::cross(QuatVector, to_glm_vec3(v)));
    // glm::vec3 uuv(glm::cross(QuatVector, uv));

    // return to_vector3(to_glm_vec3(v) + ((uv * q.w) + uuv) * 2.0f);

    // -- Unity -----------------------------------------

    // float num1  = q.x * 2.0f;
    // float num2  = q.y * 2.0f;
    // float num3  = q.z * 2.0f;
    // float num4  = q.x * num1;
    // float num5  = q.y * num2;
    // float num6  = q.z * num3;
    // float num7  = q.x * num2;
    // float num8  = q.x * num3;
    // float num9  = q.y * num3;
    // float num10 = q.w * num1;
    // float num11 = q.w * num2;
    // float num12 = q.w * num3;

    // Vector3 vector3;
    // vector3.x = (float)((1.0 - ((double)num5 + (double)num6)) * (double)v.x +
    //                     ((double)num7 - (double)num12) * (double)v.y + ((double)num8 + (double)num11) * (double)v.z);
    // vector3.y =
    //     (float)(((double)num7 + (double)num12) * (double)v.x + (1.0f - ((double)num4 + (double)num6)) * (double)v.y +
    //             ((double)num9 - (double)num10) * (double)v.z);
    // vector3.z = (float)(((double)num8 - (double)num11) * (double)v.x + ((double)num9 + (double)num10) * (double)v.y +
    //                     (1.0 - ((double)num4 + (double)num5)) * (double)v.z);
    // return vector3;
}

// -- direct assignment operators -----------------------

Quaternion Quaternion::operator=(const Quaternion & rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;

    return (*this);
}

// -- compound assignment operators ---------------------

inline Quaternion & Quaternion::operator+=(const Quaternion & rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;

    return *this;
}

inline Quaternion & Quaternion::operator-=(const Quaternion & rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;

    return *this;
}

Quaternion & Quaternion::operator*=(const Quaternion & rhs)
{
    float new_x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
    float new_y = w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z;
    float new_z = w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x;
    float new_w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;

    Set(new_x, new_y, new_z, new_w);

    return *this;
}

inline Quaternion & Quaternion::operator*=(float rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;

    return *this;
}

inline Quaternion & Quaternion::operator/=(float rhs)
{
    *this *= 1.0f / rhs;

    return *this;
}

// -- comparison operators ------------------------------

inline bool Quaternion::operator==(const Quaternion & rhs) const
{
    // return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w);

    bool x_is_equal = abs(x - rhs.x) < EPSILON_FLOAT;
    bool y_is_equal = abs(y - rhs.y) < EPSILON_FLOAT;
    bool z_is_equal = abs(z - rhs.z) < EPSILON_FLOAT;
    bool w_is_equal = abs(w - rhs.w) < EPSILON_FLOAT;

    return (x_is_equal && y_is_equal && z_is_equal && w_is_equal);
}

inline bool Quaternion::operator!=(const Quaternion & rhs) const
{
    // return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;

    return (!(*this == rhs));
}

// -- insertion operators -------------------------------

std::ostream & VDEngine::operator<<(std::ostream & os, const Quaternion & q)
{
    os << std::fixed << std::setprecision(5);

    os << "Quat( " << q.x << "  " << q.y << "  " << q.z << "  " << q.w << " )";

    os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
    return os;
}