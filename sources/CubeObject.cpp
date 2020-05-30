#include "VDEngine/Renderer/CubeObject.h"

using namespace VDEngine;

CubeObj::CubeObj() : AObject()
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

    m_vert_positions.insert(m_vert_positions.begin(), std::begin(verticesArray), std::end(verticesArray));
    m_vert_colors.insert(m_vert_colors.begin(), std::begin(vColorsArray), std::end(vColorsArray));
    m_vert_textCoords.insert(m_vert_textCoords.begin(), std::begin(vTexCoordsArray), std::end(vTexCoordsArray));
}

CubeObj::CubeObj(AShader * shader) : AObject(shader)
{
    float verticesArray[] = {
        0.5f,  0.5f,  0.0f, // top right
        0.5f,  -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f  // top left
    };

    float vColorsArray[] = {
        1.0f, 0.0f, 0.0f, // top right
        0.0f, 1.0f, 0.0f, // bottom right
        0.0f, 0.0f, 1.0f, // bottom left
        1.0f, 1.0f, 0.0f  // top left
    };

    float vTexCoordsArray[] = {
        1.0f, 1.0f, // top right
        1.0f, 0.0f, // bottom right
        0.0f, 0.0f, // bottom left
        0.0f, 1.0f, // top left
    };

    m_vert_positions.insert(m_vert_positions.begin(), std::begin(verticesArray), std::end(verticesArray));
    m_vert_colors.insert(m_vert_colors.begin(), std::begin(vColorsArray), std::end(vColorsArray));
    m_vert_textCoords.insert(m_vert_textCoords.begin(), std::begin(vTexCoordsArray), std::end(vTexCoordsArray));
}