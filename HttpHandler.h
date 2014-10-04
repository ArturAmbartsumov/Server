#ifndef HttpHandler_h
#define HttpHandler_h

#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <time.h>

#include "FileSystem.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

class HttpHandler {

public:
    //Методы
    HttpHandler();
    void setRootDir(std::string path);
    void exec(int clientSocket);

private:
    //Переменные
    FileSystem fs;
    int currentClient;

    //Методы
    std::string readDataFromSocket(int client);
    HttpRequest buildRequest(std::string data);
    HttpResponse buildResponse(HttpRequest &request);
    void sendDataToSocket(HttpResponse &response, std::string filePath);
    void sendHeaders(HttpResponse &response);
    void sendFile(HttpResponse &response, std::string filePath);
    std::string getDate();
};

#endif // #define HttpHandler_h