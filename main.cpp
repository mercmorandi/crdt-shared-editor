#include <iostream>
#include "NetworkServer.h"
#include "SharedEditor.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    NetworkServer server;
    SharedEditor ed1(server);
    SharedEditor ed2(server);
    std::cout<<"done"<<std::endl;



    return 0;
}