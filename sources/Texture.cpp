#include "VDEngine/Renderer/Texture.h"

using namespace VDEngine;

Texture::Texture()
{
    m_texWrapSParam     = GL_REPEAT;
    m_texWrapTParam     = GL_REPEAT;
    m_texMinFilterParam = GL_LINEAR;
    m_texMagFilterParam = GL_LINEAR;

    m_file_name = "";

    // UUID
    m_uuid = uuids::uuid_system_generator{}();
    // assert(!m_uuid.is_nil());
    // assert(m_uuid.version() == uuids::uuid_version::random_number_based);
    // assert(m_uuid.variant() == uuids::uuid_variant::rfc);

    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);

    GLubyte data[] = {255, 255, 255, 255};

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_texWrapSParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_texWrapTParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_texMinFilterParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_texMagFilterParam);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

Texture::Texture(const std::string & text_name)
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

    m_texWrapSParam     = GL_REPEAT;
    m_texWrapTParam     = GL_REPEAT;
    m_texMinFilterParam = GL_LINEAR;
    m_texMagFilterParam = GL_LINEAR;

    // UUID
    m_uuid = uuids::uuid_system_generator{}();
    // assert(!m_uuid.is_nil());
    // assert(m_uuid.version() == uuids::uuid_version::random_number_based);
    // assert(m_uuid.variant() == uuids::uuid_variant::rfc);

    // uuids::uuid id2 = uuids::uuid::from_string("5c4f2287-f8d4-40a8-8398-2089dfb3a825").value();

    Create(text_name);
}

uuids::uuid Texture::GetUUID() const
{
    return (m_uuid);
}

const std::string Texture::GetFileName() const
{
    return (m_file_name);
}

void Texture::Create(const std::string & text_name)
{
    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);

    // Texture : Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_texWrapSParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_texWrapTParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_texMinFilterParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_texMagFilterParam);

    m_file_name = text_name;

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

void Texture::Bind(int textureActiveId) const
{
    glActiveTexture(GL_TEXTURE0 + textureActiveId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
}