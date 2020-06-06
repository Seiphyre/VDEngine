#ifndef VDENGINE_TEXTURE_MANAGER_H_
#define VDENGINE_TEXTURE_MANAGER_H_

// C++ Standard libs
#include <list>

// Internal headers
#include "VDEngine/Core/Singleton.h"
#include "VDEngine/Renderer/Texture.h"

namespace VDEngine
{

class TextureManager : public Singleton<TextureManager>
{
    friend class Singleton<TextureManager>;

  private:
    std::list<Texture *> m_textures;
    Texture *            m_default_texture;

    TextureManager();

  public:
    ~TextureManager();

    Texture * LoadTexture(const std::string & text_file_name);
    Texture * GetTexture(uuids::uuid texture_uuid);
    Texture * GetTextureByFileName(const std::string & file_name);
    Texture * GetTexture();
};

} // namespace VDEngine

#endif /* VDENGINE_TEXTURE_MANAGER_H_ */