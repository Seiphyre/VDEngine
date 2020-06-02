#include "VDEngine/Renderer/MeshRenderer.h"

using namespace VDEngine;

MeshRender::MeshRender(Mesh * mesh)
{
    m_mesh      = mesh;
    m_transform = new Transform();

    SetMaterial(MaterialManager::getInstance()->GetMaterial());
}

MeshRender::MeshRender(Mesh * mesh, Material * material)
{
    m_mesh      = mesh;
    m_transform = new Transform();

    SetMaterial(material);
}

// MeshRender::MeshRender(const MeshRender & other)
// {
//     m_mesh      = other.m_mesh;
//     m_shader    = other.m_shader;
//     m_transform = other.m_transform;
//     m_VAO       = other.m_VAO;
//     m_textures  = other.m_textures;
// }

MeshRender::~MeshRender()
{
    glDeleteVertexArrays(1, &m_VAO);
}

Transform * MeshRender::GetTransform() const
{
    return m_transform;
}

void MeshRender::SetMaterial(Material * material)
{
    m_material = material;
    SetShaderParamsFromMesh();
}

void MeshRender::SetShaderParamsFromMesh()
{
    glGenVertexArrays(1, &m_VAO);

    // Set Vertex attributes
    std::vector<s_shaderParameter> vertex_attributes = m_material->shader->GetAttributes();
    for (int i = 0; i < vertex_attributes.size(); i++)
    {
        // About vertex attributes : INDEX (from glGetActiveAttrib) = LOCATION (used by glVertexAttribPointer)
        int index = vertex_attributes[i].index;

        if (vertex_attributes[i].name == "v_Position")
            SetVertexAttribVec3(index, m_mesh->vert_positions.data(), m_mesh->vert_positions.size());
        else if (vertex_attributes[i].name == "v_Normal")
            SetVertexAttribVec3(index, m_mesh->vert_normals.data(), m_mesh->vert_normals.size());
        else if (vertex_attributes[i].name == "v_Color")
            SetVertexAttribVec3(index, m_mesh->vert_colors.data(), m_mesh->vert_colors.size());
        else if (vertex_attributes[i].name == "v_TexCoord")
            SetVertexAttribVec2(index, m_mesh->vert_textCoords.data(), m_mesh->vert_textCoords.size());
    }

    // SetVertexAttribVec3(0, m_mesh->vert_positions.data(), m_mesh->vert_positions.size());
    // SetVertexAttribVec3(1, m_mesh->vert_colors.data(), m_mesh->vert_colors.size());
    // SetVertexAttribVec2(2, m_mesh->vert_textCoords.data(), m_mesh->vert_textCoords.size());
}

void MeshRender::SetShaderParamsFromCamera(Camera * camera)
{
    // Set Uniforms
    std::vector<s_shaderParameter> uniforms = m_material->shader->GetUniforms();
    for (int i = 0; i < uniforms.size(); i++)
    {
        if (uniforms[i].name == "u_ViewMat")
            SetMat4(uniforms[i].name, camera->GetViewMatrix());

        else if (uniforms[i].name == "u_ProjMat")
            SetMat4(uniforms[i].name, camera->GetProjectionMatrix());

        else if (uniforms[i].name == "u_Camera_Position")
            SetVec3(uniforms[i].name, camera->GetTransform()->position);
    }
}
void MeshRender::SetShaderParamsFromTransform()
{
    // Set Uniforms
    std::vector<s_shaderParameter> uniforms = m_material->shader->GetUniforms();
    for (int i = 0; i < uniforms.size(); i++)
    {
        // About uniforms : INDEX (from glGetActiveAttrib) != LOCATION (used by glVertexAttribPointer)
        if (uniforms[i].name == "u_ModelMat")
            SetMat4(uniforms[i].name, m_transform->GetMatrix());
        if (uniforms[i].name == "u_NormalMat")
            SetMat4(uniforms[i].name, m_transform->GetNormalMatrix());
    }
}

void MeshRender::SetShaderParamsFromMaterial()
{
    // Set Uniforms
    std::vector<s_shaderParameter> uniforms = m_material->shader->GetUniforms();
    for (int i = 0; i < uniforms.size(); i++)
    {
        // About uniforms : INDEX (from glGetActiveAttrib) != LOCATION (used by glVertexAttribPointer)
        if (uniforms[i].name == "u_Diffuse_Map")
        {
            if (m_material->diffuse_map != nullptr)
                SetInt(uniforms[i].name, DIFFUSE_MAP_TEXT_UNIT);
            // else
            //     std::cout << "WARNING: u_Diffuse_Map requierd, but diffuse map is null in the material." <<
            //     std::endl;
        }

        else if (uniforms[i].name == "u_Diffuse_Color")
            SetVec3(uniforms[i].name, m_material->diffuse_color);

        if (uniforms[i].name == "u_Specular_Map")
        {
            if (m_material->diffuse_map != nullptr)
                SetInt(uniforms[i].name, SPECULAR_MAP_TEXT_UNIT);
            // else
            //     std::cout << "WARNING: u_Specular_Map requierd, but specular map is null in the material." <<
            //     std::endl;
        }

        else if (uniforms[i].name == "u_Specular_Color")
            SetVec3(uniforms[i].name, m_material->specular_color);

        else if (uniforms[i].name == "u_Shininess")
            SetFloat(uniforms[i].name, m_material->shininess);
    }
}

void MeshRender::SetShaderParamsFromLight(Light * light)
{
    // Set Uniforms
    std::vector<s_shaderParameter> uniforms = m_material->shader->GetUniforms();
    for (int i = 0; i < uniforms.size(); i++)
    {
        // About uniforms : INDEX (from glGetActiveAttrib) != LOCATION (used by glVertexAttribPointer)
        if (uniforms[i].name == "u_Light_Color")
            SetVec3(uniforms[i].name, light->color);
        if (uniforms[i].name == "u_Light_Type")
            SetInt(uniforms[i].name, (int)light->type);

        if (uniforms[i].name == "u_Light_Position" && (light->type == POINT || light->type == SPOT))
            SetVec3(uniforms[i].name, light->GetTransform()->position);
        if (uniforms[i].name == "u_Light_Direction" && (light->type == DIRECTIONAL || light->type == SPOT))
            SetVec3(uniforms[i].name, light->GetTransform()->GetForwardDir());

        if (uniforms[i].name == "u_Light_Attenuation_Const" && (light->type == POINT || light->type == SPOT))
            SetFloat(uniforms[i].name, light->att_constant);
        if (uniforms[i].name == "u_Light_Attenuation_Linear" && (light->type == POINT || light->type == SPOT))
            SetFloat(uniforms[i].name, light->att_linear);
        if (uniforms[i].name == "u_Light_Attenuation_Quad" && (light->type == POINT || light->type == SPOT))
            SetFloat(uniforms[i].name, light->att_quadratic);

        if (uniforms[i].name == "u_Light_Inner_CutOff" && light->type == SPOT)
            SetFloat(uniforms[i].name, glm::cos(glm::radians(light->inner_cutOff)));
        if (uniforms[i].name == "u_Light_Outer_CutOff" && light->type == SPOT)
            SetFloat(uniforms[i].name, glm::cos(glm::radians(light->outer_cutOff)));
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
    glUniform1i(glGetUniformLocation(m_material->shader->GetShaderProgramId(), name.c_str()), (int)value);
    // glUniform1i(location, (int)value);
}
// ------------------------------------------------------------------------
void MeshRender::SetInt(const std::string & name, int value) const
{
    glUniform1i(glGetUniformLocation(m_material->shader->GetShaderProgramId(), name.c_str()), value);
    // glUniform1i(location, value);
}
// ------------------------------------------------------------------------
void MeshRender::SetFloat(const std::string & name, float value) const
{
    glUniform1f(glGetUniformLocation(m_material->shader->GetShaderProgramId(), name.c_str()), value);
    // glUniform1f(location, value);
}
// ------------------------------------------------------------------------
void MeshRender::SetVec2(const std::string & name, const glm::vec2 & value) const
{
    glUniform2fv(glGetUniformLocation(m_material->shader->GetShaderProgramId(), name.c_str()), 1, &value[0]);
    // glUniform2fv(location, 1, &value[0]);
}
void MeshRender::SetVec2(const std::string & name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(m_material->shader->GetShaderProgramId(), name.c_str()), x, y);
    // glUniform2f(location, x, y);
}
// ------------------------------------------------------------------------
void MeshRender::SetVec3(const std::string & name, const glm::vec3 & value) const
{
    glUniform3fv(glGetUniformLocation(m_material->shader->GetShaderProgramId(), name.c_str()), 1, &value[0]);
    // glUniform3fv(location, 1, &value[0]);
}
void MeshRender::SetVec3(const std::string & name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(m_material->shader->GetShaderProgramId(), name.c_str()), x, y, z);
    // glUniform3f(location, x, y, z);
}
// ------------------------------------------------------------------------
void MeshRender::SetVec4(const std::string & name, const glm::vec4 & value) const
{
    glUniform4fv(glGetUniformLocation(m_material->shader->GetShaderProgramId(), name.c_str()), 1, &value[0]);
    // glUniform4fv(location, 1, &value[0]);
}
void MeshRender::SetVec4(const std::string & name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(m_material->shader->GetShaderProgramId(), name.c_str()), x, y, z, w);
    // glUniform4f(location, x, y, z, w);
}
// ------------------------------------------------------------------------
void MeshRender::SetMat2(const std::string & name, const glm::mat2 & mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_material->shader->GetShaderProgramId(), name.c_str()), 1, GL_FALSE,
                       &mat[0][0]);
    // glUniformMatrix2fv(location, 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void MeshRender::SetMat3(const std::string & name, const glm::mat3 & mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_material->shader->GetShaderProgramId(), name.c_str()), 1, GL_FALSE,
                       &mat[0][0]);
    // glUniformMatrix3fv(const std::string & name, 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void MeshRender::SetMat4(const std::string & name, const glm::mat4 & mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_material->shader->GetShaderProgramId(), name.c_str()), 1, GL_FALSE,
                       &mat[0][0]);
    // glUniformMatrix4fv(const std::string & name, 1, GL_FALSE, &mat[0][0]);
}

void MeshRender::Draw(Camera * camera, Light * light, GLenum mode)
{
    // Bind Textures -----------
    // for (int i = 0; i < m_material->textures.size(); i++)
    // {
    //     m_material->textures[i]->Bind(i);
    // }
    if (m_material->diffuse_map != nullptr) // && shader have this param ... OPTI
        m_material->diffuse_map->Bind(DIFFUSE_MAP_TEXT_UNIT);
    else
        TextureManager::getInstance()->GetTexture()->Bind(DIFFUSE_MAP_TEXT_UNIT);

    if (m_material->specular_map != nullptr) // && shader have this param ... OPTI
        m_material->specular_map->Bind(SPECULAR_MAP_TEXT_UNIT);
    else
        TextureManager::getInstance()->GetTexture()->Bind(SPECULAR_MAP_TEXT_UNIT);

    m_material->shader->Use();

    // Bind Vertex Attributes --
    glBindVertexArray(m_VAO);

    // Bind Uniforms -----------
    SetShaderParamsFromMaterial();
    SetShaderParamsFromTransform();
    SetShaderParamsFromCamera(camera);
    SetShaderParamsFromLight(light);

    // Draw ---------------------
    glPolygonMode(GL_FRONT_AND_BACK, mode);

    int size;
    // glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    size = m_mesh->vert_positions.size() / 3;
    glDrawArrays(GL_TRIANGLES, 0, size);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBindVertexArray(0);

    // Unbind Textures -----------
    // for (int i = 0; i < m_material->textures.size(); i++)
    // {
    //     glActiveTexture(GL_TEXTURE0 + i);
    //     glBindTexture(GL_TEXTURE_2D, 0);
    // }

    glActiveTexture(GL_TEXTURE0 + DIFFUSE_MAP_TEXT_UNIT);
    glBindTexture(GL_TEXTURE_2D, 0);

    glActiveTexture(GL_TEXTURE0 + SPECULAR_MAP_TEXT_UNIT);
    glBindTexture(GL_TEXTURE_2D, 0);
}

// void MeshRender::Init()
// {
//     SetShaderParamsFromMesh();
// }
