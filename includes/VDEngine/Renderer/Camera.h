

#ifndef VDENGINE_META_HEADER
#define VDENGINE_META_HEADER

#include "metaStuff/Meta.h"

#endif /* VDENGINE_META_HEADER */

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
    friend auto meta::registerMembers<VDEngine::Camera>();
    
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

#ifndef META_REGISTER_VDENGINE_CAMERA
#define META_REGISTER_VDENGINE_CAMERA

template <>
inline auto meta::registerMembers< VDEngine::Camera >() 
{
    return std::tuple_cat(
        meta::getMembers< VDEngine::Component >(),
        meta::members(
meta::member("m_fov", &VDEngine::Camera::m_fov),
meta::member("m_near", &VDEngine::Camera::m_near),
meta::member("m_far", &VDEngine::Camera::m_far) 
    ));
}

#endif /* META_REGISTER_VDENGINE_CAMERA */

