#include "LCommentAutomaton.h"

LCommentAutomaton::LCommentAutomaton() : Automaton(TokenType::COMMENT){
    this->aType = "LComment";
}
//TODO MAKE IT GO TILL EITHER A NEW LINE OR UNTIL IT REACHES THE LAST CHAR INPUT.SIZE()-1
void LCommentAutomaton::S0(const std::string &input) {

    if(input.size() >=2) {
        if(input.at(0) == '#' && input.at(1) == '|') {
            this->inputRead = 0;
        }
        else if(input.at(0) == '#') {
            this->inputRead += 1;
            S1(input);
        }
        else {
            this->inputRead = 0;
        }
    }
    else if(input.at(0) == '#') {
        this->inputRead += 1;
        S1(input);
    }
    else if(input.size() == 1 && input.at(0) == '#') {
        this->inputRead +=1;
    }
    else {
        this->inputRead = 0;
    }



    //    if(input.at(this->inputRead) == '#') {
//        this->inputRead += 1;
//        S1(input);
//    }
//    else {
//        this->inputRead = 0;
//    }
}

void LCommentAutomaton::S1(const std::string &input) {
    bool stillGood = true;
    size_t idx = 1;
    while (stillGood && idx < input.size()) {
        //if (input.at(idx) == '\n' || input.at(idx) == '|') {
        if (input.at(idx) == '\n') {
            stillGood = false;
        }
        else {
            idx += 1;
            this->inputRead += 1;
        }
    }
}

