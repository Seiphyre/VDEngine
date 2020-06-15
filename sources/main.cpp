#include "glad/glad.h"
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

#include "VDEngine/Core/GameObject.h"
#include "VDEngine/Core/GameEngine.h"
#include "VDEngine/Core/FileHandler.h"
#include "VDEngine/Core/Time.h"
#include "VDEngine/Input/Input.h"

#include "VDEngine/Renderer/ModelLoader.h"
#include "VDEngine/Renderer/Model.h"

#include "../resources/scripts/FPSCameraController.h"

using namespace VDEngine;

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

    // Load Shaders --

    ShaderManager * shader_manager = ShaderManager::getInstance();

    Shader * lit_default_shader   = shader_manager->LoadShader("Lit_Default.vert", "Lit_Default.frag");
    Shader * unlit_default_shader = shader_manager->LoadShader("Unlit_Default.vert", "Unlit_Default.frag");

    // Load Textures --

    Texture * measurement_diff      = TextureManager::getInstance()->LoadTexture("measurement_floor.png");
    Texture * wooden_container_diff = TextureManager::getInstance()->LoadTexture("container2.png");
    Texture * wooden_container_spec = TextureManager::getInstance()->LoadTexture("container2_specular.png");
    // Texture * emoji_tex       = TextureManager::getInstance()->LoadTexture("awesomeface.png");

    // Load Materials --
    MaterialManager * material_manager = MaterialManager::getInstance();

    Material * floor_mat   = material_manager->LoadMaterial(lit_default_shader);
    floor_mat->shininess   = 128.0f;
    floor_mat->diffuse_map = measurement_diff;

    Material * cube_mat    = material_manager->LoadMaterial(lit_default_shader);
    cube_mat->shininess    = 128.0f;
    cube_mat->diffuse_map  = wooden_container_diff;
    cube_mat->specular_map = wooden_container_spec;

    Material * light_mat     = material_manager->LoadMaterial(unlit_default_shader);
    light_mat->diffuse_color = glm::vec3(1.0, 1.0, 1.0);

    Material * light2_mat    = material_manager->LoadMaterial(unlit_default_shader);
    light_mat->diffuse_color = glm::vec3(1.0, 1.0, 1.0);

    // Models / Meshes --

    Model * backpack_model = ModelLoader::getInstance()->LoadModel("backpack.obj");

    Mesh * plane_mesh = MeshFactory::getInstance()->CreatePlane();
    Mesh * cube_mesh  = MeshFactory::getInstance()->CreateCube();

    // -- CREATE SCENE --------------------------------------------------

    // mesh renderers

    MeshRender * floor_renderer        = new MeshRender(plane_mesh, floor_mat);
    MeshRender * cube_renderer         = new MeshRender(cube_mesh, cube_mat);
    MeshRender * light_gizmo_renderer  = new MeshRender(cube_mesh, light_mat);
    MeshRender * light2_gizmo_renderer = new MeshRender(cube_mesh, light2_mat);

    // Camera ----------
    VDEngine::Camera * camera = new VDEngine::Camera();

    // Light -----------
    VDEngine::Light * light = new Light(POINT, glm::vec3(1.0f, 1.0f, 1.0f));
    light->att_linear       = 0.045f;
    light->att_quadratic    = 0.0075f;

    VDEngine::Light * light2 = new Light(SPOT, glm::vec3(1.0f, 1.0f, 1.0f));
    light2->att_linear       = 0.045f;
    light2->att_quadratic    = 0.0075f;
    light2->inner_cutOff     = 15;
    light2->outer_cutOff     = 20;

    // VDEngine::Light * light3 = new Light(DIRECTIONAL, glm::vec3(1.0f, 1.0f, 1.0f));

    // Behaviours ---
    FPSCameraController * camera_controller = new FPSCameraController(camera);

    // -- Game Objects ----------

    GameObject * backpack_go                         = backpack_model->CreateGameObjectFromModel();
    backpack_go->GetComponent<Transform>()->position = glm::vec3(0.0, 1.0, 1.0);
    backpack_go->GetTransform()->scale               = glm::vec3(0.5, 0.5, 0.5);
    backpack_go->GetTransform()->Rotate(-30.0, 0.0, 0.0);
    backpack_go->name = "backpack_root";

    GameObject * floor_go = new GameObject({floor_renderer});
    floor_go->name        = "floor";
    floor_go->GetTransform()->Rotate(-90.0f, WORLD_RIGHT);
    floor_go->GetTransform()->scale = glm::vec3(10.0f, 10.0f, 1.0f);

    GameObject * cube_go = new GameObject({cube_renderer});
    cube_go->name        = "cube";
    cube_go->GetTransform()->Translate(glm::vec3(0.0f, 0.5f, 0.0f));
    // cube->GetTransform()->LookAt(glm::vec3(0.0f, 0.5f, 0.0f));
    // cube->GetTransform()->Rotate(glm::vec3(0.0f, -45.0f, 0.0f));

    GameObject * Camera_go = new GameObject({camera});
    Camera_go->name        = "main_camera";
    Camera_go->GetTransform()->Translate(glm::vec3(0.0f, 1.0f, 5.0f));
    Camera_go->GetTransform()->Rotate(45.0f, WORLD_UP);

    GameObject * light_go           = new GameObject({light_gizmo_renderer, light});
    light_go->name                  = "light1";
    light_go->GetTransform()->scale = glm::vec3(0.5f, 0.5f, 0.5f);

    GameObject * light2_go = new GameObject({light2_gizmo_renderer, light2});
    light2_go->name        = "light2";
    light2_go->GetTransform()->Translate(glm::vec3(0.0f, 5.0f, 0.0f));
    light2_go->GetTransform()->Rotate(glm::vec3(90.0, 0.0, 0.0));
    light2_go->GetTransform()->scale = glm::vec3(0.5f, 0.5f, 0.5f);

    // GameObject * empty_go = new GameObject();
    // cube_go->AttachParent(empty_go);
    // backpack_go->AttachParent(empty_go);
    // empty_go->GetTransform()->position += glm::vec3(4.0, 0.0, 0.0);
    // empty_go->GetTransform()->Rotate(glm::vec3(0.0, 0.0, 45.0));

    // GameObject * light3_go = new GameObject ({light3});
    // light->GetTransform()->Rotate(glm::vec3(45.0f, 0.0f, 45.0f));

    std::vector<MeshRender *> backpack_renderers = backpack_go->GetComponentsInChildren<MeshRender>();

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

        const float radius = 3.0f;
        float       camX   = sin((float)VDEngine::Time::GetTime() * 0.5f) * radius;
        float       camZ   = cos((float)VDEngine::Time::GetTime() * 0.5f) * radius;

        light_go->GetTransform()->position = glm::vec3(camX, 2.5f, camZ);
        light_go->GetTransform()->LookAt(glm::vec3(0.0f, 0.5f, 0.0f));

        // Renderer ------------------------------

        // Clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw

        for (int i = 0; i < backpack_renderers.size(); i++)
        {
            // std::cout << "Draw [" << i << "]." << std::endl;
            // // std::cout << "name :" << backpack_renderers[i]->GetGameObject()->name << "." << std::endl;
            // // if (backpack_renderers[i]->GetGameObject()->GetParent() != nullptr)
            // //     std::cout << "Parent_name :" << backpack_renderers[i]->GetGameObject()->GetParent()->name << "."
            // //               << std::endl;
            backpack_renderers[i]->Draw(camera, {light, light2});
        }
        cube_go->GetComponent<MeshRender>()->Draw(camera, {light, light2});
        floor_go->GetComponent<MeshRender>()->Draw(camera, {light, light2});
        light_go->GetComponent<MeshRender>()->Draw(camera, {light, light2});
        light2_go->GetComponent<MeshRender>()->Draw(camera, {light, light2});

        // Display
        glFlush();
        glfwSwapBuffers(s_window);

        VDEngine::Time::Update();
    }

    glfwTerminate();

    return 0;
}