#ifndef CAMERA_H_
#define CAMERA_H_

#include <GLFW/glfw3.h>

#include "VDEngine/Core/Transform.h"

namespace VDEngine
{

class Camera
{
  private:
    Transform * m_transform;
    float       m_fov;
    float       m_near;
    float       m_far;

  public:
    Camera();
    ~Camera();

    Transform * GetTransform() const;
    float       GetFOV() const;

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

    void SetFOV(float fov);
};

} // namespace VDEngine

#endif /* CAMERA_H_ */