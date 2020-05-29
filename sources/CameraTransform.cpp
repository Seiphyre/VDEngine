#include "CameraTransform.h"

#define ORIENTATION_DEFAULT_FORWARD (glm::vec3(0, 0, -1))
#define ORIENTATION_DEFAULT_UP (glm::vec3(0, 1, 0))
#define ORIENTATION_DEFAULT_RIGHT (glm::vec3(1, 0, 0))

CameraTransform::CameraTransform(const glm::vec3 & position) : m_position(position), m_rotation(1, 0, 0, 0)
{
}

CameraTransform::~CameraTransform()
{
}

glm::vec3 CameraTransform::Forward() const
{
    return glm::rotate(m_rotation, ORIENTATION_DEFAULT_FORWARD);
}

glm::vec3 CameraTransform::Up() const
{
    return glm::rotate(m_rotation, ORIENTATION_DEFAULT_UP);
}

glm::vec3 CameraTransform::Right() const
{
    return glm::rotate(m_rotation, ORIENTATION_DEFAULT_RIGHT);
}

glm::vec3 CameraTransform::Position() const
{
    return m_position;
}

glm::quat CameraTransform::Rotation() const
{
    return m_rotation;
}

void CameraTransform::SetPosition(const glm::vec3 & position)
{
    m_position = position;
}

void CameraTransform::Translate(const glm::vec3 & vector)
{
    m_position += vector;
}

void CameraTransform::Rotate(float angle, const glm::vec3 & axis)
{
    m_rotation = glm::rotate(m_rotation, glm::radians(angle), axis);
}

void CameraTransform::Roll(float angle)
{
    Rotate(angle, ORIENTATION_DEFAULT_FORWARD);
}

void CameraTransform::Yaw(float angle)
{
    Rotate(angle, ORIENTATION_DEFAULT_UP);
}

void CameraTransform::Pitch(float angle)
{
    Rotate(angle, ORIENTATION_DEFAULT_RIGHT);
}

glm::mat4 CameraTransform::ModelMatrix(const glm::mat4 & scale) const
{
    return glm::translate(m_position) * glm::toMat4(m_rotation) * scale;
}

glm::mat4 CameraTransform::View() const
{
    return glm::lookAt(m_position, m_position + Forward(), Up());
}
