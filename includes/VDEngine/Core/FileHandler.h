#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#ifdef __APPLE__
#    include <mach-o/dyld.h>
#endif
#include "stb/stb_image.h"

#include <fstream>
#include <string>

#include "Singleton.h"

namespace VDEngine
{

class FileHandler : public Singleton<FileHandler>
{
    friend class Singleton<FileHandler>;

  public:
    const std::string     LoadFromTextFile(const std::string & path);
    const unsigned char * LoadFromImageFile(const std::string & path, int & width, int & height, int & format);

    const std::string     LoadShader(const std::string & file_name);
    const unsigned char * LoadTexture(const std::string & file_name, int & width, int & height, int & format);

    const std::string RootPath;

    static const std::string RootToResourcesPath;
    static const std::string RootToShaderPath;
    static const std::string RootToTexturePath;

  private:
    FileHandler();

    const std::string GetAppRootPath();
};

} // namespace VDEngine

#endif