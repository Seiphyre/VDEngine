

#ifndef VDENGINE_META_HEADER
#define VDENGINE_META_HEADER

#include "metaStuff/Meta.h"

#endif /* VDENGINE_META_HEADER */

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
    friend auto meta::registerMembers<VDEngine::Image>();
    
  private:
    int                   m_width;
    int                   m_height;
    e_imgFormat           m_format;
    const unsigned char * m_data;

  public:
    Image(const std::string & file_path);
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

#ifndef META_REGISTER_VDENGINE_IMAGE
#define META_REGISTER_VDENGINE_IMAGE

template <>
inline auto meta::registerMembers< VDEngine::Image >() 
{
    return meta::members( 
meta::member("m_width", &VDEngine::Image::m_width),
meta::member("m_height", &VDEngine::Image::m_height),
meta::member("m_format", &VDEngine::Image::m_format),
meta::member("m_data", &VDEngine::Image::m_data) 
    );
}

#endif /* META_REGISTER_VDENGINE_IMAGE */

