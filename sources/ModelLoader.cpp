#include "VDEngine/Renderer/ModelLoader.h"

using namespace VDEngine;

ModelLoader::ModelLoader()
{
}

ModelLoader::~ModelLoader()
{
}

Model * ModelLoader::LoadModel(const std::string & file_name)
{
    Assimp::Importer importer;
    std::string      file_path;
    const aiScene *  scene;

    file_path = FileHandler::RootToResourcesPath + "models/" + file_name;

    // aiProcess_Triangulate :
    // if the model does not (entirely) consist of triangles, it should transform all the model's primitive shapes to
    // triangles first

    // aiProcess_FlipUVs:
    // flips the texture coordinates on the y-axis

    // aiProcess_GenNormals:
    // creates normal vectors for each vertex if the model doesn't contain normal vectors.
    scene = importer.ReadFile(file_path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_OptimizeMeshes |
                                             aiProcess_OptimizeGraph);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    return ProcessNode(scene->mRootNode, scene);
}

Model * ModelLoader::ProcessNode(aiNode * node, const aiScene * scene)
{
    Model * model = new Model();

    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh * aiMesh = scene->mMeshes[node->mMeshes[i]];

        model->mesh     = ProcessMesh(aiMesh, scene);
        model->material = ProcessMaterial(aiMesh, scene);

        model->mesh_renderer = new MeshRender(model->mesh, model->material);
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        // std::cout << "Go to Child" << std::endl;
        model->children.push_back(ProcessNode(node->mChildren[i], scene));
    }

    return model;
}

Mesh * ModelLoader::ProcessMesh(aiMesh * mesh, const aiScene * scene)
{
    // std::cout << "ProcessMesh" << std::endl;
    std::vector<glm::vec3> v_positions;
    std::vector<glm::vec3> v_normals;
    std::vector<glm::vec3> v_colors;
    std::vector<glm::vec2> v_texCoords;

    std::vector<unsigned int> indices;

    // process vertex positions, normals and texture coordinates
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        glm::vec3 position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        v_positions.push_back(position);

        glm::vec3 normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        v_normals.push_back(normal);

        if (mesh->mColors[0]) // Up to 8 color per vertex allow
        {
            glm::vec3 color = glm::vec3(mesh->mColors[0][i].r, mesh->mColors[0][i].g, mesh->mColors[0][i].b);
            v_colors.push_back(color);
        }
        else
            v_colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));

        if (mesh->mTextureCoords[0]) // Up to 8 textCoords per vertex allow
        {
            glm::vec2 texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            v_texCoords.push_back(texCoord);
        }
        else
            v_texCoords.push_back(glm::vec2(0.0f, 0.0f));
    }

    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    return new Mesh(v_positions, v_normals, v_colors, v_texCoords, indices);
}

Material * ModelLoader::ProcessMaterial(aiMesh * mesh, const aiScene * scene)
{
    Material * material = MaterialManager::getInstance()->LoadMaterial(ShaderManager::getInstance()->GetShader());

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial * aiMaterial = scene->mMaterials[mesh->mMaterialIndex];

        if (aiMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            aiString texture_name;
            aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &texture_name);

            Texture * texture = TextureManager::getInstance()->GetTextureByFileName(texture_name.C_Str());
            if (texture == nullptr)
                material->diffuse_map = TextureManager::getInstance()->LoadTexture(texture_name.C_Str());
            else
                material->diffuse_map = texture;
        }

        if (aiMaterial->GetTextureCount(aiTextureType_SPECULAR) > 0)
        {
            aiString texture_name;
            aiMaterial->GetTexture(aiTextureType_SPECULAR, 0, &texture_name);

            Texture * texture = TextureManager::getInstance()->GetTextureByFileName(texture_name.C_Str());
            if (texture == nullptr)
                material->specular_map = TextureManager::getInstance()->LoadTexture(texture_name.C_Str());
            else
                material->specular_map = texture;
        }

        // mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
        // material.Diffuse = glm::vec3(color.r, color.b, color.g);

        // mat->Get(AI_MATKEY_COLOR_AMBIENT, color);
        // material.Ambient = glm::vec3(color.r, color.b, color.g);

        // mat->Get(AI_MATKEY_COLOR_SPECULAR, color);
        // material.Specular = glm::vec3(color.r, color.b, color.g);

        // mat->Get(AI_MATKEY_SHININESS, shininess);
        // material.Shininess = shininess;
    }

    return material;
}