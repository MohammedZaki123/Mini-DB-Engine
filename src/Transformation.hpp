# include <string>
# include <any>
# include <typeindex>
# include <unordered_map>
# include "Date.hpp"
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

// std::any fromstr(std::string typeName, std::string value){
    // make four checks for every type
    // encapsulate type inside std::any 
// }
bool moreThan(std::any a, std::any b) {
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
bool isTypeCompatible(std::any value, std::string colType)
{
    std::unordered_map <std::string, std::type_index> colValueType = {
   {"integer", typeid(int) },
        { "double",  typeid(double) },
        { "string",  typeid(std::string) },
        { "date",    typeid(Date) }
};
    std::type_index valType = std::type_index(value.type());
    if(valType == colValueType.at(colType)){
        return true;
    }
    return false;
}


