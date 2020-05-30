#ifndef VDENGINE_DEFAULT_SHADER_H_
#define VDENGINE_DEFAULT_SHADER_H_

// C++ Standard libs
#include <iostream>

// Internal headers
#include "AShader.h"

namespace VDEngine
{

class DefaultShader : public AShader
{
  protected:
    void SetVertexShaderSource();
    void SetFragmentShaderSource();
};

} // namespace VDEngine

#endif /* VDENGINE_DEFAULT_SHADER_H_ */