#ifndef PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
#define PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
#include "Token.h"
#include "Predicate.h"
#include "Rule.h"

class DatalogProgram {
private:

public:
//have 4 vectors for schemes, facts, rules, and queries.
    std::vector<Predicate*> schemes;
    //TODO make the facts strings into the domain
    std::vector<Predicate*> facts;
    //std::vector<Predicate*> rules;
    std::vector<Predicate*> queries;
    std::vector<Rule*> rules;
};



#endif //PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
