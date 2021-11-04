#ifndef PROJECT1_STARTER_CODE_PREDICATE_H
#define PROJECT1_STARTER_CODE_PREDICATE_H
#include <vector>
#include <string>
#include "Parameter.h"

//It is an ID with a vector of predicates after it

class Predicate {
private:
std::string id;
std::vector<Parameter*> parameters;

public:

    Predicate(std::string theId) {this->id = theId;};

    std::string getID(){return this->id;};

    std::string getStrVal() {
        std::string a = "";
        for (Parameter * p : this->parameters) {
            if (p->IsString()) {
                a += "String ";
            }
            else {
                a += "ID ";
            }
        }
        return a;
    }

    void addParam(Parameter* param) {this->parameters.push_back(param);};
    std::string toString() {
        std::string toReturn = this->id + "(";
        for(size_t i = 0; i<this->parameters.size()-1; i++) {
            toReturn += this->parameters.at(i)->toString() + ",";
        }
        toReturn += this->parameters.back()->toString() + ")";
        return toReturn;
    };
    std::vector<std::string> getParameters() {
        std::vector<std::string>toReturn;
        for (size_t i = 0; i<this->parameters.size(); i++) {
            toReturn.push_back(this->parameters.at(i)->toString());
        }
        return toReturn;
    }
    unsigned long getNumberofParam() {
        return this->parameters.size();
    }

    std::vector<Parameter*> getParameterVector() {
        return this->parameters;
    };
    std::vector<Parameter*> getConstParameterVector() const {
        return this->parameters;
    };

    void AddAParameter(Parameter* toadd) {this->parameters.push_back(toadd);};


};



#endif //PROJECT1_STARTER_CODE_PREDICATE_H
