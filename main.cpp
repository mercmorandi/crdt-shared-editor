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
    ed1.localInsert(1,'l');
    ed1.localInsert(2,'d');
    ed1.localInsert(2,'c');
    ed1.localInsert(3,'b');
    ed1.localInsert(0,'a');
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout<<"done in "<<elapsed.count()<<std::endl;
    server.disconnect(&ed1);

    return 0;
}