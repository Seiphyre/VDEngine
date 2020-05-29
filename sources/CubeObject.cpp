#include "VDEngine/Renderer/CubeObject.h"

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

    // NOT USED
    unsigned int indicesArray[] = {
        0,  1,  2,  0,  2,  3,  // front
        4,  5,  6,  4,  6,  7,  // back
        8,  9,  10, 8,  10, 11, // top
        12, 13, 14, 12, 14, 15, // bottom
        16, 17, 18, 16, 18, 19, // right
        20, 21, 22, 20, 22, 23  // left
    };

    m_vert_positions.insert(m_vert_positions.begin(), std::begin(verticesArray), std::end(verticesArray));
    m_vert_colors.insert(m_vert_colors.begin(), std::begin(vColorsArray), std::end(vColorsArray));
    m_vert_textCoords.insert(m_vert_textCoords.begin(), std::begin(vTexCoordsArray), std::end(vTexCoordsArray));
    m_elem_indices.insert(m_elem_indices.begin(), std::begin(indicesArray), std::end(indicesArray));
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

    unsigned int indicesArray[] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    m_vert_positions.insert(m_vert_positions.begin(), std::begin(verticesArray), std::end(verticesArray));
    m_vert_colors.insert(m_vert_colors.begin(), std::begin(vColorsArray), std::end(vColorsArray));
    m_vert_textCoords.insert(m_vert_textCoords.begin(), std::begin(vTexCoordsArray), std::end(vTexCoordsArray));
    m_elem_indices.insert(m_elem_indices.begin(), std::begin(indicesArray), std::end(indicesArray));
}