#pragma once
#include <string>
#include <any>

struct SQLTerm {
    std::string _strTableName;
    std::string _strColumnName;
    std::string _strOperator;
    std::any _objValue;
};
