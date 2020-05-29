#include "DefaultShader.h"

void DefaultShader::SetVertexShaderSource()
{
    if (!m_vert_shader_source.empty())
        return;

    // m_vert_shader_source = "#version 330 core\n"
    //                       "layout (location = 0) in vec3 aPos;\n"
    //                       "void main()\n"
    //                       "{\n"
    //                       "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    //                       "}\0";

    m_vert_shader_source = FileHandler::getInstance()->LoadShader("DefaultShader.vert");
}

void DefaultShader::SetFragmentShaderSource()
{
    if (!m_frag_shader_source.empty())
        return;

    // m_frag_shader_source = "#version 330 core\n"
    //                         "out vec4 FragColor;\n"
    //                         "void main()\n"
    //                         "{\n"
    //                         "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    //                         "}\0";

    m_frag_shader_source = FileHandler::getInstance()->LoadShader("DefaultShader.frag");
}