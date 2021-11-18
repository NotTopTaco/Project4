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
        this->output += this->setRules();
        this->output += this->setQueries();

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
    std::string setRules() {
        std::string toReturn = "Rule Evaluation\n";
        bool tupleAdded = true;
        int loopedTimes = 0;
        while(tupleAdded) {
            loopedTimes += 1;
            tupleAdded = false;
            for(Rule * R : this->dataLog.rules){
                toReturn += R->ToString() + "\n";
                size_t oldSize = this->dataBase.theMap[R->headPredicate->getID()]->rowSize();
                if(R->bodyPredicates.size() == 1) {
                    //no joins are necessary TODO just evaluate the predicate and update it in the database???
                    //TODO evaluate the querie and then reorder
                    //TODO TODO TODO************ call the evaluatepredicate on EACH querie, then project the parameters of the Rule
                    Relation* copyRel = new Relation(this->dataBase.theMap[R->bodyPredicates.at(0)->getID()]->getName(), this->dataBase.theMap[R->bodyPredicates.at(0)->getID()]->getHeader().attributes);
                    for(Tuple T : this->dataBase.theMap[R->bodyPredicates.at(0)->getID()]->getRows()) {
                        copyRel->addTuple(T);
                    }
                    copyRel = evaluatePredicate(R->bodyPredicates.at(0)->getParameters(), copyRel);
                    //TODO now you project with the actual headPredicate.
                   std::vector<size_t> commonindecies = CommonIndex(R->headPredicate->getParameters(), R->bodyPredicates.at(0)->getParameters());
                   *copyRel = copyRel->Project(commonindecies);
                    for(const Tuple& tup : copyRel->getRows()) {
                        //if() {}
                        size_t sizebeforeAdd = this->dataBase.theMap[R->headPredicate->getID()]->rowSize();
                        this->dataBase.theMap[R->headPredicate->getID()]->addTuple(const_cast<Tuple &>(tup));
                        if(this->dataBase.theMap[R->headPredicate->getID()]->rowSize() > sizebeforeAdd) {
                            toReturn += "  ";
                            for (size_t i = 0; i < tup.getSize(); i++) {

                                if (i == tup.getSize() - 1) {
                                    toReturn += this->dataBase.theMap[R->headPredicate->getID()]->getHeader().attributes.at(i) + "=" + tup.getAVal(i);
                                } else {
                                    toReturn += this->dataBase.theMap[R->headPredicate->getID()]->getHeader().attributes.at(i) + "=" + tup.getAVal(i) + ", ";
                                }
                            }
                            toReturn += "\n";
                        }
                    }

                }
                else {
                    std::vector<Relation*> toJoin;
                    size_t indexer = 0;
                    for(Predicate * p : R->bodyPredicates) {

                        Relation* copyRel = new Relation(this->dataBase.theMap[p->getID()]->getName(), this->dataBase.theMap[p->getID()]->getHeader().attributes);
                        for(Tuple T : this->dataBase.theMap[R->bodyPredicates.at(indexer)->getID()]->getRows()) {
                            copyRel->addTuple(T);
                        }
                        copyRel = evaluatePredicate(R->bodyPredicates.at(indexer)->getParameters(), copyRel);
                        toJoin.push_back(copyRel);
                        indexer += 1;
                    }
                    for(size_t i = 0; i<toJoin.size()-1; i++) {
                        toJoin.at(i+1) = toJoin.at(i)->NatJoin(*(toJoin.at(i+1)));
                    }
                    //std::vector<size_t> commonIndexs = toJoin.back()->CommonIndex(toJoin.back()->getHeader(),this->dataBase.theMap[R->headPredicate->getID()]->getHeader());
                    std::vector<size_t> commonIndexs = CommonIndex(R->headPredicate->getParameters(), toJoin.back()->getHeader().attributes);
                    *toJoin.back() = toJoin.back()->Project(commonIndexs);
                    //toJoin.back()->Project(commonIndexs);
                    //this->dataBase.theMap[R->headPredicate->getID()]->Unionize(*toJoin.back());
                    for(const Tuple& tup : toJoin.back()->getRows()) {
                        size_t sizebeforeAdd = this->dataBase.theMap[R->headPredicate->getID()]->rowSize();
                        this->dataBase.theMap[R->headPredicate->getID()]->addTuple(const_cast<Tuple &>(tup));
                        if(this->dataBase.theMap[R->headPredicate->getID()]->rowSize() > sizebeforeAdd) {
                            toReturn += "  ";
                            for (size_t i = 0; i < tup.getSize(); i++) {

                                if (i == tup.getSize() - 1) {
                                    toReturn += this->dataBase.theMap[R->headPredicate->getID()]->getHeader().attributes.at(i) + "=" + tup.getAVal(i);
                                } else {
                                    toReturn += this->dataBase.theMap[R->headPredicate->getID()]->getHeader().attributes.at(i) + "=" + tup.getAVal(i) + ", ";
                                }
                            }
                            toReturn += "\n";
                        }
                    }
                    if(this->dataBase.theMap[R->headPredicate->getID()]->rowSize() > oldSize) {
                        tupleAdded = true;
                    }
                }

            }

        }
        toReturn+= "\nSchemes populated after " + std::to_string(loopedTimes)+ " passes through the Rules.\n\n";
        return toReturn;
    };
//    std::vector<Relation> RightHandRelations() {
//        //create using evaluatePredicate function
//    }
    std::string setQueries() {
        std::string theOut = "Query Evaluation";
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

        //theOut += "\n\n\n\n";
        //this->dataBase.theMap["marriedTo"] = this->dataBase.theMap["marriedTo"]->NatJoin(*(this->dataBase.theMap["childOf"]));
        //theOut += this->dataBase.theMap["marriedTo"]->toString() + "\n";
        return theOut.substr(0,theOut.size()-1);
    };
    std::vector<size_t> CommonIndex(std::vector<std::string> aH, std::vector<std::string> bH) {
        std::vector<size_t> indecies;

        for (size_t i = 0; i <aH.size(); i++) {
            for (size_t j = 0; j <bH.size(); j++) {
                if(aH.at(i) == bH.at(j)) {
                    indecies.push_back(j);
                }

            }

        }


        /*for(size_t i = 0; i<aH.size(); i++) {
            for(size_t j = 0; j<bH.size(); j++) {
                if(bH.at(j) == aH.at(i)) {
                    indecies.push_back(i);
                }
            }
        }*/
        return indecies;
    }
    //Relation* evaluatePredicate(const Predicate& pred, Relation * relation){
    //TODO make another evaluate Predicate for rules, because the params and relation come from different relations, so the orders will be different.
    //TODO make it just take in a predicate, then make a copy from the database
    Relation* evaluatePredicate(std::vector<std::string> params, Relation * relation){
        //have a map of string to index to easily see if we've seen it before
        //also store as a vector of strings in the natural order and a vector of indexes, so you can just pas the strings to the rename for teh header and the indexes to your project
        std::vector<size_t> commonIdxs = CommonIndex(params, relation->getHeader().attributes);
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
                    //TODO fix the projection, it just assumes that we got teh rigtht order
                    projInts.push_back(idx);
                }

            }

            idx += 1;
        }
        if(projInts.size() > 0) {
            //*relation = relation->Project(projInts);
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
