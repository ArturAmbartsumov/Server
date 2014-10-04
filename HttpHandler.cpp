#include "HttpHandler.h"

HttpHandler::HttpHandler() {
    currentClient = 0;
}

void HttpHandler::setRootDir(std::string path) {
    fs.setRootDir(path);
}

void HttpHandler::exec(int clientSocket) {
    std::cout << "exec" << std::endl;
    currentClient = clientSocket;
    std::string data = readDataFromSocket(currentClient);
    HttpRequest request = buildRequest(data);
    HttpResponse response = buildResponse(request);
    sendDataToSocket(response, request.URL);
    close(clientSocket);
    currentClient = 0;
}

std::string HttpHandler::readDataFromSocket(int client) {
    char data[1024];
    int bytesReaded = (int)recv(client, &data, 1024, 0);
    if(bytesReaded == 0)
        std::cout << "Reading data error" << std::endl;
    std::string strBuffer(data,1024);
    return strBuffer;
}

HttpRequest HttpHandler::buildRequest(std::string data) {
    HttpRequest r;
    r.parsData(data);
    return r;
}

HttpResponse HttpHandler::buildResponse(HttpRequest &request) {
    HttpResponse r;
    r.CONNECTION = "close";
    r.DATE = getDate();
    if (request.METHOD != "GET" && request.METHOD != "HEAD") {
        r.CONTENT_LENGTH = 0;
        r.STATUS_CODE = "405 METHOD NOT ALLOWED";
        return r;
    }
    std::string path_status = fs.resolvePath(request.URL);
    if (path_status == "OK") {
        r.STATUS_CODE = "200 OK";
        r.CONTENT_LENGTH = fs.getFileLength();
        r.CONTENT_TYPE = fs.getFileType();
    }
    if (path_status == "Not Found") {
        r.STATUS_CODE = "404 Not Found";
        r.CONTENT_LENGTH = 0;
    }
    if (path_status == "FORBIDDEN") {
        r.STATUS_CODE = "403 FORBIDDEN";
        r.CONTENT_LENGTH = 0;
    }
    return r;
}

void HttpHandler::sendDataToSocket(HttpResponse &response, std::string filePath) {
    sendHeaders(response);
    if (response.STATUS_CODE == "200 OK") {
        sendFile(response, filePath);
    }
    close(currentClient);
}

void HttpHandler::sendHeaders(HttpResponse &response) {
    std::string respStr = response.getStringResponse();
    ssize_t s = send(currentClient, respStr.c_str(), respStr.length(), 0);
    if (s == -1 || errno == EPIPE) {
        std::cout << "EPIPE при отправке заголовков, errno =  " << errno << "\n";
        close(currentClient);
        return;
    }
}

void HttpHandler::sendFile(HttpResponse &response, std::string filePath) {
    int fd = open(filePath.c_str(), O_RDWR);
    off_t offset = 0;
    off_t fl = response.CONTENT_LENGTH;
    int ret = sendfile(fd, currentClient, offset, &fl, NULL, 0);
    if (ret == -1) {
        std::cout << "EPIPE при отправке заголовков, errno =  " << errno << "\n";
    }
    close(fd);
}

std::string HttpHandler::getDate() {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer,80,"%a, %d %b %G %T GMT",timeinfo);

    std::string dateStr(buffer);
    return  dateStr;
}
