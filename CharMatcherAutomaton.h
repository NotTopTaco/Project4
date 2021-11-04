
#ifndef PROJECT1_STARTER_CODE_CHARMATCHERAUTOMATON_H
#define PROJECT1_STARTER_CODE_CHARMATCHERAUTOMATON_H
#include "Automaton.h"

class CharMatcherAutomaton: public Automaton {
private:
    char toMatch;

public:
    CharMatcherAutomaton(char toMatch, TokenType type);
    int Start(const std::string& input);
    void S0(const std::string& input);
    Token* CreateToken(std::string input, int lineNumber) { return new Token(type, input, lineNumber); }

};

#endif //PROJECT1_STARTER_CODE_CHARMATCHERAUTOMATON_H
