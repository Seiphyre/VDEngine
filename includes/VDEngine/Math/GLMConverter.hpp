#ifndef VDENGINE_GLM_CONVERTER_H_
#define VDENGINE_GLM_CONVERTER_H_

// External libs
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/matrix.hpp"

// Internal headers
#include "VDEngine/Math/Vectors.hpp"
#include "VDEngine/Math/Quaternion.h"
#include "VDEngine/Math/Matrix4.h"

namespace VDEngine
{

// -- Vectors --

inline glm::vec2 to_glm_vec2(const Vector2 & vec)
{
    return glm::vec2(vec.x, vec.y);
}

inline Vector2 to_vector2(const glm::vec2 & vec)
{
    return Vector2(vec.x, vec.y);
}

inline glm::vec3 to_glm_vec3(const Vector3 & vec)
{
    return glm::vec3(vec.x, vec.y, vec.z);
}

inline Vector3 to_vector3(const glm::vec3 & vec)
{
    return Vector3(vec.x, vec.y, vec.z);
}

inline glm::vec4 to_glm_vec4(const Vector4 & vec)
{
    return glm::vec4(vec.x, vec.y, vec.z, vec.w);
}

inline Vector4 to_vector4(const glm::vec4 & vec)
{
    return Vector4(vec.x, vec.y, vec.z, vec.w);
}

// -- Quaternions --

inline Quaternion to_quaternion(const glm::quat & quat)
{
    Quaternion quaternion;

    quaternion.x = quat.x;
    quaternion.y = quat.y;
    quaternion.z = quat.z;
    quaternion.w = quat.w;

    return quaternion;
}

inline glm::quat to_glm_quat(const Quaternion & quaternion)
{
    glm::quat quat;

    quat.x = quaternion.x;
    quat.y = quaternion.y;
    quat.z = quaternion.z;
    quat.w = quaternion.w;

    return quat;
}

// -- Matrix --

inline Matrix4 to_matrix4(const glm::mat4 & mat4)
{
    Matrix4 matrix4;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            matrix4(i, j) = mat4[i][j];

    return matrix4;
}

inline glm::mat4 to_glm_mat4(const Matrix4 & matrix4)
{
    glm::mat4 mat4;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            mat4[i][j] = matrix4(i, j);

    return mat4;
}

} // namespace VDEngine

#endif /* VDENGINE_GLM_CONVERTER_H_ */