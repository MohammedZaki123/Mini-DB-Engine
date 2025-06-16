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
    Record( std::unordered_map<std::string, std::any> types,
           const std::vector<std::string>& values);
            // turning every value to its correct datatype based on column type map which
            //  stores column as the key and datatype string as a value

    // Constructor 2: Takes a map of values
    Record(const std::unordered_map<std::string, std::any>& values, std::unordered_map<std::string, std::any> types);
    // storing every value in values instance variable of object

    bool operator==(Record record);
    bool operator<(Record record);
    bool operator>(Record record);

};