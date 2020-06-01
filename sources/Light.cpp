#include "VDEngine/Renderer/Light.h"

using namespace VDEngine;

Light::Light()
{
    color = glm::vec3(1.0f, 1.0f, 1.0f);

    m_transform = new Transform();
}

Light::Light(const glm::vec3 & light_color)
{
    color = light_color;

    m_transform = new Transform();
}

Light::~Light()
{
    delete m_transform;
}

Transform * Light::GetTransform() const
{
    return (m_transform);
}