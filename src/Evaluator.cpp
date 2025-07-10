#include "Evaluator.hpp"

bool Evaluator::getSingularDecision(std::string opt, std::any objVal, std::any colVal)
{
    Decider dec;
    bool singleDecision = false;
    if(opt == ">"){
        singleDecision = dec.isMoreThan(colVal,objVal);
    }else if(opt == ">="){
        singleDecision = dec.isMoreThan(colVal, objVal) or dec.isEqual(colVal,objVal);
    }else if(opt == "<"){
        singleDecision = dec.isLessThan(colVal, objVal) ;
    }else if(opt == "<="){
        singleDecision = dec.isLessThan(colVal,objVal) or dec.isEqual(colVal,objVal);
    }else if(opt == "!="){
        singleDecision = !dec.isEqual(colVal,objVal);
    }else{
        singleDecision = dec.isEqual(colVal,objVal);
    }
    return singleDecision;
}

bool Evaluator::getMultiDecision(bool decision1, std::string logicalOperator, bool decision2)
{
    bool decision = false;
    if(logicalOperator == "AND"){
        decision = decision1 and decision2;
    }else if(logicalOperator == "OR"){
        decision = decision1 or decision2;
    }else{
        // XOR 
        decision = decision1 xor decision2; 
    }
    return decision;
}

Evaluator::Evaluator(std::vector<SQLTerm> terms, std::vector<std::string> opts)
{
    this->sqlTerms = terms;
    this->operators = opts;
}

bool Evaluator::formTheDecision(Record &record)
{
    bool decisionRes = false;
    for(int i = 0 ; i < sqlTerms.size(); i++){
        bool singularDecision = getSingularDecision(sqlTerms[i]._strOperator,sqlTerms[i]._objValue,record.getVals().at(sqlTerms[i]._strColumnName));
        if(i != 0){
            decisionRes = getMultiDecision(decisionRes,operators[i-1],singularDecision);
        }else{
            decisionRes = singularDecision;
        }
    }
    return decisionRes;
}


