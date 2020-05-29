#ifndef CUBEOBJECT_H
#define CUBEOBJECT_H

#include "AObject.h"

class CubeObj : public AObject
{
  public:
    CubeObj();
    CubeObj(AShader * shader);
};

#endif