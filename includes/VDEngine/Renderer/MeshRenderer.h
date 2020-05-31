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
#include "VDEngine/Renderer/Camera.h"

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

    void Draw(Camera * camera, GLenum mode = GL_FILL);

  protected:
    void SetShaderParamsFromMesh();
    void SetShaderParamsFromCamera(Camera * camera);
    void SetShaderParamsFromTransform();
    void SetShaderParamsFromMaterial();

    // Set Vertex Attrib
    void SetVertexAttribVec3(int layout_index, const float * data, int data_size);
    void SetVertexAttribVec2(int layout_index, const float * data, int data_size);

    // Set Uniforms
    void SetBool(const std::string & name, bool value) const;

    void SetInt(const std::string & name, int value) const;

    void SetFloat(const std::string & name, float value) const;

    void SetVec2(const std::string & name, const glm::vec2 & value) const;
    void SetVec2(const std::string & name, float x, float y) const;

    void SetVec3(const std::string & name, const glm::vec3 & value) const;
    void SetVec3(const std::string & name, float x, float y, float z) const;

    void SetVec4(const std::string & name, const glm::vec4 & value) const;
    void SetVec4(const std::string & name, float x, float y, float z, float w);

    void SetMat2(const std::string & name, const glm::mat2 & mat) const;
    void SetMat3(const std::string & name, const glm::mat3 & mat) const;
    void SetMat4(const std::string & name, const glm::mat4 & mat) const;

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