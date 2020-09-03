

#ifndef VDENGINE_META_HEADER
#define VDENGINE_META_HEADER

#include "metaStuff/Meta.h"

#endif /* VDENGINE_META_HEADER */

#ifndef VDENGINE_TEXTURE_H_
#define VDENGINE_TEXTURE_H_

// C++ Standard libs
#include <string>

// External libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stduuid/uuid.h"

// Internal headers
#include "VDEngine/Core/Image.h"

namespace VDEngine
{

class Texture
{
    friend auto meta::registerMembers<VDEngine::Texture>();
    
  private:
    unsigned int m_textureId;
    uuids::uuid  m_uuid;

    GLint m_texWrapSParam;
    GLint m_texWrapTParam;
    GLint m_texMinFilterParam;
    GLint m_texMagFilterParam;

    std::string m_file_name;
    std::string m_file_path;

  public:
    Texture();
    Texture(const std::string & file_path);

    uuids::uuid       GetUUID() const;
    const std::string GetFileName() const;

    void Create(const std::string & file_path);
    void Bind(int textureActiveId = 0) const;
};

} // namespace VDEngine

#endif /* VDENGINE_TEXTURE_H_ */

#ifndef META_REGISTER_VDENGINE_TEXTURE
#define META_REGISTER_VDENGINE_TEXTURE

template <>
inline auto meta::registerMembers< VDEngine::Texture >() 
{
    return meta::members( 
meta::member("m_textureId", &VDEngine::Texture::m_textureId),
meta::member("m_uuid", &VDEngine::Texture::m_uuid),
meta::member("m_texWrapSParam", &VDEngine::Texture::m_texWrapSParam),
meta::member("m_texWrapTParam", &VDEngine::Texture::m_texWrapTParam),
meta::member("m_texMinFilterParam", &VDEngine::Texture::m_texMinFilterParam),
meta::member("m_texMagFilterParam", &VDEngine::Texture::m_texMagFilterParam),
meta::member("m_file_name", &VDEngine::Texture::m_file_name),
meta::member("m_file_path", &VDEngine::Texture::m_file_path) 
    );
}

#endif /* META_REGISTER_VDENGINE_TEXTURE */

