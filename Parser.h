#ifndef PROJECT1_STARTER_CODE_PARSER_H
#define PROJECT1_STARTER_CODE_PARSER_H
#include "Token.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include <vector>
#include <set>

class Parser {
protected:
    std::vector<Token*> tokens;
    int index;
    std::vector<std::string> idS;
    std::vector<std::string> strings;

public:
    bool isRule = false;
    Parser(std::vector<Token*> tokenInput) {this->tokens = tokenInput; this->index = 0;};
    DatalogProgram dataLog;

    DatalogProgram getDataLog(){return this->dataLog;};
    //TODO make a datalog object in parseand then call datalogprgrm
    void Parse() {
        //DatalogProgram * datalogProgram = new DatalogProgram();
        this->DatalogPrgrm();
    }; // Place the try...catch here
    //Make void functions for all the productions
    void Match(Token* current, std::string correctTknType) {
        if (current->tokenTypeToString() != correctTknType) {
            throw (current);
        }
    };

    void DatalogPrgrm() {
        Match(this->tokens.at(this->index), "SCHEMES");
        this->index += 1;
        Match(this->tokens.at(this->index), "COLON");
        this->index += 1;
        this->Scheme();
        this->SchemeList();
        Match(this->tokens.at(this->index), "FACTS");
        this->index += 1;
        Match(this->tokens.at(this->index), "COLON");
        this->index += 1;
        this->FactList();
        Match(this->tokens.at(this->index), "RULES");
        this->index += 1;
        Match(this->tokens.at(this->index), "COLON");
        this->index += 1;
        isRule = true;
        this->RuleList();
        Match(this->tokens.at(this->index), "QUERIES");
        this->index += 1;
        Match(this->tokens.at(this->index), "COLON");
        this->index += 1;
        isRule = false;
        this->Query();
        this->QueryList();
        Match(this->tokens.at(this->index), "EOF");
    };
    void SchemeList() {
        //this is the followset of schemelist
        if (this->tokens.at(index)->tokenTypeToString() == "FACTS") {
            //this->index +=1;
        }
        else {
            this->Scheme();
            this->SchemeList();
        }
    };
    void FactList() {
        if (this->tokens.at(index)->tokenTypeToString() == "RULES") {
            //this->index += 1;
        }
        else {
            this->Fact();
            this->FactList();
        }
    };
    void RuleList() {
        if (this->tokens.at(index)->tokenTypeToString() == "QUERIES") {
            //this->index +=1;
        }
        else {
            this->pRule();
            this->RuleList();
        }
    };
    void QueryList() {
        if (this->tokens.at(index)->tokenTypeToString() == "EOF") {
            //this->index += 1;
        }
        else {
            this->Query();
            this->QueryList();
        }
    };
    void Scheme() {
        Match(this->tokens.at(this->index), "ID");
        dataLog.schemes.push_back(new Predicate(this->tokens.at(this->index)->getInfo()));
        this->index += 1;
        Match(this->tokens.at(this->index), "LEFT_PAREN");
        this->index += 1;
        Match(this->tokens.at(this->index), "ID");
        dataLog.schemes.at(dataLog.schemes.size()-1)->addParam(new Parameter(this->tokens.at(this->index)->getInfo()));
        this->index += 1;
        this->IdList();
        for(size_t i=0; i < this->idS.size(); i++) {
            dataLog.schemes.back()->addParam(new Parameter(this->idS.at(i)));
        }
        this->idS.clear();
        //have to empty it
//        for(size_t i=0; i<this->idS.size(); i++) {
//            this->idS.pop_back();
//        }
        Match(this->tokens.at(this->index), "RIGHT_PAREN");
        this->index += 1;
    };
    void Fact() {
        //TODO include the strings in the domain
        Match(this->tokens.at(this->index), "ID");
        dataLog.facts.push_back(new Predicate(this->tokens.at(this->index)->getInfo()));
        this->index += 1;
        Match(this->tokens.at(this->index), "LEFT_PAREN");
        this->index += 1;
        Match(this->tokens.at(this->index), "STRING");
        dataLog.facts.at(dataLog.facts.size()-1)->addParam(new Parameter(this->tokens.at(this->index)->getInfo()));
        this->index += 1;
        this->StringList();
        for(size_t i=0; i < this->strings.size(); i++) {
            dataLog.facts.back()->addParam(new Parameter(this->strings.at(i), true));
        }
        this->strings.clear();

        Match(this->tokens.at(this->index), "RIGHT_PAREN");
        this->index += 1;
        Match(this->tokens.at(this->index), "PERIOD");
        this->index += 1;
    };
    void pRule() {
        this->HeadPredicate();
        Match(this->tokens.at(this->index), "COLON_DASH");
        this->index += 1;
        this->pPredicate();
        this->PredicateList();
        Match(this->tokens.at(this->index), "PERIOD");
        this->index += 1;
    };
    void Query() {
        this->pPredicate();
        Match(this->tokens.at(this->index), "Q_MARK");
        this->index += 1;
    };
    void HeadPredicate() {
        Match(this->tokens.at(this->index), "ID");
        dataLog.rules.push_back(new Rule(new Predicate(this->tokens.at(this->index)->getInfo())));
        this->index += 1;
        Match(this->tokens.at(this->index), "LEFT_PAREN");
        this->index += 1;
        Match(this->tokens.at(this->index), "ID");
        dataLog.rules.at(dataLog.rules.size()-1)->addHeadParam(new Parameter(this->tokens.at(this->index)->getInfo()));
        this->index += 1;
        this->IdList();
        for(size_t i=0; i < this->idS.size(); i++) {
            dataLog.rules.back()->addHeadParam(new Parameter(this->idS.at(i)));
        }
        this->idS.clear();
        Match(this->tokens.at(this->index), "RIGHT_PAREN");
        this->index += 1;
    };
    void pPredicate() {
        if (isRule) {
            Match(this->tokens.at(this->index), "ID");
            dataLog.rules.back()->addBodyPredicate(new Predicate(this->tokens.at(this->index)->getInfo()));
            this->index += 1;
            Match(this->tokens.at(this->index), "LEFT_PAREN");
            this->index += 1;
            this->pParameter();
            this->ParameterList();
            for(size_t i=0; i < this->idS.size(); i++) {
                dataLog.rules.back()->addBodyParam(new Parameter(this->idS.at(i)));
            }
            this->idS.clear();
            Match(this->tokens.at(this->index), "RIGHT_PAREN");
            this->index += 1;
        }
        else {
            Match(this->tokens.at(this->index), "ID");
            dataLog.queries.push_back(new Predicate(this->tokens.at(this->index)->getInfo()));
            this->index += 1;
            Match(this->tokens.at(this->index), "LEFT_PAREN");
            this->index += 1;
            this->pParameter();
            this->ParameterList();
            for(size_t i=0; i < this->idS.size(); i++) {
                if(this->idS.at(i).substr(0,1) == "\'") {
                    dataLog.queries.back()->addParam(new Parameter(this->idS.at(i), true));
                }
                else {
                    dataLog.queries.back()->addParam(new Parameter(this->idS.at(i), false));
                }

            }
            this->idS.clear();
            Match(this->tokens.at(this->index), "RIGHT_PAREN");
            this->index += 1;
        }
    };
    void PredicateList() {
        if (this->tokens.at(index)->tokenTypeToString() == "PERIOD") {
            //this->index +=1;
        }
        else {
            Match(this->tokens.at(this->index), "COMMA");
            this->index += 1;
            this->pPredicate();
            this->PredicateList();
        }
    };
    void ParameterList() {
        if (this->tokens.at(index)->tokenTypeToString() == "RIGHT_PAREN") {
            //this->index+=1;
        }
        else{
            Match(this->tokens.at(this->index), "COMMA");
            this->index += 1;
            this->pParameter();
            this->ParameterList();
        }
    };
    void StringList() {
        if (this->tokens.at(index)->tokenTypeToString() == "RIGHT_PAREN") {
            //this->index += 1;
        }
        else {
            Match(this->tokens.at(this->index), "COMMA");
            this->index += 1;
            Match(this->tokens.at(this->index), "STRING");
            strings.push_back(this->tokens.at(this->index)->getInfo());
            this->index += 1;
            this->StringList();
        }
    };
    void IdList() {
        if (this->tokens.at(index)->tokenTypeToString() == "RIGHT_PAREN") {
            //this->index += 1;
//            return this->idS;
//            for(size_t i=0; i<this->idS.size(); i++) {
//                this->idS.pop_back();
//            }
        }
        else {
            Match(this->tokens.at(this->index), "COMMA");
            this->index += 1;
            Match(this->tokens.at(this->index), "ID");
            idS.push_back(this->tokens.at(this->index)->getInfo());
            this->index += 1; //Don't update cause you need to check if the next one is a right Paren
            this->IdList();
        }
    };
    void pParameter() {
        if(isRule) {
            if (this->tokens.at(this->index)->tokenTypeToString() != "STRING" && this->tokens.at(this->index)->tokenTypeToString() != "ID") {
                throw (tokens.at(this->index));
            }
            else {
                idS.push_back(this->tokens.at(this->index)->getInfo());
                this->index += 1;
            }
        }
        else {
            if (this->tokens.at(this->index)->tokenTypeToString() != "STRING" && this->tokens.at(this->index)->tokenTypeToString() != "ID") {
                throw (tokens.at(this->index));
            }
            else {
                idS.push_back(this->tokens.at(this->index)->getInfo());
                this->index += 1;
            }
        }

    };
    std::string toString() {
        std::string toReturn = "";
        toReturn += "Schemes(" + std::to_string(dataLog.schemes.size()) + "):\n";
        if (dataLog.schemes.size() > 0) {
            for (size_t i = 0; i < dataLog.schemes.size(); i++){
                toReturn += "  " + dataLog.schemes.at(i)->toString() + "\n";
            }
        }

        if (dataLog.facts.size() > 0) {
            toReturn += "Facts(" + std::to_string(dataLog.facts.size()) + "):\n";
            for (size_t i = 0; i < dataLog.facts.size(); i++){
                toReturn += "  " + dataLog.facts.at(i)->toString() + ".\n";
            }
        }
        else {
            toReturn += "Facts(" + std::to_string(dataLog.facts.size()) + "):\n";
        }

        // RULES
        if(dataLog.rules.size() > 0) {
            toReturn += "Rules(" + std::to_string(dataLog.rules.size()) + "):\n";
            for (size_t i = 0; i < dataLog.rules.size(); i++){
                toReturn += "  " + dataLog.rules.at(i)->ToString() + "\n";
            }
        }
        else {
            toReturn += "Rules(" + std::to_string(dataLog.rules.size()) + "):\n";
        }

        //TODO QUERIES
        toReturn += "Queries(" + std::to_string(dataLog.queries.size()) + "):\n";
        if(dataLog.queries.size() > 0) {
            for (size_t i = 0; i < dataLog.queries.size(); i++){
                toReturn += "  " + dataLog.queries.at(i)->toString() + "?\n";
            }
        }


        //Domains
        std::set<std::string> theDomain;
        std::set<std::string>::iterator itr;
        if (dataLog.facts.size() > 0) {

            for (size_t i = 0; i < dataLog.facts.size(); i++){
                 for(size_t j = 0; j < dataLog.facts.at(i)->getParameterVector().size(); j++){
                     theDomain.insert(dataLog.facts.at(i)->getParameterVector().at(j)->toString());
                 }
            }


            toReturn += "Domain(" + std::to_string(theDomain.size()) + "):\n";
            for (itr=theDomain.begin(); itr != theDomain.end(); itr++) {
                toReturn += "  " + *itr + "\n";
            }
//            for (size_t i = 0; i < dataLog.facts.size(); i++){
//                toReturn += dataLog.facts.at(i)->getParameters();
//            }
        }
        else {
            toReturn += "Domain(" + std::to_string(theDomain.size()) + "):\n";
        }
        return toReturn;
    };
};


#endif //PROJECT1_STARTER_CODE_PARSER_H
