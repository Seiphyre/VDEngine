#ifndef AOBJECT_H_
#define AOBJECT_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include <vector>

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
    ~AObject();

    void Init();

    Transform * GetTransform() const;
    void                  SetShader(AShader * shader);
    void                  AddTexture(const std::string & text_name);
    void                  AddTexture(Texture * texture);

    void Draw(const glm::mat4 & view, const glm::mat4 & projection, GLenum mode = GL_FILL) const;

  protected:
    void AttribShaderParams();

    unsigned int m_VAO;

    std::vector<float>        m_vert_positions;
    std::vector<float>        m_vert_colors;
    std::vector<float>        m_vert_textCoords;
    std::vector<unsigned int> m_elem_indices;

    AShader *              m_shader;
    std::vector<Texture *> m_textures;
    Transform *  m_transform;
};

} // namespace VDEngine

#endif /* AOBJECT_H_ */