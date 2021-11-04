//
// Created by Jacob Scott McKenzie on 10/23/21.
//

#ifndef PROJECT1_STARTER_CODE_TUPLE_H
#define PROJECT1_STARTER_CODE_TUPLE_H
#include <vector>
#include <string>
class Tuple {
private:
    std::vector<std::string> values;
public:

    //std::set library requires all the setted types to have a less than
    // operator to know how to sort
    bool operator< (const Tuple &rhs) const {
        return values < rhs.values;
    }
    size_t getSize() {return this->values.size();};
    std::string getAVal(int i){return this->values.at(i);};
    std::string getAVal(size_t index){return this->values.at(index);};
    void addVal(std::string toAdd){this->values.push_back(toAdd);};
    Tuple() {};
    Tuple(std::vector<std::string> vals) {this->values = vals;};
    std::string getValues(size_t index) {return this->values.at(index);};
    std::string toString() {
        std::string s = "";
        for (size_t i = 0; i<this->values.size(); i++) {
            if (i == this->values.size() - 1) {
                s += this->values.at(i) + "\n";
            }
            else {
                s += this->values.at(i) + ", ";
            }
        }
        return s;
    };
};
#endif //PROJECT1_STARTER_CODE_TUPLE_H
