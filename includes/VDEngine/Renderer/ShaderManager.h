#ifndef VDENGINE_SHADER_MANAGER_H_
#define VDENGINE_SHADER_MANAGER_H_

// C++ Standard libs
#include <list>
#include <type_traits>

// Internal headers
#include "VDEngine/Core/Singleton.h"
#include "VDEngine/Renderer/AShader.h"
#include "VDEngine/Renderer/DefaultShader.h"

namespace VDEngine
{

class ShaderManager : public Singleton<ShaderManager>
{
    friend class Singleton<ShaderManager>;

  private:
    std::list<AShader *> m_shaders;

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

        m_shaders.push_back(shader);

        return shader;
    }

    template <class T> T * GetShader()
    {
        static_assert(std::is_base_of<AShader, T>::value,
                      "Error: T in ShaderManager::GetShader is not base of AShader.");

        std::list<AShader *>::iterator it = m_shaders.begin();
        for (int i = 0; i < m_shaders.size(); i++)
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

}

#endif /* VDENGINE_SHADER_MANAGER_H_ */