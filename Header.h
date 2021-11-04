//
// Created by Jacob Scott McKenzie on 10/23/21.
//

#ifndef PROJECT1_STARTER_CODE_HEADER_H
#define PROJECT1_STARTER_CODE_HEADER_H
#include <vector>
#include <string>
#include "Tuple.h"
class Header {
public:
    std::vector<std::string> attributes;
    Header(std::vector<std::string> attr) {this->attributes = attr;};
    Header(){};
};


#endif //PROJECT1_STARTER_CODE_HEADER_H
