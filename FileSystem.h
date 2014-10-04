#ifndef FileSystem_h
#define FileSystem_h

#include <fstream>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <cstring>
#include <iostream>
#include <string>

class FileSystem {
public:
    void setRootDir(std::string rd);

    std::string resolvePath(std::string &path);
    unsigned int getFileLength();
    std::string getFileType();

protected:
    //Переменные
    std::string root_dir;
    unsigned int fileLength;
    std::string fileType;

    //методы
    void setFileType(std::string type);
};

#endif // #define FileSystem_h