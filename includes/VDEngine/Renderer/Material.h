

#ifndef VDENGINE_META_HEADER
#define VDENGINE_META_HEADER

#include "metaStuff/Meta.h"

#endif /* VDENGINE_META_HEADER */

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

#include "VDEngine/Math/Vectors.hpp"

namespace VDEngine
{

#define DIFFUSE_MAP_TEXT_UNIT 0
#define SPECULAR_MAP_TEXT_UNIT 1

class Material
{
    friend auto meta::registerMembers<VDEngine::Material>();
    
  public:
    Material();
    ~Material();

    uuids::uuid GetUUID();
    // void AddTexture(uuids::uuid texture_uuid);
    // void AddTexture(const Texture * texture);

    Shader * shader;

    Vector3   diffuse_color;
    Texture * diffuse_map;

    Vector3   specular_color;
    Texture * specular_map;

    float shininess;

  private:
    uuids::uuid m_uuid;
};

} // namespace VDEngine

#endif /* VDENGINE_MATERIAL_H_ */

#ifndef META_REGISTER_VDENGINE_MATERIAL
#define META_REGISTER_VDENGINE_MATERIAL

template <>
inline auto meta::registerMembers< VDEngine::Material >() 
{
    return meta::members( 
meta::member("shader", &VDEngine::Material::shader),
meta::member("diffuse_color", &VDEngine::Material::diffuse_color),
meta::member("diffuse_map", &VDEngine::Material::diffuse_map),
meta::member("specular_color", &VDEngine::Material::specular_color),
meta::member("specular_map", &VDEngine::Material::specular_map),
meta::member("shininess", &VDEngine::Material::shininess),
meta::member("m_uuid", &VDEngine::Material::m_uuid) 
    );
}

#endif /* META_REGISTER_VDENGINE_MATERIAL */

