#include "CharMatcherAutomaton.h"

CharMatcherAutomaton::CharMatcherAutomaton(char toMatch, TokenType type) : Automaton(type) {
    this->toMatch = toMatch;
    this->type = type;
    this->aType = "CharMatch";
}

void CharMatcherAutomaton::S0(const std::string &input) {
    if (input.at(0) == toMatch){
        this->inputRead = 1;
    }
    else {
        this->inputRead = 0;
    }
}


