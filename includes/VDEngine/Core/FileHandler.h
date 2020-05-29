#ifndef VDENGINE_FILE_HANDLER_H_
#define VDENGINE_FILE_HANDLER_H_

#ifdef __APPLE__
#    include <mach-o/dyld.h> // Mac OS functions ( ex: _NSGetExecutablePath() )
#endif

// C++ Standard libs
#include <iostream>
#include <fstream>
#include <string>

// External libs
#include "stb/stb_image.h"

// Internal headers
#include "Singleton.h"

namespace VDEngine
{

class FileHandler : public Singleton<FileHandler>
{
    friend class Singleton<FileHandler>;

  public:

    // -- Public Methodes --

    const std::string     LoadFromTextFile(const std::string & path) const;
    const unsigned char * LoadFromImageFile(const std::string & path, int & width, int & height, int & format) const ;

    const std::string     LoadShader(const std::string & file_name) const ;
    const unsigned char * LoadTexture(const std::string & file_name, int & width, int & height, int & format) const;

    // -- Public Attributes --

    const std::string RootPath;

    static const std::string RootToResourcesPath;
    static const std::string RootToShaderPath;
    static const std::string RootToTexturePath;

  private:

    // -- Privates Methodes --

    FileHandler();

    const std::string GetAppRootPath();
};

} // namespace VDEngine

#endif /* VDENGINE_FILE_HANDLER_H_ */