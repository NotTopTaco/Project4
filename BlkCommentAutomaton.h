//
// Created by Jacob Scott McKenzie on 9/14/21.
//

#ifndef PROJECT1_STARTER_CODE_BLKCOMMENTAUTOMATON_H
#define PROJECT1_STARTER_CODE_BLKCOMMENTAUTOMATON_H

#include "Automaton.h"

class BlkCommentAutomaton: public Automaton {
private:

public:
    BlkCommentAutomaton();
    int invalidRead = 0;
    bool Undef = false;
    int Start(const std::string& input);
    void S0(const std::string& input);
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
    void SF(const std::string& input);
    void SUndef();
    void Serr();
    Token* CreateToken(std::string input, int lineNumber) { return new Token(type, input, lineNumber); }
};




#endif //PROJECT1_STARTER_CODE_BLKCOMMENTAUTOMATON_H
