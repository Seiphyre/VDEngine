#include "VDEngine/Quaternion.h"

VDEngine::Quaternion::Quaternion()
{
    w = 1.0f;
    y = 0.0f;
    z = 0.0f;
    x = 0.0f;
}

VDEngine::Quaternion::Quaternion(float w, float y, float z, float x)
{
    this->w = w;
    this->y = y;
    this->z = z;
    this->x = x;
}

VDEngine::Quaternion::~Quaternion()
{
}

void VDEngine::Quaternion::FromEuler(glm::vec3 euler)
{
    // Must be in radian
    float heading  = glm::radians(euler.y);
    float attitude = glm::radians(euler.x);
    float bank     = glm::radians(euler.z);

    double c1   = cos(heading / 2.0f);
    double s1   = sin(heading / 2.0f);
    double c2   = cos(attitude / 2.0f);
    double s2   = sin(attitude / 2.0f);
    double c3   = cos(bank / 2.0f);
    double s3   = sin(bank / 2.0f);
    double c1c2 = c1 * c2;
    double s1s2 = s1 * s2;

    w = c1c2 * c3 - s1s2 * s3;
    x = c1c2 * s3 + s1s2 * c3;
    y = s1 * c2 * c3 + c1 * s2 * s3;
    z = c1 * s2 * c3 - s1 * c2 * s3;
}

glm::vec3 VDEngine::Quaternion::ToEulerAngle() const
{
    float heading;
    float attitude;
    float bank;

    double sqw  = w * w;
    double sqx  = x * x;
    double sqy  = y * y;
    double sqz  = z * z;
    double unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
    double test = x * y + z * w;

    // singularity at north pole
    if (test > 0.499 * unit)
    {
        heading  = 2.0f * atan2(x, w);
        attitude = glm::pi<float>() / 2.0f;
        bank     = 0.0f;

        return glm::degrees(glm::vec3(attitude, heading, bank));
    }

    // singularity at south pole
    if (test < -0.499 * unit)
    {
        heading  = -2.0f * atan2(x, w);
        attitude = glm::pi<float>() / 2.0f;
        bank     = 0.0f;

        return glm::degrees(glm::vec3(attitude, heading, bank));
    }

    heading  = atan2(2.0f * y * w - 2.0f * x * z, sqx - sqy - sqz + sqw);
    attitude = asin(2.0f * test / unit);
    bank     = atan2(2.0f * x * w - 2.0f * y * z, -sqx + sqy - sqz + sqw);

    return glm::degrees(glm::vec3(attitude, heading, bank));
}
glm::mat4 VDEngine::Quaternion::ToRotationMatrix() const
{
    glm::mat4 matrix = glm::mat4(1.0f);

    float xx = x * x;
    float xy = x * y;
    float xz = x * z;
    float xw = x * w;

    float yy = y * y;
    float yz = y * z;
    float yw = y * w;

    float zz = z * z;
    float zw = z * w;

    matrix[0][0] = 1 - 2 * (yy + zz);
    matrix[0][1] = 2 * (xy + zw);
    matrix[0][2] = 2 * (xz - yw);

    matrix[1][0] = 2 * (xy - zw);
    matrix[1][1] = 1 - 2 * (xx + zz);
    matrix[1][2] = 2 * (yz + xw);

    matrix[2][0] = 2 * (xz + yw);
    matrix[2][1] = 2 * (yz - xw);
    matrix[2][2] = 1 - 2 * (xx + yy);

    return matrix;
}