#include "VDEngine/Input.h"

VDEngine::Input::Input()
{
    GLFWwindow * current_context = glfwGetCurrentContext();

    // Input Mode Settings ------------

    glfwSetInputMode(current_context, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetInputMode(current_context, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    // glfwSetInputMode(current_context, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Init Mouse Position ------------

    int width;
    int height;
    glfwGetWindowSize(current_context, &width, &height);

    m_mouse_position       = glm::vec2((float)width / 2.0f, (float)height / 2.0f);
    m_mouse_delta_position = glm::vec2((float)width / 2.0f, (float)height / 2.0f);
    m_scroll_offset        = glm::vec2(0.0f, 0.0f);

    // Scroll -------------------------
    auto callback = [](GLFWwindow * window, double xoffset, double yoffset) -> void {
        ScrollData * scrollData  = nullptr;
        void *       userPointer = glfwGetWindowUserPointer(window);

        // If already exist ...
        if (userPointer != NULL && userPointer != nullptr)
        {
            // ... Update values
            scrollData = static_cast<ScrollData *>(userPointer);
            if (scrollData)
            {
                scrollData->xoffset = xoffset;
                scrollData->yoffset = yoffset;
            }
        }

        // Else, we create it
        if (scrollData == nullptr)
        {
            scrollData = new ScrollData();

            scrollData->xoffset = xoffset;
            scrollData->yoffset = yoffset;
        }

        glfwSetWindowUserPointer(window, scrollData);
    };

    glfwSetScrollCallback(current_context, callback);
}

void VDEngine::Input::Update()
{
    glfwPollEvents();

    // Update Mouse events ---------------
    GLFWwindow * current_context = glfwGetCurrentContext();
    double       xpos;
    double       ypos;

    glfwGetCursorPos(current_context, &xpos, &ypos);

    m_mouse_delta_position = glm::vec2(xpos - m_mouse_position.x, ypos - m_mouse_position.y);
    m_mouse_position       = glm::vec2(xpos, ypos);

    // Update Scroll event --------------
    void * data = glfwGetWindowUserPointer(current_context);

    if (data != NULL && data != nullptr)
    {
        // Try to get Scroll Data
        ScrollData * scrollData = static_cast<ScrollData *>(data);
        if (scrollData)
        {
            m_scroll_offset = glm::vec2(scrollData->xoffset, scrollData->yoffset);
        }

        // Free ptr
        delete (data);
        glfwSetWindowUserPointer(current_context, NULL);
    }
    else
    {
        m_scroll_offset = glm::vec2(0.0f, 0.0f);
    }
}

bool VDEngine::Input::GetKeyUp(int key_code) const
{
    GLFWwindow * current_context = glfwGetCurrentContext();

    if (glfwGetKey(current_context, key_code) == GLFW_RELEASE)
        return true;

    return false;
}

bool VDEngine::Input::GetKeyDown(int key_code) const
{
    GLFWwindow * current_context = glfwGetCurrentContext();

    if (glfwGetKey(current_context, key_code) == GLFW_PRESS)
        return true;

    return false;
}

bool VDEngine::Input::GetMouseButtonUp(int button_code) const
{
    GLFWwindow * current_context = glfwGetCurrentContext();

    if (glfwGetMouseButton(current_context, button_code) == GLFW_RELEASE)
        return true;

    return false;
}
bool VDEngine::Input::GetMouseButtonDown(int button_code) const
{
    GLFWwindow * current_context = glfwGetCurrentContext();

    if (glfwGetMouseButton(current_context, button_code) == GLFW_PRESS)
        return true;

    return false;
}

bool VDEngine::Input::GetScrollUp() const
{
    if (m_scroll_offset.y > 0)
        return true;

    return false;
}

bool VDEngine::Input::GetScrollDown() const
{
    if (m_scroll_offset.y < 0)
        return true;

    return false;
}

glm::vec2 VDEngine::Input::GetScroll() const
{
    return m_scroll_offset;
}

glm::vec2 VDEngine::Input::GetMousePosition() const
{
    return m_mouse_position;
}
glm::vec2 VDEngine::Input::GetMouseDeltaPosition() const
{
    return m_mouse_delta_position;
}