

#ifndef VDENGINE_META_HEADER
#define VDENGINE_META_HEADER

#include "metaStuff/Meta.h"

#endif /* VDENGINE_META_HEADER */

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
    friend auto meta::registerMembers<VDEngine::Light>();
    
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

#ifndef META_REGISTER_VDENGINE_LIGHT
#define META_REGISTER_VDENGINE_LIGHT

template <>
inline auto meta::registerMembers< VDEngine::Light >() 
{
    return std::tuple_cat(
        meta::getMembers< VDEngine::Component >(),
        meta::members(
meta::member("color", &VDEngine::Light::color),
meta::member("type", &VDEngine::Light::type),
meta::member("att_constant", &VDEngine::Light::att_constant),
meta::member("att_linear", &VDEngine::Light::att_linear),
meta::member("att_quadratic", &VDEngine::Light::att_quadratic),
meta::member("inner_cutOff", &VDEngine::Light::inner_cutOff),
meta::member("outer_cutOff", &VDEngine::Light::outer_cutOff) 
    ));
}

#endif /* META_REGISTER_VDENGINE_LIGHT */

