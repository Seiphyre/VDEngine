#ifndef DEFAULT_SHADER_H
#define DEFAULT_SHADER_H

#include <GLFW/glfw3.h>
#include <iostream>

#include "AShader.h"

namespace VDEngine
{

class DefaultShader : public AShader
{
  protected:
    void SetVertexShaderSource();
    void SetFragmentShaderSource();
};

}

#endif