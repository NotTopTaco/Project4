#include "MatcherAutomaton.h"

MatcherAutomaton::MatcherAutomaton(std::string toMatch, TokenType type) : Automaton(type) {
    this->toMatch = toMatch;
    this->type = type;
    this->aType = "keyword";
}

//int MatcherAutomaton::Start(const std::string &input) {
//Don't need it because the base class has it implemented.
//}

void MatcherAutomaton::S0(const std::string &input) {
    bool stillGood = true;
    std::string matcher = this->toMatch;
    if (this->toMatch.size() > input.size()) {
        stillGood = false;
        this->inputRead = 0;
    }
    else {
        for(size_t i=0; i<this->toMatch.size(); i++){
            //TODO: add an if stillGood is flase, to not do the rest to prevent out of bounds
            if (input.at(i) == EOF || input.at(i) == '\n' || input.at(i) == '\t' || input.at(i) == ' ') {
                stillGood = false;
                this->inputRead = 0;
//            if(i != 0){
//                i = i - 1;
//            }
            }
            if(stillGood) {
                if((input.at(i) == matcher.at(i)) && stillGood){
                    this->inputRead += 1;
                }
                else {
                    stillGood = false;
                    this->inputRead = 0;
                }
            }
        }

        if (stillGood && this->toMatch.size() < input.size()) {
            if(input.at(this->toMatch.size()) == EOF ||input.at(this->toMatch.size()) ==' ' || input.at(this->toMatch.size()) == '\t' || input.at(this->toMatch.size()) == '\n' || input.at(this->toMatch.size()) == ':') {
                stillGood = true;

            }
            else {
                this->inputRead = 0;
            }
        }
    }

   //TODO: make it check the next character
    //if(input )

}



