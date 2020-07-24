#include "FPSCameraController.h"

using namespace VDEngine;

FPSCameraController::FPSCameraController(Camera * camera)
{
    m_camera = camera;

    m_rotation_sensibility = 0.05f;
    m_move_speed           = 5.0f;

    Vector3 rotation = camera->GetTransform()->rotation.GetEuler();

    rot_x = rotation.x;
    rot_y = rotation.y;
}

FPSCameraController::~FPSCameraController()
{
}

void FPSCameraController::Update()
{
    // -- MOVE FORWARD --------------------
    if (Input::getInstance()->GetKeyDown(GLFW_KEY_W))
    {
        Vector3 view_forward = m_camera->GetTransform()->GetForwardDir();
        float   speed        = m_move_speed * (float)Time::GetDeltaTime();

        // std::cout << m_camera->GetTransform()->position << std::endl;
        // std::cout << m_camera->GetTransform()->position + view_forward << std::endl << std::endl;

        m_camera->GetTransform()->Translate(view_forward * speed);
    }
    // -- MOVE BACKWARD --------------------
    if (Input::getInstance()->GetKeyDown(GLFW_KEY_S))
    {
        Vector3 view_forward = m_camera->GetTransform()->GetForwardDir();
        float   speed        = m_move_speed * (float)Time::GetDeltaTime();

        m_camera->GetTransform()->Translate(-1.0f * view_forward * speed);
    }

    // -- MOVE LEFT --------------------
    if (Input::getInstance()->GetKeyDown(GLFW_KEY_A))
    {
        Vector3 view_right = m_camera->GetTransform()->GetRightDir();
        float   speed      = m_move_speed * (float)Time::GetDeltaTime();

        m_camera->GetTransform()->Translate(-1.0f * view_right * speed);
    }

    // -- MOVE RIGHT --------------------
    if (Input::getInstance()->GetKeyDown(GLFW_KEY_D))
    {
        Vector3 view_right = m_camera->GetTransform()->GetRightDir();
        float   speed      = m_move_speed * (float)Time::GetDeltaTime();

        m_camera->GetTransform()->Translate(view_right * speed);
    }

    // -- MOVE DOWN --------------------
    if (Input::getInstance()->GetKeyDown(GLFW_KEY_Q))
    {
        Vector3 view_up = m_camera->GetTransform()->GetUpDir();
        float   speed   = m_move_speed * (float)Time::GetDeltaTime();

        m_camera->GetTransform()->Translate(-1.0f * view_up * speed);
    }

    // -- MOVE UP ----------------------
    if (Input::getInstance()->GetKeyDown(GLFW_KEY_E))
    {
        Vector3 view_up = m_camera->GetTransform()->GetUpDir();
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
        // https://gamedev.stackexchange.com/questions/136174/im-rotating-an-object-on-two-axes-so-why-does-it-keep-twisting-around-the-thir
        // https://docs.godotengine.org/fr/stable/tutorials/3d/using_transforms.html#axis-order
        // --> problem if X rotate before Y (OK: ZYX, YXZ // KO: XYZ, ZXY)

        Vector2 delta_pos = Input::getInstance()->GetMouseDeltaPosition();
        delta_pos *= m_rotation_sensibility;

        rot_x += delta_pos.y; // haut: - // bas: +
        rot_y -= delta_pos.x; // droite: - // gauche: +

        // Clamp [0,360[

        if (rot_y < 0.0f)
            rot_y = 360 - rot_y;

        else if (rot_y >= 360.0f)
            rot_y = fmod(rot_y, 360.0f);

        if (rot_x < 0.0f)
            rot_x = 360 - rot_x;

        else if (rot_x >= 360.0f)
            rot_x = fmodf(rot_x, 360.0f);

        // Prevent singularity
        if (rot_x > 89.0f && rot_x <= 180.0f)
            rot_x = 89.0f;

        if (rot_x > 180.0f && rot_x < 271.0f)
            rot_x = 271.0f;

        // -- SOLUTION 1 --------------

        m_camera->GetTransform()->rotation = Quaternion::CreateFromEuler(Vector3(rot_x, rot_y, 0.0f));

        // -- END SOLUTION 1 ----------

        // // -- SOLUTION 2 -------------

        // // Form a view vector using total pitch & yaw as spherical coordinates.
        // auto pitch = to_radians(rot_x);
        // auto yaw   = to_radians(rot_y);

        // Vector3 forward = Vector3(cos(pitch) * sin(yaw), sin(pitch), cos(pitch) * cos(yaw));

        // // Construct an orientation or view matrix pointing in that direction.
        // Quaternion newRotation = Quaternion::LookRotation(forward, Vector3(0, 1, 0));

        // // Apply it to our object.
        // m_camera->GetTransform()->rotation = newRotation;

        // // -- END SOLUTION 2 ----------
    }
}