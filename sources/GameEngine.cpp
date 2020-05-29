#include "VDEngine/Core/GameEngine.h"

VDEngine::GameEngine::GameEngine()
{
}

bool VDEngine::GameEngine::Init()
{
    return true;
    //     glfwInit();

    //     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // #ifdef __APPLE__
    //     MacOS requires the forward compatibility bit to create any core profile context glfwWindowHint(
    //         GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    //     Retina Support glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
    // #endif

    //     Create the windows GLFWwindow * s_window = glfwCreateWindow(800, 600, "VDEngine Game", NULL, NULL);
    //     if (s_window == NULL)
    //     {
    //         std::cout << "Failed to create GLFW window" << std::endl;
    //         glfwTerminate();
    //         return -1;
    //     }
    //     glfwMakeContextCurrent(s_window);

    //     Handle resizing glfwSetFramebufferSizeCallback(s_window, framebuffer_size_callback);

    //     Init GLAD if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    //     {
    //         std::cout << "Failed to initialize GLAD" << std::endl;
    //         const char * description;
    //         int          code = glfwGetError(&description);

    //         if (description)
    //             display_error_message(code, description);

    //         return -1;
    //     }

    //     OpenGL Viewport int width, height;
    //     glfwGetFramebufferSize(s_window, &width, &height);
    //     glViewport(0, 0, width, height);
}