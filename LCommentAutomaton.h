#ifndef PROJECT1_STARTER_CODE_LCOMMENTAUTOMATON_H
#define PROJECT1_STARTER_CODE_LCOMMENTAUTOMATON_H

#include "Automaton.h"

class LCommentAutomaton: public Automaton {
private:

public:
    LCommentAutomaton();
    int Start(const std::string& input);
    void S0(const std::string& input);
    void S1(const std::string& input);
    Token* CreateToken(std::string input, int lineNumber) { return new Token(type, input, lineNumber); }
};



#endif //PROJECT1_STARTER_CODE_LCOMMENTAUTOMATON_H
