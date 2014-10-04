#include <iostream>
#include "string"

#include "Server.h"

int main() {
    Server server(8001, 1, 1000, "/Users/artur/http-test-suite/");
    server.run_server();
}