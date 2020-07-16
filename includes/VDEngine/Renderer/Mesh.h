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