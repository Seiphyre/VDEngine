

#ifndef VDENGINE_META_HEADER
#define VDENGINE_META_HEADER

#include "metaStuff/Meta.h"

#endif /* VDENGINE_META_HEADER */

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
    friend auto meta::registerMembers<VDEngine::Model>();
    

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

#ifndef META_REGISTER_VDENGINE_MODEL
#define META_REGISTER_VDENGINE_MODEL

template <>
inline auto meta::registerMembers< VDEngine::Model >() 
{
    return meta::members( 
meta::member("children", &VDEngine::Model::children),
meta::member("mesh_renderer", &VDEngine::Model::mesh_renderer),
meta::member("mesh", &VDEngine::Model::mesh),
meta::member("material", &VDEngine::Model::material),
meta::member("name", &VDEngine::Model::name) 
    );
}

#endif /* META_REGISTER_VDENGINE_MODEL */

