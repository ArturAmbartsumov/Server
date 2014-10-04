#include "Server.h"

Server::Server(int port, int thread_number, int maxQueue, std::string rootDir):workersList(thread_number) {
    initSocket(port, maxQueue);
    initHandler(rootDir);
    nextWorker = 0;
}

void Server::initSocket(int port, int maxQueue) {
    //Создание сокета
    std::cout << "Создание сокета: ";
    mainSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mainSocket != -1)
        std::cout << "Ок" << std::endl;
    else
        std::cout << "Ошибка создания сокета!" << std::endl;

    //Адресс сокета
    sockaddr_in socketAddres;
    socketAddres.sin_family = AF_INET;
    socketAddres.sin_port = htons(port);
    socketAddres.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    //Бин
    std::cout << "Бинд сокета: ";
    int bs = bind(mainSocket, (sockaddr *) &socketAddres, sizeof(sockaddr));
    if (bs != -1)
        std::cout << "Ок" << std::endl;
    else
        std::cout << "Ошибка bind!" << std::endl;

    //Слушать сокет
    std::cout << "Создание сокета: ";
    int ls = listen(mainSocket, maxQueue);
    if (ls != -1)
        std::cout << "Ок" << std::endl << std::endl;
    else
        std::cout << "Ошибка listen!" << std::endl;
}

void Server::run_server() {
    startWorkers();

    while(true) {
        int client = accept(mainSocket, NULL, NULL);
        if (client == -1) {
            std::unique_lock<std::mutex> locker(cout_lock);
            std::cout << "Ошибка: accept" << std::endl;
            break;
        }
        Worker* worker = getNextWorker();
        worker->addClient(client);
    }
}

Worker* Server::getNextWorker() {
    Worker* temp = &workersList[nextWorker];
    nextWorker = (int) ((nextWorker + 1) % workersList.size());
    return temp;
}

void Server::startWorkers() {
    for (int i = 0; i < workersList.size(); i++) {
        std::thread workerThr(&Worker::run, &workersList[i], handler);
        workerThr.detach();
        std::cout << "Поток " << i << " запущен" << std::endl;
    }
}

void Server::initHandler(std::string root_dir) {
    handler.setRootDir(root_dir);
}
