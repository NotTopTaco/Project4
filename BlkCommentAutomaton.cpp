#include "BlkCommentAutomaton.h"

BlkCommentAutomaton::BlkCommentAutomaton() : Automaton(TokenType::COMMENT){
    this->aType = "CommentString";
    this->inputRead = 0;

}

void BlkCommentAutomaton::S0(const std::string& input) {
    if (input.at(this->inputRead) == '#') {
        //this->inputRead = +1;
        this->inputRead += 1;
        S1(input);
    }
    else {
        Serr();
    }
}
void BlkCommentAutomaton::S1(const std::string& input) {
    if (this->inputRead < input.size() && input.at(this->inputRead) == '|') {
        this->inputRead += 1;
        S2(input);
    }
    else {
        Serr();
    }
}
void BlkCommentAutomaton::S2(const std::string& input) {
    if(this->inputRead < input.size()) {
        if (input.at(this->inputRead) == '|') {
            this->inputRead += 1;
            S3(input);
        }
        else if (input.at(this->inputRead) == '\n'){
            this->newLines += 1;
            this->inputRead += 1;
            S2(input);
        }
        else {
            this->inputRead += 1;
            S2(input);
        }
    }
    else {
        SUndef();
    }

}
void BlkCommentAutomaton::S3(const std::string& input) {
    if (this->inputRead < input.size()) {
        if (input.at(this->inputRead) == '#') {
            this->inputRead += 1;
            SF(input);
        }
        else if (input.at(this->inputRead) == '\n') {
            this->newLines += 1;
            this->inputRead += 1;
            S2(input);
        }
        else {
            this->inputRead +=1;
            S2(input);
        }
    }
    else {
        SUndef();
    }
}
void BlkCommentAutomaton::SF(const std::string& input) {
    //Successfully terminated.
}

void BlkCommentAutomaton::SUndef() {
//    this->invalidRead = this->inputRead;
//    this->inputRead = 0;
    this->aType = "undef";
    this->type = TokenType::UNDEFINED;
    Undef = true;
}

void BlkCommentAutomaton::Serr() {
    this->inputRead = 0;
}


