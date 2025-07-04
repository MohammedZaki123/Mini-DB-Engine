#pragma once
# include <string>
# include <any>
# include <typeindex>
# include <unordered_map>
# include "Date.hpp"
    std::string toStr(const std::any& val);
    std::any fromStr(std::string typeName, std::string value);
    bool isMoreThan(std::any a, std::any b);
    bool isLessThan(std::any a, std::any b);
    bool isEqual(std::any a, std::any b);
    bool isTypeCompatible(std::any value, std::string colType);
      


