#ifndef VDENGINE_IMAGE_H_
#define VDENGINE_IMAGE_H_

// C++ Standard libs
#include <string>

// External libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb/stb_image.h"

// Internal headers
#include "FileHandler.h"

namespace VDEngine
{

enum e_imgFormat : int
{
    GREY       = 1,
    GREY_ALPHA = 2,
    RGB        = 3,
    RGBA       = 4
};

class Image
{
  private:
    int                   m_width;
    int                   m_height;
    e_imgFormat           m_format;
    const unsigned char * m_data;

  public:
    Image(const std::string & file_name);
    Image(const Image &) = default;
    ~Image();

    Image & operator=(const Image &) = default;

    int                   GetWidth() const;
    int                   GetHeight() const;
    e_imgFormat           GetFormat() const;
    const unsigned char * GetData() const;

    static GLuint ToGLFormat(e_imgFormat format);
};

} // namespace VDEngine

#endif /* VDENGINE_IMAGE_H_ */