#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "MatcherAutomaton.h"
#include "IDAutomaton.h"
#include "LCommentAutomaton.h"
#include "CharMatcherAutomaton.h"
#include "StringAutomaton.h"
#include "BlkCommentAutomaton.h"
#include <string>
#include <iostream>

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
}



void Lexer::CreateAutomata() {
    //automata.push_back(new ColonAutomaton());
    //automata.push_back(new ColonDashAutomaton());
    // TODO: Add the other needed automata here

    automata.push_back(new MatcherAutomaton("Schemes", TokenType::SCHEMES));
    automata.push_back(new MatcherAutomaton("Facts", TokenType::FACTS));
    automata.push_back(new MatcherAutomaton("Rules", TokenType::RULES));
    automata.push_back(new MatcherAutomaton("Queries", TokenType::QUERIES));
    automata.push_back(new ColonDashAutomaton());
    //automata.push_back(new MatcherAutomaton(":-", TokenType::COLON_DASH));
    automata.push_back(new IDAutomaton());
    automata.push_back(new CharMatcherAutomaton(',', TokenType::COMMA));
    automata.push_back(new CharMatcherAutomaton(':', TokenType::COLON));
    automata.push_back(new CharMatcherAutomaton('.', TokenType::PERIOD));
    automata.push_back(new CharMatcherAutomaton('?', TokenType::Q_MARK));
    automata.push_back(new CharMatcherAutomaton('(', TokenType::LEFT_PAREN));
    automata.push_back(new CharMatcherAutomaton(')', TokenType::RIGHT_PAREN));
    automata.push_back(new CharMatcherAutomaton('*', TokenType::MULTIPLY));
    automata.push_back(new CharMatcherAutomaton('+', TokenType::ADD));
    automata.push_back(new StringAutomaton());
    automata.push_back(new BlkCommentAutomaton());
    //automata.push_back(new CharMatcherAutomaton(EOF, TokenType::EOF_TYPE));

    automata.push_back(new LCommentAutomaton());

}

void Lexer::Run(std::string& input) {
    if(input.size() == 0) {
        Token * efffToken = new Token(TokenType::EOF_TYPE, "", 1);
        tokens.push_back(efffToken);
    }
    // TODO: convert this pseudo-code with the algorithm into actual C++ code
    int lineNumber = 1;
    int maxRead;
    int maxNewLines;
    bool whitespace = false;
    // TODO: make this handle EOF and whitespaces, for \n add too the current line#

    bool endOfFile = false;
    while (input.size() > 0) {
        maxRead = 0;
        Automaton* maxAutomaton = automata.at(0);
        if(input.at(0) == EOF) {
            Token * effToken = new Token(TokenType::EOF_TYPE, "", lineNumber);
            tokens.push_back(effToken);
        }
        else if(input.at(0) == '\n' || input.at(0) == ' ' || input.at(0) == '\t') {
            whitespace = true;
            if (input.at(0) == '\n') {
                lineNumber += 1;
            }
            if(input.size() >=2){
                input = input.substr(1, input.size());
            }
            else if(input.size() == 1) {
                //input = input.substr(0,1); //TODO LOOK AT THIS
                //input = "";
                input.erase();
                endOfFile = true;
                whitespace = false;
            }
            while (whitespace) {
                if(input.at(0) == EOF) {
                    Token * efToken = new Token(TokenType::EOF_TYPE, "", lineNumber);
                    tokens.push_back(efToken);
                    whitespace = false;
                }
               else if (input.at(0) == '\n' || input.at(0) == ' ' || input.at(0) == '\t') {
                    whitespace = true;
                    if (input.at(0) == '\n') {
                        lineNumber += 1;
                    }
                    if(input.size() >=2){
                        input = input.substr(1, input.size());
                    }
                    else if(input.size() == 1) {
                        //input = input.substr(0,1);
                        input.erase();
                        endOfFile = true;
                        whitespace = false;
                    }

                } else {
                    whitespace = false;
                }
            }
        }
        //bool undefined = false;
        if (!endOfFile) {
            for (Automaton * aut : automata) {
                int inputRead = aut->Start(input);
                if(inputRead == 0 && aut->aType == "CommentString"){
                    //if(aut->Undef)
                }
                if (inputRead == maxRead){
                    //if a tie, make it go to the keyword, not ID.
                    if (aut->aType == "keyword") {
                        maxRead = inputRead;
                        maxAutomaton = aut;
                        maxNewLines = aut->NewLinesRead();
                    }
                }
                else if (inputRead > maxRead) {
                    maxRead = inputRead;
                    maxAutomaton = aut;
                    maxNewLines = aut->NewLinesRead();
                }
                // else if (inputRead == maxRead && aut)
            }

            //if(maxRead == 0 && (||))
            //only if the one that read the most read more than 0, create the token, So it must be a weird single character thing
            if (maxRead > 0) {

                if(maxAutomaton->aType == "undef") {
                    Token *unToken = maxAutomaton->CreateToken(input.substr(0,maxRead), lineNumber);
                    tokens.push_back(unToken);
                    lineNumber += maxNewLines;
                    //std::cout << unToken->toString() << std::endl;
                }
                else {
                    //I added a star
                    Token * newToken = maxAutomaton->CreateToken(input.substr(0,maxRead), lineNumber);
                    //lineNumber += maxAutomaton->NewLinesRead();
                    lineNumber += maxNewLines;
                    tokens.push_back(newToken);
                    //TODO:THIS IS A TEST
                    //std::cout << newToken->toString() << std::endl;
                }

            }
            else {
                    maxRead = 1;
                // TODO: Fix below
                //Token * newToken = new Token(TokenType::UNDEFINED, input.substr(0,maxRead), lineNumber);
                Token * nNewToken = new Token(TokenType::UNDEFINED, input.substr(0,maxRead), lineNumber);
                tokens.push_back(nNewToken);
                //std::cout << nNewToken->toString() << std::endl;
            }
            //input = input.substr(maxRead, input.size());
            if(maxAutomaton->aType != "undef") {
                input = input.substr(maxRead);
            }
            else {
                input.erase(0,maxRead);
                //std::cout << "Input Size: "+ std::to_string(input.size()) << std::endl;
            }

//            if(input.size() == 1) {
//                std::cout << "This is the state: " << std::endl;
//            }
//            if(input.empty()) {
//                std::cout << "It empty" << std::endl;
//            }

        }

        if (input.size() == 0) {
            Token * efnewToken = new Token(TokenType::EOF_TYPE, "", lineNumber);
            tokens.push_back(efnewToken);
            //std::cout << efnewToken->toString() << std::endl;

        }
    }
    //tokens.push_back(endofFIle);
    //return the end of the file token.
    /*
    set lineNumber to 1
     // While there are more characters to tokenize
    loop while input.size() > 0 {
        set maxRead to 0
        set maxAutomaton to the first automaton in automata

        // TODO: you need to handle whitespace inbetween tokens

        // Here is the "Parallel" part of the algorithm
        //   Each automaton runs with the same input
        foreach automaton in automata {
            inputRead = automaton.Start(input)
            if (inputRead > maxRead) {
                set maxRead to inputRead
                set maxAutomaton to automaton
            }
        }
        // Here is the "Max" part of the algorithm
        if maxRead > 0 {
            set newToken to maxAutomaton.CreateToken(...)
                increment lineNumber by maxAutomaton.NewLinesRead()
                add newToken to collection of all tokens
        }
        // No automaton accepted input
        // Create single character undefined token
        else {
            set maxRead to 1
                set newToken to a  new undefined Token
                (with first character of input)
                add newToken to collection of all tokens
        }
        // Update `input` by removing characters read to create Token
        remove maxRead characters from input
    }
    add end of file token to all tokens
    */
}

std::string Lexer::toString() {
    std::string outP = "";
    for(Token * t : tokens) {
        outP += t->toString() + "\n";
    }
    outP += "Total Tokens = " + std::to_string(tokens.size());
    return outP;
}
