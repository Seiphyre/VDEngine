#include "VDEngine/Renderer/TextureManager.h"

using namespace VDEngine;

TextureManager::TextureManager()
{
    m_default_texture = new Texture();
}

TextureManager::~TextureManager()
{
    delete m_default_texture;
}

Texture * TextureManager::LoadTexture(const std::string & text_file_name)
{
    Texture * texture = new Texture(text_file_name);

    if (texture != nullptr)
    {
        m_textures.push_back(texture);
        return texture;
    }
    else
    {
        std::cout << "[Texture Manager] Failed to load texture." << std::endl;
        return nullptr;
    }
}

Texture * TextureManager::GetTexture(uuids::uuid texture_uuid)
{
    std::list<Texture *>::iterator result = std::find_if(
        m_textures.begin(), m_textures.end(), [texture_uuid](Texture * t) { return (texture_uuid == t->GetUUID()); });

    if (result != m_textures.end())
        return *result;

    return nullptr;
}

Texture * TextureManager::GetTextureByFileName(const std::string & file_name)
{
    std::list<Texture *>::iterator result = std::find_if(
        m_textures.begin(), m_textures.end(), [file_name](Texture * t) { return (file_name == t->GetFileName()); });

    if (result != m_textures.end())
        return *result;

    return nullptr;
}

Texture * TextureManager::GetTexture()
{
    return (m_default_texture);
}