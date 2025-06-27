# include "FactoryObjectCreation.hpp"

FileManager * Factory::createMgrfromType(FileManager * ptr, std::string typeName)
{
    if (typeName == "metadata") {
        ptr = new MetaDataManager();
    } else if (typeName == "disk") {
        ptr = new DiskInfoManager();
    // } else if (typeName == "Index"){
    //     ptr = new IndexManager();
    }else{
        ptr = nullptr;
    }   
    return ptr;
}

