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
    std::string path;
    // FileManager pointer points to PageManager object to access csv files (pages) stored in the disk
    FileManager * mgr;

public:
    Page(std::string name,  std::any minPKValue, void* maxPKValue, int totalRecords, std::string path);
    bool isTarget(Record * record);  // Assuming Record type is represented as void*
    std::vector<std::string> insertRec(Record* record); // Assuming Record type is represented as void*
    std::vector<std::string> shiftRec(std::vector<std::string> record);  // Assuming Record type is represented as void*


    // Getters
    const std::string& getName() const { return name; }
    const std::any& getMinPKValue() const { return minPKValue; }
    const std::any& getMaxPKValue() const { return maxPKValue; }
    int getTotalRecords() const { return totalRecords; }
    const std::string& getPath() const { return path; }
    FileManager* getFileManager() const { return mgr; }

    // Setters
    void setName(const std::string& newName) { name = newName; }
    void setName(std::string&& newName) { name = std::move(newName); }
    
    void setMinPKValue(const std::any& newValue) { minPKValue = newValue; }
    void setMinPKValue(std::any&& newValue) { minPKValue = std::move(newValue); }
    
    void setMaxPKValue(const std::any& newValue) { maxPKValue = newValue; }
    void setMaxPKValue(std::any&& newValue) { maxPKValue = std::move(newValue); }
    
    void setTotalRecords(int newTotal) { totalRecords = newTotal; }
    
    void setPath(const std::string& newPath) { path = newPath; }
    void setPath(std::string&& newPath) { path = std::move(newPath); }
    
    void setFileManager(FileManager* newMgr) { mgr = newMgr; }

};
