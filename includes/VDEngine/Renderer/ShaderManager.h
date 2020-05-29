#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <list>
#include <type_traits>

#include "VDEngine/Core/Singleton.h"
#include "VDEngine/Renderer/AShader.h"
#include "VDEngine/Renderer/DefaultShader.h"

class ShaderManager : public Singleton<ShaderManager>
{
    friend class Singleton<ShaderManager>;

  private:
    std::list<AShader *> _shaders;

    ShaderManager()
    {
    }

  public:
    template <class T> T * LoadShader()
    {
        static_assert(std::is_base_of<AShader, T>::value,
                      "Error: T in ShaderManager::LoadShader is not base of AShader.");

        T * shader = new T();
        shader->Build();

        _shaders.push_back(shader);

        return shader;
    }

    template <class T> T * GetShader()
    {
        static_assert(std::is_base_of<AShader, T>::value,
                      "Error: T in ShaderManager::GetShader is not base of AShader.");

        std::list<AShader *>::iterator it = _shaders.begin();
        for (int i = 0; i < _shaders.size(); i++)
        {
            T * ptr = dynamic_cast<T *>(*it);
            if (ptr)
            {
                return ptr;
            }
            it++;
        }

        return LoadShader<T>();
    }
};

#endif