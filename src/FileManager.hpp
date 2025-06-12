# pragma once
class FileManager{
    // return type is not void, it will be changed later
    virtual void readCSV() = 0;
    // input parameter will be changed later
    virtual void writeCSV() = 0;
    // input parameter will be changd later
    virtual void checkExistence() = 0;

    virtual void createCSV() = 0;

    virtual void createFile() = 0;
};
class MetaDataManager: public FileManager{
    
};


class PageManager: public FileManager{

};

class DiskInfoManager: public FileManager{
    
};

class IndexManager: public FileManager{

};