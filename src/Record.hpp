# pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <any>  // For std::any
# include "Transformer.hpp"
# include "Decider.hpp"
class Record {
    std::string clusteringKey;
    std::unordered_map<std::string, std::any> vals;
    // static variable because column datatypes is shared for every created record
    std::unordered_map<std::string, std::string> datatypes;

    // Constructor 1: Takes vectors of columns and values
    public:
    Record(const  std::unordered_map<std::string, std::string>& types,
           std::vector<std::pair<std::string, std::string>>& values, std::string key);
            // turning every value to its correct datatype based on column type map which
            //  stores column as the key and datatype string as a value

    // Constructor 1.5: Same as constructor but does not take Clustring key name as an input

    Record(const  std::unordered_map<std::string, std::string>& types,
           std::vector<std::pair<std::string, std::string>>& values);

    // Constructor 2: Takes a map of values
    Record(const std::unordered_map<std::string, std::any>& values, std::unordered_map<std::string, std::string> types
    , std::string key);
    // storing every value in values instance variable of object


    bool operator==(Record& record);
    bool operator<(Record &record);
    bool operator>(Record &record);
    // Instance Getters and Setters
const std::string& getClusteringKey() const;
void setClusteringKey(const std::string& key);

const std::unordered_map<std::string, std::any>& getVals() const;
void setVals(const std::unordered_map<std::string, std::any>& v);

// Static Getters and Setters
 std::unordered_map<std::string, std::string>& getDatatypes();
void setDatatypes(const std::unordered_map<std::string, std::string>& types);

const std::vector<std::string> toString(std::vector<std::string> columns);

// Remaining member functions: comparison between non clustering key column values
// Comparing a value of a table column to a record for the same column
// more than function
// less than function
// equal function 

};