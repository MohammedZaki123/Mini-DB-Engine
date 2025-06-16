#include "DBApp.hpp"
# include "FactoryObjectCreation.hpp"

DBApp::DBApp()
{
    datatypes = {"integer", "string", "double", "date"};
}
void DBApp::init(){
   Factory  objectCreator = Factory();
   metadatamgr = objectCreator.createMgrfromType(metadatamgr,"metadata");
   diskinfomgr = objectCreator.createMgrfromType(diskinfomgr,"disk");   
   metadatamgr->createFile();
   diskinfomgr->createFile();
}

void DBApp::createTable(const std::string &tableName, const std::string &clusteringKeyColumn, const std::unordered_map<std::string, std::string> &colNameType, const std::unordered_map<std::string, std::any> &colNameMin, const std::unordered_map<std::string, std::any> &colNameMax)
{
    MetaDataManager * mgr = dynamic_cast<MetaDataManager*>(this->metadatamgr);
    if(mgr->checkExistence(tableName)){
        throw DBAppException("A table is already created with the same name in the database");
    }
    // iterating using begin() and end()
    for(auto i = colNameType.begin() ; i != colNameType.end(); i++){
        std::transform(i->second.begin(),i->second.end(),i->second.begin(), ::tolower);
        if(!std::count(datatypes.begin(),datatypes.end(),i->second)){
            throw DBAppException("a column" + i->first + "datatype is not within acceptable datatypes");
        }
        if(){
        }
        if(){
        }
    }
    
    delete mgr;
}

void DBApp::createIndex(const std::string &tableName, const std::string &colName)
{
}

void DBApp::insertIntoTable(const std::string &tableName, const std::unordered_map<std::string, std::any> &colNameValue)
{
}

void DBApp::updateTable(const std::string &tableName, const std::string &clusteringKeyValue, const std::unordered_map<std::string, std::any> &colNameValue)
{
}

void DBApp::deleteFromTable(const std::string &tableName, const std::unordered_map<std::string, std::any> &colNameValue)
{
}

std::vector<std::unordered_map<std::string, std::any>> DBApp::selectFromTable(const std::vector<SQLTerm> &sqlTerms, const std::vector<std::string> &logicalOperators)
{
    return std::vector<std::unordered_map<std::string, std::any>>();
}
