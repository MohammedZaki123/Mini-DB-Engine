# pragma once
# include "Record.hpp"
# include "FileManager.hpp"
# include <queue>
# include "Exception.hpp"                                                                                                                                     
# include "DBApp.config"
# include "Evaluator.hpp"
class Page {
private:
    std::string name;
    std::any minPKValue;  // 'any' type represented as void pointer
    std::any maxPKValue;  // 'any' type represented as void pointer
    int totalRecords;
    // queue is used over vector to improve performance of poping first element
    // in vector deleting first element time complexity is O(n)
    // in queue deleting first element time complexity is O(1)
    std::queue<std::vector<std::string>> currRecs;
    std::vector<std::vector<std::string>> finalRecs;    
    // PageManager object points to PageManager object to access csv files (pages) stored in the disk
    PageManager manager;

public:
    Page(std::string name, std::string pkType, std::string pkColName);
    Page(std::string tableName, int noOfPages, std::any min, std::any max);
    // This function for insertion, 
    // In the case of updating,the following function does not the existence of record in this page
    // But if the record exist in the table, it will definitely appear in this page
    bool isTarget(Record & record);
    bool isTarget(std::any keyVal);  
    void insertRec(Record & record, std::vector<std::string> &remRec);
    void shiftRec(std::vector<std::string>& record);  
    void insertRec(std::vector<std::string> record, std::vector<std::string> colNames);
    bool updateRec(std::any keyVal, std::unordered_map<std::string, std::any> newVals, std::unordered_map<std::string, std::string> types, std::string keyCol);
    void fetchRecords(const std::unordered_map<std::string, std::string> types   ,const std::vector<SQLTerm> & terms,const  std::vector<std::string> operators, std::vector<std::unordered_map<std::string, std::any>>& tuples, std::string keyCol);
    void eraseRecs(const std::unordered_map<std::string, std::string> types , const std::unordered_map<std::string, std::any> vals, int & delRows);
    bool fillGaps(Page & page);
    void terminatePage();
    void reWrite();
    const std::vector<std::string> toString(std::string tableName);
    // Getters
    const std::string& getName() const { return name; }
    const std::any& getMinPKValue() const { return minPKValue; }
    const std::any& getMaxPKValue() const { return maxPKValue; }
    int getTotalRecords() const { return totalRecords; }
    PageManager getFileManager() const { return manager; }
    std::queue<std::vector<std::string>> getCurrRecs();
    // used to pop first element of queue
    void popCurrRecs();
    // Setters
    // void setName(const std::string& newName) { name = newName; }
    // void setName(std::string&& newName) { name = std::move(newName); }
    
    // void setMinPKValue(const std::any& newValue) { minPKValue = newValue; }
    // void setMinPKValue(std::any&& newValue) { minPKValue = std::move(newValue); }
    
    // void setMaxPKValue(const std::any& newValue) { maxPKValue = newValue; }
    // void setMaxPKValue(std::any&& newValue) { maxPKValue = std::move(newValue); }
    
    // void setTotalRecords(int newTotal) { totalRecords = newTotal; }
    
    // void setFileManager(FileManager* newMgr) { mgr = newMgr; }

};
