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
    glm::mat4 view;
    view = glm::lookAt(to_glm_vec3(m_transform->position),
                       to_glm_vec3(m_transform->position) +
                           (to_glm_vec3(m_transform->GetForwardDir()) * glm::vec3(1.0f, 1.0f, -1.0f)),
                       glm::vec3(0.0f, 1.0f, 0.0f));

    return to_matrix4(view);

    // ---------------

    // // https://www.3dgep.com/understanding-the-view-matrix/#Look_At_Camera

    // // OpenGL view is looking toward -Z
    // // -- Flip Z --
    // Quaternion view_orientation;
    // Vector3    view_forward = m_transform->rotation.GetForward();

    // view_forward.Scale(Vector3(1.0f, 1.0f, -1.0f));
    // view_orientation = Quaternion::LookRotation(view_forward);

    // // -- compose matrix --

    // Matrix4 orientation_mat = Matrix4::CreateRotationMatrix(view_orientation);
    // Matrix4 translation_mat = Matrix4::CreateTranslationMatrix(-m_transform->position);

    // return orientation_mat * translation_mat;
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