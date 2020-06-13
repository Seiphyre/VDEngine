#ifndef VDENGINE_CAMERA_H_
#define VDENGINE_CAMERA_H_

// External libs
#include <GLFW/glfw3.h>

// Internal headers
#include "VDEngine/Core/Transform.h"
#include "VDEngine/Core/Component.h"

namespace VDEngine
{

class Camera : public Component
{
  private:
    float m_fov;
    float m_near;
    float m_far;

  public:
    Camera();
    Camera(const Camera &) = default;
    ~Camera();

    Camera & operator=(const Camera &) = default;

    float GetFOV() const;

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

    void SetFOV(float fov);
};

} // namespace VDEngine

#endif /* VDENGINE_CAMERA_H_ */