#ifndef VDENGINE_MESH_RENDERER_H_
#define VDENGINE_MESH_RENDERER_H_

// C++ Standard libs
#include <regex>
#include <math.h>
#include <vector>

// External libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Internal headers
#include "VDEngine/Core/Component.h"

#include "VDEngine/Renderer/MaterialManager.h"
#include "VDEngine/Renderer/ShaderManager.h"
#include "VDEngine/Renderer/Texture.h"
#include "VDEngine/Renderer/TextureManager.h"
#include "VDEngine/Renderer/Mesh.h"
#include "VDEngine/Renderer/Camera.h"
#include "VDEngine/Renderer/Material.h"
#include "VDEngine/Renderer/Light.h"

#include "VDEngine/Math/Vectors.hpp"
#include "VDEngine/Math/Matrix4.h"

namespace VDEngine
{

class MeshRender : public Component
{
  public:
    MeshRender(Mesh * mesh);
    MeshRender(Mesh * mesh, Material * material);
    MeshRender(const MeshRender &) = default;
    ~MeshRender();

    MeshRender & operator=(const MeshRender &) = default;

    // void Init();

    Mesh * GetMesh() const;
    void   SetMaterial(Material * material);

    void Draw(Camera * camera, const std::vector<Light *> & lights, GLenum mode = GL_FILL);

  protected:
    void SetShaderParamsFromMesh();
    void SetShaderParamsFromCamera(Camera * camera);
    void SetShaderParamsFromLight(const std::vector<Light *> & light);
    void SetShaderParamsFromTransform();
    void SetShaderParamsFromMaterial();

    bool GetShaderParamArrayNameAndIndex(const std::string & full_name, const std::string & array_name,
                                         std::string & param_name, int & param_index);
    bool GetShaderParamStructNameAndIndex(const std::string & full_name, const std::string & struct_name,
                                          std::string & param_name);

    // Set Vertex Attrib
    void SetVertexAttribVec3(int layout_index, const Vector3 * data, int data_size);
    void SetVertexAttribVec2(int layout_index, const Vector2 * data, int data_size);

    // Set Uniforms
    void SetBool(const std::string & name, bool value) const;

    void SetInt(const std::string & name, int value) const;

    void SetFloat(const std::string & name, float value) const;

    void SetVec2(const std::string & name, const Vector2 & value) const;
    void SetVec2(const std::string & name, float x, float y) const;

    void SetVec3(const std::string & name, const Vector3 & value) const;
    void SetVec3(const std::string & name, float x, float y, float z) const;

    void SetVec4(const std::string & name, const Vector4 & value) const;
    void SetVec4(const std::string & name, float x, float y, float z, float w);

    // void SetMat2(const std::string & name, const glm::mat2 & mat) const;
    // void SetMat3(const std::string & name, const glm::mat3 & mat) const;
    void SetMat4(const std::string & name, const Matrix4 & mat) const;

    unsigned int m_VAO;

    // Component : MATERIAL
    Material * m_material;

    // Component : MESH
    Mesh * m_mesh;
};

} // namespace VDEngine

#endif /* VDENGINE_MESH_RENDERER_H_ */