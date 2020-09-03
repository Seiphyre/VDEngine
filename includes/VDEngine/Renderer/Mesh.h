

#ifndef VDENGINE_META_HEADER
#define VDENGINE_META_HEADER

#include "metaStuff/Meta.h"

#endif /* VDENGINE_META_HEADER */

#ifndef VDENGINE_MESH_H_
#define VDENGINE_MESH_H_

// C++ Standard libs
#include <vector>

// External libs
// #include <glm/glm.hpp>

// Internal headers
#include "VDEngine/Math/Vectors.hpp"

namespace VDEngine
{

class Mesh
{
    friend auto meta::registerMembers<VDEngine::Mesh>();
    
  public:
    Mesh();
    Mesh(std::vector<Vector3> vpos, std::vector<Vector3> vnormal, std::vector<Vector3> vcolor,
         std::vector<Vector2> vtext, std::vector<unsigned int> indices);
    ~Mesh();

    std::vector<Vector3>      vert_positions;
    std::vector<Vector3>      vert_normals;
    std::vector<Vector3>      vert_colors;
    std::vector<Vector2>      vert_textCoords;
    std::vector<unsigned int> indices;
};

} // namespace VDEngine

#endif /* VDENGINE_MESH_H_ */

#ifndef META_REGISTER_VDENGINE_MESH
#define META_REGISTER_VDENGINE_MESH

template <>
inline auto meta::registerMembers< VDEngine::Mesh >() 
{
    return meta::members( 
meta::member("vert_positions", &VDEngine::Mesh::vert_positions),
meta::member("vert_normals", &VDEngine::Mesh::vert_normals),
meta::member("vert_colors", &VDEngine::Mesh::vert_colors),
meta::member("vert_textCoords", &VDEngine::Mesh::vert_textCoords),
meta::member("indices", &VDEngine::Mesh::indices) 
    );
}

#endif /* META_REGISTER_VDENGINE_MESH */

