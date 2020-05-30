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
    AttribShaderParams();
}

void MeshRender::AttribShaderParams()
{
    glGenVertexArrays(1, &m_VAO);

    SetVertexAttribVec3(0, m_mesh->vert_positions.data(), m_mesh->vert_positions.size());
    SetVertexAttribVec3(1, m_mesh->vert_colors.data(), m_mesh->vert_colors.size());
    SetVertexAttribVec2(2, m_mesh->vert_textCoords.data(), m_mesh->vert_textCoords.size());
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

void MeshRender::Draw(const glm::mat4 & view, const glm::mat4 & projection, GLenum mode) const
{
    // Bind Textures
    for (int i = 0; i < m_textures.size(); i++)
    {
        m_textures[i]->Bind(i);
    }

    // GL_LINE
    m_shader->Use();
    glBindVertexArray(m_VAO);

    // UNIFORMS
    for (int i = 0; i < m_textures.size(); i++)
    {
        m_shader->SetInt("uTexture" + std::to_string(i + 1), i);

        // std::string textName = "uTexture" + std::to_string(i + 1);
        // glUniform1i(glGetUniformLocation(_shader->GetShaderProgramId(), textName.c_str()), i); // set it manually
    }

    // unsigned int transformLoc = glGetUniformLocation(_shader->GetShaderProgramId(), "uTransform");
    // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(_transform->GetMatrix()));

    m_shader->SetMat4("uModel", m_transform->GetMatrix());
    m_shader->SetMat4("uView", view);
    m_shader->SetMat4("uProjection", projection);

    // Uniforms (Need _shader->Use())
    // float timeValue = glfwGetTime();
    // float greenValue = sin(timeValue) / 2.0f + 0.5f;
    // int vertexColorLocation = glGetUniformLocation(_shader->GetShaderProgramId(), "vertexColor");
    // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    glPolygonMode(GL_FRONT_AND_BACK, mode);

    int size;
    // glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    size = m_mesh->vert_positions.size() / 3;
    glDrawArrays(GL_TRIANGLES, 0, size);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBindVertexArray(0);

    // Unbind Textures
    for (int i = 0; i < m_textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void MeshRender::Init()
{
    AttribShaderParams();
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