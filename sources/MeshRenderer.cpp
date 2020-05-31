#include "VDEngine/Renderer/MeshRenderer.h"

using namespace VDEngine;

MeshRender::MeshRender(Mesh * mesh)
{
    m_mesh      = mesh;
    m_shader    = ShaderManager::getInstance()->GetShader<DefaultShader>();
    m_transform = new Transform();
}

MeshRender::MeshRender(Mesh * mesh, AShader * shader)
{
    m_mesh      = mesh;
    m_shader    = shader;
    m_transform = new Transform();
}
MeshRender::~MeshRender()
{
    glDeleteVertexArrays(1, &m_VAO);
}

Transform * MeshRender::GetTransform() const
{
    return m_transform;
}

void MeshRender::SetShader(AShader * shader)
{
    m_shader = shader;
    SetShaderParamsFromMesh();
}

void MeshRender::SetShaderParamsFromMesh()
{
    glGenVertexArrays(1, &m_VAO);

    // Set Vertex attributes
    std::vector<s_shaderParameter> vertex_attributes = m_shader->GetAttributes();
    for (int i = 0; i < vertex_attributes.size(); i++)
    {
        // About vertex attributes : INDEX (from glGetActiveAttrib) = LOCATION (used by glVertexAttribPointer)
        int index = vertex_attributes[i].index;

        if (vertex_attributes[i].name == "aPosition")
            SetVertexAttribVec3(index, m_mesh->vert_positions.data(), m_mesh->vert_positions.size());
        else if (vertex_attributes[i].name == "aColor")
            SetVertexAttribVec3(index, m_mesh->vert_colors.data(), m_mesh->vert_colors.size());
        else if (vertex_attributes[i].name == "aTexCoord")
            SetVertexAttribVec2(index, m_mesh->vert_textCoords.data(), m_mesh->vert_textCoords.size());
    }

    // SetVertexAttribVec3(0, m_mesh->vert_positions.data(), m_mesh->vert_positions.size());
    // SetVertexAttribVec3(1, m_mesh->vert_colors.data(), m_mesh->vert_colors.size());
    // SetVertexAttribVec2(2, m_mesh->vert_textCoords.data(), m_mesh->vert_textCoords.size());
}

void MeshRender::SetShaderParamsFromCamera(Camera * camera)
{
    // Set Uniforms
    std::vector<s_shaderParameter> uniforms = m_shader->GetUniforms();
    for (int i = 0; i < uniforms.size(); i++)
    {
        if (uniforms[i].name == "uView")
            SetMat4(uniforms[i].name, camera->GetViewMatrix());

        else if (uniforms[i].name == "uProjection")
            SetMat4(uniforms[i].name, camera->GetProjectionMatrix());
    }
}
void MeshRender::SetShaderParamsFromTransform()
{
    // Set Uniforms
    std::vector<s_shaderParameter> uniforms = m_shader->GetUniforms();
    for (int i = 0; i < uniforms.size(); i++)
    {
        // About uniforms : INDEX (from glGetActiveAttrib) != LOCATION (used by glVertexAttribPointer)
        if (uniforms[i].name == "uModel")
            SetMat4(uniforms[i].name, m_transform->GetMatrix());
    }
}

void MeshRender::SetShaderParamsFromMaterial()
{
    // Set Uniforms
    std::vector<s_shaderParameter> uniforms = m_shader->GetUniforms();
    for (int i = 0; i < uniforms.size(); i++)
    {
        // About uniforms : INDEX (from glGetActiveAttrib) != LOCATION (used by glVertexAttribPointer)
        if (uniforms[i].name == "uTexture_2" && m_textures.size() > 0)
            SetInt(uniforms[i].name, 0); // 0 is a texture unit (texture unit == index of m_material->getTextures())

        else if (uniforms[i].name == "uTexture_1" && m_textures.size() > 1)
            SetInt(uniforms[i].name, 1);
    }
}

void MeshRender::SetVertexAttribVec3(int layout_index, const float * data, int data_size)
{
    // VAO - Save the config
    glBindVertexArray(m_VAO);

    // VBO - Bind vertex attributes
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // [0] Vertex Positions
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data_size * sizeof(float), data, GL_STATIC_DRAW);

    glVertexAttribPointer(layout_index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(layout_index);

    // Clean
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &VBO);
}
void MeshRender::SetVertexAttribVec2(int layout_index, const float * data, int data_size)
{
    // VAO - Save the config
    glBindVertexArray(m_VAO);

    // VBO - Bind vertex attributes
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // [2] Texels
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data_size * sizeof(float), data, GL_STATIC_DRAW);

    glVertexAttribPointer(layout_index, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(layout_index);

    // Clean
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &VBO);
}

// utility uniform functions
// ------------------------------------------------------------------------
void MeshRender::SetBool(const std::string & name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_shader->GetShaderProgramId(), name.c_str()), (int)value);
    // glUniform1i(location, (int)value);
}
// ------------------------------------------------------------------------
void MeshRender::SetInt(const std::string & name, int value) const
{
    glUniform1i(glGetUniformLocation(m_shader->GetShaderProgramId(), name.c_str()), value);
    // glUniform1i(location, value);
}
// ------------------------------------------------------------------------
void MeshRender::SetFloat(const std::string & name, float value) const
{
    glUniform1f(glGetUniformLocation(m_shader->GetShaderProgramId(), name.c_str()), value);
    // glUniform1f(location, value);
}
// ------------------------------------------------------------------------
void MeshRender::SetVec2(const std::string & name, const glm::vec2 & value) const
{
    glUniform2fv(glGetUniformLocation(m_shader->GetShaderProgramId(), name.c_str()), 1, &value[0]);
    // glUniform2fv(location, 1, &value[0]);
}
void MeshRender::SetVec2(const std::string & name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(m_shader->GetShaderProgramId(), name.c_str()), x, y);
    // glUniform2f(location, x, y);
}
// ------------------------------------------------------------------------
void MeshRender::SetVec3(const std::string & name, const glm::vec3 & value) const
{
    glUniform3fv(glGetUniformLocation(m_shader->GetShaderProgramId(), name.c_str()), 1, &value[0]);
    // glUniform3fv(location, 1, &value[0]);
}
void MeshRender::SetVec3(const std::string & name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(m_shader->GetShaderProgramId(), name.c_str()), x, y, z);
    // glUniform3f(location, x, y, z);
}
// ------------------------------------------------------------------------
void MeshRender::SetVec4(const std::string & name, const glm::vec4 & value) const
{
    glUniform4fv(glGetUniformLocation(m_shader->GetShaderProgramId(), name.c_str()), 1, &value[0]);
    // glUniform4fv(location, 1, &value[0]);
}
void MeshRender::SetVec4(const std::string & name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(m_shader->GetShaderProgramId(), name.c_str()), x, y, z, w);
    // glUniform4f(location, x, y, z, w);
}
// ------------------------------------------------------------------------
void MeshRender::SetMat2(const std::string & name, const glm::mat2 & mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_shader->GetShaderProgramId(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
    // glUniformMatrix2fv(location, 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void MeshRender::SetMat3(const std::string & name, const glm::mat3 & mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_shader->GetShaderProgramId(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
    // glUniformMatrix3fv(const std::string & name, 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void MeshRender::SetMat4(const std::string & name, const glm::mat4 & mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_shader->GetShaderProgramId(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
    // glUniformMatrix4fv(const std::string & name, 1, GL_FALSE, &mat[0][0]);
}

void MeshRender::Draw(Camera * camera, GLenum mode)
{
    // Bind Textures -----------
    for (int i = 0; i < m_textures.size(); i++)
    {
        m_textures[i]->Bind(i);
    }

    m_shader->Use();

    // Bind Vertex Attributes --
    glBindVertexArray(m_VAO);

    // Bind Uniforms -----------
    SetShaderParamsFromMaterial();
    SetShaderParamsFromTransform();
    SetShaderParamsFromCamera(camera);

    // Draw ---------------------
    glPolygonMode(GL_FRONT_AND_BACK, mode);

    int size;
    // glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    size = m_mesh->vert_positions.size() / 3;
    glDrawArrays(GL_TRIANGLES, 0, size);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBindVertexArray(0);

    // Unbind Textures -----------
    for (int i = 0; i < m_textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void MeshRender::Init()
{
    SetShaderParamsFromMesh();
}

void MeshRender::AddTexture(uuids::uuid texture_uuid)
{
    Texture * texture = TextureManager::getInstance()->GetTexture(texture_uuid);

    if (texture != nullptr)
        m_textures.push_back(texture);
    else
    {
        std::cout << "[AObject] Could not add Texture to the object." << std::endl;
    }
}
void MeshRender::AddTexture(const Texture * texture)
{
    m_textures.push_back(texture);
}