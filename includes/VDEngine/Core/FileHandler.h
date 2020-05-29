#ifndef VDENGINE_FILE_HANDLER_H_
#define VDENGINE_FILE_HANDLER_H_

#ifdef __APPLE__
#    include <mach-o/dyld.h> // Mac OS functions ( ex: _NSGetExecutablePath() )
#endif

#include <fstream>
#include <string>

#include "stb/stb_image.h"

#include "Singleton.h"

namespace VDEngine
{

class FileHandler : public Singleton<FileHandler>
{
    friend class Singleton<FileHandler>;

  public:
    const std::string     LoadFromTextFile(const std::string & path) const;
    const unsigned char * LoadFromImageFile(const std::string & path, int & width, int & height, int & format) const ;

    const std::string     LoadShader(const std::string & file_name) const ;
    const unsigned char * LoadTexture(const std::string & file_name, int & width, int & height, int & format) const;

    const std::string RootPath;

    static const std::string RootToResourcesPath;
    static const std::string RootToShaderPath;
    static const std::string RootToTexturePath;

  private:
    FileHandler();

    const std::string GetAppRootPath();
};

} // namespace VDEngine

#endif /* VDENGINE_FILE_HANDLER_H_ */