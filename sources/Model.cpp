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

GameObject * Model::CreateGameObjectFromModel()
{
    return ProcessGameObject(this);
}

GameObject * Model::ProcessGameObject(Model * model_node)
{
    GameObject * go_node = new GameObject();

    // Set game object
    if (model_node->mesh_renderer != nullptr)
    {
        // Deep copy
        MeshRender * mesh_renderer = new MeshRender(*model_node->mesh_renderer);
        go_node->AddComponent(mesh_renderer);
    }

    if (model_node->name != "")
    {
        go_node->name = model_node->name;
    }

    // Set children (if any)
    for (int i = 0; i < model_node->children.size(); i++)
    {
        GameObject * go_child_node = ProcessGameObject(model_node->children[i]);
        go_child_node->AttachParent(go_node);
    }

    return go_node;
}