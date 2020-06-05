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
    glm::vec3 verticesArray[] = {
        glm::vec3(-0.5f, -0.5f, -0.5f), //
        glm::vec3(0.5f, -0.5f, -0.5f),  //
        glm::vec3(0.5f, 0.5f, -0.5f),   //
        glm::vec3(0.5f, 0.5f, -0.5f),   //
        glm::vec3(-0.5f, 0.5f, -0.5f),  //
        glm::vec3(-0.5f, -0.5f, -0.5f), //

        glm::vec3(-0.5f, -0.5f, 0.5f), //
        glm::vec3(0.5f, -0.5f, 0.5f),  //
        glm::vec3(0.5f, 0.5f, 0.5f),   //
        glm::vec3(0.5f, 0.5f, 0.5f),   //
        glm::vec3(-0.5f, 0.5f, 0.5f),  //
        glm::vec3(-0.5f, -0.5f, 0.5f), //

        glm::vec3(-0.5f, 0.5f, 0.5f),   //
        glm::vec3(-0.5f, 0.5f, -0.5f),  //
        glm::vec3(-0.5f, -0.5f, -0.5f), //
        glm::vec3(-0.5f, -0.5f, -0.5f), //
        glm::vec3(-0.5f, -0.5f, 0.5f),  //
        glm::vec3(-0.5f, 0.5f, 0.5f),   //

        glm::vec3(0.5f, 0.5f, 0.5f),   //
        glm::vec3(0.5f, 0.5f, -0.5f),  //
        glm::vec3(0.5f, -0.5f, -0.5f), //
        glm::vec3(0.5f, -0.5f, -0.5f), //
        glm::vec3(0.5f, -0.5f, 0.5f),  //
        glm::vec3(0.5f, 0.5f, 0.5f),   //

        glm::vec3(-0.5f, -0.5f, -0.5f), //
        glm::vec3(0.5f, -0.5f, -0.5f),  //
        glm::vec3(0.5f, -0.5f, 0.5f),   //
        glm::vec3(0.5f, -0.5f, 0.5f),   //
        glm::vec3(-0.5f, -0.5f, 0.5f),  //
        glm::vec3(-0.5f, -0.5f, -0.5f), //

        glm::vec3(-0.5f, 0.5f, -0.5f), //
        glm::vec3(0.5f, 0.5f, -0.5f),  //
        glm::vec3(0.5f, 0.5f, 0.5f),   //
        glm::vec3(0.5f, 0.5f, 0.5f),   //
        glm::vec3(-0.5f, 0.5f, 0.5f),  //
        glm::vec3(-0.5f, 0.5f, -0.5f), //
    };

    glm::vec3 normalsArray[] = {
        glm::vec3(0.0f, 0.0f, -1.0f), //
        glm::vec3(0.0f, 0.0f, -1.0f), //
        glm::vec3(0.0f, 0.0f, -1.0f), //
        glm::vec3(0.0f, 0.0f, -1.0f), //
        glm::vec3(0.0f, 0.0f, -1.0f), //
        glm::vec3(0.0f, 0.0f, -1.0f), //

        glm::vec3(0.0f, 0.0f, 1.0f), //
        glm::vec3(0.0f, 0.0f, 1.0f), //
        glm::vec3(0.0f, 0.0f, 1.0f), //
        glm::vec3(0.0f, 0.0f, 1.0f), //
        glm::vec3(0.0f, 0.0f, 1.0f), //
        glm::vec3(0.0f, 0.0f, 1.0f), //

        glm::vec3(-1.0f, 0.0f, 0.0f), //
        glm::vec3(-1.0f, 0.0f, 0.0f), //
        glm::vec3(-1.0f, 0.0f, 0.0f), //
        glm::vec3(-1.0f, 0.0f, 0.0f), //
        glm::vec3(-1.0f, 0.0f, 0.0f), //
        glm::vec3(-1.0f, 0.0f, 0.0f), //

        glm::vec3(1.0f, 0.0f, 0.0f), //
        glm::vec3(1.0f, 0.0f, 0.0f), //
        glm::vec3(1.0f, 0.0f, 0.0f), //
        glm::vec3(1.0f, 0.0f, 0.0f), //
        glm::vec3(1.0f, 0.0f, 0.0f), //
        glm::vec3(1.0f, 0.0f, 0.0f), //

        glm::vec3(0.0f, -1.0f, 0.0f), //
        glm::vec3(0.0f, -1.0f, 0.0f), //
        glm::vec3(0.0f, -1.0f, 0.0f), //
        glm::vec3(0.0f, -1.0f, 0.0f), //
        glm::vec3(0.0f, -1.0f, 0.0f), //
        glm::vec3(0.0f, -1.0f, 0.0f), //

        glm::vec3(0.0f, 1.0f, 0.0f), //
        glm::vec3(0.0f, 1.0f, 0.0f), //
        glm::vec3(0.0f, 1.0f, 0.0f), //
        glm::vec3(0.0f, 1.0f, 0.0f), //
        glm::vec3(0.0f, 1.0f, 0.0f), //
        glm::vec3(0.0f, 1.0f, 0.0f), //
    };

    glm::vec3 vColorsArray[] = {
        // Back
        glm::vec3(0.0, 0.0, 1.0), //
        glm::vec3(0.0, 0.0, 1.0), //
        glm::vec3(0.0, 0.0, 1.0), //
        glm::vec3(0.0, 0.0, 1.0), //
        glm::vec3(0.0, 0.0, 1.0), //
        glm::vec3(0.0, 0.0, 1.0), //

        // Front face
        glm::vec3(0.5, 0.5, 1.0), //
        glm::vec3(0.5, 0.5, 1.0), //
        glm::vec3(0.5, 0.5, 1.0), //
        glm::vec3(0.5, 0.5, 1.0), //
        glm::vec3(0.5, 0.5, 1.0), //
        glm::vec3(0.5, 0.5, 1.0), //

        // Left face
        glm::vec3(1.0, 0.0, 0.0), //
        glm::vec3(1.0, 0.0, 0.0), //
        glm::vec3(1.0, 0.0, 0.0), //
        glm::vec3(1.0, 0.0, 0.0), //
        glm::vec3(1.0, 0.0, 0.0), //
        glm::vec3(1.0, 0.0, 0.0), //

        // Right face
        glm::vec3(1.0, 0.5, 0.5), //
        glm::vec3(1.0, 0.5, 0.5), //
        glm::vec3(1.0, 0.5, 0.5), //
        glm::vec3(1.0, 0.5, 0.5), //
        glm::vec3(1.0, 0.5, 0.5), //
        glm::vec3(1.0, 0.5, 0.5), //

        // Bottom face
        glm::vec3(0.0, 1.0, 0.0), //
        glm::vec3(0.0, 1.0, 0.0), //
        glm::vec3(0.0, 1.0, 0.0), //
        glm::vec3(0.0, 1.0, 0.0), //
        glm::vec3(0.0, 1.0, 0.0), //
        glm::vec3(0.0, 1.0, 0.0), //

        // Top face
        glm::vec3(0.5, 1.0, 0.5), //
        glm::vec3(0.5, 1.0, 0.5), //
        glm::vec3(0.5, 1.0, 0.5), //
        glm::vec3(0.5, 1.0, 0.5), //
        glm::vec3(0.5, 1.0, 0.5), //
        glm::vec3(0.5, 1.0, 0.5), //
    };

    glm::vec2 vTexCoordsArray[] = {
        glm::vec2(0.0f, 0.0f), //
        glm::vec2(1.0f, 0.0f), //
        glm::vec2(1.0f, 1.0f), //
        glm::vec2(1.0f, 1.0f), //
        glm::vec2(0.0f, 1.0f), //
        glm::vec2(0.0f, 0.0f), //

        glm::vec2(0.0f, 0.0f), //
        glm::vec2(1.0f, 0.0f), //
        glm::vec2(1.0f, 1.0f), //
        glm::vec2(1.0f, 1.0f), //
        glm::vec2(0.0f, 1.0f), //
        glm::vec2(0.0f, 0.0f), //

        glm::vec2(1.0f, 0.0f), //
        glm::vec2(1.0f, 1.0f), //
        glm::vec2(0.0f, 1.0f), //
        glm::vec2(0.0f, 1.0f), //
        glm::vec2(0.0f, 0.0f), //
        glm::vec2(1.0f, 0.0f), //

        glm::vec2(1.0f, 0.0f), //
        glm::vec2(1.0f, 1.0f), //
        glm::vec2(0.0f, 1.0f), //
        glm::vec2(0.0f, 1.0f), //
        glm::vec2(0.0f, 0.0f), //
        glm::vec2(1.0f, 0.0f), //

        glm::vec2(0.0f, 1.0f), //
        glm::vec2(1.0f, 1.0f), //
        glm::vec2(1.0f, 0.0f), //
        glm::vec2(1.0f, 0.0f), //
        glm::vec2(0.0f, 0.0f), //
        glm::vec2(0.0f, 1.0f), //

        glm::vec2(0.0f, 1.0f), //
        glm::vec2(1.0f, 1.0f), //
        glm::vec2(1.0f, 0.0f), //
        glm::vec2(1.0f, 0.0f), //
        glm::vec2(0.0f, 0.0f), //
        glm::vec2(0.0f, 1.0f)  //
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
    glm::vec3 verticesArray[] = {
        glm::vec3(-0.5f, -0.5f, 0.0f), //
        glm::vec3(0.5f, -0.5f, 0.0f),  //
        glm::vec3(0.5f, 0.5f, 0.0f),   //
        glm::vec3(0.5f, 0.5f, 0.0f),   //
        glm::vec3(-0.5f, 0.5f, 0.0f),  //
        glm::vec3(-0.5f, -0.5f, 0.0f), //
    };

    glm::vec3 normalsArray[] = {
        glm::vec3(0.0f, 0.0f, 1.0f), //
        glm::vec3(0.0f, 0.0f, 1.0f), //
        glm::vec3(0.0f, 0.0f, 1.0f), //
        glm::vec3(0.0f, 0.0f, 1.0f), //
        glm::vec3(0.0f, 0.0f, 1.0f), //
        glm::vec3(0.0f, 0.0f, 1.0f), //
    };

    glm::vec3 vColorsArray[] = {
        glm::vec3(1.0, 1.0, 1.0), //
        glm::vec3(1.0, 1.0, 1.0), //
        glm::vec3(1.0, 1.0, 1.0), //
        glm::vec3(1.0, 1.0, 1.0), //
        glm::vec3(1.0, 1.0, 1.0), //
        glm::vec3(1.0, 1.0, 1.0), //
    };

    glm::vec2 vTexCoordsArray[] = {
        glm::vec2(0.0f, 0.0f), //
        glm::vec2(1.0f, 0.0f), //
        glm::vec2(1.0f, 1.0f), //
        glm::vec2(1.0f, 1.0f), //
        glm::vec2(0.0f, 1.0f), //
        glm::vec2(0.0f, 0.0f), //
    };

    Mesh * mesh = new Mesh();

    mesh->vert_positions.insert(mesh->vert_positions.begin(), std::begin(verticesArray), std::end(verticesArray));
    mesh->vert_normals.insert(mesh->vert_normals.begin(), std::begin(normalsArray), std::end(normalsArray));
    mesh->vert_colors.insert(mesh->vert_colors.begin(), std::begin(vColorsArray), std::end(vColorsArray));
    mesh->vert_textCoords.insert(mesh->vert_textCoords.begin(), std::begin(vTexCoordsArray), std::end(vTexCoordsArray));

    return mesh;
}