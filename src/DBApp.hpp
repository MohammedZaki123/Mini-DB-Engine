#pragma once
#include <string>
#include <unordered_map>
#include <any>
#include <vector>
# include "SQLTerm.hpp"
# include "FileManager.hpp"
# include "FactoryObjectCreation.hpp"
# include "Exception.hpp"
# include <algorithm>
# include "Date.hpp"

// static const unsigned int maxRowPerPage = 3;


// Forward declaration
// enum Datatypes{
//     INTEGER, DOUBLE, STRING, DATE
// };
class DBApp {
    FileManager * diskinfomgr;
    FileManager * metadatamgr;
    std::vector<std::string> datatypes;
    std::vector<std::string> logicalOperators;
    std::vector<std::string> comparisonOperators;
public:
    // Creates a table with the given schema and constraints
    DBApp();
    // Calls Abstract Factory Method which allocated object for different fileManager types
    void init(); 
    void createTable(
        std::string& tableName,
       const  std::string& clusteringKeyColumn,
        std::unordered_map<std::string, std::string>& colNameType,
        std::unordered_map<std::string, std::any>& colNameMin,
        std::unordered_map<std::string, std::any>& colNameMax
    );

    // Creates a sparse index on a specific column
    void createIndex(
        const std::string& tableName,
        const std::string& colName
    );

    // Inserts a single row (must include clustering key)
    void insertIntoTable(
        const std::string& tableName,
        std::unordered_map<std::string, std::any>& colNameValue
    );

    // Updates a row by clustering key, new values given in colNameValue
    void updateTable(
        const std::string& tableName,
        const std::string strClusteringKeyValue,
        const std::unordered_map<std::string, std::any>& colNameValue
    );

    // Deletes row(s) where all given key-value conditions match
    void deleteFromTable(
        const std::string& tableName,
        const std::unordered_map<std::string, std::any>& colNameValue
    );

    // Selects rows that satisfy SQLTerm conditions combined with operators
    void selectFromTable(
        const std::vector<SQLTerm>& sqlTerms,
        const std::vector<std::string>& logicalOperators
    );
    void printResults(std::vector<std::unordered_map<std::string, std::any>> res);
};