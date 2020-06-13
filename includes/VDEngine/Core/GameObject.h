#ifndef VDENGINE_GAME_OBJECT_H_
#define VDENGINE_GAME_OBJECT_H_

// C++ Standard libs
#include <vector>

// Internal headers
#include "VDEngine/Core/Component.h"
#include "VDEngine/Core/Transform.h"

namespace VDEngine
{

class GameObject
{
  public:
    GameObject();
    GameObject(std::vector<Component *> components);
    ~GameObject();

    void AddComponent(Component * component);
    void RemoveComponent(Component * component);
    void AttachParent(GameObject * parent);
    void DetachParent();

    Transform *            GetTransform() const;
    template <class T> T * GetComponent()
    {
        static_assert(std::is_base_of<Component, T>::value,
                      "Error: T in GameObject::GetComponent is not base of Component.");

        // Transform ??

        std::vector<Component *>::iterator it = m_components.begin();
        for (int i = 0; i < m_components.size(); i++)
        {
            T * component = dynamic_cast<T *>(*it);
            if (component)
            {
                return component;
            }
            it++;
        }

        return nullptr;
    }

    std::string name;

  private:
    void RemoveChild(GameObject * child);

    GameObject *              m_parent;
    Transform *               m_transform;
    std::vector<GameObject *> m_children;
    std::vector<Component *>  m_components;
};

} // namespace VDEngine

#endif /* VDENGINE_GAME_OBJECT_H_ */