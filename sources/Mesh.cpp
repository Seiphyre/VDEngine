#include "VDEngine/Renderer/Mesh.h"

using namespace VDEngine;

Mesh::Mesh()
{
}
Mesh::Mesh(std::vector<Vector3> vpos, std::vector<Vector3> vnormal, std::vector<Vector3> vcolor,
           std::vector<Vector2> vtext, std::vector<unsigned int> indices)
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