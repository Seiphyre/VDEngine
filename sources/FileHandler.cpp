#include "VDEngine/Core/FileHandler.h"

using namespace VDEngine;

const std::string FileHandler::RootToResourcesPath = "resources/";
const std::string FileHandler::RootToTexturePath   = "resources/textures/";
const std::string FileHandler::RootToShaderPath    = "resources/shaders/";

FileHandler::FileHandler() : RootPath(GetAppRootPath())
{
}

const std::string FileHandler::GetAppRootPath()
{
#ifdef __APPLE__

    char     execPath[PATH_MAX];
    uint32_t size = sizeof(execPath);
    if (_NSGetExecutablePath(execPath, &size) == 0)
    {
        char realExecPath[1024];
        realpath(execPath, realExecPath);

        std::string realExecPath_str(realExecPath);

        std::size_t found;

        for (int i = 0; i < 2; i++)
        {
            found            = realExecPath_str.find_last_of("/");
            realExecPath_str = realExecPath_str.substr(0, found);
        }
        std::string rootPath = realExecPath_str + "/";

        return std::string(rootPath);
    }
    else
        printf("buffer too small; need size %u\n", size);

    return "";

#else

    std::cout << "[FileHandler::GetAppRootPath] No implementation on this architecture." << std::endl;
    return "";
#endif
}

const std::string FileHandler::LoadFromTextFile(const std::string & path) const
{
    std::ifstream file;
    file.open(path);

    std::string line;
    std::string fileContent = "";

    if (file.is_open())
    {
        while (getline(file, line))
        {
            fileContent.append(line + "\n");
        }
        file.close();
    }
    else
        std::cout << "Unable to open file";

    return fileContent + "\0";
}

const unsigned char * FileHandler::LoadFromImageFile(const std::string & path, int & width, int & height,
                                                     int & format) const
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char * data = stbi_load(path.c_str(), &width, &height, &format, 0);

    return data;
}

const std::string FileHandler::LoadShader(const std::string & file_name) const
{
    std::string path = RootPath + RootToShaderPath + file_name;

    return (LoadFromTextFile(path));
}

const unsigned char * FileHandler::LoadTexture(const std::string & file_name, int & width, int & height,
                                               int & format) const
{
    std::string path = RootPath + RootToTexturePath + file_name;

    return (LoadFromImageFile(path, width, height, format));
}