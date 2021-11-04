//
// Created by Jacob Scott McKenzie on 10/25/21.
//

#ifndef PROJECT1_STARTER_CODE_INTERPRETER_H
#define PROJECT1_STARTER_CODE_INTERPRETER_H
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Database.h"
#include <map>

class Interpreter {
private:
    Database dataBase;
    DatalogProgram dataLog;
    std::string output;

public:
    Interpreter(DatalogProgram DataLog) {
        this->dataLog = DataLog;
        this->setSchemes();
        this->setFacts();
        this->output = this->setQueries();

    };
    void setSchemes() {
        for(Predicate* p : this->dataLog.schemes) {
            this->dataBase.addRelation(p);
        }
    };
    void setFacts() {
        for(Predicate* p : this->dataLog.facts) {
            std::vector<std::string> a;
            for(Parameter* Param : p->getParameterVector()) {
                a.push_back(Param->toString());
            }
            Tuple t(a);
            this->dataBase.theMap[p->getID()]->addTuple(t);
        }
    };
    std::string setQueries() {
        std::string theOut = "";
        for (Predicate* p : this->dataLog.queries) {
           Relation* copyRel = new Relation(this->dataBase.theMap[p->getID()]->getName(), this->dataBase.theMap[p->getID()]->getHeader().attributes);
           for(Tuple T : this->dataBase.theMap[p->getID()]->getRows()) {
               copyRel->addTuple(T);
           }
           copyRel = evaluatePredicate(p->getParameters(), copyRel);
            theOut += p->toString() + "?";
            if(copyRel->getRows().size() >0) {
                theOut += " Yes(" + std::to_string(copyRel->getRows().size()) + ")\n";
                if(copyRel->renamed) {
                    for (Tuple T: copyRel->getRows()) {
                        theOut += "  ";
                        for (size_t i = 0; i < T.getSize(); i++) {

                            if (i == T.getSize() - 1) {
                                theOut += copyRel->getHeader().attributes.at(i) + "=" + T.getAVal(i);
                            } else {
                                theOut += copyRel->getHeader().attributes.at(i) + "=" + T.getAVal(i) + ", ";
                            }
                        }
                        theOut += "\n";
                    }
                }
            }
            else {
                theOut += " No\n";
            }

        }

        theOut += "\n\n\n\n";
        this->dataBase.theMap["marriedTo"] = this->dataBase.theMap["marriedTo"]->NatJoin(*(this->dataBase.theMap["childOf"]));
        theOut += this->dataBase.theMap["marriedTo"]->toString() + "\n";
        return theOut.substr(0,theOut.size()-1);
    };

    //Relation* evaluatePredicate(const Predicate& pred, Relation * relation){
    Relation* evaluatePredicate(std::vector<std::string> params, Relation * relation){
        //have a map of string to index to easily see if we've seen it before
        //also store as a vector of strings in the natural order and a vector of indexes, so you can just pas the strings to the rename for teh header and the indexes to your project
        std::vector<int> projInts;
        std::vector<std::string> renameHeadStr;
        std::map<std::string,int> checker;
        size_t idx = 0;
        for(std::string p : params) {
            if(p.substr(0,1) == "\'") {
                *relation = relation->Select(idx, p);
            }
            else {
                //check if we have seen before
                if (checker.count(p) > 0) {
                    *relation = relation->Select(checker[p], idx);
                   //DONT NEED TO UPDATE IF ALREADY SEEN checker[p->toString()] = idx;
                }
                else {
                    checker[p] = idx;
                    renameHeadStr.push_back(p);
                    projInts.push_back(idx);
                }

            }

            idx += 1;
        }
        if(projInts.size() > 0) {
            *relation = relation->Project(projInts);
            *relation = relation->Rename(renameHeadStr);
            return new Relation(relation->getName(), relation->getHeader().attributes, relation->getRows());
        }
        else {
            return new Relation(relation->getName(), relation->getHeader().attributes, relation->getRows(), false);
        }


    };

    std::string printDB(){
//       std::string a = "";
//        for(Predicate* p : dataLog.queries) {
//            a += p->getStrVal();
//            a += "\n";
//        }
        return this->output;
        //return this->dataBase.toString();
    };
};
#endif //PROJECT1_STARTER_CODE_INTERPRETER_H
