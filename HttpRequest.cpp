#include "HttpRequest.h"

HttpRequest::HttpRequest() {
    METHOD = "";
    HTTP_VERSION = "";
    URL = "";
}

void HttpRequest::parsData(std::string data) {
    size_t i = 0;
    while(data[i] != ' ') {
        METHOD += data[i];
        i++;
    }
    i++;
    while(data[i] != ' ') {
        URL += data[i];
        i++;
    }
    i++;
    while(data[i] != '\n') {
        HTTP_VERSION += data[i];
        i++;
    }
    urlParser();
}

void HttpRequest::urlParser() {
    std::string temp = URL;
    URL = "";
    int i = 0;
    std::string hex = "";

    //Замена кодов %XX
    while(temp[i] != '\0') {
        if(temp[i] != '%') {
            URL += temp[i];
            continue;
        }
        hex += URL[++i];
        hex += URL[++i];
        URL += (char) hexToDec(hex);
        i++;
    }

    //Если в урле есть "..", то заменать урл
    if(URL.find("..") != std::string::npos){
        URL = "brokenURL";
        return;
    }
    size_t sign = URL.find("?");
    if(URL.find("?") != std::string::npos)
        URL = URL.substr(0, URL.find("?"));
}

int HttpRequest::hexToDec(std::string &hex) {
    int temp = 0;
    int resultCode = 0;
    const int base = 16;
    for(unsigned int i = 0; i < hex.length(); i++) {
        if(check(hex[i], '0' , '9'))
            temp = hex[i] - '0';
        if(check(hex[i], 'a', 'f'))
            temp = hex[i] - 'a' + 10; // a = 10, f = 15
        if(check(hex[i], 'A', 'F') )
            temp = hex[i] - 'A' + 10; //A = 10, F = 15
        resultCode += temp * pow(base, hex.length() - i - 1);
    }
    return resultCode;
}

bool HttpRequest::check(int a, int l, int r) {
    return a >= l ? a <= r : false;
}
