#ifndef VDENGINE_MATERIAL_MANAGER_H_
#define VDENGINE_MATERIAL_MANAGER_H_

// C++ Standard libs
#include <list>

// External libs
#include <glm/glm.hpp>

// Internal headers
#include "VDEngine/Core/Singleton.h"
#include "VDEngine/Renderer/Material.h"

namespace VDEngine
{

class MaterialManager : public Singleton<MaterialManager>
{
    friend class Singleton<MaterialManager>;

  private:
    std::list<Material *> m_materials;
    Material *            m_default_material;

    MaterialManager();

  public:
    Material * LoadMaterial(Shader * shader, float shininess = 64.0f,
                            const glm::vec3 & diffuse_color  = glm::vec3(1.0, 1.0, 1.0),
                            const glm::vec3 & specular_color = glm::vec3(1.0, 1.0, 1.0),
                            Texture * diffuse_map = nullptr, Texture * specular_map = nullptr);
    Material * GetMaterial(uuids::uuid shader_uuid);
    Material * GetMaterial();
};

} // namespace VDEngine

#endif /* VDENGINE_MATERIAL_MANAGER_H_ */