#include "VDEngine/Renderer/MaterialManager.h"

using namespace VDEngine;

MaterialManager::MaterialManager()
{
    m_default_material = new Material();
}

Material * MaterialManager::LoadMaterial(Shader * shader, const glm::vec3 & diffuse_color,
                                         std::vector<Texture *> textures)
{
    Material * material = new Material();

    material->shader        = shader;
    material->textures      = textures;
    material->diffuse_color = diffuse_color;
    // for (int i = 0; i < textures.size(); i++)
    //     material->textures.push_back(textures[i]);

    if (material != nullptr)
    {
        m_materials.push_back(material);
        return material;
    }
    else
    {
        std::cout << "[Material Manager] Failed to load material." << std::endl;
        return nullptr;
    }
}

Material * MaterialManager::GetMaterial(uuids::uuid material_uuid)
{
    std::list<Material *>::iterator result =
        std::find_if(m_materials.begin(), m_materials.end(),
                     [material_uuid](Material * m) { return (material_uuid == m->GetUUID()); });

    if (result != m_materials.end())
        return *result;

    return nullptr;
}

Material * MaterialManager::GetMaterial()
{
    return (m_default_material);
}