//
// Created by merkm on 07/05/2019.
//

#include <algorithm>
#include "SharedEditor.h"
#include "NetworkServer.h"

SharedEditor::SharedEditor(const NetworkServer& server) : _server(const_cast<NetworkServer &>(server)){
    this->_siteId = this->_server.connect(this);
}

SharedEditor::SharedEditor(SharedEditor &sharedEditor) :_server(sharedEditor._server) {
    this->_siteId = sharedEditor._siteId;
}

SharedEditor::SharedEditor(SharedEditor *&sharedEditor) : _server(sharedEditor->_server) {
    this->_siteId = sharedEditor->_siteId;

}

void SharedEditor::localInsert(int index, char value) {
    //&& index <= this->_symbols.size()
    if (index > 0 ){
        this->_symbols.emplace_back(this->_siteId,this->prog_numb,value,index);
        std::sort(this->_symbols.begin(),this->_symbols.end());
    }
}

/*bool SharedEditor::operator==(const SharedEditor &other) {
    return other._siteId == this->_siteId;
}*/

