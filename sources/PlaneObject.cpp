#include "VDEngine/Renderer/PlaneObject.h"

using namespace VDEngine;

PlaneObj::PlaneObj() : AObject()
{
    float verticesArray[] = {
        -0.5f, -0.5f, 0.0f, //
        0.5f,  -0.5f, 0.0f, //
        0.5f,  0.5f,  0.0f, //
        0.5f,  0.5f,  0.0f, //
        -0.5f, 0.5f,  0.0f, //
        -0.5f, -0.5f, 0.0f, //
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

PlaneObj::PlaneObj(AShader * shader) : AObject(shader)
{
    float verticesArray[] = {
        -0.5f, -0.5f, -0.5f, //
        0.5f,  -0.5f, -0.5f, //
        0.5f,  0.5f,  -0.5f, //
        0.5f,  0.5f,  -0.5f, //
        -0.5f, 0.5f,  -0.5f, //
        -0.5f, -0.5f, -0.5f, //
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