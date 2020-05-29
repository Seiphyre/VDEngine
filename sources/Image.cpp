#include "VDEngine/Core/Image.h"

using namespace VDEngine;

GLuint Image::ToGLFormat(e_imgFormat format)
{
    GLuint gl_format;

    switch (format)
    {
        case RGB:
            gl_format = GL_RGB;
            break;
        case RGBA:
            gl_format = GL_RGBA;
            break;
        default:
            gl_format = GL_RED;
            std::cout << "[ToGLFormat] Format cannot be converted. It will be set to GL_RED." << std::endl;
            break;
    }

    return gl_format;
}

Image::Image(const std::string file_name)
{
    // Format
    //       1           grey
    //       2           grey, alpha
    //       3           red, green, blue
    //       4           red, green, blue, alpha

    _data = FileHandler::getInstance()->LoadTexture(file_name, _width, _height, (int &)_format);
}

Image::~Image()
{
    delete (_data);
}

int Image::GetWidth() const
{
    return (_width);
}
int Image::GetHeight() const
{
    return (_height);
}

e_imgFormat Image::GetFormat() const
{
    return (_format);
}

const unsigned char * Image::GetData() const
{
    return (_data);
}