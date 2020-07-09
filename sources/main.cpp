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

#include "metaStuff/Meta.h"
#include "nlohmann/json.hpp"
#include "VDEngine/Serialization/JsonCast.h"
#include "VDEngine/Math/Vectors.hpp"

#include "glm/gtx/vector_angle.hpp"

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

    std::string resources_path = FileHandler::getInstance()->resources_path;
    std::string text_path      = resources_path + "textures/";
    std::string shad_path      = resources_path + "shaders/";
    std::string model_path     = resources_path + "models/";

    // Load Shaders --

    ShaderManager * shader_manager = ShaderManager::getInstance();

    Shader * lit_default_shader =
        shader_manager->LoadShader(shad_path + "Lit_Default.vert", shad_path + "Lit_Default.frag");
    Shader * unlit_default_shader =
        shader_manager->LoadShader(shad_path + "Unlit_Default.vert", shad_path + "Unlit_Default.frag");

    // Load Textures --

    TextureManager * texture_manager = TextureManager::getInstance();

    Texture * measurement_diff      = texture_manager->LoadTexture(text_path + "measurement_floor.png");
    Texture * wooden_container_diff = texture_manager->LoadTexture(text_path + "container2.png");
    Texture * wooden_container_spec = texture_manager->LoadTexture(text_path + "container2_specular.png");
    // Texture * emoji_tex       = texture_manager->LoadTexture(text_path + "awesomeface.png");

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

    Model * backpack_model = ModelLoader::getInstance()->LoadModel(model_path + "backpack.obj");

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

    // GameObject * go = new GameObject();

    // std::cout << "Members of class GameObject:\n";
    // meta::doForAllMembers<GameObject>([](const auto & member) { std::cout << "* " << member.getName() << '\n'; });

    // // if (meta::hasMember<GameObject>("name"))
    // // {
    // //     std::cout << "GameObject has member named 'name'\n";
    // //     meta::
    // // }
    // std::cout << &(go->name) << std::endl;
    // meta::doForAllMembers<GameObject>([&go](const auto & member) {
    //     using MemberT = meta::get_member_type<decltype(member)>;

    //     auto name = meta::getMemberValue<std::string>(light2_go, "name");

    //     // if (dynamic_cast<Transform *>(meta::getMemberValue<MemberT>(light2_go, member.getName())))
    //     //     std::cout << "Transform" << std::endl;

    //     std::cout << "* " << member.getName() << &(member.get(*go)) << ", type = " << typeid(MemberT).name() << '\n';
    // });

    // auto name = meta::getMemberValue<std::string>(light2_go, "name");
    // std::cout << "Got GameObject's name: " << name << '\n';

    // std::cout << "Serializing GameObject:" << '\n';
    // json root = light2_go->GetTransform()->position;
    // std::cout << std::setw(4) << root << std::endl;

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

void test_vector2()
{
    glm::vec2 vec2_1 = glm::vec2(-1, 0);
    glm::vec2 vec2_2 = glm::vec2(2.0f, 4.0f);
    glm::vec2 vec2_3 = glm::vec2(0, 0);

    Vector2 vector2_1 = Vector2::VecLeft();
    Vector2 vector2_2 = Vector2(2.0f, 4.0f);
    Vector2 vector2_3 = Vector2::VecZero();

    // Angle ----

    std::cout << "** Angle ************" << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector2::Angle(vector2_1, vector2_2) << std::endl;
    std::cout << "GLM: " << glm::degrees(glm::angle(glm::normalize(vec2_1), glm::normalize(vec2_2))) << std::endl;

    std::cout << "VDEngine: " << Vector2::Angle(vector2_2, vector2_3) << std::endl;
    std::cout << "GLM: " << glm::degrees(glm::angle(glm::normalize(vec2_2), glm::normalize(vec2_3))) << std::endl;

    std::cout << "VDEngine: " << Vector2::Angle(vector2_3, vector2_1) << std::endl;
    std::cout << "GLM: " << glm::degrees(glm::angle(glm::normalize(vec2_3), glm::normalize(vec2_1))) << std::endl;

    std::cout << std::endl;

    // -- Distance --

    std::cout << "** Distance *********" << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector2::Distance(vector2_3, vector2_2) << std::endl;
    std::cout << "GLM:      " << glm::distance(vec2_3, vec2_2) << std::endl;

    std::cout << "VDEngine: " << Vector2::Distance(vector2_2, vector2_1) << std::endl;
    std::cout << "GLM:      " << glm::distance(vec2_2, vec2_1) << std::endl;

    std::cout << "VDEngine: " << Vector2::Distance(vector2_1, vector2_3) << std::endl;
    std::cout << "GLM:      " << glm::distance(vec2_1, vec2_3) << std::endl;

    std::cout << std::endl;

    // -- Dot --

    std::cout << "** Dot **************" << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector2::Dot(vector2_2, vector2_1) << std::endl;
    std::cout << "GLM:      " << glm::dot(vec2_2, vec2_1) << std::endl;

    std::cout << "VDEngine: " << Vector2::Dot(vector2_3, vector2_2) << std::endl;
    std::cout << "GLM:      " << glm::dot(vec2_3, vec2_2) << std::endl;

    std::cout << "VDEngine: " << Vector2::Dot(vector2_1, vector2_3) << std::endl;
    std::cout << "GLM:      " << glm::dot(vec2_1, vec2_3) << std::endl;

    std::cout << std::endl;

    // -- GetMagnitude --

    std::cout << "** Magnitude ********" << std::endl << std::endl;

    std::cout << "VDEngine: " << vector2_2.GetMagnitude() << std::endl;
    std::cout << "GLM:      " << glm::length(vec2_2) << std::endl;

    std::cout << "VDEngine: " << vector2_3.GetMagnitude() << std::endl;
    std::cout << "GLM:      " << glm::length(vec2_3) << std::endl;

    std::cout << "VDEngine: " << vector2_1.GetMagnitude() << std::endl;
    std::cout << "GLM:      " << glm::length(vec2_1) << std::endl;

    std::cout << std::endl;

    // -- Normalize / GetNormalized --

    std::cout << "** Get Normalized ********" << std::endl << std::endl;

    std::cout << "VDEngine: " << vector2_2.GetNormalized() << std::endl;
    std::cout << "GLM:      " << to_vector2(glm::normalize(vec2_2)) << std::endl << std::endl;

    std::cout << "VDEngine: " << vector2_2 << std::endl;
    std::cout << "GLM:      " << to_vector2(vec2_2) << std::endl << std::endl;

    std::cout << "** Normalize ********" << std::endl << std::endl;

    vector2_2.Normalize();
    vec2_2 = glm::normalize(vec2_2);
    std::cout << "VDEngine: " << vector2_2 << std::endl;
    std::cout << "GLM:      " << to_vector2(vec2_2) << std::endl;

    vector2_3.Normalize();
    vec2_3 = glm::normalize(vec2_3);
    std::cout << "VDEngine: " << vector2_3 << std::endl;
    std::cout << "GLM:      " << to_vector2(vec2_3) << std::endl;

    std::cout << std::endl;

    // -- Normalize / GetNormalized --

    std::cout << "** Lerp ********" << std::endl << std::endl;

    vec2_3 = glm::vec2(0.0f, 0.0f);

    std::cout << "VDEngine: " << Vector2::Lerp(vector2_3, vector2_2, 0) << std::endl;
    std::cout << "GLM:      " << to_vector2(glm::lerp(vec2_3, vec2_2, 0.0f)) << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector2::Lerp(vector2_3, vector2_2, 0.2f) << std::endl;
    std::cout << "GLM:      " << to_vector2(glm::lerp(vec2_3, vec2_2, 0.2f)) << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector2::Lerp(vector2_3, vector2_2, 0.5f) << std::endl;
    std::cout << "GLM:      " << to_vector2(glm::lerp(vec2_3, vec2_2, 0.5f)) << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector2::Lerp(vector2_3, vector2_2, 0.9f) << std::endl;
    std::cout << "GLM:      " << to_vector2(glm::lerp(vec2_3, vec2_2, 0.9f)) << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector2::Lerp(vector2_3, vector2_2, 1.0f) << std::endl;
    std::cout << "GLM:      " << to_vector2(glm::lerp(vec2_3, vec2_2, 1.0f)) << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector2::Lerp(vector2_3, vector2_2, 23) << std::endl;
    std::cout << "GLM:      " << to_vector2(glm::lerp(vec2_3, vec2_2, 23.0f)) << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector2::Lerp(vector2_3, vector2_2, -0.5f) << std::endl;
    std::cout << "GLM:      " << to_vector2(glm::lerp(vec2_3, vec2_2, -0.5f)) << std::endl << std::endl;

    // -- Operators --

    // Vector2::operator==;
    // Vector2::operator!=;

    // Vector2::operator-;

    // Vector2::operator*;
    // Vector2::operator+;
    // Vector2::operator-;
    // Vector2::operator/;

    // Vector2::operator*=;
    // Vector2::operator+=;
    // Vector2::operator-=;
    // Vector2::operator/=;
}

void test_vector3()
{
    glm::vec3 vec1 = glm::vec3(-1.0f, 0.0f, 0.0f);
    glm::vec3 vec2 = glm::vec3(2.0f, 4.0f, 8.0f);
    glm::vec3 vec3 = glm::vec3(0.0f, 0.0f, 0.0f);

    Vector3 vector1 = Vector3::VecLeft();
    Vector3 vector2 = Vector3(2.0f, 4.0f, 8.0f);
    Vector3 vector3 = Vector3::VecZero();

    // Angle ----

    std::cout << "** Angle ************" << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector3::Angle(vector1, vector2) << std::endl;
    std::cout << "GLM: " << glm::degrees(glm::angle(glm::normalize(vec1), glm::normalize(vec2))) << std::endl;

    std::cout << "VDEngine: " << Vector3::Angle(vector2, vector3) << std::endl;
    std::cout << "GLM: " << glm::degrees(glm::angle(glm::normalize(vec2), glm::normalize(vec3))) << std::endl;

    std::cout << "VDEngine: " << Vector3::Angle(vector3, vector1) << std::endl;
    std::cout << "GLM: " << glm::degrees(glm::angle(glm::normalize(vec3), glm::normalize(vec1))) << std::endl;

    std::cout << std::endl;

    // -- Distance --

    std::cout << "** Distance *********" << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector3::Distance(vector3, vector2) << std::endl;
    std::cout << "GLM:      " << glm::distance(vec3, vec2) << std::endl;

    std::cout << "VDEngine: " << Vector3::Distance(vector2, vector1) << std::endl;
    std::cout << "GLM:      " << glm::distance(vec2, vec1) << std::endl;

    std::cout << "VDEngine: " << Vector3::Distance(vector1, vector3) << std::endl;
    std::cout << "GLM:      " << glm::distance(vec1, vec3) << std::endl;

    std::cout << std::endl;

    // -- Dot --

    // dot (left, up) = 0
    // dot (left, left) =  1 (ou +)
    // dot (left, right) = -1 (ou -)
    // dot (zero, one) = 0

    std::cout << "** Dot **************" << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector3::Dot(vector2, vector1) << std::endl;
    std::cout << "GLM:      " << glm::dot(vec2, vec1) << std::endl;

    std::cout << "VDEngine: " << Vector3::Dot(vector3, vector2) << std::endl;
    std::cout << "GLM:      " << glm::dot(vec3, vec2) << std::endl;

    std::cout << "VDEngine: " << Vector3::Dot(vector1, vector3) << std::endl;
    std::cout << "GLM:      " << glm::dot(vec1, vec3) << std::endl;

    std::cout << "VDEngine: " << Vector3::Dot(Vector3::VecLeft(), Vector3::VecUp()) << std::endl;
    std::cout << "GLM:      " << glm::dot(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)) << std::endl;

    std::cout << "VDEngine: " << Vector3::Dot(Vector3::VecLeft(), Vector3::VecLeft()) << std::endl;
    std::cout << "GLM:      " << glm::dot(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)) << std::endl;

    std::cout << "VDEngine: " << Vector3::Dot(Vector3::VecLeft(), Vector3::VecRight()) << std::endl;
    std::cout << "GLM:      " << glm::dot(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)) << std::endl;

    std::cout << "VDEngine: " << Vector3::Dot(Vector3::VecZero(), Vector3::VecOne()) << std::endl;
    std::cout << "GLM:      " << glm::dot(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)) << std::endl;

    std::cout << std::endl;

    // -- cross --

    // cross (left, right) = 0
    // cross (right, right) = 0
    // cross (zero, one) = 0

    std::cout << "** Cross **************" << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector3::Cross(vector2, vector1) << std::endl;
    std::cout << "GLM:      " << to_vector3(glm::cross(vec2, vec1)) << std::endl;

    std::cout << "VDEngine: " << Vector3::Cross(vector3, vector2) << std::endl;
    std::cout << "GLM:      " << to_vector3(glm::cross(vec3, vec2)) << std::endl;

    std::cout << "VDEngine: " << Vector3::Cross(vector1, vector3) << std::endl;
    std::cout << "GLM:      " << to_vector3(glm::cross(vec1, vec3)) << std::endl;

    std::cout << "VDEngine: " << Vector3::Cross(Vector3::VecLeft(), Vector3::VecRight()) << std::endl;
    std::cout << "GLM:      " << to_vector3(glm::cross(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)))
              << std::endl;

    std::cout << "VDEngine: " << Vector3::Cross(Vector3::VecRight(), Vector3::VecRight()) << std::endl;
    std::cout << "GLM:      " << to_vector3(glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)))
              << std::endl;

    std::cout << "VDEngine: " << Vector3::Cross(Vector3::VecZero(), Vector3::VecOne()) << std::endl;
    std::cout << "GLM:      " << to_vector3(glm::cross(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)))
              << std::endl;

    std::cout << std::endl;

    // -- GetMagnitude --

    std::cout << "** Magnitude ********" << std::endl << std::endl;

    std::cout << "VDEngine: " << vector2.GetMagnitude() << std::endl;
    std::cout << "GLM:      " << glm::length(vec2) << std::endl;

    std::cout << "VDEngine: " << vector3.GetMagnitude() << std::endl;
    std::cout << "GLM:      " << glm::length(vec3) << std::endl;

    std::cout << "VDEngine: " << vector1.GetMagnitude() << std::endl;
    std::cout << "GLM:      " << glm::length(vec1) << std::endl;

    std::cout << std::endl;

    // -- Normalize / GetNormalized --

    std::cout << "** Get Normalized ********" << std::endl << std::endl;

    std::cout << "VDEngine: " << vector2.GetNormalized() << std::endl;
    std::cout << "GLM:      " << to_vector3(glm::normalize(vec2)) << std::endl << std::endl;

    std::cout << "VDEngine: " << vector2 << std::endl;
    std::cout << "GLM:      " << to_vector3(vec2) << std::endl << std::endl;

    std::cout << "** Normalize ********" << std::endl << std::endl;

    vector2.Normalize();
    vec2 = glm::normalize(vec2);
    std::cout << "VDEngine: " << vector2 << std::endl;
    std::cout << "GLM:      " << to_vector3(vec2) << std::endl;

    vector3.Normalize();
    vec3 = glm::normalize(vec3);
    std::cout << "VDEngine: " << vector3 << std::endl;
    std::cout << "GLM:      " << to_vector3(vec3) << std::endl;

    std::cout << std::endl;

    // -- Lerp --

    std::cout << "** Lerp ********" << std::endl << std::endl;

    vec3 = glm::vec3(0.0f, 0.0f, 0.0f);

    std::cout << "VDEngine: " << Vector3::Lerp(vector3, vector2, 0) << std::endl;
    std::cout << "GLM:      " << to_vector3(glm::lerp(vec3, vec2, 0.0f)) << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector3::Lerp(vector3, vector2, 0.2f) << std::endl;
    std::cout << "GLM:      " << to_vector3(glm::lerp(vec3, vec2, 0.2f)) << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector3::Lerp(vector3, vector2, 0.5f) << std::endl;
    std::cout << "GLM:      " << to_vector3(glm::lerp(vec3, vec2, 0.5f)) << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector3::Lerp(vector3, vector2, 0.9f) << std::endl;
    std::cout << "GLM:      " << to_vector3(glm::lerp(vec3, vec2, 0.9f)) << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector3::Lerp(vector3, vector2, 1.0f) << std::endl;
    std::cout << "GLM:      " << to_vector3(glm::lerp(vec3, vec2, 1.0f)) << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector3::Lerp(vector3, vector2, 23) << std::endl;
    std::cout << "GLM:      " << to_vector3(glm::lerp(vec3, vec2, 23.0f)) << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector3::Lerp(vector3, vector2, -0.5f) << std::endl;
    std::cout << "GLM:      " << to_vector3(glm::lerp(vec3, vec2, -0.5f)) << std::endl << std::endl;

    // -- Operators --

    // Vector3::operator==;
    // Vector3::operator!=;

    // Vector3::operator-;

    // Vector3::operator*;
    // Vector3::operator+;
    // Vector3::operator-;
    // Vector3::operator/;

    // Vector3::operator*=;
    // Vector3::operator+=;
    // Vector3::operator-=;
    // Vector3::operator/=;
}

void test_vector4()
{
    glm::vec4 vec1 = glm::vec4(1.0f, -1.0f, 0.0f, 0.0f);
    glm::vec4 vec2 = glm::vec4(2.0f, 4.0f, 8.0f, 16.0f);
    glm::vec4 vec3 = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

    Vector4 vector1 = Vector4(1.0f, -1.0f, 0.0f, 0.0f);
    Vector4 vector2 = Vector4(2.0f, 4.0f, 8.0f, 16.0f);
    Vector4 vector3 = Vector4::VecZero();

    // -- Distance --

    std::cout << "** Distance *********" << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector4::Distance(vector3, vector2) << std::endl;
    std::cout << "GLM:      " << glm::distance(vec3, vec2) << std::endl;

    std::cout << "VDEngine: " << Vector4::Distance(vector2, vector1) << std::endl;
    std::cout << "GLM:      " << glm::distance(vec2, vec1) << std::endl;

    std::cout << "VDEngine: " << Vector4::Distance(vector1, vector3) << std::endl;
    std::cout << "GLM:      " << glm::distance(vec1, vec3) << std::endl;

    std::cout << std::endl;

    // -- Dot --

    // dot (zero, one) = 0

    std::cout << "** Dot **************" << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector4::Dot(vector2, vector1) << std::endl;
    std::cout << "GLM:      " << glm::dot(vec2, vec1) << std::endl;

    std::cout << "VDEngine: " << Vector4::Dot(vector3, vector2) << std::endl;
    std::cout << "GLM:      " << glm::dot(vec3, vec2) << std::endl;

    std::cout << "VDEngine: " << Vector4::Dot(vector1, vector3) << std::endl;
    std::cout << "GLM:      " << glm::dot(vec1, vec3) << std::endl;

    std::cout << "VDEngine: " << Vector4::Dot(Vector4::VecZero(), Vector4::VecOne()) << std::endl;
    std::cout << "GLM:      " << glm::dot(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 0.0f))
              << std::endl;

    std::cout << std::endl;

    // -- GetMagnitude --

    std::cout << "** Magnitude ********" << std::endl << std::endl;

    std::cout << "VDEngine: " << vector2.GetMagnitude() << std::endl;
    std::cout << "GLM:      " << glm::length(vec2) << std::endl;

    std::cout << "VDEngine: " << vector3.GetMagnitude() << std::endl;
    std::cout << "GLM:      " << glm::length(vec3) << std::endl;

    std::cout << "VDEngine: " << vector1.GetMagnitude() << std::endl;
    std::cout << "GLM:      " << glm::length(vec1) << std::endl;

    std::cout << std::endl;

    // -- Normalize / GetNormalized --

    std::cout << "** Get Normalized ********" << std::endl << std::endl;

    std::cout << "VDEngine: " << vector2.GetNormalized() << std::endl;
    std::cout << "GLM:      " << to_vector4(glm::normalize(vec2)) << std::endl << std::endl;

    std::cout << "VDEngine: " << vector2 << std::endl;
    std::cout << "GLM:      " << to_vector4(vec2) << std::endl << std::endl;

    std::cout << "** Normalize ********" << std::endl << std::endl;

    vector2.Normalize();
    vec2 = glm::normalize(vec2);
    std::cout << "VDEngine: " << vector2 << std::endl;
    std::cout << "GLM:      " << to_vector4(vec2) << std::endl;

    vector3.Normalize();
    vec3 = glm::normalize(vec3);
    std::cout << "VDEngine: " << vector3 << std::endl;
    std::cout << "GLM:      " << to_vector4(vec3) << std::endl;

    std::cout << std::endl;

    // -- Lerp --

    std::cout << "** Lerp ********" << std::endl << std::endl;

    vec3 = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

    std::cout << "VDEngine: " << Vector4::Lerp(vector3, vector2, 0) << std::endl;
    std::cout << "GLM:      " << to_vector4(glm::lerp(vec3, vec2, 0.0f)) << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector4::Lerp(vector3, vector2, 0.2f) << std::endl;
    std::cout << "GLM:      " << to_vector4(glm::lerp(vec3, vec2, 0.2f)) << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector4::Lerp(vector3, vector2, 0.5f) << std::endl;
    std::cout << "GLM:      " << to_vector4(glm::lerp(vec3, vec2, 0.5f)) << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector4::Lerp(vector3, vector2, 0.9f) << std::endl;
    std::cout << "GLM:      " << to_vector4(glm::lerp(vec3, vec2, 0.9f)) << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector4::Lerp(vector3, vector2, 1.0f) << std::endl;
    std::cout << "GLM:      " << to_vector4(glm::lerp(vec3, vec2, 1.0f)) << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector4::Lerp(vector3, vector2, 23) << std::endl;
    std::cout << "GLM:      " << to_vector4(glm::lerp(vec3, vec2, 23.0f)) << std::endl << std::endl;

    std::cout << "VDEngine: " << Vector4::Lerp(vector3, vector2, -0.5f) << std::endl;
    std::cout << "GLM:      " << to_vector4(glm::lerp(vec3, vec2, -0.5f)) << std::endl << std::endl;

    // -- Operators --

    // Vector4::operator==;
    // Vector4::operator!=;

    // Vector4::operator-;

    // Vector4::operator*;
    // Vector4::operator+;
    // Vector4::operator-;
    // Vector4::operator/;

    // Vector4::operator*=;
    // Vector4::operator+=;
    // Vector4::operator-=;
    // Vector4::operator/=;
}