#ifndef VDENGINE_LIGHT_H_
#define VDENGINE_LIGHT_H_

// External libs
#include <glm/glm.hpp>

// Internal headers
#include "VDEngine/Core/Transform.h"

namespace VDEngine
{

class Light
{
  public:
    Light();
    Light(const glm::vec3 & light_color);
    ~Light();

    Transform * GetTransform() const;

    glm::vec3 color;

  private:
    Transform * m_transform;
};

} // namespace VDEngine

#endif /* VDENGINE_LIGHT_H_ */