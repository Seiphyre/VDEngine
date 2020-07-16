#ifndef VDENGINE_LIGHT_H_
#define VDENGINE_LIGHT_H_

// External libs
// #include <glm/glm.hpp>

// Internal headers
#include "VDEngine/Core/Component.h"
#include "VDEngine/Math/Vectors.hpp"

namespace VDEngine
{

enum e_LightType : int
{
    DIRECTIONAL = 0,
    SPOT        = 1,
    POINT       = 2
};

class Light : public Component
{
  public:
    Light();
    Light(e_LightType light_type, const Vector3 & light_color);
    ~Light();

    Vector3 color;

    e_LightType type;

    // Point
    float att_constant;
    float att_linear;
    float att_quadratic;

    // Spot
    float inner_cutOff;
    float outer_cutOff;
};

} // namespace VDEngine

#endif /* VDENGINE_LIGHT_H_ */