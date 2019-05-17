#include <utility>

//
// Created by merkm on 09/05/2019.
//

#include "Symbol.h"

Symbol::Symbol(int client_id, int prog_numb, char symbol) {
    this->symbol= symbol;
    //this->pos = std::move(pos);
    this->id.client_id = client_id;
    this->id._count = prog_numb;
}

bool Symbol::operator<(const Symbol &s) {
     return (this->pos < s.pos);
}

const Symbol::Id &Symbol::getId() const {
    return id;
}

char Symbol::getSymbol() const {
    return symbol;
}

const std::vector<int> &Symbol::getPos() const {
    return pos;
}

void Symbol::setPos(const std::vector<int> &posV) {
    Symbol::pos = posV;
}

Symbol::Symbol(const Symbol &symbol) {
    this->setPos(symbol.getPos());
    this->id = symbol.id;
    this->symbol = symbol.symbol;
}

bool Symbol::operator==(const Symbol &left) {
    return this->pos == left.pos;
}

Symbol::Symbol() = default;

