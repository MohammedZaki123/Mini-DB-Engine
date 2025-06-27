# include "Transformation.hpp"

std::string toStr(const std::any& val) {
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

std::any fromStr(std::string typeName, std::string value){
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
bool isEqual(std::any a, std::any b){
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

bool isMoreThan(std::any a, std::any b) {
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
bool isLessThan(std::any a, std::any b) {
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

bool isTypeCompatible(std::any value, std::string colType)
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