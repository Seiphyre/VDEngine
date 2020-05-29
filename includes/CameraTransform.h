#ifndef CAMERA_TRANSFORM_H_
#define CAMERA_TRANSFORM_H_

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>

class CameraTransform
{
  public:
    CameraTransform(const glm::vec3 & position = glm::vec3(0, 0, 0));
    ~CameraTransform();

    glm::vec3 Forward() const;
    glm::vec3 Up() const;
    glm::vec3 Right() const;

    glm::vec3 Position() const;
    glm::quat Rotation() const;

    void SetPosition(const glm::vec3 & position);
    void Translate(const glm::vec3 & vector);

    void Rotate(float angle, const glm::vec3 & axis);
    void Roll(float angle);
    void Yaw(float angle);
    void Pitch(float angle);

    glm::mat4 ModelMatrix(const glm::mat4 & scale = glm::mat4(1)) const;
    glm::mat4 View() const;

  protected:
    glm::vec3 m_position;
    glm::quat m_rotation;
};

#endif /* CAMERA_TRANSFORM_H_ */