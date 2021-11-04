#ifndef PROJECT1_STARTER_CODE_IDAUTOMATON_H
#define PROJECT1_STARTER_CODE_IDAUTOMATON_H
#include "Automaton.h"
class IDAutomaton: public Automaton {
private:

public:
    IDAutomaton();
    int Start(const std::string& input);
    void S0(const std::string& input);
    void S1(const std::string& input);
    Token* CreateToken(std::string input, int lineNumber) { return new Token(type, input, lineNumber); }
};


#endif //PROJECT1_STARTER_CODE_IDAUTOMATON_H
