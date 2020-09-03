#ifndef VDENGINE_COMPONENT_H_
#define VDENGINE_COMPONENT_H_

namespace VDEngine
{

class GameObject;
class Transform;

class Component
{
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

#endif /* VDENGINE_COMPONENT_H_ */