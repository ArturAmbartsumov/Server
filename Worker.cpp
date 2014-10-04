#include "Worker.h"

void Worker::run(HttpHandler handler) {
    this->httpHandler = handler;

    while(true) {
        {
            std::unique_lock<std::mutex> locker(waiting_lock);
            while(!notified) { // от ложных пробуждений
                waiting_client.wait(locker);
            }
            notified = false;
        }
        while (getQueueSize()) {
            httpHandler.exec(nextClient());
        }
    }
}


size_t Worker::getQueueSize() {
    std::lock_guard<std::recursive_mutex> locker(queue_lock);
    return clientsQueue.size();
}

void Worker::addClient(int client) {
    {
        std::lock_guard<std::recursive_mutex> locker(queue_lock);
        clientsQueue.push(client);
    }
    std::unique_lock<std::mutex> locker(waiting_lock);
    notified = true;
    waiting_client.notify_one();
}

int Worker::nextClient() {
    std::lock_guard<std::recursive_mutex> locker(queue_lock);
    int temp = clientsQueue.front();
    clientsQueue.pop();
    return temp;
}
