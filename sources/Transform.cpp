#include "Transform.h"

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

    // rotation_matrix = glm::rotate(rotation_matrix, glm::radians(euler_angle.x), X_3D_AXIS);
    // rotation_matrix = glm::rotate(rotation_matrix, glm::radians(euler_angle.y), Y_3D_AXIS);
    // rotation_matrix = glm::rotate(rotation_matrix, glm::radians(euler_angle.z), Z_3D_AXIS);

    // Scale
    scale_matrix = glm::scale(scale_matrix, scale);

    final_matrix = translation_matrix * rotation_matrix * scale_matrix;

    return final_matrix;
}

glm::vec3 Transform::GetForwardDir() const
{
    // const glm::mat4 inverted = glm::inverse(transformationMatrix);
    // const glm::vec3 forward = normalize(glm::vec3(inverted[2]));

    const glm::mat4 matrix  = GetMatrix();
    const glm::vec3 forward = normalize(glm::vec3(matrix[2]));

    return (forward);
}
glm::vec3 Transform::GetUpDir()
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
    // XYZ order : pitch, yaw, roll
    // return glm::degrees(glm::eulerAngles(rotation));

    return (euler_angle);
}
void Transform::SetEulerRotation(const glm::vec3 & euler_rotation)
{
    // XYZ order : pitch, yaw, roll
    // rotation = glm::quat(glm::radians(euler_rotation));

    euler_angle = euler_rotation;

    // Clamp angle between -360 and 360
    euler_angle.x = fmodf(euler_angle.x, 360);
    euler_angle.y = fmodf(euler_angle.y, 360);
    euler_angle.z = fmodf(euler_angle.z, 360);

    // Clamp angle between 0 and 360
    if (euler_angle.x < 0)
        euler_angle.x = 360.0f - euler_angle.x;
    if (euler_angle.y < 0)
        euler_angle.y = 360.0f - euler_angle.y;
    if (euler_angle.z < 0)
        euler_angle.z = 360.0f - euler_angle.z;

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

    // glm::quat new_rotation(glm::radians(eulers));
    // rotation = glm::normalize(rotation * new_rotation);
}
void Transform::Rotate(float pitch, float yaw, float roll)
{
    // Rotate(x, X_3D_AXIS);
    // Rotate(y, Y_3D_AXIS);
    // Rotate(z, Z_3D_AXIS);

    // pitch = glm::radians(pitch);
    // yaw   = glm::radians(yaw);
    // roll  = glm::radians(roll);

    // rotation = glm::quat(glm::vec3(pitch, 0.0f, 0.0f)) * rotation;
    // rotation = glm::quat(glm::vec3(0.0f, yaw, 0.0f)) * rotation;
    // rotation = glm::quat(glm::vec3(0.0f, 0.0f, roll)) * rotation;
}

void Transform::Rotate(float angle, const glm::vec3 & rotation_axis)
{
    rotation = glm::rotate(rotation, glm::radians(angle), glm::normalize(rotation_axis));

    rotation_matrix = glm::toMat4(rotation);
    glm::extractEulerAngleXYZ(rotation_matrix, euler_angle.x, euler_angle.y, euler_angle.z);
    euler_angle = glm::degrees(euler_angle);

    // std::cout << "ROTATION : X:" << euler_angle.x << " Y: " << euler_angle.y << " Z: " << euler_angle.z << std::endl;
}

void Transform::LookAt(const glm::vec3 & target)
{

    glm::vec3 zaxis = glm::normalize(target - position);
    glm::vec3 xaxis = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), zaxis));
    glm::vec3 yaxis = glm::normalize(glm::cross(zaxis, xaxis));

    glm::mat4 view = {glm::vec4(xaxis.x, xaxis.y, xaxis.z, -glm::dot(xaxis, position)),
                      glm::vec4(yaxis.x, yaxis.y, yaxis.z, -glm::dot(yaxis, position)),
                      glm::vec4(zaxis.x, zaxis.y, zaxis.z, -glm::dot(zaxis, position)), glm::vec4(0, 0, 0, 1)};

    // glm::mat4 view = glm::lookAt(_translation, target, glm::vec3(0.0f, 1.0f, 0.0f));
    // view           = glm::inverse(view);

    // glm::mat4 transformation; // your transformation matrix.
    glm::vec3 scale;
    glm::quat qRotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(view, scale, qRotation, translation, skew, perspective);

    // Because it is a conjugate quaternion
    // qRotation = glm::conjugate(qRotation);

    glm::vec3 eRotation = glm::degrees(glm::eulerAngles(qRotation)); // * 3.14159f / 180.f;
    rotation            = eRotation;

    // std::cout << _rotation.x << "/" << _rotation.y << "/" << _rotation.z << std::endl;
    // std::cout << eRotation.x << "/" << eRotation.y << "/" << eRotation.z << std::endl;

    // glm::vec3 translation = glm::vec3(view[0][3], view[1][3], view[2][3]);
    // view[0][3]            = 0;
    // view[1][3]            = 0;
    // view[2][3]            = 0;

    // glm::vec3 scale = glm::vec3(sqrtf(powf(view[0][0], 2) + powf(view[0][1], 2) + powf(view[0][2], 2)),
    //                             sqrtf(powf(view[1][0], 2) + powf(view[1][1], 2) + powf(view[1][2], 2)),
    //                             sqrtf(powf(view[2][0], 2) + powf(view[2][1], 2) + powf(view[2][2], 2)));
}