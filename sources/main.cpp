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
#include "VDEngine/Math/Quaternion.h"
#include "VDEngine/Math/Matrix4.h"
#include "VDEngine/Math/GLMConverter.hpp"

#include <glm/glm.hpp>
#include "glm/gtx/compatibility.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/vector_angle.hpp"
// #include <glm/gtc/quaternion.hpp>
// #include <glm/gtx/quaternion.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtx/matrix_decompose.hpp>
// #include <glm/gtx/euler_angles.hpp>
// #include <glm/gtc/type_ptr.hpp>

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
    light_mat->diffuse_color = Vector3::VecOne();

    Material * light2_mat    = material_manager->LoadMaterial(unlit_default_shader);
    light_mat->diffuse_color = Vector3::VecOne();

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
    VDEngine::Light * light = new Light(POINT, Vector3::VecOne());
    light->att_linear       = 0.045f;
    light->att_quadratic    = 0.0075f;

    VDEngine::Light * light2 = new Light(SPOT, Vector3::VecOne());
    light2->att_linear       = 0.045f;
    light2->att_quadratic    = 0.0075f;
    light2->inner_cutOff     = 15;
    light2->outer_cutOff     = 20;

    // VDEngine::Light * light3 = new Light(DIRECTIONAL, glm::vec3(1.0f, 1.0f, 1.0f));

    // Behaviours ---
    FPSCameraController * camera_controller = new FPSCameraController(camera);

    // -- Game Objects ----------

    GameObject * backpack_go                         = backpack_model->CreateGameObjectFromModel();
    backpack_go->GetComponent<Transform>()->position = Vector3(0.0, 1.0, 1.0);
    backpack_go->GetTransform()->scale               = Vector3(0.5, 0.5, 0.5);
    backpack_go->GetTransform()->Rotate(-30.0, 0.0, 0.0);
    backpack_go->name = "backpack_root";

    GameObject * floor_go = new GameObject({floor_renderer});
    floor_go->name        = "floor";
    floor_go->GetTransform()->Rotate(-90.0f, Vector3::VecRight());
    floor_go->GetTransform()->scale = Vector3(10.0f, 10.0f, 1.0f);

    GameObject * cube_go = new GameObject({cube_renderer});
    cube_go->name        = "cube";
    cube_go->GetTransform()->Translate(Vector3(0.0f, 0.5f, 0.0f));
    // cube->GetTransform()->LookAt(glm::vec3(0.0f, 0.5f, 0.0f));
    // cube->GetTransform()->Rotate(glm::vec3(0.0f, -45.0f, 0.0f));

    GameObject * Camera_go = new GameObject({camera});
    Camera_go->name        = "main_camera";
    Camera_go->GetTransform()->Translate(Vector3(0.0f, 1.0f, 5.0f));
    Camera_go->GetTransform()->Rotate(45.0f, Vector3::VecUp());

    GameObject * light_go           = new GameObject({light_gizmo_renderer, light});
    light_go->name                  = "light1";
    light_go->GetTransform()->scale = Vector3(0.5f, 0.5f, 0.5f);

    GameObject * light2_go = new GameObject({light2_gizmo_renderer, light2});
    light2_go->name        = "light2";
    light2_go->GetTransform()->Translate(Vector3(0.0f, 5.0f, 0.0f));
    light2_go->GetTransform()->Rotate(Vector3(90.0, 0.0, 0.0));
    light2_go->GetTransform()->scale = Vector3(0.5f, 0.5f, 0.5f);

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
    // meta::doForAllMembers<GameObject>([](const auto & member) { std::cout << "* " << member.getName() << '\n';
    // });

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

    //     std::cout << "* " << member.getName() << &(member.get(*go)) << ", type = " << typeid(MemberT).name() <<
    //     '\n';
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

        // // User update ---------------------------

        camera_controller->Update();

        const float radius = 3.0f;
        float       camX   = sin((float)VDEngine::Time::GetTime() * 0.5f) * radius;
        float       camZ   = cos((float)VDEngine::Time::GetTime() * 0.5f) * radius;

        light_go->GetTransform()->position = Vector3(camX, 2.5f, camZ);
        light_go->GetTransform()->LookAt(Vector3(0.0f, 0.5f, 0.0f));

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
            // //     std::cout << "Parent_name :" << backpack_renderers[i]->GetGameObject()->GetParent()->name <<
            // "."
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

/*void test_quaternion()
{
    Quaternion vde_q1 = Quaternion();
    Quaternion vde_q2 = Quaternion(1, 0, 0, 0);

    Quaternion vde_q3 = Quaternion::CreateFromEuler(Vector3(0, 0, 0)); // zero
    Quaternion vde_q4 = Quaternion::CreateFromEuler(Vector3(0, 90, 90));
    Quaternion vde_q5 = Quaternion::CreateFromEuler(Vector3(260, 185, -270)); // singularité x
    Quaternion vde_q6 = Quaternion::CreateFromEuler(Vector3(36, 720, 192));   // y > 360
    Quaternion vde_q7 = Quaternion::CreateFromEuler(Vector3(-36, -720, 192)); // x negative + y < -360

    Quaternion vde_q8  = Quaternion::CreateFromAxisAngle(Vector3(90, 0, 45), 45);
    Quaternion vde_q9  = Quaternion::CreateFromAxisAngle(Vector3(0, 0, 0), 90);
    Quaternion vde_q10 = Quaternion::CreateFromAxisAngle(Vector3(0.5, 0, 0.5), 20);
    Quaternion vde_q11 = Quaternion::CreateFromAxisAngle(Vector3(1, 0, 0), 2000);

    Quaternion vde_q12 = Quaternion(vde_q4);

    Vector3 axis_8, axis_9, axis_10, axis_11;
    float   angle_8, angle_9, angle_10, angle_11;

    vde_q8.GetAxisAngle(axis_8, angle_8);
    vde_q9.GetAxisAngle(axis_9, angle_9);
    vde_q10.GetAxisAngle(axis_10, angle_10);
    vde_q11.GetAxisAngle(axis_11, angle_11);

    std::cout << "-- FromTo --" << std::endl << std::endl;

    Vector3 target1(1, 1, 1);
    Vector3 target2(1, 34, 4);
    Vector3 target3(-11, 0, -40);

    target1.Normalize();
    target2.Normalize();
    target3.Normalize();

    glm::quat q1 = glm::quatLookAt(to_glm_vec3(target1), glm::vec3(0, 1, 0));
    glm::quat q2 = glm::quatLookAt(to_glm_vec3(target2), glm::vec3(0, 1, 0));
    glm::quat q3 = glm::quatLookAt(to_glm_vec3(target3), glm::vec3(0, 1, 0));

    // target1.Scale(Vector3(1, 1, -1));
    // target2.Scale(Vector3(1, 1, -1));
    // target3.Scale(Vector3(1, 1, -1));

    std::cout << "vde_q1: " << Quaternion::LookRotation(target1) << std::endl;
    std::cout << "glm:    " << q1.x << "  " << q1.y << "  " << q1.z << "  " << q1.w << std::endl << std::endl;

    std::cout << "vde_q2: " << Quaternion::LookRotation(target2) << std::endl;
    std::cout << "glm:    " << q2.x << "  " << q2.y << "  " << q2.z << "  " << q2.w << std::endl << std::endl;

    std::cout << "vde_q3: " << Quaternion::LookRotation(target3) << std::endl;
    std::cout << "glm:    " << q3.x << "  " << q3.y << "  " << q3.z << "  " << q3.w << std::endl << std::endl;

    std::cout << "vde_q3: " << Quaternion::LookRotation(target1).GetEuler() << std::endl;
    Quaternion q4(q1.x, q1.y, q1.z, q1.w);
    std::cout << "glm:    " << q4.GetEuler() << std::endl << std::endl;

    // std::cout << vde_q4.GetInversed() * Vector3::VecForward() << std::endl; // <===== PROBLEM ?
    // std::cout << to_vector3(glm::vec3(0, 0, 1) * glm::quat(vde_q4.w, vde_q4.x, vde_q4.y, vde_q4.z))
    //           << std::endl; // <===== PROBLEM ?

    // std::cout << "vde_q1:     " << Quaternion::FromTo(Vector3::VecForward(), vde_q4.GetForward()) << std::endl;
    // std::cout << "validation: " << Quaternion::FromTo(Vector3::VecForward(), vde_q4.GetForward()).GetEuler()
    //           << std::endl
    //           << std::endl;

    // std::cout << "-- Look Rotation --" << std::endl << std::endl;

    Vector3 q_forward = Vector3(1, 1, 1);
    // q_forward.Scale(Vector3(-1, 1, 1));
    Quaternion qq = Quaternion(-0.3, 0.4, 0.1, 0.9); // Quaternion::LookRotation(q_forward);

    glm::quat qq1 = glm::quat();
    qq1.x         = -0.32506;
    qq1.y         = 0.32506;
    qq1.z         = 0;
    qq1.w         = 0.88807;

    glm::quat qq2 = glm::quat();
    qq2.x         = 0.07536;
    qq2.y         = 0.07536;
    qq2.z         = 0.07536;
    qq2.w         = 0.99144;

    glm::quat qq3 = qq2 * qq1;

    std::cout << "vde_q1:     " << qq.GetEuler() << std::endl;
    std::cout << "glm:    " << qq3.x << "  " << qq3.y << "  " << qq3.z << "  " << qq3.w << std::endl << std::endl;

    // std::cout << "vde_q1:     " << Vector3::Cross(Vector3(2, 4, 8), Vector3(20, 30, 40)) << std::endl;
    // std::cout << "vde_q1:     " << Vector3::Cross(Vector3(20, 30, 40), Vector3(2, 4, 8)) << std::endl;

    // std::cout << "-- Basic constructors --" << std::endl << std::endl;

    // std::cout << "vde_q1:     " << vde_q1 << std::endl;
    // std::cout << "validation: " << std::endl << std::endl;

    // std::cout << "vde_q2:     " << vde_q2 << std::endl;
    // std::cout << "validation: " << std::endl << std::endl;

    // std::cout << "vde_q12:    " << vde_q12 << std::endl;
    // std::cout << "validation: " << std::endl << std::endl;

    // std::cout << "-- Euler constructors --" << std::endl << std::endl;

    // std::cout << "vde_q3:     " << vde_q3 << std::endl;
    // std::cout << "validation: Quat( 0.00000  0.00000  0.00000  1.00000 )" << std::endl << std::endl;

    // std::cout << "vde_q4:     " << vde_q4 << std::endl;
    // std::cout << "validation: Quat( -0.50000  0.50000  0.50000  0.50000 )" << std::endl << std::endl;

    // std::cout << "vde_q5:     " << vde_q5 << std::endl;
    // std::cout << "validation: Quat( -0.43046  0.47771  -0.56099  0.52133 )" << std::endl << std::endl;

    // std::cout << "vde_q6:     " << vde_q6 << std::endl;
    // std::cout << "validation: Quat( -0.03230  0.30732  0.94585  -0.09941 )" << std::endl << std::endl;

    // std::cout << "vde_q7:     " << vde_q7 << std::endl;
    // std::cout << "validation: Quat( 0.03230  -0.30732  0.94585  -0.09941 )" << std::endl << std::endl;

    // std::cout << "-- Euler Getters --" << std::endl << std::endl;

    // std::cout << "euler_q3:   " << vde_q3.GetEuler() << std::endl;
    // std::cout << "validation: Vec3( 0.00000  0.00000  0.00000 )" << std::endl << std::endl;

    // std::cout << "euler_q4:   " << vde_q4.GetEuler() << std::endl;
    // std::cout << "validation: Vec3( 0.00000  90.00000  90.00000 )" << std::endl << std::endl;

    // std::cout << "euler_q5:   " << vde_q5.GetEuler() << std::endl;
    // std::cout << "validation: Vec3( 280.00000  5.00000  270.00000 )" << std::endl << std::endl;

    // std::cout << "euler_q6:   " << vde_q6.GetEuler() << std::endl;
    // std::cout << "validation: Vec3( 36.00000  0.00003  192.00002 )" << std::endl << std::endl;

    // std::cout << "euler_q7:   " << vde_q7.GetEuler() << std::endl;
    // std::cout << "validation: Vec3( 324.00000  360.00000  192.00000 )" << std::endl << std::endl;

    // std::cout << "-- Axis angle constructors --" << std::endl << std::endl;

    // std::cout << "vde_q8:     " << vde_q8 << std::endl;
    // std::cout << "validation: Quat( 0.34228  0.00000  0.17114  0.92388 )" << std::endl << std::endl;

    // std::cout << "vde_q9:     " << vde_q9 << std::endl;
    // std::cout << "validation: Quat( 0.00000  0.00000  0.00000  1.00000 )" << std::endl << std::endl;

    // std::cout << "vde_q10:    " << vde_q10 << std::endl;
    // std::cout << "validation: Quat( 0.12279  0.00000  0.12279  0.98481 )" << std::endl << std::endl;

    // std::cout << "vde_q11:    " << vde_q11 << std::endl;
    // std::cout << "validation: Quat( -0.98481  0.00000  0.00000  0.17365 )" << std::endl << std::endl;

    // std::cout << "-- Axis angle getters --" << std::endl << std::endl;

    // std::cout << "axis_8:     " << axis_8 << std::endl;
    // std::cout << "validation: Vec3( 0.89443  0.00000  0.44721 )" << std::endl << std::endl;

    // std::cout << "angle_8:    " << angle_8 << std::endl;
    // std::cout << "validation: 45" << std::endl << std::endl;

    // std::cout << "axis_9:     " << axis_9 << std::endl;
    // std::cout << "validation: Vec3( 0.00000  0.00000  0.00000 )" << std::endl << std::endl;

    // std::cout << "angle_9:    " << angle_9 << std::endl;
    // std::cout << "validation: 0" << std::endl << std::endl;

    // std::cout << "axis_10:    " << axis_10 << std::endl;
    // std::cout << "validation: Vec3( 0.70711  0.00000  0.70711 )" << std::endl << std::endl;

    // std::cout << "angle_10:   " << angle_10 << std::endl;
    // std::cout << "validation: 20" << std::endl << std::endl;

    // std::cout << "axis_11:    " << axis_11 << std::endl;
    // std::cout << "validation: Vec3( -1.00000  0.00000  0.00000 )" << std::endl << std::endl;

    // std::cout << "angle_11:   " << angle_11 << std::endl;
    // std::cout << "validation: 160" << std::endl << std::endl;
}*/

void test_matrix()
{
    // --------------------------------------

    // Vector3 t1 = Vector3(1, 1, 1);
    // Vector3 t2 = Vector3(10, 0, 42);
    // Vector3 t3 = Vector3(5, -20, 42);
    // Vector3 t4;
    // Vector3 t5;
    // Vector3 t6;

    // Quaternion r0 = Quaternion::CreateFromEuler(Vector3(-300, -200, -100)); // mat to quat : case 0
    // Quaternion r1 = Quaternion::CreateFromEuler(Vector3(0, 90, 90));        // mat to quat : case 1
    // Quaternion r2 = Quaternion::CreateFromEuler(Vector3(-10, 205, 50));     // mat to quat : case 3
    // Quaternion r3 = Quaternion::CreateFromEuler(Vector3(-100, -200, -300)); // mat to quat : case 4
    // Quaternion r4;
    // Quaternion r5;
    // Quaternion r6;

    // Vector3 s1 = Vector3(1, 1, 1);
    // Vector3 s2 = Vector3(5, 5, 5);
    // Vector3 s3 = Vector3(20, 3, 47);
    // Vector3 s4;
    // Vector3 s5;
    // Vector3 s6;

    // -------------------------------------

    // -- Compose / Decompose -------

    // Matrix4 m0 = Matrix4::ComposeTRS(t1, r0, s1);
    // Matrix4 m1 = Matrix4::ComposeTRS(t1, r1, s1);
    // Matrix4 m2 = Matrix4::ComposeTRS(t2, r2, s2);
    // Matrix4 m3 = Matrix4::ComposeTRS(t3, r3, s3);

    // std::cout << "-- ComposeTRS ---" << std::endl << std::endl;

    // std::cout << "m0 : " << std::endl << m0 << std::endl << std::endl;
    // std::cout << "m1 : " << std::endl << m1 << std::endl << std::endl;
    // std::cout << "m2 : " << std::endl << m2 << std::endl << std::endl;
    // std::cout << "m3 : " << std::endl << m3 << std::endl << std::endl;

    // std::cout << "-- AffineDecompose ---" << std::endl << std::endl;

    // Matrix4::AffineDecompose(m0, t4, r4, s4);
    // std::cout << "m0 -> translation: " << t4 << std::endl;
    // std::cout << "m2 -> rotation:    " << r0 << std::endl;
    // std::cout << "m0 -> rotation:    " << r4 << std::endl;
    // std::cout << "m0 -> scale:       " << s4 << std::endl << std::endl;

    // Matrix4::AffineDecompose(m1, t4, r4, s4);
    // std::cout << "m1 -> translation: " << t4 << std::endl;
    // std::cout << "m2 -> rotation:    " << r1 << std::endl;
    // std::cout << "m1 -> rotation:    " << r4 << std::endl;
    // std::cout << "m1 -> scale:       " << s4 << std::endl << std::endl;

    // Matrix4::AffineDecompose(m2, t5, r5, s5);
    // std::cout << "m2 -> translation: " << t5 << std::endl;
    // std::cout << "m2 -> rotation:    " << r2 << std::endl;
    // std::cout << "m2 -> rotation:    " << r5 << std::endl;
    // std::cout << "m2 -> scale:       " << s5 << std::endl << std::endl;

    // Matrix4::AffineDecompose(m3, t6, r6, s6);
    // std::cout << "m3 -> translation: " << t6 << std::endl;
    // std::cout << "m3 -> rotation:    " << r3.GetEuler() << std::endl;
    // std::cout << "m3 -> rotation:    " << r6.GetEuler() << std::endl;
    // std::cout << "m3 -> scale:       " << s6 << std::endl << std::endl;

    // -- END Compose / Decomponse --

    // -- Transpose / Invert / GetDerminant ------------

    // Matrix4   m0     = Matrix4::ComposeTRS(t1, r0, s1);
    // glm::mat4 glm_m0 = to_glm_mat4(m0);
    // Matrix4   m1     = Matrix4::ComposeTRS(t1, r1, s1);
    // glm::mat4 glm_m1 = to_glm_mat4(m1);
    // Matrix4   m2     = Matrix4::ComposeTRS(t2, r2, s2);
    // glm::mat4 glm_m2 = to_glm_mat4(m2);
    // Matrix4   m3     = Matrix4::ComposeTRS(t3, r3, s3);
    // glm::mat4 glm_m3 = to_glm_mat4(m3);

    // //

    // std::cout << "-- Transpose ---" << std::endl << std::endl;

    // std::cout << "m0:     " << std::endl << m0.GetTransposed() << std::endl;
    // std::cout << "glm_m0: " << std::endl << to_matrix4(glm::transpose(glm_m0)) << std::endl << std::endl;

    // std::cout << "m1:     " << std::endl << m1.GetTransposed() << std::endl;
    // std::cout << "glm_m1: " << std::endl << to_matrix4(glm::transpose(glm_m1)) << std::endl << std::endl;

    // std::cout << "m2:     " << std::endl << m2.GetTransposed() << std::endl;
    // std::cout << "glm_m2: " << std::endl << to_matrix4(glm::transpose(glm_m2)) << std::endl << std::endl;

    // std::cout << "m3:     " << std::endl << m3.GetTransposed() << std::endl;
    // std::cout << "glm_m3: " << std::endl << to_matrix4(glm::transpose(glm_m3)) << std::endl << std::endl;

    // //

    // std::cout << "-- Invert ---" << std::endl << std::endl;

    // std::cout << "m0:     " << std::endl << m0.GetInverted() << std::endl;
    // std::cout << "glm_m0: " << std::endl << to_matrix4(glm::inverse(glm_m0)) << std::endl << std::endl;

    // std::cout << "m1:     " << std::endl << m1.GetInverted() << std::endl;
    // std::cout << "glm_m1: " << std::endl << to_matrix4(glm::inverse(glm_m1)) << std::endl << std::endl;

    // std::cout << "m2:     " << std::endl << m2.GetInverted() << std::endl;
    // std::cout << "glm_m2: " << std::endl << to_matrix4(glm::inverse(glm_m2)) << std::endl << std::endl;

    // std::cout << "m3: " << std::endl << m3.GetInverted() << std::endl;
    // std::cout << "glm_m3: " << std::endl << to_matrix4(glm::inverse(glm_m3)) << std::endl << std::endl;

    // //

    // std::cout << "-- GetDeterminant ---" << std::endl << std::endl;

    // std::cout << "m0:     " << m0.GetDeterminant() << std::endl;
    // std::cout << "glm_m0: " << glm::determinant(glm_m0) << std::endl << std::endl;

    // std::cout << "m1:     " << m1.GetDeterminant() << std::endl;
    // std::cout << "glm_m1: " << glm::determinant(glm_m1) << std::endl << std::endl;

    // std::cout << "m2:     " << m2.GetDeterminant() << std::endl;
    // std::cout << "glm_m2: " << glm::determinant(glm_m2) << std::endl << std::endl;

    // std::cout << "m3:     " << m3.GetDeterminant() << std::endl;
    // std::cout << "glm_m3: " << glm::determinant(glm_m3) << std::endl << std::endl;

    // -- END Transpose / Invert / GetDerminant -------

    // -- perspective / ortho -------------------------

    // fov negative             V
    // fov = 0 (exception)      V
    // aspect = 0 (exception)   V
    // aspect negative          V
    // aspect [0, 1]            V
    // aspect > 1               V
    // near > far               V
    // near negative            V
    // far negative             V
    // near = far (exception)   V

    // Matrix4   m0     = Matrix4::CreatePerspective(90, -0.5f, 1, -100);
    // glm::mat4 glm_m0 = glm::perspective(to_radians(90.0f), -0.5f, 1.0f, -100.0f);
    // Matrix4   m1     = Matrix4::CreatePerspective(30.0f, 12.7f, 10.0f, 2000.0f);
    // glm::mat4 glm_m1 = glm::perspective(to_radians(30.0f), 12.7f, 10.0f, 2000.0f);
    // Matrix4   m2     = Matrix4::CreatePerspective(30.0f, 12.7f, -10.0f, 2000.0f);
    // glm::mat4 glm_m2 = glm::perspective(to_radians(30.0f), 12.7f, -10.0f, 2000.0f);
    // Matrix4   m3     = Matrix4::CreatePerspective(30.0f, 0.0f, 100.0f, 1.0f);
    // glm::mat4 glm_m3 = glm::perspective(to_radians(30.0f), 0.0f, 100.0f, 1.0f);
    // Matrix4   m4     = Matrix4::CreatePerspective(45.0f, 1.0f, 1.0f, 1.0f);
    // glm::mat4 glm_m4 = glm::perspective(to_radians(45.0f), 1.0f, 1.0f, 1.0f);

    // //

    // std::cout << "-- perpective ---" << std::endl << std::endl;

    // std::cout << "m0:     " << std::endl << m0 << std::endl;
    // std::cout << "glm_m0: " << std::endl << to_matrix4(glm_m0) << std::endl << std::endl;

    // std::cout << "m1:     " << std::endl << m1 << std::endl;
    // std::cout << "glm_m1: " << std::endl << to_matrix4(glm_m1) << std::endl << std::endl;

    // std::cout << "m2:     " << std::endl << m2 << std::endl;
    // std::cout << "glm_m2: " << std::endl << to_matrix4(glm_m2) << std::endl << std::endl;

    // std::cout << "m3:     " << std::endl << m3 << std::endl;
    // std::cout << "glm_m3: " << std::endl << to_matrix4(glm_m3) << std::endl << std::endl;

    // std::cout << "m4:     " << std::endl << m4 << std::endl;
    // std::cout << "glm_m4: " << std::endl << to_matrix4(glm_m4) << std::endl << std::endl;

    // ------------------------------------------

    // near > far               V
    // near negative            V
    // far negative             V
    // left > right             V
    // left negative            V
    // right negative           V
    // bottom > top             V
    // bottom negative          V
    // top negative             V
    // far = near (exception)   V
    // right = left (exception) V
    // top = bottom (exception) V

    // Matrix4   m0     = Matrix4::CreateOrtho(5.0f, 100.0f, 1.0f, 10.0f, 100.0f, 1.0f);
    // glm::mat4 glm_m0 = glm::ortho(5.0f, 100.0f, 1.0f, 10.0f, 100.0f, 1.0f);
    // Matrix4   m1     = Matrix4::CreateOrtho(5.0f, 100.0f, 1.0f, 10.0f, -1.0f, 100.0f);
    // glm::mat4 glm_m1 = glm::ortho(5.0f, 100.0f, 1.0f, 10.0f, -1.0f, 100.0f);
    // Matrix4   m2     = Matrix4::CreateOrtho(5.0f, 100.0f, 1.0f, 10.0f, 1.0f, -100.0f);
    // glm::mat4 glm_m2 = glm::ortho(5.0f, 100.0f, 1.0f, 10.0f, 1.0f, -100.0f);

    // Matrix4   m3     = Matrix4::CreateOrtho(50.0f, 200.0f, 96.0f, 17.0f, 1.0f, 100.0f);
    // glm::mat4 glm_m3 = glm::ortho(50.0f, 200.0f, 96.0f, 17.0f, 1.0f, 100.0f);
    // Matrix4   m4     = Matrix4::CreateOrtho(50.0f, 200.0f, -17.0f, 96.0f, 1.0f, 100.0f);
    // glm::mat4 glm_m4 = glm::ortho(50.0f, 200.0f, -17.0f, 96.0f, 1.0f, 100.0f);
    // Matrix4   m5     = Matrix4::CreateOrtho(50.0f, 200.0f, 17.0f, -96.0f, 1.0f, 100.0f);
    // glm::mat4 glm_m5 = glm::ortho(50.0f, 200.0f, 17.0f, -96.0f, 1.0f, 100.0f);

    // Matrix4   m6     = Matrix4::CreateOrtho(307.0f, 42.0f, 23.0f, 230.0f, 18.0f, 201.0f);
    // glm::mat4 glm_m6 = glm::ortho(307.0f, 42.0f, 23.0f, 230.0f, 18.0f, 201.0f);
    // Matrix4   m7     = Matrix4::CreateOrtho(-42.0f, 307.0f, 23.0f, 230.0f, 18.0f, 201.0f);
    // glm::mat4 glm_m7 = glm::ortho(-42.0f, 307.0f, 23.0f, 230.0f, 18.0f, 201.0f);
    // Matrix4   m8     = Matrix4::CreateOrtho(42.0f, -307.0f, 23.0f, 230.0f, 18.0f, 201.0f);
    // glm::mat4 glm_m8 = glm::ortho(42.0f, -307.0f, 23.0f, 230.0f, 18.0f, 201.0f);

    // Matrix4   m9      = Matrix4::CreateOrtho(307.0f, 42.0f, 23.0f, 230.0f, 100.0f, 100.0f);
    // glm::mat4 glm_m9  = glm::ortho(307.0f, 42.0f, 23.0f, 230.0f, 100.0f, 100.0f);
    // Matrix4   m10     = Matrix4::CreateOrtho(-42.0f, 307.0f, 50.0f, 50.0f, 18.0f, 201.0f);
    // glm::mat4 glm_m10 = glm::ortho(-42.0f, 307.0f, 50.0f, 50.0f, 18.0f, 201.0f);
    // Matrix4   m11     = Matrix4::CreateOrtho(-7.0f, -7.0f, 23.0f, 230.0f, 18.0f, 201.0f);
    // glm::mat4 glm_m11 = glm::ortho(-7.0f, -7.0f, 23.0f, 230.0f, 18.0f, 201.0f);

    // //

    // std::cout << "-- ortho ---" << std::endl << std::endl;

    // std::cout << "m0: " << std::endl << m0 << std::endl;
    // std::cout << "glm_m0: " << std::endl << to_matrix4(glm_m0) << std::endl << std::endl;

    // std::cout << "m1: " << std::endl << m1 << std::endl;
    // std::cout << "glm_m1: " << std::endl << to_matrix4(glm_m1) << std::endl << std::endl;

    // std::cout << "m2: " << std::endl << m2 << std::endl;
    // std::cout << "glm_m2: " << std::endl << to_matrix4(glm_m2) << std::endl << std::endl;

    // std::cout << "m3: " << std::endl << m3 << std::endl;
    // std::cout << "glm_m3: " << std::endl << to_matrix4(glm_m3) << std::endl << std::endl;

    // std::cout << "m4: " << std::endl << m4 << std::endl;
    // std::cout << "glm_m4: " << std::endl << to_matrix4(glm_m4) << std::endl << std::endl;

    // std::cout << "m5: " << std::endl << m5 << std::endl;
    // std::cout << "glm_m5: " << std::endl << to_matrix4(glm_m5) << std::endl << std::endl;

    // std::cout << "m6: " << std::endl << m6 << std::endl;
    // std::cout << "glm_m6: " << std::endl << to_matrix4(glm_m6) << std::endl << std::endl;

    // std::cout << "m7: " << std::endl << m7 << std::endl;
    // std::cout << "glm_m7: " << std::endl << to_matrix4(glm_m7) << std::endl << std::endl;

    // std::cout << "m8: " << std::endl << m8 << std::endl;
    // std::cout << "glm_m8: " << std::endl << to_matrix4(glm_m8) << std::endl << std::endl;

    // std::cout << "m9: " << std::endl << m9 << std::endl;
    // std::cout << "glm_m9: " << std::endl << to_matrix4(glm_m9) << std::endl << std::endl;

    // std::cout << "m10: " << std::endl << m10 << std::endl;
    // std::cout << "glm_m10: " << std::endl << to_matrix4(glm_m10) << std::endl << std::endl;

    // std::cout << "m11: " << std::endl << m11 << std::endl;
    // std::cout << "glm_m11: " << std::endl << to_matrix4(glm_m11) << std::endl << std::endl;

    //-- END perspective / ortho ----------------------
}
