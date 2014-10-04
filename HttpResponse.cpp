
#include "HttpResponse.h"

HttpResponse::HttpResponse() {
    CONTENT_LENGTH = 0;
}

std::string HttpResponse::getStringResponse() {
    std::stringstream respStream;
    respStream << "HTTP/1.1 " << STATUS_CODE << "\r\n" << "Date: " << DATE << "\r\n" << "Server: MYSERV\r\n" ;
    if(STATUS_CODE == "200 OK") {
        respStream << "Content-Type: " << CONTENT_TYPE << "\r\n";
    }
    respStream << "Content-Length: " << CONTENT_LENGTH << "\r\n" << "Connection: " << CONNECTION << "\r\n\r\n";
    std::string responseStr = respStream.str();
    return responseStr;
}