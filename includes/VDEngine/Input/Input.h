#ifndef VDENGINE_INPUT_H_
#define VDENGINE_INPUT_H_

// External libs
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>

// Internal headers
#include "VDEngine/Core/Singleton.h"

namespace VDEngine
{

struct ScrollData
{
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

    glm::vec2 GetScroll() const;

    glm::vec2 GetMousePosition() const;
    glm::vec2 GetMouseDeltaPosition() const;

  private:
    Input();

    glm::vec2 m_mouse_position;
    glm::vec2 m_mouse_delta_position;
    glm::vec2 m_scroll_offset;
};

} // namespace VDEngine

#endif /* VDENGINE_INPUT_H_ */