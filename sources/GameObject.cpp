#include "VDEngine/Core/GameObject.h"

using namespace VDEngine;

GameObject::GameObject()
{
    name        = "";
    m_parent    = nullptr;
    m_transform = new Transform();
}

GameObject::GameObject(std::vector<Component *> components)
{
    name        = "";
    m_parent    = nullptr;
    m_transform = new Transform();

    for (int i = 0; i < components.size(); i++)
        AddComponent(components[i]);
}

GameObject::~GameObject()
{
    delete (m_transform);
}

void GameObject::AddComponent(Component * component)
{
    component->m_game_object = this;
    component->m_transform   = m_transform;
    m_components.push_back(component);
}
void GameObject::RemoveComponent(Component * component)
{
    std::vector<Component *>::iterator it =
        std::find_if(m_components.begin(), m_components.end(), [component](Component * c) { return (component == c); });

    if (it != m_components.end())
    {
        (*it)->m_game_object = nullptr;
        (*it)->m_transform   = nullptr;
        m_components.erase(it);
    }
    else
    {
        std::cout << "Component not found. Cannot be removed from " << name << "." << std::endl;
    }
}

void GameObject::AttachParent(GameObject * parent)
{

    // Detach the previous parent if any
    if (m_parent != nullptr)
        DetachParent();

    // Attach new parent if not null
    if (parent != nullptr)
    {
        // Update this
        m_parent = parent;
        // Update parent
        parent->m_children.push_back(this);
    }
}

void GameObject::DetachParent()
{
    if (m_parent != nullptr)
    {
        // Update parent
        m_parent->RemoveChild(this);
        // Update this
        m_parent = nullptr;
    }
}

GameObject * GameObject::GetParent() const
{
    return m_parent;
}

Transform * GameObject::GetTransform() const
{
    return (m_transform);
}

void GameObject::AddChild(GameObject * child)
{
    child->m_parent = this;
    m_children.push_back(child);
}

void GameObject::RemoveChild(GameObject * child)
{
    std::vector<GameObject *>::iterator it =
        std::find_if(m_children.begin(), m_children.end(), [child](GameObject * go) { return (child == go); });

    if (it != m_children.end())
    {
        (*it)->m_parent = nullptr;
        m_children.erase(it);
    }
    else
    {
        std::cout << "Child not found. Cannot be removed from " << name << "." << std::endl;
    }
}