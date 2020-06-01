#ifndef VDENGINE_MATERIAL_H_
#define VDENGINE_MATERIAL_H_

// C++ Standard libs
#include <vector>

// External libs
#include "stduuid/uuid.h"

// Internal headers
#include "VDEngine/Renderer/ShaderManager.h"
#include "VDEngine/Renderer/Shader.h"
#include "VDEngine/Renderer/TextureManager.h"
#include "VDEngine/Renderer/Texture.h"

namespace VDEngine
{

#define DIFFUSE_MAP_TEXT_UNIT 0
#define SPECULAR_MAP_TEXT_UNIT 1

class Material
{
  public:
    Material();
    ~Material();

    uuids::uuid GetUUID();
    // void AddTexture(uuids::uuid texture_uuid);
    // void AddTexture(const Texture * texture);

    Shader * shader;

    glm::vec3 diffuse_color;
    Texture * diffuse_map;

    glm::vec3 specular_color;
    Texture * specular_map;

    float shininess;

  private:
    uuids::uuid m_uuid;
};

} // namespace VDEngine

#endif /* VDENGINE_MATERIAL_H_ */