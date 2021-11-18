//
// Created by Jacob Scott McKenzie on 10/23/21.
//

#ifndef PROJECT1_STARTER_CODE_RELATION_H
#define PROJECT1_STARTER_CODE_RELATION_H
#include <vector>
#include <string>
#include <set>
#include "Header.h"
#include <map>

#include "Tuple.h"
class Relation {
private:
    std::string name;
    Header*  header;
    //has to be a set, DO NOT USE A POINTER, b/c set would just look at duplicate pointers not pointer reference values
    std::set<Tuple> rows;
public:
    bool renamed = true;
    std::string getName(){return this->name;};
    Header getHeader(){return *this->header;};
    std::set<Tuple> getRows(){return this->rows;};
    size_t rowSize(){return this->rows.size();};
    Relation(std::string nombre, std::vector<std::string> heder) {
        this->name = nombre;
        this->header = new Header(heder);
    };
    Relation(std::string nombre, std::vector<std::string> heder, std::set<Tuple> tups) {
        this->name = nombre;
        this->header = new Header(heder);
        for(Tuple T : tups) {
            this->rows.insert(T);
        }
    };
    Relation(std::string nombre, std::vector<std::string> heder, std::set<Tuple> tups, bool rename) {
        this->name = nombre;
        this->header = new Header(heder);
        for(Tuple T : tups) {
            this->rows.insert(T);
        }
        this->renamed = rename;
    };
    Relation(std::string nombre, Header* heder, std::set<Tuple> tups) {
        this->name = nombre;
        this->header = heder;
        this->rows = tups;
    };
    Relation(std::string nombre) {this->name = nombre;};
    Relation(std::vector<std::string> heder, std::set<Tuple> tups) {
        this->name = "";
        this->header = new Header(heder);
        this->rows = tups;
    };
    void addHeader(Header* h){this->header = h;};
    const void addTuple(Tuple& t) {this->rows.insert(t);};
    std::string toString() {
        std::string temp = "";
        for(size_t i = 0; i< this->header->attributes.size(); i++) {
            if(i == this->header->attributes.size() - 1) {
                temp += this->header->attributes.at(i) + "\n";
            }
            else {
                temp += this->header->attributes.at(i) + ", ";
            }
        }
        for(Tuple T : rows) {
            temp += T.toString();
        }
        return temp;
    };

    //Methods

    void removeRow(Tuple T) {
        this->rows.erase(T);
    };

    //the index is the column, return any tuple that has that value in that column.
    Relation Select(size_t idx, std::string value) {
        //Don't delete
        /*Relation R(this->name, this->header,this->rows);
        for(Tuple T : rows) {
            if(T.getVals().at(idx) != value) {
                R.removeRow(T);
            }
        }
        return R;*/
        std::set<Tuple> toKeep;
        for(Tuple T : rows) {
            if(T.getAVal(idx) == value) {
                toKeep.insert(T);
            }
        }
        return *(new Relation(this->name, this->header->attributes, toKeep));

    };
    Relation Select(size_t idx1, size_t idx2) {
        /*Relation R(this->name, this->header,this->rows);
        for(Tuple T : rows) {
            if(T.getVals().at(idx1) != T.getVals().at(idx2)) {
                R.removeRow(T);
            }
        }
        return R;*/
        std::set<Tuple> toKeep;
        for(Tuple T : this->rows) {
            if(T.getAVal(idx1) == T.getAVal(idx2)) {
                toKeep.insert(T);
            }
        }
        return *(new Relation(this->name, this->header->attributes, toKeep));

    };
    Relation Project(std::vector<int> indxs) {
        std::set<Tuple> upTups;
        std::vector<std::string> valToKeep;

        for(Tuple T : this->rows) {
            std::vector<std::string> valToAdd;
            for(int idx : indxs) {
                valToAdd.push_back(T.getAVal(idx));
            }
            if(valToAdd.size() != 0) {
                Tuple curT(valToAdd);
                upTups.insert(curT);
            }
        }
        //TODO do I need to update the header?
        return *(new Relation(this->name, this->header->attributes, upTups));
    };
    Relation Project(std::vector<size_t> indxs) {
        std::set<Tuple> upTups;
        std::vector<std::string> valToKeep;

        for(Tuple T : this->rows) {
            std::vector<std::string> valToAdd;
            for(size_t idx : indxs) {
                valToAdd.push_back(T.getAVal(idx));
            }
            if(valToAdd.size() != 0) {
                Tuple curT(valToAdd);
                upTups.insert(curT);
            }
        }
        //TODO do I need to update the header?
        return *(new Relation(this->name, this->header->attributes, upTups));
    };
    Relation Rename(std::vector<std::string> upHeadVals){
        return *(new Relation(this->name, new Header(upHeadVals), this->rows));
    };
    Relation Unionize(Relation rAdd) {
        std::set<Tuple> tupless = this->rows;
        for(Tuple tup : rAdd.getRows()) {
            //if() {}
            tupless.insert(tup);
        }
        return *(new Relation(this->name, this->header, tupless));
    }
    Relation* NatJoin2(Relation rJoin) {
        //std::vector<size_t> t1 = CommonIndexx(this->header->attributes,rJoin.getHeader().attributes);
        //std::vector<size_t> t2 = CommonIndexx(rJoin.getHeader().attributes, this->header->attributes);
        std::map<size_t,size_t> t1 = CommonIdx(this->header->attributes,rJoin.getHeader().attributes);
        //TODO use the map to see if they are the same
        std::set<Tuple> newRows;

        for(Tuple tup1 : this->rows) {
            for(Tuple tup2: rJoin.getRows()) {
                bool jable = true;
                if (t1.size() != 0) {
                    for(std::pair<size_t , size_t> element : t1) {
                        if(tup1.getAVal(element.first) != tup2.getAVal(element.second)){
                            jable = false;
                        }
                    }


//                    for(size_t i=0; i<t1.size();i++) {
//                        if(tup1.getAVal(i) != tup2.getAVal(t1.at(i))){
//                            jable = false;
//                        }
//                    }
                }
                if(jable) {
                    std::vector<std::string> newTup;
                    if(t1.size() == 0) {
                        for(size_t i = 0; i < tup1.getSize(); i++) {
                            newTup.push_back(tup1.getAVal(i));
                        }
                        for(size_t i = 0; i < tup2.getSize(); i++) {
                            newTup.push_back(tup2.getAVal(i));
                        }
                    }
                    else {
                        for(size_t i = 0; i < tup1.getSize(); i++) {
                            newTup.push_back(tup1.getAVal(i));
                        }
                        for(size_t j = 0; j < tup2.getSize(); j++) {
                            bool isCommon = false;

                            /*for(size_t z : t1) {
                                if(j == z) {
                                    isCommon = true;
                                }
                            }*/
                            for (std::pair<size_t , size_t> element : t1) {
                                if(element.second == j){
                                    isCommon = true;
                                }
                            }
                            if(!isCommon) {
                                newTup.push_back(tup2.getAVal(j));
                            }
                        }
                    }

                    Tuple a(newTup);
                    newRows.insert(a);
                }
            }
            }
        return new Relation(CombineHeaders(*(this->header),rJoin.getHeader()),newRows);
    }
    Relation* NatJoin(Relation rJoin) {
        //TODO get the indecies in common, then go through all rows and see if you can join em, if you can, do it
        std::vector<size_t> t1 = CommonIndex(*(this->header),rJoin.getHeader());
        std::vector<size_t> t2 = CommonIndex(rJoin.getHeader(),*(this->header));
        //std::vector<size_t> t11 = CommonIndexx(this->header->attributes,rJoin.getHeader().attributes);
        //std::vector<size_t> t22 = CommonIndexx(rJoin.getHeader().attributes,this->header->attributes);
        std::set<Tuple> newRows;
        for(Tuple tup1 : this->rows) {
            for(Tuple tup2: rJoin.getRows()) {

                if (isJoinable(tup1,tup2,t1,t2)) {
                    std::vector<std::string> newTup;
                    if(t1.size() == 0 && t2.size() == 0) {
                        for(size_t i = 0; i < tup1.getSize(); i++) {
                            newTup.push_back(tup1.getAVal(i));
                        }
                        for(size_t i = 0; i < tup2.getSize(); i++) {
                            newTup.push_back(tup2.getAVal(i));
                        }
                    }
                    else {
                        for(size_t i = 0; i < tup1.getSize(); i++) {
                            newTup.push_back(tup1.getAVal(i));
                        }
                        for(size_t j = 0; j < tup2.getSize(); j++) {
                            bool isCommon = false;
                            for(size_t z : t2) {
                                if(j == z) {
                                    isCommon = true;
                                }
                            }
                            if(!isCommon) {
                                newTup.push_back(tup2.getAVal(j));
                            }
                        }
                    }

                    Tuple a(newTup);
                    newRows.insert(a);
                }
            }

        }

        //Relation theResult(CombineHeaders(*(this->header),rJoin.getHeader()),newRows);
        //return theResult;
        return new Relation(CombineHeaders(*(this->header),rJoin.getHeader()),newRows);
    }
    std::vector<size_t> CommonIndex(Header aH, Header bH) {
        //std::vector<size_t> indecies = CommonIndexx(aH.attributes,bH.attributes);
        std::vector<size_t> indecies;
        for(size_t i = 0; i<aH.attributes.size(); i++) {
            for(size_t j = 0; j<bH.attributes.size(); j++) {
                if(bH.attributes.at(j) == aH.attributes.at(i)) {
                    //TODO make it j
                    indecies.push_back(i);
                }
            }
        }
        return indecies;
    }
    bool isJoinable(Tuple a, Tuple b, std::vector<size_t> aIdx, std::vector<size_t> bIdx) {
        //bool resultado = false;
        /*if(aIdx2 == bIdx2) {
            for(size_t i = 0; i < aIdx2.size(); i++) {
                if(a.getAVal(aIdx2.at(i)) != b.getAVal(i)) {
                    return false;
                }
            }
            return true;
        }*/
        if(aIdx.empty() && bIdx.empty()) {
            return true;
        }
        else {
            if(aIdx.size() != bIdx.size()) {
                return false;
            }
            else {
                for(size_t i = 0; i < aIdx.size(); i++) {
                    if(a.getAVal(aIdx.at(i)) != b.getAVal(bIdx.at(i))) {
                        //if(a.getAVal(aIdx.at(i)) != b.getAVal(i)) {
                            return false;
                        }
                }

            }
        }
        return true;
    }
    std::vector<size_t> CommonIndexx(std::vector<std::string> aH, std::vector<std::string> bH) {
        std::vector<size_t> indecies;

        for (size_t i = 0; i < aH.size(); i++) {
            for (size_t j = 0; j < bH.size(); j++) {
                if (aH.at(i) == bH.at(j)) {
                    indecies.push_back(j);
                }

            }

        }
        return indecies;
    }
    std::map<size_t,size_t> CommonIdx(std::vector<std::string> aH, std::vector<std::string> bH) {
        std::map<size_t,size_t> indecies;
        for (size_t i = 0; i < aH.size(); i++) {
            for (size_t j = 0; j < bH.size(); j++) {
                if (aH.at(i) == bH.at(j)) {
                    indecies.insert({i,j});
                }

            }

        }
        return indecies;
    };

    std::vector<std::string> CombineHeaders(Header a, Header b) {
        std::vector<std::string> newAttrs;
        for(size_t i = 0; i< a.attributes.size(); i++) {
            newAttrs.push_back(a.attributes.at(i));
        }
        for(size_t i=0; i< b.attributes.size(); i++) {
            bool theSame = false;
            for(std::string s : newAttrs){
                if(b.attributes.at(i) == s) {
                    theSame = true;
                }
            }
            if(!theSame) {
                newAttrs.push_back(b.attributes.at(i));
            }
        }
        return newAttrs;
    }

};
#endif //PROJECT1_STARTER_CODE_RELATION_H
