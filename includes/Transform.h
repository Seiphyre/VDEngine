#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VDEngine/Quaternion.h"

#define X_3D_AXIS glm::vec3(1.0f, 0.0f, 0.0f)
#define Y_3D_AXIS glm::vec3(0.0f, 1.0f, 0.0f)
#define Z_3D_AXIS glm::vec3(0.0f, 0.0f, 1.0f)

class Transform
{
  public:
    Transform();
    ~Transform();

    glm::mat4 GetMatrix() const;

    glm::vec3 GetForwardDir() const;
    glm::vec3 GetUpDir();
    glm::vec3 GetRightDir() const;

    glm::vec3 GetEulerRotation() const;
    void      SetEulerRotation(const glm::vec3 & euler_rotation);

    void Translate(const glm::vec3 & translation);
    void Translate(float x, float y, float z);

    void Rotate(const glm::vec3 & eulers);
    void Rotate(float x, float y, float z);
    void Rotate(float angle, const glm::vec3 & rotation_axis);

    void LookAt(const glm::vec3 & target);

    glm::vec3 position;
    glm::vec3 scale;

    glm::quat rotation;
    glm::vec3 euler_angle;
    glm::mat4 rotation_matrix;
};

#endif /* TRANSFORM_H_ */