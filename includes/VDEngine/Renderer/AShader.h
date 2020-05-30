#ifndef VDENGINE_ASHADER_H_
#define VDENGINE_ASHADER_H_

// C++ Standard libs
#include <iostream>

// External libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Internal headers
#include "VDEngine/Core/FileHandler.h"

namespace VDEngine
{

class AShader
{
  public:
    AShader();
    virtual ~AShader();

    virtual void Build();

    unsigned int GetShaderProgramId();

    void SetBool(const std::string & name, bool value) const;

    void SetInt(const std::string & name, int value) const;

    void SetFloat(const std::string & name, float value) const;

    void SetVec2(const std::string & name, const glm::vec2 & value) const;
    void SetVec2(const std::string & name, float x, float y) const;

    void SetVec3(const std::string & name, const glm::vec3 & value) const;
    void SetVec3(const std::string & name, float x, float y, float z) const;

    void SetVec4(const std::string & name, const glm::vec4 & value) const;
    void SetVec4(const std::string & name, float x, float y, float z, float w);

    void SetMat2(const std::string & name, const glm::mat2 & mat) const;
    void SetMat3(const std::string & name, const glm::mat3 & mat) const;
    void SetMat4(const std::string & name, const glm::mat4 & mat) const;

    virtual void Use() const;

  protected:
    virtual void SetVertexShaderSource()   = 0;
    virtual void SetFragmentShaderSource() = 0;

    virtual void CompileVertexShader();
    virtual void CompileFragmentShader();
    virtual void LinkProgram() const;

    unsigned int m_vert_shader_id;
    std::string  m_vert_shader_source;

    unsigned int m_frag_shader_id;
    std::string  m_frag_shader_source;

    unsigned int m_shader_program_id;
};

} // namespace VDEngine

#endif /* VDENGINE_ASHADER_H_ */