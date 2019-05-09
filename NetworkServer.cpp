//
// Created by merkm on 07/05/2019.
//

#include <algorithm>
#include <iostream>
#include "NetworkServer.h"

NetworkServer::NetworkServer() {
    this->id_generator = 0;
}

int NetworkServer::connect(SharedEditor *sharedEditor) {
    //auto ptr = std::shared_ptr<SharedEditor>(sharedEditor);
    this->editors.push_back(std::shared_ptr<SharedEditor>(sharedEditor));
    this->id_generator++;
    return this->id_generator;
}

void NetworkServer::disconnect(SharedEditor *sharedEditor) {
    //todo erase from vector editors disconnected
    auto it = std::find(this->editors.begin(),this->editors.end(),std::shared_ptr<SharedEditor>(sharedEditor));
    if(it != this->editors.end()){
        this->editors.erase(it);
        std::cout<<">>>> Editor Disconnected correctly"<<std::endl;
    }


}

NetworkServer::NetworkServer(NetworkServer &networkServer) {

}

void NetworkServer::send(const Message &m) {
    this->queue.push(m);
}

void NetworkServer::dispatchMessage() {

}

NetworkServer::~NetworkServer() = default;

