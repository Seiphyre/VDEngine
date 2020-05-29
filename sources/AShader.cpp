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

void AShader::LinkProgram() const
{
    glAttachShader(m_shader_program_id, m_vert_shader_id);
    glAttachShader(m_shader_program_id, m_frag_shader_id);
    glLinkProgram(m_shader_program_id);

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

// utility uniform functions
// ------------------------------------------------------------------------
void AShader::SetBool(const std::string & name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_shader_program_id, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void AShader::SetInt(const std::string & name, int value) const
{
    glUniform1i(glGetUniformLocation(m_shader_program_id, name.c_str()), value);
}
// ------------------------------------------------------------------------
void AShader::SetFloat(const std::string & name, float value) const
{
    glUniform1f(glGetUniformLocation(m_shader_program_id, name.c_str()), value);
}
// ------------------------------------------------------------------------
void AShader::SetVec2(const std::string & name, const glm::vec2 & value) const
{
    glUniform2fv(glGetUniformLocation(m_shader_program_id, name.c_str()), 1, &value[0]);
}
void AShader::SetVec2(const std::string & name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(m_shader_program_id, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void AShader::SetVec3(const std::string & name, const glm::vec3 & value) const
{
    glUniform3fv(glGetUniformLocation(m_shader_program_id, name.c_str()), 1, &value[0]);
}
void AShader::SetVec3(const std::string & name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(m_shader_program_id, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void AShader::SetVec4(const std::string & name, const glm::vec4 & value) const
{
    glUniform4fv(glGetUniformLocation(m_shader_program_id, name.c_str()), 1, &value[0]);
}
void AShader::SetVec4(const std::string & name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(m_shader_program_id, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void AShader::SetMat2(const std::string & name, const glm::mat2 & mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_shader_program_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void AShader::SetMat3(const std::string & name, const glm::mat3 & mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_shader_program_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void AShader::SetMat4(const std::string & name, const glm::mat4 & mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_shader_program_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}