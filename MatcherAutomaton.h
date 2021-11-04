#ifndef PROJECT1_STARTER_CODE_MATCHERAUTOMATON_H
#define PROJECT1_STARTER_CODE_MATCHERAUTOMATON_H
#include "Automaton.h"

class MatcherAutomaton: public Automaton {
private:
    std::string toMatch;

public:
    MatcherAutomaton(std::string toMatch, TokenType type);
    int Start(const std::string& input);
    void S0(const std::string& input);
    Token* CreateToken(std::string input, int lineNumber) { return new Token(type, input, lineNumber); }

};


#endif //PROJECT1_STARTER_CODE_MATCHERAUTOMATON_H
