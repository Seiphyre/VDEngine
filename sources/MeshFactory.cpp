#include "VDEngine/Renderer/MeshFactory.h"

using namespace VDEngine;

MeshFactory::MeshFactory()
{
}

MeshFactory::~MeshFactory()
{
}

Mesh * MeshFactory::CreateCube()
{
    Vector3 verticesArray[] = {
        Vector3(-0.5f, -0.5f, -0.5f), //
        Vector3(0.5f, -0.5f, -0.5f),  //
        Vector3(0.5f, 0.5f, -0.5f),   //
        Vector3(0.5f, 0.5f, -0.5f),   //
        Vector3(-0.5f, 0.5f, -0.5f),  //
        Vector3(-0.5f, -0.5f, -0.5f), //

        Vector3(-0.5f, -0.5f, 0.5f), //
        Vector3(0.5f, -0.5f, 0.5f),  //
        Vector3(0.5f, 0.5f, 0.5f),   //
        Vector3(0.5f, 0.5f, 0.5f),   //
        Vector3(-0.5f, 0.5f, 0.5f),  //
        Vector3(-0.5f, -0.5f, 0.5f), //

        Vector3(-0.5f, 0.5f, 0.5f),   //
        Vector3(-0.5f, 0.5f, -0.5f),  //
        Vector3(-0.5f, -0.5f, -0.5f), //
        Vector3(-0.5f, -0.5f, -0.5f), //
        Vector3(-0.5f, -0.5f, 0.5f),  //
        Vector3(-0.5f, 0.5f, 0.5f),   //

        Vector3(0.5f, 0.5f, 0.5f),   //
        Vector3(0.5f, 0.5f, -0.5f),  //
        Vector3(0.5f, -0.5f, -0.5f), //
        Vector3(0.5f, -0.5f, -0.5f), //
        Vector3(0.5f, -0.5f, 0.5f),  //
        Vector3(0.5f, 0.5f, 0.5f),   //

        Vector3(-0.5f, -0.5f, -0.5f), //
        Vector3(0.5f, -0.5f, -0.5f),  //
        Vector3(0.5f, -0.5f, 0.5f),   //
        Vector3(0.5f, -0.5f, 0.5f),   //
        Vector3(-0.5f, -0.5f, 0.5f),  //
        Vector3(-0.5f, -0.5f, -0.5f), //

        Vector3(-0.5f, 0.5f, -0.5f), //
        Vector3(0.5f, 0.5f, -0.5f),  //
        Vector3(0.5f, 0.5f, 0.5f),   //
        Vector3(0.5f, 0.5f, 0.5f),   //
        Vector3(-0.5f, 0.5f, 0.5f),  //
        Vector3(-0.5f, 0.5f, -0.5f), //
    };

    Vector3 normalsArray[] = {
        Vector3(0.0f, 0.0f, -1.0f), //
        Vector3(0.0f, 0.0f, -1.0f), //
        Vector3(0.0f, 0.0f, -1.0f), //
        Vector3(0.0f, 0.0f, -1.0f), //
        Vector3(0.0f, 0.0f, -1.0f), //
        Vector3(0.0f, 0.0f, -1.0f), //

        Vector3(0.0f, 0.0f, 1.0f), //
        Vector3(0.0f, 0.0f, 1.0f), //
        Vector3(0.0f, 0.0f, 1.0f), //
        Vector3(0.0f, 0.0f, 1.0f), //
        Vector3(0.0f, 0.0f, 1.0f), //
        Vector3(0.0f, 0.0f, 1.0f), //

        Vector3(-1.0f, 0.0f, 0.0f), //
        Vector3(-1.0f, 0.0f, 0.0f), //
        Vector3(-1.0f, 0.0f, 0.0f), //
        Vector3(-1.0f, 0.0f, 0.0f), //
        Vector3(-1.0f, 0.0f, 0.0f), //
        Vector3(-1.0f, 0.0f, 0.0f), //

        Vector3(1.0f, 0.0f, 0.0f), //
        Vector3(1.0f, 0.0f, 0.0f), //
        Vector3(1.0f, 0.0f, 0.0f), //
        Vector3(1.0f, 0.0f, 0.0f), //
        Vector3(1.0f, 0.0f, 0.0f), //
        Vector3(1.0f, 0.0f, 0.0f), //

        Vector3(0.0f, -1.0f, 0.0f), //
        Vector3(0.0f, -1.0f, 0.0f), //
        Vector3(0.0f, -1.0f, 0.0f), //
        Vector3(0.0f, -1.0f, 0.0f), //
        Vector3(0.0f, -1.0f, 0.0f), //
        Vector3(0.0f, -1.0f, 0.0f), //

        Vector3(0.0f, 1.0f, 0.0f), //
        Vector3(0.0f, 1.0f, 0.0f), //
        Vector3(0.0f, 1.0f, 0.0f), //
        Vector3(0.0f, 1.0f, 0.0f), //
        Vector3(0.0f, 1.0f, 0.0f), //
        Vector3(0.0f, 1.0f, 0.0f), //
    };

    Vector3 vColorsArray[] = {
        // Back
        Vector3(0.0, 0.0, 1.0), //
        Vector3(0.0, 0.0, 1.0), //
        Vector3(0.0, 0.0, 1.0), //
        Vector3(0.0, 0.0, 1.0), //
        Vector3(0.0, 0.0, 1.0), //
        Vector3(0.0, 0.0, 1.0), //

        // Front face
        Vector3(0.5, 0.5, 1.0), //
        Vector3(0.5, 0.5, 1.0), //
        Vector3(0.5, 0.5, 1.0), //
        Vector3(0.5, 0.5, 1.0), //
        Vector3(0.5, 0.5, 1.0), //
        Vector3(0.5, 0.5, 1.0), //

        // Left face
        Vector3(1.0, 0.0, 0.0), //
        Vector3(1.0, 0.0, 0.0), //
        Vector3(1.0, 0.0, 0.0), //
        Vector3(1.0, 0.0, 0.0), //
        Vector3(1.0, 0.0, 0.0), //
        Vector3(1.0, 0.0, 0.0), //

        // Right face
        Vector3(1.0, 0.5, 0.5), //
        Vector3(1.0, 0.5, 0.5), //
        Vector3(1.0, 0.5, 0.5), //
        Vector3(1.0, 0.5, 0.5), //
        Vector3(1.0, 0.5, 0.5), //
        Vector3(1.0, 0.5, 0.5), //

        // Bottom face
        Vector3(0.0, 1.0, 0.0), //
        Vector3(0.0, 1.0, 0.0), //
        Vector3(0.0, 1.0, 0.0), //
        Vector3(0.0, 1.0, 0.0), //
        Vector3(0.0, 1.0, 0.0), //
        Vector3(0.0, 1.0, 0.0), //

        // Top face
        Vector3(0.5, 1.0, 0.5), //
        Vector3(0.5, 1.0, 0.5), //
        Vector3(0.5, 1.0, 0.5), //
        Vector3(0.5, 1.0, 0.5), //
        Vector3(0.5, 1.0, 0.5), //
        Vector3(0.5, 1.0, 0.5), //
    };

    Vector2 vTexCoordsArray[] = {
        Vector2(0.0f, 0.0f), //
        Vector2(1.0f, 0.0f), //
        Vector2(1.0f, 1.0f), //
        Vector2(1.0f, 1.0f), //
        Vector2(0.0f, 1.0f), //
        Vector2(0.0f, 0.0f), //

        Vector2(0.0f, 0.0f), //
        Vector2(1.0f, 0.0f), //
        Vector2(1.0f, 1.0f), //
        Vector2(1.0f, 1.0f), //
        Vector2(0.0f, 1.0f), //
        Vector2(0.0f, 0.0f), //

        Vector2(1.0f, 0.0f), //
        Vector2(1.0f, 1.0f), //
        Vector2(0.0f, 1.0f), //
        Vector2(0.0f, 1.0f), //
        Vector2(0.0f, 0.0f), //
        Vector2(1.0f, 0.0f), //

        Vector2(1.0f, 0.0f), //
        Vector2(1.0f, 1.0f), //
        Vector2(0.0f, 1.0f), //
        Vector2(0.0f, 1.0f), //
        Vector2(0.0f, 0.0f), //
        Vector2(1.0f, 0.0f), //

        Vector2(0.0f, 1.0f), //
        Vector2(1.0f, 1.0f), //
        Vector2(1.0f, 0.0f), //
        Vector2(1.0f, 0.0f), //
        Vector2(0.0f, 0.0f), //
        Vector2(0.0f, 1.0f), //

        Vector2(0.0f, 1.0f), //
        Vector2(1.0f, 1.0f), //
        Vector2(1.0f, 0.0f), //
        Vector2(1.0f, 0.0f), //
        Vector2(0.0f, 0.0f), //
        Vector2(0.0f, 1.0f)  //
    };

    Mesh * mesh = new Mesh();

    mesh->vert_positions.insert(mesh->vert_positions.begin(), std::begin(verticesArray), std::end(verticesArray));
    mesh->vert_normals.insert(mesh->vert_normals.begin(), std::begin(normalsArray), std::end(normalsArray));
    mesh->vert_colors.insert(mesh->vert_colors.begin(), std::begin(vColorsArray), std::end(vColorsArray));
    mesh->vert_textCoords.insert(mesh->vert_textCoords.begin(), std::begin(vTexCoordsArray), std::end(vTexCoordsArray));

    return mesh;
}

Mesh * MeshFactory::CreatePlane()
{
    Vector3 verticesArray[] = {
        Vector3(-0.5f, -0.5f, 0.0f), //
        Vector3(0.5f, -0.5f, 0.0f),  //
        Vector3(0.5f, 0.5f, 0.0f),   //
        Vector3(0.5f, 0.5f, 0.0f),   //
        Vector3(-0.5f, 0.5f, 0.0f),  //
        Vector3(-0.5f, -0.5f, 0.0f), //
    };

    Vector3 normalsArray[] = {
        Vector3(0.0f, 0.0f, 1.0f), //
        Vector3(0.0f, 0.0f, 1.0f), //
        Vector3(0.0f, 0.0f, 1.0f), //
        Vector3(0.0f, 0.0f, 1.0f), //
        Vector3(0.0f, 0.0f, 1.0f), //
        Vector3(0.0f, 0.0f, 1.0f), //
    };

    Vector3 vColorsArray[] = {
        Vector3(1.0, 1.0, 1.0), //
        Vector3(1.0, 1.0, 1.0), //
        Vector3(1.0, 1.0, 1.0), //
        Vector3(1.0, 1.0, 1.0), //
        Vector3(1.0, 1.0, 1.0), //
        Vector3(1.0, 1.0, 1.0), //
    };

    Vector2 vTexCoordsArray[] = {
        Vector2(0.0f, 0.0f), //
        Vector2(1.0f, 0.0f), //
        Vector2(1.0f, 1.0f), //
        Vector2(1.0f, 1.0f), //
        Vector2(0.0f, 1.0f), //
        Vector2(0.0f, 0.0f), //
    };

    Mesh * mesh = new Mesh();

    mesh->vert_positions.insert(mesh->vert_positions.begin(), std::begin(verticesArray), std::end(verticesArray));
    mesh->vert_normals.insert(mesh->vert_normals.begin(), std::begin(normalsArray), std::end(normalsArray));
    mesh->vert_colors.insert(mesh->vert_colors.begin(), std::begin(vColorsArray), std::end(vColorsArray));
    mesh->vert_textCoords.insert(mesh->vert_textCoords.begin(), std::begin(vTexCoordsArray), std::end(vTexCoordsArray));

    return mesh;
}