#ifndef VDENGINE_MESH_RENDERER_H_
#define VDENGINE_MESH_RENDERER_H_

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
#include "VDEngine/Renderer/TextureManager.h"
#include "VDEngine/Renderer/Mesh.h"

namespace VDEngine
{

class MeshRender
{
  public:
    MeshRender(Mesh * mesh);
    MeshRender(Mesh * mesh, AShader * shader);
    MeshRender(const MeshRender &) = default;
    ~MeshRender();

    MeshRender & operator=(const MeshRender &) = default;

    void Init();

    Transform * GetTransform() const;
    void        SetShader(AShader * shader);
    void        AddTexture(uuids::uuid texture_uuid);
    void        AddTexture(const Texture * texture);

    void Draw(const glm::mat4 & view, const glm::mat4 & projection, GLenum mode = GL_FILL) const;

  protected:
    void AttribShaderParams();
    void SetVertexAttribVec3(int layout_index, const float * data, int data_size);
    void SetVertexAttribVec2(int layout_index, const float * data, int data_size);

    unsigned int m_VAO;

    // Component : MATERIAL
    AShader *                    m_shader;
    std::vector<const Texture *> m_textures;

    // Component : MESH
    Mesh * m_mesh;

    // Component : TRANSFORM
    Transform * m_transform;
};

} // namespace VDEngine

#endif /* VDENGINE_MESH_RENDERER_H_ */