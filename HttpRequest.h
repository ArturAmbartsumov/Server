#ifndef HttpRequest_h
#define HttpRequest_h

#include <string>
#include <cmath>

class HttpRequest {

public:
    //Переменные
    std::string METHOD;
    std::string URL;
    std::string HTTP_VERSION;

    //Методы
    HttpRequest();
    void parsData(std::string data);

private:
    int hexToDec(std::string &hex);
    bool check(int a, int l, int r);
    void urlParser();
};

#endif // #define HttpRequest_h