#ifndef FPS_CAMERA_CONTROLLER_H_
#define FPS_CAMERA_CONTROLLER_H_

#include <cmath>

#include "VDEngine/Time.h"
#include "VDEngine/Input.h"
#include "VDEngine/Camera.h"

class FPSCameraController
{
  public:
    FPSCameraController(VDEngine::Camera * camera);
    ~FPSCameraController();

    void Update();

    VDEngine::Camera * m_camera; // shared
    float              m_rotation_sensibility;
    float              m_move_speed;
};

#endif /* FPS_CAMERA_CONTROLLER_H_ */