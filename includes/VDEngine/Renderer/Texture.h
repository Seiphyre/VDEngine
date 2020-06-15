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