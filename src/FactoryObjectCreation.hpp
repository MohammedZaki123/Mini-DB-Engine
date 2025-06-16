# pragma once
# include "FileManager.hpp"
# include <string>
class Factory{
    public:
    FileManager * createMgrfromType(FileManager * mgr, std::string typeName);
};