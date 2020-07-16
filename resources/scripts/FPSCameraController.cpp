#include "FPSCameraController.h"

using namespace VDEngine;

FPSCameraController::FPSCameraController(Camera * camera)
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
    if (Input::getInstance()->GetKeyDown(GLFW_KEY_W))
    {
        Vector3 view_forward = m_camera->GetTransform()->GetForwardDir() * Vector3(1.0f, 1.0f, -1.0f);
        float   speed        = m_move_speed * (float)Time::GetDeltaTime();

        m_camera->GetTransform()->Translate(view_forward * speed);
    }
    // -- MOVE BACKWARD --------------------
    if (Input::getInstance()->GetKeyDown(GLFW_KEY_S))
    {
        Vector3 view_forward = m_camera->GetTransform()->GetForwardDir() * Vector3(1.0f, 1.0f, -1.0f);
        float   speed        = m_move_speed * (float)Time::GetDeltaTime();

        m_camera->GetTransform()->Translate(-1.0f * view_forward * speed);
    }

    // -- MOVE LEFT --------------------
    if (Input::getInstance()->GetKeyDown(GLFW_KEY_A))
    {
        Vector3 view_right = m_camera->GetTransform()->GetRightDir() * Vector3(1.0f, 1.0f, -1.0f);
        float   speed      = m_move_speed * (float)Time::GetDeltaTime();

        m_camera->GetTransform()->Translate(-1.0f * view_right * speed);
    }

    // -- MOVE RIGHT --------------------
    if (Input::getInstance()->GetKeyDown(GLFW_KEY_D))
    {
        Vector3 view_right = m_camera->GetTransform()->GetRightDir() * Vector3(1.0f, 1.0f, -1.0f);
        float   speed      = m_move_speed * (float)Time::GetDeltaTime();

        m_camera->GetTransform()->Translate(view_right * speed);
    }

    // -- MOVE DOWN --------------------
    if (Input::getInstance()->GetKeyDown(GLFW_KEY_Q))
    {
        Vector3 view_up = m_camera->GetTransform()->GetUpDir() * Vector3(1.0f, 1.0f, -1.0f);
        float   speed   = m_move_speed * (float)Time::GetDeltaTime();

        m_camera->GetTransform()->Translate(-1.0f * view_up * speed);
    }

    // -- MOVE UP ----------------------
    if (Input::getInstance()->GetKeyDown(GLFW_KEY_E))
    {
        Vector3 view_up = m_camera->GetTransform()->GetUpDir() * Vector3(1.0f, 1.0f, -1.0f);
        float   speed   = m_move_speed * (float)Time::GetDeltaTime();

        m_camera->GetTransform()->Translate(view_up * speed);
    }

    // -- ZOOM IN/OUT -------------------------
    if (Input::getInstance()->GetScroll().y != 0.0f)
    {
        float scroll_delta = Input::getInstance()->GetScroll().y;
        float fov          = m_camera->GetFOV();

        fov -= scroll_delta;

        if (fov < 1.0f)
            fov = 1.0f;
        if (fov > 45.0f)
            fov = 45.0f;

        m_camera->SetFOV(fov);
    }

    // -- ROTATE Y/X AXIS ---------------------
    if (Input::getInstance()->GetMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
    {
        Vector2 delta_pos = Input::getInstance()->GetMouseDeltaPosition();
        delta_pos *= m_rotation_sensibility;

        Vector3 rotation = m_camera->GetTransform()->rotation.GetEuler();

        rotation.x += delta_pos.y;
        rotation.y += delta_pos.x;

        // if (rotation.x > 89.0f && rotation.x <= 180.0f)
        //     rotation.x = 89.0f;

        // if (rotation.x > 180.0f && rotation.x < 271.0f)
        //     rotation.x = 271.0f;

        // std::cout << "x: " << rotation.x << " y: " << rotation.y << std::endl;

        m_camera->GetTransform()->rotation = Quaternion::CreateFromEuler(rotation);
    }
}