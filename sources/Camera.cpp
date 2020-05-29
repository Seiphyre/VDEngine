#include "VDEngine/Renderer/Camera.h"

using namespace VDEngine;

Camera::Camera()
{
    m_transform = new Transform();

    m_fov  = 45.0f;
    m_near = 0.1f;
    m_far  = 100.0f;
}

Camera::~Camera()
{
    delete m_transform;
}

Transform * Camera::GetTransform() const
{
    return (m_transform);
}

float Camera::GetFOV() const
{
    return (m_fov);
}

glm::mat4 Camera::GetViewMatrix() const
{
    glm::mat4 view;
    view =
        glm::lookAt(m_transform->position,
                    m_transform->position + (m_transform->GetForwardDir() * glm::vec3(1.0f, 1.0f, -1.0f)), Y_3D_AXIS);

    return view;
}

glm::mat4 Camera::GetProjectionMatrix() const
{
    GLFWwindow * current_context = glfwGetCurrentContext();
    int          width;
    int          height;

    glfwGetWindowSize(current_context, &width, &height);

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(m_fov), (float)width / (float)height, m_near, m_far);

    return projection;
}

void Camera::SetFOV(float fov)
{
    m_fov = fov;
}