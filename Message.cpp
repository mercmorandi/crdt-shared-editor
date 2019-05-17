//
// Created by merkm on 07/05/2019.
//

#include "Message.h"

Message::Message(bool insert, const Symbol& symbol, int siteId_sender) {
    this->insert = insert;
    this->symbol = symbol;
    this->siteId_sender = siteId_sender;
}

bool Message::isInsert() const {
    return insert;
}

const Symbol &Message::getSymbol() const {
    return symbol;
}

int Message::getSiteIdSender() const {
    return siteId_sender;
}
