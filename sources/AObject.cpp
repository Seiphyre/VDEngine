#include "VDEngine/Renderer/AObject.h"

using namespace VDEngine;

AObject::AObject()
{
    m_shader    = ShaderManager::getInstance()->GetShader<DefaultShader>();
    m_transform = new Transform();
}

AObject::AObject(AShader * shader)
{
    m_shader    = shader;
    m_transform = new Transform();
}
AObject::~AObject()
{
    glDeleteVertexArrays(1, &m_VAO);

    delete (m_shader);
}

Transform * AObject::GetTransform() const
{
    return m_transform;
}

void AObject::SetShader(AShader * shader)
{
    m_shader = shader;
    AttribShaderParams();
}

void AObject::AttribShaderParams()
{
    // VAO - Save the config
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    // VBO - Bind vertex attributes
    unsigned int VBO[3];
    glGenBuffers(3, VBO);

    // [0] Vertex Positions
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, m_vert_positions.size() * sizeof(float), m_vert_positions.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // [1] Vertex Colors
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, m_vert_colors.size() * sizeof(float), m_vert_colors.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);

    // [2] Vertex Colors
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, m_vert_textCoords.size() * sizeof(float), m_vert_textCoords.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(2);

    // EBO - Bind the element array
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_elem_indices.size() * sizeof(unsigned int), m_elem_indices.data(),
                 GL_STATIC_DRAW);

    // Clean
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteBuffers(3, VBO);
    glDeleteBuffers(1, &EBO);
}

void AObject::Draw(const glm::mat4 & view, const glm::mat4 & projection, GLenum mode) const
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
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    // glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    glDrawArrays(GL_TRIANGLES, 0, size / sizeof(GLfloat));

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBindVertexArray(0);
}

void AObject::Init()
{
    AttribShaderParams();
}

void AObject::AddTexture(const std::string & text_name)
{
    m_textures.push_back(new Texture(text_name));
}
void AObject::AddTexture(const Texture * texture)
{
    m_textures.push_back(texture);
}