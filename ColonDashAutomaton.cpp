#include "ColonDashAutomaton.h"

void ColonDashAutomaton::S0(const std::string& input) {
    if (input[0] == ':') {
        inputRead += 1;
        //index += 1;
        S1(input);
    }
}

void ColonDashAutomaton::S1(const std::string& input) {
    if (input.size() >= 2) {
        if (input[1] == '-') {
            inputRead += 1;
        }
        else {
            inputRead = 0;
        }
    }
    else {
        inputRead = 0;
    }
}