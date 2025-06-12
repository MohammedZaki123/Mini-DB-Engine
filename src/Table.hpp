#pragma once
# include "Index.hpp"
#include <string>
#include <unordered_map>
#include <any>
# include "FileManager.hpp"

// Forward declaration

class Table {
private:
    std::string name;
    std::string clusteringKey;
    std::unordered_map<std::string, std::string> columnTypes;
    std::unordered_map<std::string, std::any> columnMin;
    std::unordered_map<std::string, std::any> columnMax;
    std::unordered_map<std::string, Index*> indexColumns;
    // fileManager pointer points to diskinfoManager
    FileManager * mgr; 

public:
    void insertRecord(const std::unordered_map<std::string, std::any>& values, FileManager * mgr);

    
};
