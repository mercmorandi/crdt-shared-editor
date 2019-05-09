#include <iostream>
#include "NetworkServer.h"
#include "SharedEditor.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    NetworkServer server;
    SharedEditor ed1(server);
    SharedEditor ed2(server);
    ed1.localInsert(4,'o');
    ed1.localInsert(1,'c');
    ed1.localInsert(3,'a');
    ed1.localInsert(2,'i');

    server.disconnect(&ed1);
    std::cout<<"done"<<std::endl;



    return 0;
}