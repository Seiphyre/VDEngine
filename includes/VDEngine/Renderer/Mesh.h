#ifndef VDENGINE_MESH_H_
#define VDENGINE_MESH_H_

// C++ Standard libs
#include <vector>

// External libs
#include <glm/glm.hpp>

namespace VDEngine
{

class Mesh
{
  public:
    Mesh();
    Mesh(std::vector<glm::vec3> vpos, std::vector<glm::vec3> vnormal, std::vector<glm::vec3> vcolor,
         std::vector<glm::vec2> vtext);
    ~Mesh();

    std::vector<glm::vec3> vert_positions;
    std::vector<glm::vec3> vert_normals;
    std::vector<glm::vec3> vert_colors;
    std::vector<glm::vec2> vert_textCoords;
};

} // namespace VDEngine

#endif /* VDENGINE_MESH_H_ */