#include <string>
# include "Record.hpp"
# include <any>
# include "FileManager.hpp"
# include <string>
# include <vector>
class Page {
private:
    std::string name;
    std::any minPKValue;  // 'any' type represented as void pointer
    std::any maxPKValue;  // 'any' type represented as void pointer
    int totalRecords;
    // FileManager pointer points to PageManager object to access csv files (pages) stored in the disk
    PageManager manager;

public:
    Page(std::string name, std::string pkType, std::string pkColName);
    Page(std::string tableName, int noOfPages, std::any min, std::any max);
    bool isTarget(Record & record);  
    void insertRec(Record & record, std::vector<std::string> &remRec);
    void shiftRec(std::vector<std::string>& record);  
    void insertRec(std::vector<std::string> record, std::vector<std::string> colNames);
    const std::vector<std::string> toString(std::string tableName);
    // Getters
    const std::string& getName() const { return name; }
    const std::any& getMinPKValue() const { return minPKValue; }
    const std::any& getMaxPKValue() const { return maxPKValue; }
    int getTotalRecords() const { return totalRecords; }
    PageManager getFileManager() const { return manager; }
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
