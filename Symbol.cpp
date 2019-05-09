//
// Created by merkm on 09/05/2019.
//

#include "Symbol.h"

Symbol::Symbol(int client_id, int prog_numb, char symbol, int pos) {
    this->symbol= symbol;
    this->pos.push_back(pos);
    this->id.client_id = client_id;
    this->id.prog_numb = prog_numb;
}

bool Symbol::operator<(const Symbol &s) {
     return (this->pos < s.pos);
}
