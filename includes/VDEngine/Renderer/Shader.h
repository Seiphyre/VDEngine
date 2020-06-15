#ifndef VDENGINE_SHADER_H_
#define VDENGINE_SHADER_H_

// C++ Standard libs
#include <iostream>
#include <vector>

// External libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "stduuid/uuid.h"

// Internal headers
#include "VDEngine/Core/FileHandler.h"

namespace VDEngine
{

// MESH
// VERTEX_POSITIONS
// VERTEX_COLORS
// VERTEX_TEXELS
// NORMALS

// MATERIAL -------
// TEXTURES
// AMBIANT COLOR
// DIFFUSE COLOR
// SPECULAR COLOR
// TEXTURE UV ?

// TRANSFORM ------
// MODEL MATRIX

// ENGINE ---------
// CAMERA (VIEW, PROJECTION)
// LIGHTS
// TIMER

struct s_shaderParameter
{
    int         index;
    std::string name;
    GLenum      type;
};

class Shader
{
  public:
    Shader();
    Shader(const std::string & vert_file_path, const std::string & frag_file_path);
    ~Shader();

    void Build();

    uuids::uuid                    GetUUID() const;
    unsigned int                   GetShaderProgramId();
    std::vector<s_shaderParameter> GetAttributes() const;
    std::vector<s_shaderParameter> GetUniforms() const;

    void Use() const;

  protected:
    void CompileVertexShader();
    void CompileFragmentShader();
    void LinkProgram();

    std::vector<s_shaderParameter> m_attributes;
    std::vector<s_shaderParameter> m_uniforms;

    bool m_hasBeenBuild;

    unsigned int m_vert_shader_id;
    std::string  m_vert_shader_source;
    std::string  m_vert_shader_name;
    std::string  m_vert_shader_path;

    unsigned int m_frag_shader_id;
    std::string  m_frag_shader_source;
    std::string  m_frag_shader_name;
    std::string  m_frag_shader_path;

    unsigned int m_shader_program_id;
    uuids::uuid  m_uuid;
};

} // namespace VDEngine

#endif /* VDENGINE_SHADER_H_ */