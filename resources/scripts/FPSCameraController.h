#ifndef FPS_CAMERA_CONTROLLER_H_
#define FPS_CAMERA_CONTROLLER_H_

#include <cmath>

#include "VDEngine/Core/Time.h"
#include "VDEngine/Input/Input.h"
#include "VDEngine/Renderer/Camera.h"

class FPSCameraController
{
  public:
    FPSCameraController(VDEngine::Camera * camera);
    ~FPSCameraController();

    void Update();

    VDEngine::Camera * m_camera; // shared
    float              m_rotation_sensibility;
    float              m_move_speed;

    float rot_x;
    float rot_y;
};

#endif /* FPS_CAMERA_CONTROLLER_H_ */