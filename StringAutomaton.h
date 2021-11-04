#ifndef PROJECT1_STARTER_CODE_STRINGAUTOMATON_H
#define PROJECT1_STARTER_CODE_STRINGAUTOMATON_H
#include "Automaton.h"

class StringAutomaton: public Automaton {
private:
    size_t idx;
public:
    StringAutomaton();
    int Start(const std::string& input);
    void S0(const std::string& input);
    void S1(const std::string& input);
    void S2(const std::string& input);
   // void S3(const std::string& input);
    void SF(const std::string& input);
    void SUndef();
    //void S5(const std::string& input);
    void Serr();
    int invalidRead = 0;
    bool Undef = false;
    Token* CreateToken(std::string input, int lineNumber) { return new Token(type, input, lineNumber); }
};





#endif //PROJECT1_STARTER_CODE_STRINGAUTOMATON_H
