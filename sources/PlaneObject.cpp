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

    m_vert_positions.insert(m_vert_positions.begin(), std::begin(verticesArray), std::end(verticesArray));
    m_vert_colors.insert(m_vert_colors.begin(), std::begin(vColorsArray), std::end(vColorsArray));
    m_vert_textCoords.insert(m_vert_textCoords.begin(), std::begin(vTexCoordsArray), std::end(vTexCoordsArray));
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

    m_vert_positions.insert(m_vert_positions.begin(), std::begin(verticesArray), std::end(verticesArray));
    m_vert_colors.insert(m_vert_colors.begin(), std::begin(vColorsArray), std::end(vColorsArray));
    m_vert_textCoords.insert(m_vert_textCoords.begin(), std::begin(vTexCoordsArray), std::end(vTexCoordsArray));
}