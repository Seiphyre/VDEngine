#include "VDEngine/Renderer/Material.h"

using namespace VDEngine;

Material::Material()
{
    m_uuid = uuids::uuid_system_generator{}();
    shader = ShaderManager::getInstance()->GetShader();
}

Material::~Material()
{
}

uuids::uuid Material::GetUUID()
{
    return (m_uuid);
}

// void Material::AddTexture(uuids::uuid texture_uuid)
// {
//     Texture * texture = TextureManager::getInstance()->GetTexture(texture_uuid);

//     if (texture != nullptr)
//         textures.push_back(texture);
//     else
//     {
//         std::cout << "[AObject] Could not add Texture to the object." << std::endl;
//     }
// }
// void Material::AddTexture(const Texture * texture)
// {
//     textures.push_back(texture);
// }