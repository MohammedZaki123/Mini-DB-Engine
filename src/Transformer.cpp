#include "Transformer.hpp"
# include "Date.hpp"
std::string Transformer::toStr(const std::any &val)
{
    std::string res;
    if (val.type() == typeid(int))
        res = std::to_string(std::any_cast<int>(val));

    if (val.type() == typeid(double))
        res = std::to_string(std::any_cast<double>(val));

    if (val.type() == typeid(std::string))
        res = std::any_cast<std::string>(val);

    if (val.type() == typeid(Date)) {
       const Date& d = std::any_cast<Date>(val);
       res =  d.getDate();
    }

    return res;
}

std::any Transformer::fromStr(std::string typeName, std::string value)
{
     // make four checks for every type
    // encapsulate type inside std::any
    std::any result;  
    if(typeName == "Integer"){
        int val = std::stoi(value);
        result = val;
    }else if(typeName == "String"){
        result = value;
    }else if(typeName == "Double"){
        double val = std::stod(value);
        result = val;
    }else{
        Date date = Date(value);
        result = date;
    }
    return result;
}
