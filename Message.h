//
// Created by merkm on 07/05/2019.
//

#ifndef TEST_MESSAGE_H
#define TEST_MESSAGE_H


#include <string>
#include "Symbol.h"

class Message {
    bool insert;
    int siteId_sender;
    Symbol symbol;

public:
    Message(bool insert, const Symbol& symbol, int siteId_sender);

    bool isInsert() const;

    const Symbol &getSymbol() const;

    int getSiteIdSender() const;

};


#endif //TEST_MESSAGE_H
