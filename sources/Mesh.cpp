#include "VDEngine/Renderer/Mesh.h"

using namespace VDEngine;

Mesh::Mesh()
{
}
Mesh::Mesh(std::vector<float> vpos, std::vector<float> vcolor, std::vector<float> vtext)
{
    vert_positions  = vpos;
    vert_colors     = vcolor;
    vert_textCoords = vtext;
}
Mesh::~Mesh()
{
}