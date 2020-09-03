

#ifndef VDENGINE_META_HEADER
#define VDENGINE_META_HEADER

#include "metaStuff/Meta.h"

#endif /* VDENGINE_META_HEADER */

#ifndef VDENGINE_INPUT_H_
#define VDENGINE_INPUT_H_

// External libs
#include "GLFW/glfw3.h"
// #include <glm/glm.hpp>

// Internal headers
#include "VDEngine/Core/Singleton.h"
#include "VDEngine/Math/Vector2.h"

namespace VDEngine
{

struct ScrollData
{
    friend auto meta::registerMembers<VDEngine::ScrollData>();
    
    double xoffset;
    double yoffset;
};

class Input : public Singleton<Input>
{
    friend class Singleton<Input>;

  public:
    ~Input();

    void Update();

    bool GetKeyUp(int key_code) const;
    bool GetKeyDown(int key_code) const;

    bool GetMouseButtonUp(int button_code) const;
    bool GetMouseButtonDown(int button_code) const;

    bool GetScrollUp() const;
    bool GetScrollDown() const;

    Vector2 GetScroll() const;

    Vector2 GetMousePosition() const;
    Vector2 GetMouseDeltaPosition() const;

  private:
    Input();

    Vector2 m_mouse_position;
    Vector2 m_mouse_delta_position;
    Vector2 m_scroll_offset;
};

} // namespace VDEngine

#endif /* VDENGINE_INPUT_H_ */

#ifndef META_REGISTER_VDENGINE_SCROLLDATA
#define META_REGISTER_VDENGINE_SCROLLDATA

template <>
inline auto meta::registerMembers< VDEngine::ScrollData >() 
{
    return meta::members( 
meta::member("xoffset", &VDEngine::ScrollData::xoffset),
meta::member("yoffset", &VDEngine::ScrollData::yoffset) 
    );
}

#endif /* META_REGISTER_VDENGINE_SCROLLDATA */

