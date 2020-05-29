#include "VDEngine/Renderer/TextureManager.h"

using namespace VDEngine;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
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