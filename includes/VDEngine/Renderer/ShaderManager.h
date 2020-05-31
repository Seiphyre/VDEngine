#ifndef VDENGINE_SHADER_MANAGER_H_
#define VDENGINE_SHADER_MANAGER_H_

// C++ Standard libs
#include <list>
#include <string>
//#include <type_traits>

// External libs
#include "stduuid/uuid.h"

// Internal headers
#include "VDEngine/Core/Singleton.h"
#include "VDEngine/Renderer/Shader.h"

namespace VDEngine
{

class ShaderManager : public Singleton<ShaderManager>
{
    friend class Singleton<ShaderManager>;

  private:
    std::list<Shader *> m_shaders;
    Shader *            m_default_shader;

    ShaderManager();

  public:
    Shader * LoadShader(const std::string & vert_file_name, const std::string & frag_file_name);
    Shader * GetShader(uuids::uuid shader_uuid);
    Shader * GetShader();

    // template <class T> T * LoadShader()
    // {
    //     static_assert(std::is_base_of<Shader, T>::value,
    //                   "Error: T in ShaderManager::LoadShader is not base of AShader.");

    //     T * shader = new T();
    //     shader->Build();

    //     m_shaders.push_back(shader);

    //     return shader;
    // }

    // template <class T> T * GetShader()
    // {
    //     static_assert(std::is_base_of<Shader, T>::value,
    //                   "Error: T in ShaderManager::GetShader is not base of AShader.");

    //     std::list<Shader *>::iterator it = m_shaders.begin();
    //     for (int i = 0; i < m_shaders.size(); i++)
    //     {
    //         T * ptr = dynamic_cast<T *>(*it);
    //         if (ptr)
    //         {
    //             return ptr;
    //         }
    //         it++;
    //     }

    //     return LoadShader<T>();
    // }
};

} // namespace VDEngine

#endif /* VDENGINE_SHADER_MANAGER_H_ */