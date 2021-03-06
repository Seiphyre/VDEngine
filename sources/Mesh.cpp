#include "VDEngine/Renderer/Mesh.h"

using namespace VDEngine;

Mesh::Mesh()
{
}
Mesh::Mesh(std::vector<glm::vec3> vpos, std::vector<glm::vec3> vnormal, std::vector<glm::vec3> vcolor,
           std::vector<glm::vec2> vtext, std::vector<unsigned int> indices)
{
    vert_positions  = vpos;
    vert_normals    = vnormal;
    vert_colors     = vcolor;
    vert_textCoords = vtext;
    this->indices   = indices;
}
Mesh::~Mesh()
{
}