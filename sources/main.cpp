#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <unistd.h>
#include <mach-o/dyld.h>

#include "VDEngine/Renderer/Camera.h"
#include "VDEngine/Renderer/DefaultShader.h"
#include "VDEngine/Renderer/ShaderManager.h"
#include "VDEngine/Renderer/CubeObject.h"
#include "VDEngine/Renderer/PlaneObject.h"

#include "VDEngine/Core/GameEngine.h"
#include "VDEngine/Core/FileHandler.h"
#include "VDEngine/Core/Time.h"
#include "VDEngine/Input/Input.h"

#include "../resources/scripts/FPSCameraController.h"

glm::mat4 CameraLookAt(glm::vec3 eyePos, glm::vec3 target)
{
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 zaxis = glm::normalize(eyePos - target);
    glm::vec3 xaxis = glm::normalize(glm::cross(up, zaxis));
    glm::vec3 yaxis = glm::normalize(glm::cross(zaxis, xaxis));

    glm::mat4 view = glm::mat4(1);
    view[0][0]     = xaxis.x;
    view[1][0]     = xaxis.y;
    view[2][0]     = xaxis.z;
    view[0][1]     = yaxis.x;
    view[1][1]     = yaxis.y;
    view[2][1]     = yaxis.z;
    view[0][2]     = zaxis.x;
    view[1][2]     = zaxis.y;
    view[2][2]     = zaxis.z;
    view[3][0]     = -glm::dot(xaxis, eyePos);
    view[3][1]     = -glm::dot(yaxis, eyePos);
    view[3][2]     = -glm::dot(zaxis, eyePos);

    // glm::vec3 zaxis = glm::normalize(eyePos - target);
    // glm::vec3 xaxis = glm::normalize(glm::cross(up, zaxis));
    // glm::vec3 yaxis = glm::normalize(glm::cross(zaxis, xaxis));

    // glm::mat4 view = glm::mat4(1);
    // view[0][0]     = xaxis.x;
    // view[1][0]     = xaxis.y;
    // view[2][0]     = xaxis.z;
    // view[0][1]     = yaxis.x;
    // view[1][1]     = yaxis.y;
    // view[2][1]     = yaxis.z;
    // view[0][2]     = zaxis.x;
    // view[1][2]     = zaxis.y;
    // view[2][2]     = zaxis.z;
    // view[3][0]     = -dot(xaxis, eyePos);
    // view[3][1]     = -dot(yaxis, eyePos);
    // view[3][2]     = -dot(zaxis, eyePos);

    return view;
}

glm::mat4 FPSViewRH(glm::vec3 eye, float pitch, float yaw)
{
    // yaw += glm::radians(glm::degrees(yaw) + 180.0f);
    // yaw = -yaw;

    // I assume the values are already converted to radians.
    float cosPitch = cos(pitch);
    float sinPitch = sin(pitch);
    float cosYaw   = cos(yaw);
    float sinYaw   = sin(yaw);

    glm::vec3 xaxis = glm::vec3(cosYaw, 0, -sinYaw);
    glm::vec3 yaxis = glm::vec3(sinYaw * sinPitch, cosPitch, cosYaw * sinPitch);
    glm::vec3 zaxis = glm::vec3(sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw);

    // Create a 4x4 view matrix from the right, up, forward and eye position vectors
    glm::mat4 view = glm::mat4(1);
    view[0][0]     = xaxis.x;
    view[1][0]     = xaxis.y;
    view[2][0]     = xaxis.z;
    view[0][1]     = yaxis.x;
    view[1][1]     = yaxis.y;
    view[2][1]     = yaxis.z;
    view[0][2]     = -zaxis.x;
    view[1][2]     = -zaxis.y;
    view[2][2]     = -zaxis.z;
    view[3][0]     = -glm::dot(xaxis, eye);
    view[3][1]     = -glm::dot(yaxis, eye);
    view[3][2]     = glm::dot(zaxis, eye);

    return view;

    // glm::mat4 matRoll  = glm::mat4(1.0f);
    // glm::mat4 matPitch = glm::mat4(1.0f);
    // glm::mat4 matYaw   = glm::mat4(1.0f);

    // // matRoll  = glm::rotate(matRoll, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    // matPitch = glm::rotate(matPitch, yaw, glm::vec3(0.0f, 1.0f, 0.0f));
    // matYaw   = glm::rotate(matYaw, pitch, glm::vec3(1.0f, 0.0f, 0.0f));

    // glm::mat4 rotate    = matRoll * matPitch * matYaw;
    // glm::mat4 translate = glm::mat4(1.0f);
    // translate           = glm::translate(translate, -eye);
    // return rotate * translate;
}

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
    // [...]

    // Load Textures
    // [...]

    // -- CREATE SCENE --------------------------------------------------

    // Create objects
    PlaneObj * floor = new PlaneObj();
    floor->Init();
    floor->AddTexture("measurement_floor.png");
    // floor->AddTexture("measurement_floor.png");

    floor->GetTransform()->Rotate(90.0f, X_3D_AXIS);
    floor->GetTransform()->scale = glm::vec3(10.0f, 10.0f, 1.0f);

    CubeObj * cube = new CubeObj();
    cube->Init();
    // cube->AddTexture("container.jpg");
    // cube->AddTexture("awesomeface.png");

    cube->GetTransform()->Translate(glm::vec3(0.0f, 0.5f, 0.0f));
    // cube->GetTransform()->Rotate(180.0f, X_3D_AXIS);
    // cube->GetTransform()->Rotate(180.0f, Y_3D_AXIS);
    // cube->GetTransform()->Rotate(45.0f, Z_3D_AXIS);
    // cube->GetTransform()->Rotate(-135.0f, Z_3D_AXIS);

    // Camera ----------

    VDEngine::Camera * camera = new VDEngine::Camera();

    camera->GetTransform()->Translate(glm::vec3(0.0f, 1.0f, 5.0f));
    camera->GetTransform()->Rotate(45.0f, Y_3D_AXIS);

    FPSCameraController * camera_controller = new FPSCameraController(camera);

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

        // const float radius = 5.0f;
        // float       camX   = sin((float)VDEngine::Time::GetTime() * 0.5f) * radius;
        // float       camZ   = cos((float)VDEngine::Time::GetTime() * 0.5f) * radius;

        // camera->GetTransform()->position = glm::vec3(camX, 1.0f, camZ);
        // // OU rotane 180 sur Y ?
        // camera->GetTransform()->LookAt(
        //     camera->GetTransform()->position +
        //     ((glm::vec3(0.0f, 0.5f, 0.0f) - camera->GetTransform()->position) * glm::vec3(1.0f, 1.0f, -1.0f)));

        // Renderer ------------------------------

        // Clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw

        cube->Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix());
        floor->Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix());

        // Display
        glfwSwapBuffers(s_window);

        VDEngine::Time::Update();
    }

    glfwTerminate();

    return 0;
}