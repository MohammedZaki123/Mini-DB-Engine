#pragma once
# include "Index.hpp"
#include <string>
#include <unordered_map>
#include <any>
# include "FileManager.hpp"
# include "Page.hpp"
# include "SQLTerm.hpp"
// Forward declaration

class Table {
private:
    // you may a vector datastructure instead of unordered map
    std::string name;
    std::string clusteringKey;
    std::vector<std::string> colNames;
    // std::vector<std::any> types;
    // std::vector<std::any> min;
    // std::vector<std::any> max;
    // std::vector<Index *> indices;
    // Alternative Approach
    std::unordered_map<std::string, std::string> columnTypes;
    std::unordered_map<std::string, std::any> columnMin;
    std::unordered_map<std::string, std::any> columnMax;
    std::unordered_map<std::string, Index*> indexColumns;
    // fileManager pointer points to diskinfoManager
    FileManager * manager; 

public:
    Table(std::vector<std::vector<std::string>> lines, FileManager * mgr);
    void insertRecord(const std::unordered_map<std::string, std::any>& values);
    bool  updateRecord(const std::unordered_map<std::string, std::any>& values, const std::string strClusteringKeyValue);
    void updateFilesInfo(std::vector<Page> &pages, int first, int last);
    std::vector<std::unordered_map<std::string, std::any>> retreiveResults(const std::vector<SQLTerm> &sqlTerms, const std::vector<std::string> &logicalOperators);
    const std::string& getName() const;
    const std::string& getClusteringKey() const;
    const std::unordered_map<std::string, std::string>& getColumnTypes() const;
    const std::unordered_map<std::string,       std::any>& getColumnMin() const;
    const std::unordered_map<std::string, std::any>& getColumnMax() const;
    const std::unordered_map<std::string, Index*>& getIndexColumns() const;
    const std::vector<std::string> getColNames();
    FileManager* getFileManager() const;


    // void setName(const std::string& newName);
    // void setClusteringKey(const std::string& key);
    // void setColumnTypes(const std::unordered_map<std::string, std::string>& types);
    // void setColumnMin(const std::unordered_map<std::string, std::any>& minVals);
    // void setColumnMax(const std::unordered_map<std::string, std::any>& maxVals);
    // void setIndexColumns(const std::unordered_map<std::string, Index*>& indices);
    // void setFileManager(FileManager*manager);

};
