#include "FPSCameraController.h"

FPSCameraController::FPSCameraController(VDEngine::Camera * camera)
{
    m_camera = camera;

    m_rotation_sensibility = 0.05f;
    m_move_speed           = 5.0f;
}

FPSCameraController::~FPSCameraController()
{
}

void FPSCameraController::Update()
{
    // -- MOVE FORWARD --------------------
    if (VDEngine::Input::getInstance()->GetKeyDown(GLFW_KEY_W))
    {
        glm::vec3 view_forward = m_camera->GetTransform()->GetForwardDir() * glm::vec3(1.0f, 1.0f, -1.0f);
        float     speed        = m_move_speed * (float)VDEngine::Time::GetDeltaTime();

        m_camera->GetTransform()->Translate(view_forward * speed);
    }
    // -- MOVE BACKWARD --------------------
    if (VDEngine::Input::getInstance()->GetKeyDown(GLFW_KEY_S))
    {
        glm::vec3 view_forward = m_camera->GetTransform()->GetForwardDir() * glm::vec3(1.0f, 1.0f, -1.0f);
        float     speed        = m_move_speed * (float)VDEngine::Time::GetDeltaTime();

        m_camera->GetTransform()->Translate(-1.0f * view_forward * speed);
    }

    // -- MOVE LEFT --------------------
    if (VDEngine::Input::getInstance()->GetKeyDown(GLFW_KEY_A))
    {
        glm::vec3 view_right = m_camera->GetTransform()->GetRightDir() * glm::vec3(1.0f, 1.0f, -1.0f);
        float     speed      = m_move_speed * (float)VDEngine::Time::GetDeltaTime();

        m_camera->GetTransform()->Translate(-1.0f * view_right * speed);
    }

    // -- MOVE RIGHT --------------------
    if (VDEngine::Input::getInstance()->GetKeyDown(GLFW_KEY_D))
    {
        glm::vec3 view_right = m_camera->GetTransform()->GetRightDir() * glm::vec3(1.0f, 1.0f, -1.0f);
        float     speed      = m_move_speed * (float)VDEngine::Time::GetDeltaTime();

        m_camera->GetTransform()->Translate(view_right * speed);
    }

    // -- MOVE DOWN --------------------
    if (VDEngine::Input::getInstance()->GetKeyDown(GLFW_KEY_Q))
    {
        glm::vec3 view_up = m_camera->GetTransform()->GetUpDir() * glm::vec3(1.0f, 1.0f, -1.0f);
        float     speed   = m_move_speed * (float)VDEngine::Time::GetDeltaTime();

        m_camera->GetTransform()->Translate(-1.0f * view_up * speed);
    }

    // -- MOVE UP ----------------------
    if (VDEngine::Input::getInstance()->GetKeyDown(GLFW_KEY_E))
    {
        glm::vec3 view_up = m_camera->GetTransform()->GetUpDir() * glm::vec3(1.0f, 1.0f, -1.0f);
        float     speed   = m_move_speed * (float)VDEngine::Time::GetDeltaTime();

        m_camera->GetTransform()->Translate(view_up * speed);
    }

    // -- ZOOM IN/OUT -------------------------
    if (VDEngine::Input::getInstance()->GetScroll().y != 0.0f)
    {
        float scroll_delta = VDEngine::Input::getInstance()->GetScroll().y;
        float fov          = m_camera->GetFOV();

        fov -= scroll_delta;

        if (fov < 1.0f)
            fov = 1.0f;
        if (fov > 45.0f)
            fov = 45.0f;

        m_camera->SetFOV(fov);
    }

    // -- ROTATE Y/X AXIS ---------------------
    if (VDEngine::Input::getInstance()->GetMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::vec2 delta_pos = VDEngine::Input::getInstance()->GetMouseDeltaPosition();
        delta_pos *= m_rotation_sensibility;

        glm::vec3 rotation = m_camera->GetTransform()->GetEulerRotation();

        rotation.x += delta_pos.y;
        rotation.y += delta_pos.x;

        if (rotation.x > 89.0f && rotation.x <= 180.0f)
            rotation.x = 89.0f;

        if (rotation.x > 180.0f && rotation.x < 271.0f)
            rotation.x = 271.0f;

        // std::cout << "x: " << rotation.x << " y: " << rotation.y << std::endl;

        m_camera->GetTransform()->SetEulerRotation(rotation);
    }
}