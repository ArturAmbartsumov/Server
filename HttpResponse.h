#ifndef HttpResponse_h
#define HttpResponse_h

#include <string>
#include <sstream>

#include "HttpRequest.h"

class HttpResponse {

public:
    //Переменные
    std::string STATUS_CODE;
    std::string HTTP_VERSION;
    std::string CONTENT_TYPE;
    std::string CONNECTION;
    std::string DATE;
    unsigned int CONTENT_LENGTH;

    //Методы
    HttpResponse();
    std::string getStringResponse();

};

#endif // #define HttpResponse_h