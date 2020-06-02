#ifndef VDENGINE_LIGHT_H_
#define VDENGINE_LIGHT_H_

// External libs
#include <glm/glm.hpp>

// Internal headers
#include "VDEngine/Core/Transform.h"

namespace VDEngine
{

enum e_LightType : int
{
    DIRECTIONAL = 0,
    SPOT        = 1,
    POINT       = 2
};

class Light
{
  public:
    Light();
    Light(e_LightType light_type, const glm::vec3 & light_color);
    ~Light();

    Transform * GetTransform() const;

    glm::vec3 color;

    e_LightType type;

    // Point
    float att_constant;
    float att_linear;
    float att_quadratic;

    // Spot
    float inner_cutOff;
    float outer_cutOff;

  private:
    Transform * m_transform;
};

} // namespace VDEngine

#endif /* VDENGINE_LIGHT_H_ */