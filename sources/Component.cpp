#include "VDEngine/Core/Component.h"

using namespace VDEngine;

Component::Component()
{
    m_game_object = nullptr;
    m_transform   = nullptr;
}

Component::~Component()
{
}

GameObject * Component::GetGameObject() const
{
    return (m_game_object);
}

Transform * Component::GetTransform() const
{
    return (m_transform);
}