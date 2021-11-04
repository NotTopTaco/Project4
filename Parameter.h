
#ifndef PROJECT1_STARTER_CODE_PARAMETER_H
#define PROJECT1_STARTER_CODE_PARAMETER_H
#include <string>

class Parameter {
private:
std::string p;
//TODO make this tell if the param is a string or an ID
//TODO in the toSTring of parser, go through the facts vector and for every parameter make it true
bool isString = false;
public:

    Parameter(std::string info) {this->p = info; this->isString = false;};
    Parameter(std::string info, bool isStr) {this->p = info; this->isString = isStr;};
    std::string toString() {return this->p;};
    bool IsString() {return this->isString;};

};







#endif //PROJECT1_STARTER_CODE_PARAMETER_H
