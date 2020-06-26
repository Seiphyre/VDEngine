#ifndef VDENGINE_VECTORS_HPP_
#define VDENGINE_VECTORS_HPP_

// External libs
#include "glm/glm.hpp"

// Internal headers
#include "VDEngine/Math/Vector2.h"
#include "VDEngine/Math/Vector3.h"
#include "VDEngine/Math/Vector4.h"

namespace VDEngine
{

// -- convertion operator --

inline Vector2 to_vector2(const Vector3 & vec)
{
    return Vector2(vec.x, vec.y);
}

inline Vector2 to_vector2(const Vector4 & vec)
{
    return Vector2(vec.x, vec.y);
}

inline Vector2 to_vector2(const glm::vec2 & vec)
{
    return Vector2(vec.x, vec.y);
}

// ---------------------------

inline Vector3 to_vector3(const Vector2 & vec)
{
    return Vector3(vec.x, vec.y, 0.0f);
}

inline Vector3 to_vector3(const Vector4 & vec)
{
    return Vector3(vec.x, vec.y, vec.z);
}

inline Vector3 to_vector3(const glm::vec3 & vec)
{
    return Vector3(vec.x, vec.y, vec.z);
}

// ---------------------------

inline Vector4 to_vector4(const Vector3 & vec)
{
    return Vector4(vec.x, vec.y, vec.z, 0.0f);
}

inline Vector4 to_vector4(const Vector2 & vec)
{
    return Vector4(vec.x, vec.y, 0.0f, 0.0f);
}

inline Vector4 to_vector4(const glm::vec4 & vec)
{
    return Vector4(vec.x, vec.y, vec.z, vec.w);
}

// ---------------------------

inline glm::vec2 to_glm_vec2(const Vector2 & vec)
{
    return glm::vec2(vec.x, vec.y);
}

inline glm::vec3 to_glm_vec3(const Vector3 & vec)
{
    return glm::vec3(vec.x, vec.y, vec.z);
}

inline glm::vec4 to_glm_vec4(const Vector4 & vec)
{
    return glm::vec4(vec.x, vec.y, vec.z, vec.w);
}

} // namespace VDEngine

#endif /* VDENGINE_VECTORS_HPP_ */