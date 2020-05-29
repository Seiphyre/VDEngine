#include "VDEngine/Renderer/Texture.h"

using namespace VDEngine;

Texture::Texture()
{
    _texWrapSParam     = GL_REPEAT;
    _texWrapTParam     = GL_REPEAT;
    _texMinFilterParam = GL_LINEAR;
    _texMagFilterParam = GL_LINEAR;
}

Texture::Texture(const std::string text_name)
{
    // Texture Wrapping
    // GL_REPEAT            : The default behavior for textures. Repeats the texture image.
    // GL_MIRRORED_REPEAT   : Same as GL_REPEAT but mirrors the image with each repeat.
    // GL_CLAMP_TO_EDGE     : Clamps the coordinates between 0 and 1. The result is that higher coordinates become
    // clamped to the edge, resulting in a stretched edge pattern. GL_CLAMP_TO_BORDER   : Coordinates outside the range
    // are now given a user-specified border color.

    // Texture Wrapping can be set for S (GL_TEXTURE_WRAP_S) and T (GL_TEXTURE_WRAP_T)
    // S = U = X = Horizontal
    // T = V = Y = Vertical

    // Texture Filtering
    // GL_NEAREST : (also known as nearest neighbor or point filtering) is the default texture filtering method of
    // OpenGL.
    //              When set to GL_NEAREST, OpenGL selects the texel that center is closest to the texture coordinate.
    // GL_LINEAR :  (also known as (bi)linear filtering) takes an interpolated value from the texture coordinate's
    // neighboring texels, approximating a color between the texels.
    //              The smaller the distance from the texture coordinate to a texel's center, the more that texel's
    //              color contributes to the sampled color.

    // Texture filtering can be set for magnifying (GL_TEXTURE_MAG_FILTER) and minifying (GL_TEXTURE_MIN_FILTER)
    // operations (when scaling up or downwards) so you could for example use nearest neighbor filtering when textures
    // are scaled downwards and linear filtering for upscaled textures.

    _texWrapSParam     = GL_REPEAT;
    _texWrapTParam     = GL_REPEAT;
    _texMinFilterParam = GL_LINEAR;
    _texMagFilterParam = GL_LINEAR;

    Create(text_name);
}

void Texture::Create(const std::string text_name)
{
    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);

    // Texture : Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _texWrapSParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _texWrapTParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _texMinFilterParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _texMagFilterParam);

    // Texture : Data
    Image * textureImage = new Image(text_name);

    if (textureImage->GetData() != NULL)
    {
        GLuint format = Image::ToGLFormat(textureImage->GetFormat());

        glTexImage2D(GL_TEXTURE_2D, 0 /* Mipmap level */, format, textureImage->GetWidth(), textureImage->GetHeight(),
                     0, format, GL_UNSIGNED_BYTE, textureImage->GetData());
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to create texture" << std::endl;
    }

    delete (textureImage);
}

void Texture::Bind(AShader * shader, int textureActiveId) const
{
    glActiveTexture(GL_TEXTURE0 + textureActiveId);
    glBindTexture(GL_TEXTURE_2D, _textureId);
}