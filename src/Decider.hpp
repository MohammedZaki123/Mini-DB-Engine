#pragma once
# include <any>
# include <string>

class Decider{
    public:
    bool isMoreThan(std::any a, std::any b);
    bool isLessThan(std::any a, std::any b);
    bool isEqual(std::any a, std::any b);
    bool isTypeCompatible(std::any value, std::string colType);
};