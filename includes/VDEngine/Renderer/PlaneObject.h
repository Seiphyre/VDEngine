#ifndef PLANE_OBJECT_H_
#define PLANE_OBJECT_H_

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

#endif /* PLANE_OBJECT_H_ */