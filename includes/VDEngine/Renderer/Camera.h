#ifndef VDENGINE_CAMERA_H_
#define VDENGINE_CAMERA_H_

// External libs
#include <GLFW/glfw3.h>

// Internal headers
#include "VDEngine/Core/Transform.h"
#include "VDEngine/Core/Component.h"
#include "VDEngine/Math/Matrix4.h"
#include "VDEngine/Math/GLMConverter.hpp"
#include <glm/gtx/matrix_decompose.hpp>

namespace VDEngine
{

class Camera : public Component
{
  public:
    Camera();
    Camera(const Camera &) = default;
    ~Camera();

    Camera & operator=(const Camera &) = default;

    float GetFOV() const;

    Matrix4 GetViewMatrix() const;
    Matrix4 GetProjectionMatrix() const;

    void SetFOV(float fov);

  private:
    float m_fov;
    float m_near;
    float m_far;
};

} // namespace VDEngine

#endif /* VDENGINE_CAMERA_H_ */