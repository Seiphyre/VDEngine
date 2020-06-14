#ifndef VDENGINE_MODEL_H_
#define VDENGINE_MODEL_H_

// C++ Standard libs
#include <vector>
#include <string>

// Internal headers
#include "VDEngine/Core/GameObject.h"
#include "VDEngine/Renderer/MeshRenderer.h"

namespace VDEngine
{

class Model
{

  public:
    Model();
    ~Model();

    std::vector<Model *> children;
    MeshRender *         mesh_renderer;
    Mesh *               mesh;
    Material *           material;
    std::string          name;

    GameObject * CreateGameObjectFromModel();

  private:
    GameObject * ProcessGameObject(Model * model_node);
};

} // namespace VDEngine

#endif /* VDENGINE_MODEL_H_ */