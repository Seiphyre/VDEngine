#include "VDEngine/Renderer/AShader.h"

using namespace VDEngine;

AShader::AShader()
{
    m_vert_shader_id = glCreateShader(GL_VERTEX_SHADER);
    m_frag_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    m_shader_program_id = glCreateProgram();
}

AShader::~AShader()
{
}

std::vector<s_shaderParameter> AShader::GetAttributes() const
{
    return (m_attributes);
}
std::vector<s_shaderParameter> AShader::GetUniforms() const
{
    return (m_uniforms);
}

unsigned int AShader::GetShaderProgramId()
{
    return m_shader_program_id;
}

void AShader::CompileVertexShader()
{
    SetVertexShaderSource();

    const char * c_str = m_vert_shader_source.c_str();
    glShaderSource(m_vert_shader_id, 1, &c_str, NULL);
    glCompileShader(m_vert_shader_id);

    int  success;
    char infoLog[512];
    glGetShaderiv(m_vert_shader_id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(m_vert_shader_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void AShader::CompileFragmentShader()
{
    SetFragmentShaderSource();

    const char * c_str = m_frag_shader_source.c_str();
    glShaderSource(m_frag_shader_id, 1, &c_str, NULL);
    glCompileShader(m_frag_shader_id);

    int  success;
    char infoLog[512];
    glGetShaderiv(m_frag_shader_id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(m_frag_shader_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void AShader::LinkProgram()
{
    glAttachShader(m_shader_program_id, m_vert_shader_id);
    glAttachShader(m_shader_program_id, m_frag_shader_id);
    glLinkProgram(m_shader_program_id);

    int bufsize;
    glGetProgramiv(m_shader_program_id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &bufsize);
    // std::cout << "bufsize: " << bufsize << std::endl;

    int nb_of_attributes;
    glGetProgramiv(m_shader_program_id, GL_ACTIVE_ATTRIBUTES, &nb_of_attributes);
    // std::cout << "nb of attributes : " << nb_of_attributes << std::endl;

    for (int i = 0; i < nb_of_attributes; i++)
    {
        GLenum type;
        GLchar name[bufsize];

        glGetActiveAttrib(m_shader_program_id, i, bufsize, NULL, NULL, &type, name);

        s_shaderParameter param = {
            i,                 // index
            std::string(name), // name
            type,              // type
        };

        // std::cout << "[" << param.index << "] name: " << param.name << " type: " << param.type << std::endl;

        m_attributes.push_back(param);
    }

    glGetProgramiv(m_shader_program_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &bufsize);
    // std::cout << std::endl << "bufsize: " << bufsize << std::endl;

    int nb_of_uniforms;
    glGetProgramiv(m_shader_program_id, GL_ACTIVE_UNIFORMS, &nb_of_uniforms);
    // std::cout << "nb of uniforms : " << nb_of_uniforms << std::endl;

    for (int i = 0; i < nb_of_uniforms; i++)
    {
        GLenum type;
        GLchar name[bufsize];

        glGetActiveUniform(m_shader_program_id, i, bufsize, NULL, NULL, &type, name);

        s_shaderParameter param = {
            i,                 // index
            std::string(name), // name
            type,              // type
        };

        // std::cout << "[" << param.index << "] name: " << param.name << " type: " << param.type << std::endl;

        m_uniforms.push_back(param);
    }

    int  success;
    char infoLog[512];
    glGetProgramiv(m_shader_program_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_shader_program_id, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void AShader::Build()
{
    CompileVertexShader();
    CompileFragmentShader();

    LinkProgram();

    glDeleteShader(m_vert_shader_id);
    glDeleteShader(m_frag_shader_id);
}

void AShader::Use() const
{
    glUseProgram(m_shader_program_id);
}