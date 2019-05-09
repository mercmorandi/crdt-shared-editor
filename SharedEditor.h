//
// Created by merkm on 07/05/2019.
//

#ifndef TEST_SHAREDEDITOR_H
#define TEST_SHAREDEDITOR_H


#include <memory>
#include "Symbol.h"

class NetworkServer;

class SharedEditor {
    NetworkServer& _server;
    int _siteId;
    int prog_numb = 0;
    std::vector<Symbol> _symbols;
public:
    explicit SharedEditor(const NetworkServer& m);
    SharedEditor(SharedEditor& sharedEditor);
    SharedEditor(SharedEditor* & sharedEditor);
   // bool operator==(const SharedEditor &other);

   void localInsert(int index, char value);

};




#endif //TEST_SHAREDEDITOR_H
