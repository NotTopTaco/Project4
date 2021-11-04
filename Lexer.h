#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"

//THE MACHINE/ARENA WHERE ALL THE MAGIC HAPPENS
class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;

    void CreateAutomata();

    // TODO: add any other private methods here (if needed)

public:
    Lexer();
    ~Lexer();
    std::vector<Token*> ReturnTokens() {return this->tokens;};

    void Run(std::string& input);

    std::string toString();
    
    // TODO: add other public methods here

};

#endif // LEXER_H

