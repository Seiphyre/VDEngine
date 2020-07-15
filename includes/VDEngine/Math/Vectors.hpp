#ifndef VDENGINE_VECTORS_HPP_
#define VDENGINE_VECTORS_HPP_

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

// ---------------------------

inline Vector3 to_vector3(const Vector2 & vec)
{
    return Vector3(vec.x, vec.y, 0.0f);
}

inline Vector3 to_vector3(const Vector4 & vec)
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

} // namespace VDEngine

#endif /* VDENGINE_VECTORS_HPP_ */