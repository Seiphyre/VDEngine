#ifndef VDENGINE_COMPONENT_H_
#define VDENGINE_COMPONENT_H_

#include "metaStuff/Meta.h"

namespace VDEngine
{

class GameObject;
class Transform;

class Component
{
    friend auto meta::registerMembers<VDEngine::Component>();
    friend class GameObject;

  public:
    Component();
    virtual ~Component() = 0;

    GameObject * GetGameObject() const;
    Transform *  GetTransform() const;

  protected:
    GameObject * m_game_object;
    Transform *  m_transform;
};

} // namespace VDEngine

template <>
inline auto meta::registerMembers< VDEngine::Component >() 
{
    return meta::members( 
meta::member("m_game_object", &VDEngine::Component::m_game_object),
meta::member("m_transform", &VDEngine::Component::m_transform) 
    );
}

#endif /* VDENGINE_COMPONENT_H_ */