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
    float verticesArray[] = {
        -0.5f, -0.5f, -0.5f, //
        0.5f,  -0.5f, -0.5f, //
        0.5f,  0.5f,  -0.5f, //
        0.5f,  0.5f,  -0.5f, //
        -0.5f, 0.5f,  -0.5f, //
        -0.5f, -0.5f, -0.5f, //

        -0.5f, -0.5f, 0.5f, //
        0.5f,  -0.5f, 0.5f, //
        0.5f,  0.5f,  0.5f, //
        0.5f,  0.5f,  0.5f, //
        -0.5f, 0.5f,  0.5f, //
        -0.5f, -0.5f, 0.5f, //

        -0.5f, 0.5f,  0.5f,  //
        -0.5f, 0.5f,  -0.5f, //
        -0.5f, -0.5f, -0.5f, //
        -0.5f, -0.5f, -0.5f, //
        -0.5f, -0.5f, 0.5f,  //
        -0.5f, 0.5f,  0.5f,  //

        0.5f,  0.5f,  0.5f,  //
        0.5f,  0.5f,  -0.5f, //
        0.5f,  -0.5f, -0.5f, //
        0.5f,  -0.5f, -0.5f, //
        0.5f,  -0.5f, 0.5f,  //
        0.5f,  0.5f,  0.5f,  //

        -0.5f, -0.5f, -0.5f, //
        0.5f,  -0.5f, -0.5f, //
        0.5f,  -0.5f, 0.5f,  //
        0.5f,  -0.5f, 0.5f,  //
        -0.5f, -0.5f, 0.5f,  //
        -0.5f, -0.5f, -0.5f, //

        -0.5f, 0.5f,  -0.5f, //
        0.5f,  0.5f,  -0.5f, //
        0.5f,  0.5f,  0.5f,  //
        0.5f,  0.5f,  0.5f,  //
        -0.5f, 0.5f,  0.5f,  //
        -0.5f, 0.5f,  -0.5f, //
    };

    float normalsArray[] = {
        0.0f,  0.0f,  -1.0f, //
        0.0f,  0.0f,  -1.0f, //
        0.0f,  0.0f,  -1.0f, //
        0.0f,  0.0f,  -1.0f, //
        0.0f,  0.0f,  -1.0f, //
        0.0f,  0.0f,  -1.0f, //

        0.0f,  0.0f,  1.0f, //
        0.0f,  0.0f,  1.0f, //
        0.0f,  0.0f,  1.0f, //
        0.0f,  0.0f,  1.0f, //
        0.0f,  0.0f,  1.0f, //
        0.0f,  0.0f,  1.0f, //

        -1.0f, 0.0f,  0.0f, //
        -1.0f, 0.0f,  0.0f, //
        -1.0f, 0.0f,  0.0f, //
        -1.0f, 0.0f,  0.0f, //
        -1.0f, 0.0f,  0.0f, //
        -1.0f, 0.0f,  0.0f, //

        1.0f,  0.0f,  0.0f, //
        1.0f,  0.0f,  0.0f, //
        1.0f,  0.0f,  0.0f, //
        1.0f,  0.0f,  0.0f, //
        1.0f,  0.0f,  0.0f, //
        1.0f,  0.0f,  0.0f, //

        0.0f,  -1.0f, 0.0f, //
        0.0f,  -1.0f, 0.0f, //
        0.0f,  -1.0f, 0.0f, //
        0.0f,  -1.0f, 0.0f, //
        0.0f,  -1.0f, 0.0f, //
        0.0f,  -1.0f, 0.0f, //

        0.0f,  1.0f,  0.0f, //
        0.0f,  1.0f,  0.0f, //
        0.0f,  1.0f,  0.0f, //
        0.0f,  1.0f,  0.0f, //
        0.0f,  1.0f,  0.0f, //
        0.0f,  1.0f,  0.0f, //
    };

    float vColorsArray[] = {
        // Back
        0.0, 0.0, 1.0, //
        0.0, 0.0, 1.0, //
        0.0, 0.0, 1.0, //
        0.0, 0.0, 1.0, //
        0.0, 0.0, 1.0, //
        0.0, 0.0, 1.0, //

        // Front face
        0.5, 0.5, 1.0, //
        0.5, 0.5, 1.0, //
        0.5, 0.5, 1.0, //
        0.5, 0.5, 1.0, //
        0.5, 0.5, 1.0, //
        0.5, 0.5, 1.0, //

        // Left face
        1.0, 0.0, 0.0, //
        1.0, 0.0, 0.0, //
        1.0, 0.0, 0.0, //
        1.0, 0.0, 0.0, //
        1.0, 0.0, 0.0, //
        1.0, 0.0, 0.0, //

        // Right face
        1.0, 0.5, 0.5, //
        1.0, 0.5, 0.5, //
        1.0, 0.5, 0.5, //
        1.0, 0.5, 0.5, //
        1.0, 0.5, 0.5, //
        1.0, 0.5, 0.5, //

        // Bottom face
        0.0, 1.0, 0.0, //
        0.0, 1.0, 0.0, //
        0.0, 1.0, 0.0, //
        0.0, 1.0, 0.0, //
        0.0, 1.0, 0.0, //
        0.0, 1.0, 0.0, //

        // Top face
        0.5, 1.0, 0.5, //
        0.5, 1.0, 0.5, //
        0.5, 1.0, 0.5, //
        0.5, 1.0, 0.5, //
        0.5, 1.0, 0.5, //
        0.5, 1.0, 0.5, //
    };

    float vTexCoordsArray[] = {
        0.0f, 0.0f, //
        1.0f, 0.0f, //
        1.0f, 1.0f, //
        1.0f, 1.0f, //
        0.0f, 1.0f, //
        0.0f, 0.0f, //

        0.0f, 0.0f, //
        1.0f, 0.0f, //
        1.0f, 1.0f, //
        1.0f, 1.0f, //
        0.0f, 1.0f, //
        0.0f, 0.0f, //

        1.0f, 0.0f, //
        1.0f, 1.0f, //
        0.0f, 1.0f, //
        0.0f, 1.0f, //
        0.0f, 0.0f, //
        1.0f, 0.0f, //

        1.0f, 0.0f, //
        1.0f, 1.0f, //
        0.0f, 1.0f, //
        0.0f, 1.0f, //
        0.0f, 0.0f, //
        1.0f, 0.0f, //

        0.0f, 1.0f, //
        1.0f, 1.0f, //
        1.0f, 0.0f, //
        1.0f, 0.0f, //
        0.0f, 0.0f, //
        0.0f, 1.0f, //

        0.0f, 1.0f, //
        1.0f, 1.0f, //
        1.0f, 0.0f, //
        1.0f, 0.0f, //
        0.0f, 0.0f, //
        0.0f, 1.0f  //
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
    float verticesArray[] = {
        -0.5f, -0.5f, 0.0f, //
        0.5f,  -0.5f, 0.0f, //
        0.5f,  0.5f,  0.0f, //
        0.5f,  0.5f,  0.0f, //
        -0.5f, 0.5f,  0.0f, //
        -0.5f, -0.5f, 0.0f, //
    };

    float normalsArray[] = {
        0.0f, 0.0f, 1.0f, //
        0.0f, 0.0f, 1.0f, //
        0.0f, 0.0f, 1.0f, //
        0.0f, 0.0f, 1.0f, //
        0.0f, 0.0f, 1.0f, //
        0.0f, 0.0f, 1.0f, //
    };

    float vColorsArray[] = {
        // Front face
        1.0, 1.0, 1.0, //
        1.0, 1.0, 1.0, //
        1.0, 1.0, 1.0, //
        1.0, 1.0, 1.0, //
        1.0, 1.0, 1.0, //
        1.0, 1.0, 1.0, //
    };

    float vTexCoordsArray[] = {
        0.0f, 0.0f, //
        1.0f, 0.0f, //
        1.0f, 1.0f, //
        1.0f, 1.0f, //
        0.0f, 1.0f, //
        0.0f, 0.0f, //
    };

    Mesh * mesh = new Mesh();

    mesh->vert_positions.insert(mesh->vert_positions.begin(), std::begin(verticesArray), std::end(verticesArray));
    mesh->vert_normals.insert(mesh->vert_normals.begin(), std::begin(normalsArray), std::end(normalsArray));
    mesh->vert_colors.insert(mesh->vert_colors.begin(), std::begin(vColorsArray), std::end(vColorsArray));
    mesh->vert_textCoords.insert(mesh->vert_textCoords.begin(), std::begin(vTexCoordsArray), std::end(vTexCoordsArray));

    return mesh;
}