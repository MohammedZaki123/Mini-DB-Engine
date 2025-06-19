#include "DBApp.hpp"
# include "FactoryObjectCreation.hpp"
# include <typeindex>
# include "Transformation.hpp"

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

void DBApp::createTable( std::string &tableName, const std::string &clusteringKeyColumn, std::unordered_map<std::string, std::string> &colNameType, std::unordered_map<std::string, std::any> &colNameMin, std::unordered_map<std::string, std::any> &colNameMax)
{
    std::vector<std::vector<std::string>> inputs; 
    MetaDataManager * mgr = dynamic_cast<MetaDataManager*>(this->metadatamgr);
    if(mgr->checkExistence(tableName)){
        throw DBAppException("A table is already created with the same name in the database");
    }
    // iterating using begin() and end()
    for(auto i = colNameType.begin() ; i != colNameType.end(); i++){
        std::vector<std::string> line;
        std::transform(i->second.begin(),i->second.end(),i->second.begin(), ::tolower);
        std::string colName = i->first;
        std::string type = i->second;
        if(!std::count(datatypes.begin(),datatypes.end(),i->second)){
            throw DBAppException("a column " + i->first + " datatype is not within acceptable datatypes");
        }
        // std::any minVal = colNameMin.at(colName);   
        if(!isTypeCompatible(colNameMin[colName], type)){
            throw DBAppException("The datatype of Min value of column " + i->first +  " is not compatible");
        }
        if(!isTypeCompatible(colNameMax[colName], type)){
            throw DBAppException("The datatype of Max value of column " + i->first +  " is not compatible");
        }
        // No datatype transformation is needed since both min and max value should now have the same datatype
        if(moreThan(colNameMin[colName], colNameMax[colName])){
                throw DBAppException("The minimum value exceeds maximum value of column " + i ->first);
        }
        // adding all required info for metadata file for each column
        line.push_back(tableName);
        line.push_back(i->first);
        line.push_back(i ->second);

        if(i->first == clusteringKeyColumn){
            line.push_back("True");
        } else{
            line.push_back("False");
        }
         // Column having an index (Done later)
         line.push_back("null");
         line.push_back("null");
        // to be continued 
        std::string minStr = toStr(colNameMin[colName]);
        line.push_back(minStr);
        std::string maxStr = toStr(colNameMax[colName]);
        line.push_back(maxStr);
        inputs.push_back(line);
    }
    metadatamgr->writeCSV(inputs);
    delete metadatamgr;
    delete diskinfomgr;
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






