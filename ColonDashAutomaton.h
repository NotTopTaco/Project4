#ifndef COLONDASHAUTOMATON_H
#define COLONDASHAUTOMATON_H

#include "Automaton.h"

class ColonDashAutomaton : public Automaton
{
private:


public:
    ColonDashAutomaton() : Automaton(TokenType::COLON_DASH) {}  // Call the base constructor

    void S0(const std::string& input);
    void S1(const std::string& input);
    void SF();
    void Serr();
};

#endif // COLONDASHAUTOMATON_H

