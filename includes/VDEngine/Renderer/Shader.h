

#ifndef VDENGINE_META_HEADER
#define VDENGINE_META_HEADER

#include "metaStuff/Meta.h"

#endif /* VDENGINE_META_HEADER */

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
    friend auto meta::registerMembers<VDEngine::s_shaderParameter>();
    
    int         index;
    std::string name;
    GLenum      type;
};

class Shader
{
    friend auto meta::registerMembers<VDEngine::Shader>();
    
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

#ifndef META_REGISTER_VDENGINE_S_SHADERPARAMETER
#define META_REGISTER_VDENGINE_S_SHADERPARAMETER

template <>
inline auto meta::registerMembers< VDEngine::s_shaderParameter >() 
{
    return meta::members( 
meta::member("index", &VDEngine::s_shaderParameter::index),
meta::member("name", &VDEngine::s_shaderParameter::name),
meta::member("type", &VDEngine::s_shaderParameter::type) 
    );
}

#endif /* META_REGISTER_VDENGINE_S_SHADERPARAMETER */



#ifndef META_REGISTER_VDENGINE_SHADER
#define META_REGISTER_VDENGINE_SHADER

template <>
inline auto meta::registerMembers< VDEngine::Shader >() 
{
    return meta::members( 
meta::member("m_attributes", &VDEngine::Shader::m_attributes),
meta::member("m_uniforms", &VDEngine::Shader::m_uniforms),
meta::member("m_hasBeenBuild", &VDEngine::Shader::m_hasBeenBuild),
meta::member("m_vert_shader_id", &VDEngine::Shader::m_vert_shader_id),
meta::member("m_vert_shader_source", &VDEngine::Shader::m_vert_shader_source),
meta::member("m_vert_shader_name", &VDEngine::Shader::m_vert_shader_name),
meta::member("m_vert_shader_path", &VDEngine::Shader::m_vert_shader_path),
meta::member("m_frag_shader_id", &VDEngine::Shader::m_frag_shader_id),
meta::member("m_frag_shader_source", &VDEngine::Shader::m_frag_shader_source),
meta::member("m_frag_shader_name", &VDEngine::Shader::m_frag_shader_name),
meta::member("m_frag_shader_path", &VDEngine::Shader::m_frag_shader_path),
meta::member("m_shader_program_id", &VDEngine::Shader::m_shader_program_id),
meta::member("m_uuid", &VDEngine::Shader::m_uuid) 
    );
}

#endif /* META_REGISTER_VDENGINE_SHADER */

