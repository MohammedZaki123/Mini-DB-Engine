#pragma once
# include <string>
# include <any>
# include "Date.hpp"
class Transformer{
    public:
    std::string toStr(const std::any& val);
    std::any fromStr(std::string typeName, std::string value);
};