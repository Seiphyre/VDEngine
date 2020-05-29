#ifndef VDENGINE_CUBE_OBJECT_H_
#define VDENGINE_CUBE_OBJECT_H_

// Internal headers
#include "AObject.h"

namespace VDEngine
{

class CubeObj : public AObject
{
  public:
    CubeObj();
    CubeObj(AShader * shader);
};

}

#endif /* VDENGINE_CUBE_OBJECT_H_ */