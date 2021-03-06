#include "VDEngine/Renderer/Light.h"

using namespace VDEngine;

Light::Light()
{
    color = glm::vec3(1.0f, 1.0f, 1.0f);

    type = DIRECTIONAL;

    // Range 32
    att_constant  = 1.0f;
    att_linear    = 0.14f;
    att_quadratic = 0.07f;

    inner_cutOff = 25.0f;
    outer_cutOff = 35.0f;
}

Light::Light(e_LightType light_type, const glm::vec3 & light_color)
{
    color = light_color;

    type = light_type;

    // Range 32
    att_constant  = 1.0f;
    att_linear    = 0.14f;
    att_quadratic = 0.07f;

    inner_cutOff = 25.0f;
    outer_cutOff = 35.0f;
}

Light::~Light()
{
}