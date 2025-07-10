# pragma once
# include <string>
# include <vector>
# include <unordered_set>
# include <filesystem>
# include <fstream>
# include <iostream>
// Only one interface is needed since readCSV() function takes 
class FileManager{
    protected:
    // return type is not void, it will be changed later
    std::string filePath = "resources/";
    public:
    virtual std::vector<std::vector<std::string>> readCSV(std::string name) = 0;
    // // input parameter will be changed later
    virtual void writeCSV(std::vector<std::vector<std::string>> lines) = 0;

    virtual void createFile() = 0;

    // virtual void updateFile(std::vector<std::vector<std::string>> lines);
};
class MetaDataManager: public FileManager{
    public:
    MetaDataManager();
    std::vector<std::vector<std::string>> readCSV(std::string tableName) override;
    void writeCSV(std::vector<std::vector<std::string>> lines) override;
    void createFile() override;
    // void updateFile(std::vector<std::vector<std::string>> lines) override;
    bool checkExistence(std::string tableName);
};


// class PageManager: public FileManager{
//     public:
//     PageManager();
//     ~PageManager();

// };

class DiskInfoManager: public FileManager{
    public:
    DiskInfoManager();
    std::vector<std::vector<std::string>> readCSV(std::string tableName) override;
    void writeCSV(std::vector<std::vector<std::string>> lines) override;
    // void updateFile(std::vector<std::vector<std::string>> pageLines) override;
    void createFile() override;
    void deletePages(const std::unordered_set<std::string>  & pageName);
};

// class IndexManager: public FileManager{
//     IndexManager();
//     ~IndexManager();
//     std::vector<std::vector<std::string>> readCSV();
//     void writeCSV(std::vector<std::vector<std::string>> lines);
//     void createFile();
// };

// An interface specifically for objects which manage multiple disk files
class PageManager{
    std::string filePath = "resources/"; 
    public: 
    PageManager(std::string pageName);
    std::vector<std::vector<std::string>> readCSV() ;
    void writeCSV(std::vector<std::vector<std::string>> lines) ;
    void createFile();
    void createFile(std::vector<std::string> columnHeaders);
    void deleteFile();
    // The purpose of this function is:
    // - Get minmum 
    std::vector<std::string> loadPageInfo(std::string pk);
    const std::string getPath();
};

// class IndexManager: public FileManager{

// };