#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "VDEngine/Core/Image.h"
#include "VDEngine/Renderer/AShader.h"

class Texture
{
  private:
    unsigned int _textureId;

    GLint _texWrapSParam;
    GLint _texWrapTParam;
    GLint _texMinFilterParam;
    GLint _texMagFilterParam;

  public:
    Texture();
    Texture(const std::string text_name);

    void Create(const std::string text_name);
    void Bind(AShader * shader, int textureActiveId = 0);
};

#endif /* Texture_H_ */