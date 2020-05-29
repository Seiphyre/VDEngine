#ifndef VDENGINE_QUATERNION_H_
#define VDENGINE_QUATERNION_H_

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace VDEngine
{

class Quaternion
{
  public:
    Quaternion();
    Quaternion(float w, float y, float z, float x);
    ~Quaternion();

    void FromEuler(glm::vec3 euler);

    glm::vec3 ToEulerAngle() const;
    glm::mat4 ToRotationMatrix() const;

    float w;
    float y; // Heading / Pitch
    float z; // Attitude / Yaw
    float x; // Bank / Roll
};

} // namespace VDEngine

#endif /* VDENGINE_QUATERNION_H_ */