#ifndef PROJECT1_STARTER_CODE_RULE_H
#define PROJECT1_STARTER_CODE_RULE_H
#include <string>
#include <vector>
#include "Predicate.h"
class Rule{
private:
    Predicate* headPredicate;
    std::vector<Predicate*> bodyPredicates;
public:
    Rule(Predicate* head) {this->headPredicate = head;};

    void addHeadParam(Parameter* param) {this->headPredicate->AddAParameter(param);};
    void addBodyParam(Parameter* param) {this->bodyPredicates.back()->AddAParameter(param);};
    void addBodyPredicate(Predicate* pred) {
        this->bodyPredicates.push_back(pred);
    }

    std::string ToString() {
        std::string toReturn = this->headPredicate->toString() + " :- ";
        for(size_t i = 0; i < this->bodyPredicates.size()-1; i++) {
            toReturn += this->bodyPredicates.at(i)->toString() + ",";
        }
        toReturn += this->bodyPredicates.back()->toString() + ".";
        return toReturn;
    };

};

#endif //PROJECT1_STARTER_CODE_RULE_H
