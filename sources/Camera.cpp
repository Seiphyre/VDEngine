#include "VDEngine/Renderer/Camera.h"

using namespace VDEngine;

Camera::Camera()
{
    m_fov  = 45.0f;
    m_near = 0.1f;
    m_far  = 100.0f;
}

Camera::~Camera()
{
}

float Camera::GetFOV() const
{
    return (m_fov);
}

Matrix4 Camera::GetViewMatrix() const
{
    Matrix4 view_mat;

    Vector3 eye = m_transform->position;

    Vector3 forward = m_transform->GetForwardDir();
    Vector3 right(Vector3::Cross(forward, /*Vector3::VecPosY()*/ m_transform->GetUpDir()).GetNormalized());
    Vector3 up(Vector3::Cross(right, forward));

    // M = inverse(R) * -T

    view_mat(0, 0) = right.x;
    view_mat(1, 0) = right.y;
    view_mat(2, 0) = right.z;
    view_mat(0, 1) = up.x;
    view_mat(1, 1) = up.y;
    view_mat(2, 1) = up.z;
    view_mat(0, 2) = -forward.x; // Convert from fwd: +Z to fwd: -Z
    view_mat(1, 2) = -forward.y; // Convert from fwd: +Z to fwd: -Z
    view_mat(2, 2) = -forward.z; // Convert from fwd: +Z to fwd: -Z

    view_mat(3, 0) = -Vector3::Dot(right, eye);
    view_mat(3, 1) = -Vector3::Dot(up, eye);
    view_mat(3, 2) = Vector3::Dot(forward, eye);

    return view_mat;

    // ---------------------------------------------------

    // glm::mat4 view;
    // view = glm::lookAt(to_glm_vec3(m_transform->position),
    //                    to_glm_vec3(m_transform->position) + to_glm_vec3(m_transform->GetForwardDir()),
    //                    to_glm_vec3(m_transform->GetUpDir()));

    // return to_matrix4(view);
}

Matrix4 Camera::GetProjectionMatrix() const
{
    GLFWwindow * current_context = glfwGetCurrentContext();
    int          width;
    int          height;

    glfwGetWindowSize(current_context, &width, &height);

    return Matrix4::CreatePerspective(m_fov, (float)width / (float)height, m_near, m_far);
}

void Camera::SetFOV(float fov)
{
    m_fov = fov;
}