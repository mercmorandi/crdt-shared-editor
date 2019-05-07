//
// Created by merkm on 07/05/2019.
//

#ifndef TEST_SHAREDEDITOR_H
#define TEST_SHAREDEDITOR_H


#include <memory>

class NetworkServer;

class SharedEditor {
    NetworkServer& _server;
    int _siteId;
public:
    explicit SharedEditor(const NetworkServer& m);

};




#endif //TEST_SHAREDEDITOR_H
