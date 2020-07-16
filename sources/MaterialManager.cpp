#include "VDEngine/Renderer/MaterialManager.h"

using namespace VDEngine;

MaterialManager::MaterialManager()
{
    m_default_material = new Material();
}

Material * MaterialManager::LoadMaterial(Shader * shader, float shininess, const Vector3 & diffuse_color,
                                         const Vector3 & specular_color, Texture * diffuse_map, Texture * specular_map)
{
    Material * material = new Material();

    material->shader         = shader;
    material->diffuse_map    = diffuse_map;
    material->diffuse_color  = diffuse_color;
    material->specular_map   = specular_map;
    material->specular_color = specular_color;
    material->shininess      = shininess;

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