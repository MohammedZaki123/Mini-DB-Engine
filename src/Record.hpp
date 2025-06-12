#include <string>
#include <vector>
#include <unordered_map>
#include <any>  // For std::any

class Record {
public:
    std::string clusteringKey;
    std::unordered_map<std::string, std::any> values;
    // static variable because column datatypes is shared for every created record
   static std::unordered_map<std::string, std::string> datatypes;

    // Constructor 1: Takes vectors of columns and values
    Record(const std::vector<std::string>& columnsTypes, 
           const std::vector<std::string>& values) {}

    // Constructor 2: Takes a map of values
    Record(const std::unordered_map<std::string, std::any>& values, const std::vector<std::string>& columnsTypes) {}

    

};