//
// Created by merkm on 07/05/2019.
//

#include "SharedEditor.h"
#include "NetworkServer.h"

SharedEditor::SharedEditor(const NetworkServer& server) : _server(const_cast<NetworkServer &>(server)){
    this->_siteId = this->_server.connect(this);
}

