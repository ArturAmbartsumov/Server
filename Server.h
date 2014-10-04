#ifndef Server_h
#define Server_h

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <vector>
#include <thread>

#include "Worker.h"
#include "HttpHandler.h"

class Server {

public:
    //Методы
    Server(int port, int thread_number, int maxQueue, std::string rootDir);
    void run_server();

private:
    //Мутексы
    std::mutex cout_lock;

    //Переменные
    std::vector<Worker> workersList;
    HttpHandler handler;
    int mainSocket;
    int nextWorker;

    //Методы
    void initSocket(int port, int maxQueue);
    void initHandler(std::string root_dir);
    void startWorkers();
    Worker* getNextWorker();
};

#endif // #define Server_h