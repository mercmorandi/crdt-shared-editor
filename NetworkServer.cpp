//
// Created by merkm on 07/05/2019.
//

#include "NetworkServer.h"

NetworkServer::NetworkServer() {
    this->id_generator = 0;
}

int NetworkServer::connect(SharedEditor *sharedEditor) {
    std::shared_ptr<SharedEditor> ptr = std::shared_ptr<SharedEditor>(sharedEditor);
    this->editors.push_back(ptr);
    this->id_generator++;
    return this->id_generator;
}

void NetworkServer::disconnect(SharedEditor *sharedEditor) {
    //todo erase from vector editor disconnected

}

