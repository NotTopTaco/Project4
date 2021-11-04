#include "IDAutomaton.h"
#include <cctype>

IDAutomaton::IDAutomaton() : Automaton(TokenType::ID) {
    this->aType = "ID";
}

void IDAutomaton::S0(const std::string &input) {
    if(isalpha(input.at(0))) {
        this->inputRead = 1;
        S1(input);
    }
    else {
        this->inputRead = 0;
    }
}

void IDAutomaton::S1(const std::string &input) {
    bool stillGood = true;
    size_t idx = 1;
    while (stillGood && idx <input.size()) {
        if(input.at(idx) == ',' || input.at(idx) == ':' || input.at(idx) == '.' || input.at(idx) == '?' || input.at(idx) == '(' || input.at(idx) == ')' || input.at(idx) == '*' || input.at(idx) == '+') {
            stillGood = false;
        }
        else if(isalpha(input.at(idx)) || isdigit(input.at(idx))) {
            this->inputRead += 1;
            idx += 1;
        }
        else {
            stillGood = false;
            //this->inputRead = 0;
        }
    }
//    if(input.substr(0,inputRead) == "Schemes" || input.substr(0,inputRead) == "Facts" || input.substr(0,inputRead) == "Rules" || input.substr(0,inputRead) == "Queries") {
//        this->inputRead = 0;
//    }
}


