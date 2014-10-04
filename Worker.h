#ifndef Worker_h
#define Worker_h

#include <thread>
#include <mutex>
#include <queue>
#include <unistd.h>

#include "HttpHandler.h"

class Worker {

public:
    //Методы
    void run(HttpHandler handler);
    void addClient(int client);

private:
    //Мутексы
    std::recursive_mutex queue_lock;
    std::mutex  waiting_lock;
    bool notified;
    std::condition_variable waiting_client;

    //Переменные
    HttpHandler httpHandler;
    std::queue<int> clientsQueue;

    //Методы
    size_t getQueueSize();
    int nextClient();
};

#endif // #define Worker_h