#ifndef IMAGE_H_
#define IMAGE_H_

#include <GLFW/glfw3.h>

#include <string>

#include "stb/stb_image.h"
#include "FileHandler.h"

enum e_imgFormat : int
{
    GREY = 1,
    GREY_ALPHA = 2,
    RGB = 3,
    RGBA = 4
};

class Image
{
private:
    int _width;
    int _height;
    e_imgFormat _format;
    const unsigned char *_data;

public:
    Image(const std::string file_name);
    ~Image();

    int GetWidth() const;
    int GetHeight() const;
    e_imgFormat GetFormat() const;
    const unsigned char *GetData() const;

    static GLuint ToGLFormat(e_imgFormat format);
};

#endif /* IMAGE_H_ */