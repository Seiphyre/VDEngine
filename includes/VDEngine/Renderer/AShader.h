#ifndef VDENGINE_ASHADER_H_
#define VDENGINE_ASHADER_H_

// C++ Standard libs
#include <iostream>
#include <vector>

// External libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Internal headers
#include "VDEngine/Core/FileHandler.h"

namespace VDEngine
{

enum e_componantType
{
    MESH,
    MATERIAL,
    LIGHTS
};

enum e_meshData : int
{
    VERTEX_POSITIONS = 0,
    VERTEX_COLORS    = 1,
    VERTEX_TEXELS    = 2
    // NORMALS
};

enum e_materialData : int
{
    TEXTURES = 0,
    // AMBIANT COLOR
    // DIFFUSE COLOR
    // SPECULAR COLOR
    // TEXTURE UV ?
};

// TRANSFORM ----
// MODEL MATRIX

// ENGINE ----
// CAMERA (VIEW, PROJECTION)
// LIGHTS
// TIMER

// struct s_vertexAttribData
// {
//     int             layout_index;
//     e_componantType component_type;
//     int             component_data_type;
// };

// struct s_uniformData
// {
//     const std::string name;
//     e_componantType   component_type;
//     int               component_data_type;
// };

struct s_shaderParameter
{
    int         index;
    std::string name;
    GLenum      type;
};

class AShader
{
  public:
    AShader();
    virtual ~AShader();

    virtual void Build();

    unsigned int GetShaderProgramId();

    std::vector<s_shaderParameter> GetAttributes() const;
    std::vector<s_shaderParameter> GetUniforms() const;

    virtual void Use() const;

  protected:
    virtual void SetVertexShaderSource()   = 0;
    virtual void SetFragmentShaderSource() = 0;

    virtual void CompileVertexShader();
    virtual void CompileFragmentShader();
    virtual void LinkProgram();

    std::vector<s_shaderParameter> m_attributes;
    std::vector<s_shaderParameter> m_uniforms;

    unsigned int m_vert_shader_id;
    std::string  m_vert_shader_source;

    unsigned int m_frag_shader_id;
    std::string  m_frag_shader_source;

    unsigned int m_shader_program_id;
};

} // namespace VDEngine

#endif /* VDENGINE_ASHADER_H_ */