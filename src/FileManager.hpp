# pragma once
# include <string>
# include <vector>
class FileManager{
    protected:
    // return type is not void, it will be changed later
    std::string filePath = "resources/";
    public:
    virtual std::vector<std::vector<std::string>> readCSV() = 0;
    // // input parameter will be changed later
    virtual void writeCSV(std::vector<std::vector<std::string>> lines) = 0;

    virtual void createFile() = 0;
};
class MetaDataManager: public FileManager{
    public:
    MetaDataManager();
    std::vector<std::vector<std::string>> readCSV();
    void writeCSV(std::vector<std::vector<std::string>> lines);
    void createFile();
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
    std::vector<std::vector<std::string>> readCSV();
    void writeCSV(std::vector<std::vector<std::string>> lines);
    void createFile();
};

// class IndexManager: public FileManager{
//     IndexManager();
//     ~IndexManager();
//     std::vector<std::vector<std::string>> readCSV();
//     void writeCSV(std::vector<std::vector<std::string>> lines);
//     void createFile();
// };
class PageManager: public FileManager{

};

class IndexManager: public FileManager{

};