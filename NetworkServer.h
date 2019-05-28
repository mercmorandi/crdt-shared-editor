//
// Created by merkm on 07/05/2019.
//

#ifndef TEST_NETWORKSERVER_H
#define TEST_NETWORKSERVER_H

#include <vector>
#include <queue>
#include "memory"
#include "SharedEditor.h"
#include "Message.h"


class NetworkServer{

    //std::vector<std::unique_ptr<SharedEditor>> editors;
    std::vector<SharedEditor*> editors;
    std::queue<Message> queue;
    int id_generator;

public:
     ~NetworkServer();
     NetworkServer(NetworkServer& networkServer);
     explicit NetworkServer();
     int connect(SharedEditor* sharedEditor);
     void disconnect(SharedEditor* sharedEditor);
     void send(const Message& message);
     void dispatchMessage();
};

#endif //TEST_NETWORKSERVER_H
