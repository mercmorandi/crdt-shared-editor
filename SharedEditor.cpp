//
// Created by merkm on 07/05/2019.
//

#include <algorithm>
#include <random>
#include <ctime>
#include "SharedEditor.h"
#include "NetworkServer.h"

SharedEditor::SharedEditor(const NetworkServer& server) : _server(const_cast<NetworkServer &>(server)){
    this->_siteId = this->_server.connect(this);
    this->initSymbols();
}

SharedEditor::SharedEditor(SharedEditor &sharedEditor) :_server(sharedEditor._server) {
    this->_siteId = sharedEditor._siteId;
}

SharedEditor::SharedEditor(SharedEditor *&sharedEditor) : _server(sharedEditor->_server) {
    this->_siteId = sharedEditor->_siteId;

}


std::vector<int> generatePositionRec(std::vector<int>::iterator previous, std::vector<int> prevPos, std::vector<int> nextPos, std::vector<int>::iterator next, char toInsert,std::vector<int> &newPos){

    std::random_device rd;
    std::mt19937 mt(rd());

     auto prev = previous - 1;
     auto nex = next - 1;
     auto it1 = prevPos.end() - 1;
     auto it2 = nextPos.end() - 1;
   // if(*prev == *it1  && *nex == *it2 ){ //new level added
     if(*previous == *prevPos.end() && *next == *nextPos.end()){
        newPos.push_back(5);
        return newPos;
    }
    if(*previous == *prevPos.end()){ // new pos [1, next -1]
        std::uniform_int_distribution<int> dist(1,*next-1);
        int lastCurrent = dist(rd);
        newPos.push_back(lastCurrent);
        return newPos;
    }
    if(*next == *nextPos.end()){ //new pos [previous+1, 9]
        std::uniform_int_distribution<int> dist(*previous++,9);
        int lastCurrent = dist(rd);
        newPos.push_back(lastCurrent);
        return newPos;
    }

    if(*next - *previous > 1){ // new
        std::uniform_int_distribution<int> dist(*previous+1,*next-1);
        int lastCurrent = dist(mt);
        newPos.push_back(lastCurrent);
        return newPos;
    }
    else{
        newPos.push_back(*previous);
        generatePositionRec(previous + 1,prevPos,nextPos,next + 1,toInsert,newPos);
        return newPos;

    }

}


/*std::vector<int> generatePosition(const Symbol& before, const Symbol& after, char toInsert){
    const auto& prevPos = before.getPos();
    const auto& nextPos = after.getPos();



    if(prevPos.size() == nextPos.size()){
        int lastPrev = prevPos.back();
        int lastNext = nextPos.back();
        int diff = lastNext - lastPrev;
        if( diff > 1){
            int inferiorBound = lastNext - (diff -1);
            std::random_device rd;
            std::uniform_int_distribution<int> dist(inferiorBound,lastNext-1);
            int lastCurrent = dist(rd);//int newPos = std::rand() % (diff-1) + inferiorBound;
            std::vector<int> newPos = before.getPos();
            newPos.push_back(lastCurrent);
            newPos.insert(newPos.end(),lastCurrent);
            return newPos;


        }
    }

}*/

std::vector<int> generateBetween(std::vector<int> previous, std::vector<int> next){
    std::vector<int> newPos;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::srand(std::time(nullptr));

    if(previous.size() != next.size()){
        if(previous.size() < next.size()){
            newPos.assign(next.begin(),next.end()-1);
            if(next.back() > 1){
                int lastCurrent = (std::rand()%*next.end()-1)+1;
               // std::uniform_int_distribution<int> dist(1,*next.end()-1);
                //int lastCurrent = dist(rd);
                newPos.push_back(next.back());
                return newPos;
            }
            else
            {   //add new level
                newPos.push_back(0);
                newPos.push_back(5);
                return newPos;
            }
        }
        else
        {//previous.size > next.size
            newPos.assign(previous.begin(),previous.end()-1);
            if(previous.back() < 9){
                //int lastCurrent = (std::rand()%8)+*previous.end();
                //std::uniform_int_distribution<int> dist(*previous.end()+1,9);
                //int lastCurrent = dist(rd);
                newPos.push_back(previous.back()+1);
                return newPos;
            }
            else
            {   //new level added
                newPos.push_back(previous.back());
                newPos.push_back(5);
                return newPos;
            }
        }
    }
    else
    {//previous.size() == next.size()
        if(*next.end() - *previous.end() > 1){
            newPos.assign(previous.begin(),previous.end()-1);
            //std::uniform_int_distribution<int> dist(*previous.end()+1,*next.end()-1);
            //int lastCurrent = dist(rd);
            //int lastCurrent = (std::rand()%*next.end()-1)+*previous.end()+1;
            newPos.push_back(*previous.end()+1);
            return newPos;
        }
        else
        {
            newPos.assign(previous.begin(),previous.end());
            newPos.push_back(5);
            return newPos;
        }
    }
}

//NB need to add index++ in order to manage index 0
void SharedEditor::localInsert(int index, char value) {
     int indexModified = index + 1;
     int size = this->_symbols.size();
     Symbol symbolToSend;
    if (indexModified  >= this->_symbols.size()){
        std::vector<int> pos;
        pos.push_back(indexModified);
        this->_symbols.emplace_back(this->_siteId,this->prog_numb,value);
        this->_symbols.back().setPos(pos);
        symbolToSend = this->_symbols.back();
        std::sort(this->_symbols.begin(),this->_symbols.end());

    }
    else
    {
        std::vector<int> newPos;
        newPos = generateBetween(this->_symbols[indexModified-1].getPos(),this->_symbols[indexModified].getPos());
        this->_symbols.emplace_back(this->_siteId,this->prog_numb,value);
        this->_symbols.back().setPos(newPos);
        symbolToSend = this->_symbols.back();
        std::sort(this->_symbols.begin(),this->_symbols.end());
    }
    this->prog_numb++;
    Message m(true, symbolToSend,this->_siteId);
    this->_server.send(m);
}

void SharedEditor::localErase(int index) {
    //TODO CHECK IF THIS EDITOR HAS ALREADY DELETE THE SAME SYMBOL
    Symbol symbolToSend = this->_symbols[index+1];
    this->_symbols.erase(this->_symbols.begin()+index+1);
    this->prog_numb++;
    Message m(false, symbolToSend, this->_siteId);
    this->_server.send(m);
}

void SharedEditor::initSymbols() {
    Symbol s;
    std::vector<int> v;
    v.push_back(0);
    s.setPos(v);
    this->_symbols.push_back(s);
}


void SharedEditor::process(const Message &message) {
    if(message.isInsert()){
        //todo check if current editor has inserted same char at the same global pos
        this->_symbols.push_back(message.getSymbol());
        std::sort(this->_symbols.begin(),this->_symbols.end());
    }
    else //delete
    {
        auto it = std::find(this->_symbols.begin(),this->_symbols.end(),message.getSymbol());
        if(it != this->_symbols.end()){
            this->_symbols.erase(it);
        }
    }
}

int SharedEditor::getSiteId() const {
    return _siteId;
}

std::string SharedEditor::to_string() {
    std::string seq;
  for(int i = 1; i < this->_symbols.size(); i++){
      seq.push_back(this->_symbols[i].getSymbol());
  }
    return seq;
}



/*bool SharedEditor::operator==(const SharedEditor &other) {
    return other._siteId == this->_siteId;
}*/

