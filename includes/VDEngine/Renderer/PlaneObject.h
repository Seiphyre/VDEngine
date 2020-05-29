#ifndef VDENGINE_PLANE_OBJECT_H_
#define VDENGINE_PLANE_OBJECT_H_

// Internal headers
#include "AObject.h"

namespace VDEngine
{

class PlaneObj : public AObject
{
  public:
    PlaneObj();
    PlaneObj(AShader * shader);
};

}

#endif /* VDENGINE_PLANE_OBJECT_H_ */