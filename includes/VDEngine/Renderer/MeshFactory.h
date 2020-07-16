#ifndef VDENGINE_MESH_FACTORY_H_
#define VDENGINE_MESH_FACTORY_H_

// External libs
// #include <glm/glm.hpp>

// Internal headers
#include "VDEngine/Core/Singleton.h"
#include "VDEngine/Renderer/Mesh.h"
#include "VDEngine/Math/Vectors.hpp"

namespace VDEngine
{

class MeshFactory : public Singleton<MeshFactory>
{
    friend class Singleton<MeshFactory>;

  public:
    ~MeshFactory();

    Mesh * CreateCube();
    Mesh * CreatePlane();

  private:
    MeshFactory();
};

} // namespace VDEngine

#endif /* VDENGINE_MESH_FACTORY_H_ */