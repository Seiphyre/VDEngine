#ifndef VDENGINE_AOBJECT_H_
#define VDENGINE_AOBJECT_H_

// C++ Standard libs
#include <math.h>
#include <vector>

// External libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Internal headers
#include "VDEngine/Core/Transform.h"

#include "VDEngine/Renderer/DefaultShader.h"
#include "VDEngine/Renderer/ShaderManager.h"
#include "VDEngine/Renderer/Texture.h"

namespace VDEngine
{

class AObject
{
  public:
    AObject();
    AObject(AShader * shader);
    AObject(const AObject &) = default;
    ~AObject();

    AObject & operator=(const AObject &) = default;

    void Init();

    Transform * GetTransform() const;
    void        SetShader(AShader * shader);
    void        AddTexture(const std::string & text_name);
    void        AddTexture(const Texture * texture);

    void Draw(const glm::mat4 & view, const glm::mat4 & projection, GLenum mode = GL_FILL) const;

  protected:
    void AttribShaderParams();

    unsigned int m_VAO;

    std::vector<float>        m_vert_positions;
    std::vector<float>        m_vert_colors;
    std::vector<float>        m_vert_textCoords;
    std::vector<unsigned int> m_elem_indices;

    AShader *                    m_shader;
    std::vector<const Texture *> m_textures;
    Transform *                  m_transform;
};

} // namespace VDEngine

#endif /* VDENGINE_AOBJECT_H_ */