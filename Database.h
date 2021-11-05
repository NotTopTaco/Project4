//
// Created by Jacob Scott McKenzie on 10/23/21.
//

#ifndef PROJECT1_STARTER_CODE_DATABASE_H
#define PROJECT1_STARTER_CODE_DATABASE_H
#include "Relation.h"
#include "Predicate.h"
#include "Parameter.h"
#include <map>
#include <string>
#include <vector>

class Database {
private:
    std::vector<Relation*> relations;

public:
    std::map<std::string,Relation*> theMap;
    Database() {};
    void addRelation(Predicate* scheme) {
        std::vector<std::string> a;
        for(Parameter* p : scheme->getParameterVector()) {
            a.push_back(p->toString());
        }
        Relation * r = new Relation(scheme->getID(),a);
        this->theMap[scheme->getID()] = r;
        this->relations.push_back(r);
//        this->theMap[scheme->getID()] = new Relation(scheme->getID(),a);
//        this->relations.push_back(new Relation(scheme->getID(),a));
    };
   void addTuple(std::vector<Predicate*> facts);
   std::string toString(){
       std::string temp = "";
       for(auto const &pair: theMap) {
           temp += pair.second->toString();
       }
//       for(Relation* R: relations) {
//           temp += R->toString();
//       }
       return temp;
   };
};
#endif //PROJECT1_STARTER_CODE_DATABASE_H
