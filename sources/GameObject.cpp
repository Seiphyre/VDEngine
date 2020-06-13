#include "VDEngine/Core/GameObject.h"

using namespace VDEngine;

void GameObject::AddComponent(Component * component)
{
    m_components.push_back(component);
}
void GameObject::RemoveComponent(Component * component)
{
    std::vector<Component *>::iterator it =
        std::find_if(m_components.begin(), m_components.end(), [component](Component * c) { return (component == c); });

    if (it != m_components.end())
        m_components.erase(it);
    else
    {
        std::cout << "Component not found. Cannot be removed from " << name << "." << std::endl;
    }
}

Transform * GameObject::GetTransform() const
{
    return (m_transform);
}