//
// Created by merkm on 07/05/2019.
//

#ifndef TEST_SHAREDEDITOR_H
#define TEST_SHAREDEDITOR_H


#include <memory>
#include "Symbol.h"
#include "Message.h"

class NetworkServer;

class SharedEditor {
    NetworkServer& _server;
    int _siteId;
    int prog_numb = 0;
    std::vector<Symbol> _symbols;
    int _counter = 0;
public:
    explicit SharedEditor(const NetworkServer& m);
    SharedEditor(SharedEditor& sharedEditor);
    SharedEditor(SharedEditor* & sharedEditor);
     //bool operator==(const SharedEditor &other);

   void localInsert(int index, char value);
   void localErase(int index);
   void process(const Message &message);
   std::string to_string();
    int getSiteId() const;


protected:
    void initSymbols();

};




#endif //TEST_SHAREDEDITOR_H
