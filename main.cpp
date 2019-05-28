#include <iostream>
#include "NetworkServer.h"
#include "SharedEditor.h"
#include <chrono>

int main() {
    std::cout << "Hello, World!" << std::endl;
    NetworkServer server;
    SharedEditor ed1(server);
    SharedEditor ed2(server);
    auto start = std::chrono::high_resolution_clock::now();
    ed1.localInsert(0, 'c');
    ed1.localInsert(1, 'a');
    ed1.localInsert(2,'t');
    server.dispatchMessage();
    std::cout<<"ed1: "<<ed1.to_string()<<std::endl;
    std::cout<<"ed2: "<<ed2.to_string()<<std::endl;
    ed1.localInsert(1,'h');
    ed2.localInsert(1,'o');
    //ed2.localErase(1);
    //ed1.localErase(1);
    server.dispatchMessage();
    std::cout<<"ed1: "<<ed1.to_string()<<std::endl;
    std::cout<<"ed2: "<<ed2.to_string()<<std::endl;

    server.disconnect(&ed1);


    return 0;
}