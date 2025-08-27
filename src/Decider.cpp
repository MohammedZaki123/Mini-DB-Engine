#include "Decider.hpp"
#include<typeindex>
# include "Date.hpp"
# include <unordered_map>

bool Decider::isMoreThan(std::any a, std::any b)
{
    const std::type_index typeA = a.type();
    const std::type_index typeB = b.type();
    if (typeA == typeid(int)) {
        return std::any_cast<int>(a) > std::any_cast<int>(b);
    }
    if (typeA == typeid(double)) {
        return std::any_cast<double>(a) > std::any_cast<double>(b);
    }
    if (typeA == typeid(std::string)) {
        return std::any_cast<std::string>(a) > std::any_cast<std::string>(b);
    }
    if (typeA == typeid(Date)) {
        return std::any_cast<Date>(a) > std::any_cast<Date>(b);
    }
    return false;
}

bool Decider::isLessThan(std::any a, std::any b)
{
    const std::type_index typeA = a.type();
    const std::type_index typeB = b.type();
    if (typeA == typeid(int)) {
        return std::any_cast<int>(a) < std::any_cast<int>(b);
    }
    if (typeA == typeid(double)) {
        return std::any_cast<double>(a) < std::any_cast<double>(b);
    }
    if (typeA == typeid(std::string)) {
        return std::any_cast<std::string>(a) < std::any_cast<std::string>(b);
    }
    if (typeA == typeid(Date)) {
        return std::any_cast<Date>(a) < std::any_cast<Date>(b);
    }
    return false;
}

bool Decider::isEqual(std::any a, std::any b)
{
    const std::type_index typeA = a.type();
    const std::type_index typeB = b.type();
    if (typeA == typeid(int)) {
        return std::any_cast<int>(a) == std::any_cast<int>(b);
    }
    if (typeA == typeid(double)) {
        return std::any_cast<double>(a) == std::any_cast<double>(b);
    }
    if (typeA == typeid(std::string)) {
        return std::any_cast<std::string>(a) == std::any_cast<std::string>(b);
    }
    if (typeA == typeid(Date)) {
        return std::any_cast<Date>(a) == std::any_cast<Date>(b);
    }
    return false;
}

bool Decider::isTypeCompatible(std::any value, std::string colType)
{
      std::unordered_map <std::string, std::type_index> colValueType = {
   {"Integer", typeid(int) },
        { "Double",  typeid(double) },
        { "String",  typeid(std::string) },
        { "Date",    typeid(Date) }
};
    std::type_index valType = std::type_index(value.type());
    if(valType == colValueType.at(colType)){
        return true;
    }
    return false;
}
