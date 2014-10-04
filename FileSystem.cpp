#include "FileSystem.h"

void FileSystem::setRootDir(std::string rd) {
    root_dir = rd;
    fileLength = 0;
    fileType = "";
}

std::string FileSystem::resolvePath(std::string &path) {
    struct stat _st;
    path = root_dir + path;
    int status = stat(path.c_str(), &_st);
    if (status != 0)
        return "Not Found";
    if (S_ISDIR(_st.st_mode)) { //если дирректория
        path += "index.html";
        int newStatus = stat(path.c_str(), &_st);
        if (newStatus != 0)
            return "FORBIDDEN";
    }
    if (S_ISREG(_st.st_mode)) {
        fileLength = (unsigned int) _st.st_size;
        setFileType(path);
        return "OK";
    }
}

unsigned int FileSystem::getFileLength() {
    return fileLength;
}

void FileSystem::setFileType(std::string path) {
    size_t pos = path.find_last_of(".");
    fileType = "";
    if(pos == std::string::npos)
        return;
    for(unsigned i = (int)pos; i < path.length(); i++)
        fileType += path[i];

    if(fileType == ".html") {
        fileType = "text/html";
        return;
    }
    if(fileType == ".css") {
        fileType = "text/css";
        return;
    }
    if(fileType == ".js") {
        fileType = "text/javascript";
        return;
    }
    if(fileType == ".jpg" || fileType == ".jpeg") {
        fileType = "image/jpeg";
        return;
    }
    if(fileType == ".gif") {
        fileType = "image/gif";
        return;
    }
    if(fileType == ".png") {
        fileType = "image/png";
        return;
    }
    if(fileType == ".txt") {
        fileType = "text/plain";
        return;
    }
    if(fileType == ".swf") {
        fileType = "application/x-shockwave-flash";
        return;
    }
}

std::string FileSystem::getFileType() {
    return fileType;
}
