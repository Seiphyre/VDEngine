#include "VDEngine/Renderer/ModelLoader.h"

using namespace VDEngine;

ModelLoader::ModelLoader()
{
}

ModelLoader::~ModelLoader()
{
}

Model * ModelLoader::LoadModel(const std::string & file_path)
{
    Assimp::Importer importer;
    const aiScene *  scene;

    // aiProcess_Triangulate :
    // if the model does not (entirely) consist of triangles, it should transform all the model's primitive shapes to
    // triangles first

    // aiProcess_FlipUVs:
    // flips the texture coordinates on the y-axis

    // aiProcess_GenNormals:
    // creates normal vectors for each vertex if the model doesn't contain normal vectors.
    scene = importer.ReadFile(file_path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_OptimizeGraph |
                                             aiProcess_OptimizeMeshes);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    std::string path;
    std::size_t found = file_path.find_last_of("/\\");
    if (found != std::string::npos)
        path = file_path.substr(0, found + 1);
    else
        path = file_path;

    return ProcessNode(scene->mRootNode, scene, path);
}

Model * ModelLoader::ProcessNode(aiNode * node, const aiScene * scene, const std::string & model_path)
{
    Model * model = new Model();

    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh * aiMesh      = scene->mMeshes[node->mMeshes[i]];
        model->name          = aiMesh->mName.C_Str();
        model->mesh          = ProcessMesh(aiMesh, scene);
        model->material      = ProcessMaterial(aiMesh, scene, model_path);
        model->mesh_renderer = new MeshRender(model->mesh, model->material);
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        // std::cout << "Go to Child" << std::endl;
        model->children.push_back(ProcessNode(node->mChildren[i], scene, model_path));
    }

    return model;
}

Mesh * ModelLoader::ProcessMesh(aiMesh * mesh, const aiScene * scene)
{
    // std::cout << "ProcessMesh" << std::endl;
    std::vector<Vector3> v_positions;
    std::vector<Vector3> v_normals;
    std::vector<Vector3> v_colors;
    std::vector<Vector2> v_texCoords;

    std::vector<unsigned int> indices;

    // process vertex positions, normals and texture coordinates
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vector3 position = Vector3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        v_positions.push_back(position);

        Vector3 normal = Vector3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        v_normals.push_back(normal);

        if (mesh->mColors[0]) // Up to 8 color per vertex allow
        {
            Vector3 color = Vector3(mesh->mColors[0][i].r, mesh->mColors[0][i].g, mesh->mColors[0][i].b);
            v_colors.push_back(color);
        }
        else
            v_colors.push_back(Vector3::VecOne());

        if (mesh->mTextureCoords[0]) // Up to 8 textCoords per vertex allow
        {
            Vector2 texCoord = Vector2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            v_texCoords.push_back(texCoord);
        }
        else
            v_texCoords.push_back(Vector2::VecZero());
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

Material * ModelLoader::ProcessMaterial(aiMesh * mesh, const aiScene * scene, const std::string & model_path)
{
    Material * material = MaterialManager::getInstance()->LoadMaterial(ShaderManager::getInstance()->GetShader());

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial * aiMaterial = scene->mMaterials[mesh->mMaterialIndex];

        if (aiMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            aiString texture_relative_path;
            aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &texture_relative_path);
            std::string full_path = model_path + texture_relative_path.C_Str();

            Texture * texture = TextureManager::getInstance()->GetTextureByFileName(full_path);
            if (texture == nullptr)
                material->diffuse_map = TextureManager::getInstance()->LoadTexture(full_path);
            else
                material->diffuse_map = texture;
        }

        if (aiMaterial->GetTextureCount(aiTextureType_SPECULAR) > 0)
        {
            aiString texture_relative_path;
            aiMaterial->GetTexture(aiTextureType_SPECULAR, 0, &texture_relative_path);
            std::string full_path = model_path + texture_relative_path.C_Str();

            Texture * texture = TextureManager::getInstance()->GetTextureByFileName(full_path);

            if (texture == nullptr)
            {
                material->specular_map = TextureManager::getInstance()->LoadTexture(full_path);
            }
            else
            {
                material->specular_map = texture;
            }
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