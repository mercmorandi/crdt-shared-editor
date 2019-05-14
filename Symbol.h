//
// Created by merkm on 09/05/2019.
//

#ifndef TEST_SYMBOL_H
#define TEST_SYMBOL_H
#include <vector>

class Symbol {

    struct Id{
        int client_id;
        int prog_numb;
    }id{};

    char symbol{};

    std::vector<int> pos;

public:
    Symbol(int client_id, int prog_numb, char symbol);
    Symbol();
    bool operator< (const Symbol &symbol);

    const Id &getId() const;

    char getSymbol() const;

    void setPos(const std::vector<int> &pos);

    const std::vector<int> &getPos() const;


};


#endif //TEST_SYMBOL_H
