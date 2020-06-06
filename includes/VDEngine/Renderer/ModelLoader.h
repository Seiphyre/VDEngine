#ifndef VDENGINE_MODEL_LOADER_H_
#define VDENGINE_MODEL_LOADER_H_

// C++ Standard libs
#include <vector>

// External libs
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>

// Internal headers
#include "VDEngine/Core/Singleton.h"
#include "VDEngine/Renderer/Mesh.h"
#include "VDEngine/Renderer/Model.h"
#include "VDEngine/Renderer/MaterialManager.h"

namespace VDEngine
{

class ModelLoader : public Singleton<ModelLoader>
{
    friend class Singleton<ModelLoader>;

  public:
    ModelLoader();
    ~ModelLoader();

    Model * LoadModel(const std::string & file_name);

  private:
    Model * ProcessNode(aiNode * node, const aiScene * scene);

    Mesh *     ProcessMesh(aiMesh * mesh, const aiScene * scene);
    Material * ProcessMaterial(aiMesh * mesh, const aiScene * scene);
};

} // namespace VDEngine

#endif /* VDENGINE_MODEL_LOADER_H_*/