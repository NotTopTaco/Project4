#include "StringAutomaton.h"

StringAutomaton::StringAutomaton() : Automaton(TokenType::STRING){
    this->idx = 0;
    this->inputRead = 0;
    this->aType = "CommentString";
}

void StringAutomaton::S0(const std::string &input) {

    if (input.size() >=2 && input.at(this->inputRead) == '\'') {
        this->inputRead += 1;
        S1(input);
    }
    else if (input.size() == 1 && input.at(0) == '\'') {
        this->inputRead += 1;
        SUndef();
    }
    else {
        Serr();
    }
}
void StringAutomaton::S1(const std::string &input) {
    //Checks if the next digit to look at is the end of the file.
    //was idx+1
    if(this->inputRead == input.size() - 1 && input.at(this->inputRead-1) != '\'') {
        //TODO UNDEFINED
        SUndef();
        Undef = true;
        this->invalidRead = inputRead+1;
        inputRead = 0;
    }
    else {
        this->inputRead += 1;
        //this->idx += 1;
        if (input.at(this->inputRead-1) == '\'') {
            S2(input);
        }
        else if (input.at(this->inputRead-1) == '\n'){
            this->newLines += 1;
            //TODO THIS IS WHERE I CHANGED IT
            if(this->inputRead == input.size()) {
                SUndef();
            }
            else {
                S1(input);
            }

        }
        else {
            S1(input);
        }
    }
}

void StringAutomaton::S2(const std::string &input) {
    //was idx+1
    if(this->inputRead == input.size() - 1 && input.at(this->inputRead-1) != '\'') {
        //TODO UNDEFINED
        SUndef();
        Undef = true;
        this->invalidRead = inputRead+1;
        inputRead = 0;
    }
    else {
        //check before you add it.
        if (input.at(this->inputRead) == '\'') {
            this->inputRead += 1;
            //this->idx += 1;
            S1(input);
        }
        else {
            SF(input);
        }
    }

}

void StringAutomaton::SF(const std::string &input) {

}

void StringAutomaton::SUndef() {
    this->aType = "undef";
    this->type = TokenType::UNDEFINED;
    Undef = true;
}

void StringAutomaton::Serr() {
    this->inputRead = 0;
}



/*
 * #include "StringAutomaton.h"

StringAutomaton::StringAutomaton() : Automaton(TokenType::STRING){
    this->idx = 0;
    this->inputRead = 0;
}

void StringAutomaton::S0(const std::string &input) {

    if (input.at(this->inputRead) == '\'') {
        this->inputRead += 1;
        S1(input);
    }
    else {
        Serr();
    }
}
void StringAutomaton::S1(const std::string &input) {
    //Checks if the next digit to look at is the end of the file.
    if(this->inputRead == input.size() - 1 && input.at(this->idx+1) != '\'') {
        //UNDEFINED
        this->invalidRead = inputRead+1;
        inputRead = 0;
    }
    else {
        this->inputRead += 1;
        //this->idx += 1;
        if (input.at(this->inputRead-1) == '\'') {
            S2(input);
        }
        else {
            S1(input);
        }
    }
}

void StringAutomaton::S2(const std::string &input) {
    if(this->inputRead == input.size() - 1 && input.at(this->idx+1) != '\'') {
        //UNDEFINED
        this->invalidRead = inputRead+1;
        inputRead = 0;
    }
    else {
        //check before you add it.
        if (input.at(this->inputRead) == '\'') {
            this->inputRead += 1;
            this->idx += 1;
            S1(input);
        }
        else {
            SF(input);
        }
    }

}

void StringAutomaton::SF(const std::string &input) {

}

void StringAutomaton::SUndef() {
    this->invalidRead = this->inputRead;
    this->inputRead = 0;
}

void StringAutomaton::Serr() {
    this->inputRead = 0;
}


 */
