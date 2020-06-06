#ifndef VDENGINE_MODEL_H_
#define VDENGINE_MODEL_H_

// C++ Standard libs
#include <vector>

// Internal headers
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

    void Draw(Camera * camera, std::vector<Light *> lights);
};

} // namespace VDEngine

#endif /* VDENGINE_MODEL_H_ */