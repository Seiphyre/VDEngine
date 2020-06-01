#include "VDEngine/Core/Transform.h"

using namespace VDEngine;

Transform::Transform()
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    scale    = glm::vec3(1.0f, 1.0f, 1.0f);

    rotation        = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    euler_angle     = glm::vec3(0.0f, 0.0f, 0.0f);
    rotation_matrix = glm::mat4(1.0f);
}

Transform::~Transform()
{
}

glm::mat4 Transform::GetMatrix() const
{
    glm::mat4 final_matrix       = glm::mat4(1.0f);
    glm::mat4 translation_matrix = glm::mat4(1.0f);
    // glm::mat4 rotation_matrix   = glm::mat4(1.0f);
    glm::mat4 scale_matrix = glm::mat4(1.0f);

    // Translation
    translation_matrix = glm::translate(translation_matrix, position);

    // Rotation
    // glm::quat quat = glm::quat(glm::radians(euler_angle));
    //_rotation_matrix = glm::toMat4(quat); // glm::toMat4(rotation);

    // Scale
    scale_matrix = glm::scale(scale_matrix, scale);

    final_matrix = translation_matrix * rotation_matrix * scale_matrix;

    return final_matrix;
}

glm::mat4 Transform::GetNormalMatrix() const
{
    return (glm::transpose(glm::inverse(GetMatrix())));
}

glm::vec3 Transform::GetForwardDir() const
{
    const glm::mat4 matrix  = GetMatrix();
    const glm::vec3 forward = normalize(glm::vec3(matrix[2]));

    return (forward);
}
glm::vec3 Transform::GetUpDir() const
{
    const glm::mat4 matrix = GetMatrix();
    const glm::vec3 up     = normalize(glm::vec3(matrix[1]));

    return (up);
}
glm::vec3 Transform::GetRightDir() const
{
    const glm::mat4 matrix = GetMatrix();
    const glm::vec3 right  = normalize(glm::vec3(matrix[0]));

    return (right);
}

glm::vec3 Transform::GetEulerRotation() const
{
    // return glm::degrees(glm::eulerAngles(rotation));

    return (euler_angle);
}
void Transform::SetEulerRotation(const glm::vec3 & euler_rotation)
{
    // rotation = glm::quat(glm::radians(euler_rotation));

    euler_angle = euler_rotation;

    // Clamp angle between -360 and 360
    euler_angle.x = fmodf(euler_angle.x, 360);
    euler_angle.y = fmodf(euler_angle.y, 360);
    euler_angle.z = fmodf(euler_angle.z, 360);

    // Clamp angle between 0 and 360
    if (euler_angle.x < 0)
        euler_angle.x = 360.0f + euler_angle.x;
    if (euler_angle.y < 0)
        euler_angle.y = 360.0f + euler_angle.y;
    if (euler_angle.z < 0)
        euler_angle.z = 360.0f + euler_angle.z;

    rotation        = glm::quat(glm::radians(euler_angle));
    rotation_matrix = glm::toMat4(rotation);
}

void Transform::Translate(const glm::vec3 & translation)
{
    position += translation;
}

void Transform::Translate(float x, float y, float z)
{
    Translate(glm::vec3(x, y, z));
}

void Transform::Rotate(const glm::vec3 & eulers)
{
    Rotate(eulers.x, GetRightDir());
    Rotate(eulers.y, GetUpDir());
    Rotate(eulers.z, GetForwardDir());
}
void Transform::Rotate(float pitch, float yaw, float roll)
{
    Rotate(glm::vec3(pitch, yaw, roll));
}

void Transform::Rotate(float angle, const glm::vec3 & rotation_axis)
{
    rotation = glm::rotate(rotation, glm::radians(angle), glm::normalize(rotation_axis));

    // Update rotation values

    rotation_matrix = glm::toMat4(rotation);
    glm::extractEulerAngleXYZ(rotation_matrix, euler_angle.x, euler_angle.y, euler_angle.z);
    euler_angle = glm::degrees(euler_angle);

    // std::cout << "X:" << euler_angle.x << " Y: " << euler_angle.y << " Z: " << euler_angle.z << std::endl;
}

void Transform::LookAt(const glm::vec3 & target)
{
    // Rotation calculation
    glm::vec3 zaxis = glm::normalize(target - position);
    glm::vec3 xaxis = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), zaxis));
    glm::vec3 yaxis = glm::normalize(glm::cross(zaxis, xaxis));

    glm::mat4 rotation = {glm::vec4(xaxis.x, xaxis.y, xaxis.z, 0), glm::vec4(yaxis.x, yaxis.y, yaxis.z, 0),
                          glm::vec4(zaxis.x, zaxis.y, zaxis.z, 0), glm::vec4(0, 0, 0, 1)};

    // Set rotation using SetEulerRotation()

    glm::extractEulerAngleXYZ(rotation, euler_angle.x, euler_angle.y, euler_angle.z);
    euler_angle = glm::degrees(euler_angle);

    SetEulerRotation(euler_angle);

    // std::cout << "X:" << euler_angle.x << " Y: " << euler_angle.y << " Z: " << euler_angle.z << std::endl;
}