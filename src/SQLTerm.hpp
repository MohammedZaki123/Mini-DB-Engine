#pragma once
#include <string>
#include <any>

struct SQLTerm {
    std::string _strTableName;
    std::string _strColumnName;
    // acceptable operators: >, >=, <, <=, != or =
    std::string _strOperator;
    // acceptable value types: int, string, double or Date 
    std::any _objValue; 
};
