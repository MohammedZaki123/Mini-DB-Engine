# include "SQLTerm.hpp"
# include "Record.hpp"
# include <string>
# include <vector>
# include "Decider.hpp"
// # include <any>
class Evaluator{
    std::vector<SQLTerm> sqlTerms;
    std::vector<std::string> operators;
    bool getSingularDecision(std::string opt, std::any objVal, std::any colVal);
    bool getMultiDecision(bool decision1, std::string logicalOperator, bool decision2);
    public:
    Evaluator(std::vector<SQLTerm>, std::vector<std::string> operators);
    bool formTheDecision(Record & record);
};