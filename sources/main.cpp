#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <unistd.h>
#include <mach-o/dyld.h>

#include "VDEngine/Renderer/Camera.h"
#include "VDEngine/Renderer/Light.h"
#include "VDEngine/Renderer/ShaderManager.h"
#include "VDEngine/Renderer/TextureManager.h"
#include "VDEngine/Renderer/MaterialManager.h"
#include "VDEngine/Renderer/MeshRenderer.h"
#include "VDEngine/Renderer/MeshFactory.h"

#include "VDEngine/Core/GameEngine.h"
#include "VDEngine/Core/FileHandler.h"
#include "VDEngine/Core/Time.h"
#include "VDEngine/Input/Input.h"

#include "../resources/scripts/FPSCameraController.h"

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(int argc, char * argv[])
{
    // -- ENGINE INITIALIZATION -------------------------------------

    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);

    // Create the windows
    GLFWwindow * s_window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (s_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(s_window);

    // Handle resizing
    glfwSetFramebufferSizeCallback(s_window, framebuffer_size_callback);

    // Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // OpenGL Viewport
    int width, height;
    glfwGetFramebufferSize(s_window, &width, &height);
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    // -- LOAD RESOURCES -----------------------------------------------

    // Load Shaders

    VDEngine::Shader * lit_multi_text_shader =
        VDEngine::ShaderManager::getInstance()->LoadShader("Lit_Text_Default.vert", "Lit_Text_Default.frag");

    // [...]

    // Load Textures

    VDEngine::Texture * measurement_tex = VDEngine::TextureManager::getInstance()->LoadTexture("measurement_floor.png");
    VDEngine::Texture * wooden_container_tex = VDEngine::TextureManager::getInstance()->LoadTexture("container2.png");
    VDEngine::Texture * wooden_container_spec =
        VDEngine::TextureManager::getInstance()->LoadTexture("container2_specular.png");
    // VDEngine::Texture * emoji_tex       = VDEngine::TextureManager::getInstance()->LoadTexture("awesomeface.png");

    // [...]

    // Load Materials

    // floor->AddTexture(VDEngine::TextureManager::getInstance()->GetTexture(measurement->GetUUID()));
    // floor->AddTexture(VDEngine::TextureManager::getInstance()->GetTexture(emoji->GetUUID()));

    VDEngine::Material * floor_mat = VDEngine::MaterialManager::getInstance()->LoadMaterial(lit_multi_text_shader);
    floor_mat->shininess           = 128.0f;
    floor_mat->diffuse_map         = measurement_tex;

    VDEngine::Material * cube_mat = VDEngine::MaterialManager::getInstance()->LoadMaterial(lit_multi_text_shader);
    cube_mat->shininess           = 128.0f;
    cube_mat->diffuse_map         = wooden_container_tex;
    cube_mat->specular_map        = wooden_container_spec;

    VDEngine::Material * light_mat =
        VDEngine::MaterialManager::getInstance()->LoadMaterial(VDEngine::ShaderManager::getInstance()->GetShader());
    light_mat->diffuse_color = glm::vec3(1.0, 1.0, 0.0);

    // [...]

    // -- CREATE SCENE --------------------------------------------------

    // Create objects
    VDEngine::MeshRender * floor =
        new VDEngine::MeshRender(VDEngine::MeshFactory::getInstance()->CreatePlane(), floor_mat);

    floor->GetTransform()->Rotate(-90.0f, WORLD_RIGHT);
    floor->GetTransform()->scale = glm::vec3(10.0f, 10.0f, 1.0f);

    VDEngine::MeshRender * cube =
        new VDEngine::MeshRender(VDEngine::MeshFactory::getInstance()->CreateCube(), cube_mat);

    cube->GetTransform()->Translate(glm::vec3(0.0f, 0.5f, 0.0f));
    // cube->GetTransform()->LookAt(glm::vec3(0.0f, 0.5f, 0.0f));
    // cube->GetTransform()->Rotate(glm::vec3(0.0f, -45.0f, 0.0f));

    VDEngine::MeshRender * light_gizmo =
        new VDEngine::MeshRender(VDEngine::MeshFactory::getInstance()->CreateCube(), light_mat);

    light_gizmo->GetTransform()->Translate(glm::vec3(0.0f, 1.0f, 0.0f));
    light_gizmo->GetTransform()->scale = glm::vec3(0.5f, 0.5f, 0.5f);

    // Camera ----------

    VDEngine::Camera * camera = new VDEngine::Camera();

    camera->GetTransform()->Translate(glm::vec3(0.0f, 1.0f, 5.0f));
    camera->GetTransform()->Rotate(45.0f, WORLD_UP);

    FPSCameraController * camera_controller = new FPSCameraController(camera);

    // Light -----------

    VDEngine::Light * light = new VDEngine::Light(glm::vec3(1.0f, 1.0f, 1.0f));
    light->GetTransform()->Translate(glm::vec3(0.0f, 1.0f, 0.0f));

    // -- GAME LOOP ------------------------------------------------------

    VDEngine::Time::Update();

    while (!glfwWindowShouldClose(s_window))
    {
        // Input ----------------------------

        // Update
        VDEngine::Input::getInstance()->Update();

        // -- QUIT APP --------------------
        if (VDEngine::Input::getInstance()->GetKeyDown(GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(s_window, true);

        // User update ---------------------------

        camera_controller->Update();

        // cube->GetTransform()->Rotate((float)VDEngine::Time::GetDeltaTime() * 50.0f, glm::vec3(0.0f, 1.0f, 0.0f));

        const float radius = 3.0f;
        float       camX   = sin((float)VDEngine::Time::GetTime() * 0.5f) * radius;
        float       camZ   = cos((float)VDEngine::Time::GetTime() * 0.5f) * radius;

        light_gizmo->GetTransform()->position = glm::vec3(camX, 2.5f, camZ);
        light->GetTransform()->position       = glm::vec3(camX, 2.5f, camZ);
        // OU rotane 180 sur Y ?
        // camera->GetTransform()->LookAt(
        //     camera->GetTransform()->position +
        //     ((glm::vec3(0.0f, 0.5f, 0.0f) - camera->GetTransform()->position) * glm::vec3(1.0f, 1.0f, -1.0f)));

        // Renderer ------------------------------

        // Clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw

        cube->Draw(camera, light);
        floor->Draw(camera, light);
        light_gizmo->Draw(camera, light);

        // Display
        glfwSwapBuffers(s_window);

        VDEngine::Time::Update();
    }

    glfwTerminate();

    return 0;
}