#include "VDEngine/Renderer/Model.h"

using namespace VDEngine;

Model::Model()
{
    mesh_renderer = nullptr;
    mesh          = nullptr;
    material      = nullptr;
}

Model::~Model()
{
}

void Model::Draw(Camera * camera, std::vector<Light *> lights)
{
    if (children.size() > 0)
    {
        for (int i = 0; i < children.size(); i++)
            children[i]->Draw(camera, lights);
    }

    if (mesh_renderer != nullptr)
        mesh_renderer->Draw(camera, lights);
}