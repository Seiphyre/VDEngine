#include "VDEngine/Renderer/ShaderManager.h"

using namespace VDEngine;

ShaderManager::ShaderManager()
{
    m_default_shader = new Shader("Unlit_Default.vert", "Unlit_Default.frag");
    m_default_shader->Build();
}

Shader * ShaderManager::LoadShader(const std::string & vert_file_name, const std::string & frag_file_name)
{
    Shader * shader = new Shader(vert_file_name, frag_file_name);
    shader->Build();

    if (shader != nullptr)
    {
        m_shaders.push_back(shader);
        return shader;
    }
    else
    {
        std::cout << "[Shader Manager] Failed to load shader." << std::endl;
        return nullptr;
    }
}

Shader * ShaderManager::GetShader(uuids::uuid shader_uuid)
{
    std::list<Shader *>::iterator result = std::find_if(
        m_shaders.begin(), m_shaders.end(), [shader_uuid](Shader * s) { return (shader_uuid == s->GetUUID()); });

    if (result != m_shaders.end())
        return *result;

    return nullptr;
}

Shader * ShaderManager::GetShader()
{
    return (m_default_shader);
}