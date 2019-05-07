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
    std::vector<std::shared_ptr<SharedEditor>> editors;
    std::queue<Message> queue;
    int id_generator;

public:
    explicit NetworkServer();
    int connect(SharedEditor* sharedEditor);
    void disconnect(SharedEditor* sharedEditor);
};

#endif //TEST_NETWORKSERVER_H
