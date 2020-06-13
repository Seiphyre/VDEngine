#ifndef VDENGINE_COMPONENT_H_
#define VDENGINE_COMPONENT_H_

// Internal headers
#include "VDEngine/Core/Transform.h"

namespace VDEngine
{

class GameObject;

class Component
{

    friend class GameObject;

  public:
    Component();
    ~Component();

    GameObject * GetGameObject() const;
    Transform *  GetTransform() const;

  protected:
    GameObject * m_game_object;
    Transform *  m_transform;
};

} // namespace VDEngine

#endif /* VDENGINE_COMPONENT_H_ */