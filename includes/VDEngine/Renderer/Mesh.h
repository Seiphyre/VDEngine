#ifndef VDENGINE_MESH_H_
#define VDENGINE_MESH_H_

// C++ Standard libs
#include <vector>

namespace VDEngine
{

class Mesh
{
  public:
    Mesh();
    Mesh(std::vector<float> vpos, std::vector<float> vcolor, std::vector<float> vtext);
    ~Mesh();

    std::vector<float> vert_positions;
    std::vector<float> vert_colors;
    std::vector<float> vert_textCoords;
};

} // namespace VDEngine

#endif /* VDENGINE_MESH_H_ */