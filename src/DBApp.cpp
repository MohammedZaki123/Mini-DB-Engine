#include "DBApp.hpp"
# include "FactoryObjectCreation.hpp"
# include <typeindex>
# include "Transformation.hpp"
# include "Table.hpp"
# include <algorithm>
# include <cctype>
# include <iostream>
DBApp::DBApp()
{
    datatypes = {"Integer", "String", "Double", "Date"};
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
        std::string colName = i->first;
        std::string type = i->second;
        // std::transform(colName.begin(),colName.end(),colName.begin(), ::tolower);
        // std::transform(type.begin(),type.end(),type.begin(), ::tolower);
        if(!std::count(datatypes.begin(),datatypes.end(),type)){
            throw DBAppException("a column " + i->first + " datatype is not within acceptable datatypes");
        }
        // std::any minVal = colNameMin.at(colName);   
        if(!isTypeCompatible(colNameMin[i->first], type)){
            throw DBAppException("The datatype of Min value of column " + i->first +  " is not compatible");
        }
        if(!isTypeCompatible(colNameMax[i->first], type)){
            throw DBAppException("The datatype of Max value of column " + i->first +  " is not compatible");
        }
        // No datatype transformation is needed since both min and max value should now have the same datatype
        if(isMoreThan(colNameMin[i->first], colNameMax[i->first])){
                throw DBAppException("The minimum value exceeds maximum value of column " + i ->first);
        }
        // adding all required info for metadata file for each column
        line.push_back(tableName);
        line.push_back(colName);
        line.push_back(type);

        if(i->first == clusteringKeyColumn){
            line.push_back("True");
        } else{
            line.push_back("False");
        }
         // Column having an index (Done later)
         line.push_back("null");
         line.push_back("null");
        // to be continued 
        std::string minStr = toStr(colNameMin[i->first]);
        line.push_back(minStr);
        std::string maxStr = toStr(colNameMax[i->first]);
        line.push_back(maxStr);
        inputs.push_back(line);
    }
    metadatamgr->writeCSV(inputs);
    delete metadatamgr;
    delete diskinfomgr;
    std::cout << "Table creation is done successfuly" << std::endl;
}

void DBApp::createIndex(const std::string &tableName, const std::string &colName)
{

}

void DBApp::insertIntoTable(const std::string &tableName, std::unordered_map<std::string, std::any> &colNameValue)
{
    std::vector<std::vector<std::string>> fileOut = metadatamgr->readCSV(tableName);
    if(fileOut.empty()){
        throw DBAppException("Table " + tableName + " does not exist in the database");
    }
    Table * table = new Table(fileOut,diskinfomgr);
     for(auto i = colNameValue.begin() ; i != colNameValue.end(); i++){
        std::string colName = i->first;
        // std::transform(colName.begin(),colName.end(),colName.begin(), ::tolower);       
        if(table->getColumnTypes().find(colName) == table->getColumnTypes().end()){
            throw DBAppException("Column " + colName + " does not exist in the table " + tableName);
        }
        std::string type = table->getColumnTypes().at(colName);
        if(!isTypeCompatible(i->second,type)){
            throw DBAppException("The datatype of value of column " + i->first +  " is not compatible");
        }
        std::any minValue = table->getColumnMin().at(i->first);
        std::any maxValue = table->getColumnMax().at(i->first);
        if(isLessThan(i->second,minValue)){
            throw DBAppException("To be inserted value is lower than minimum value of column " + i->first);
        }
        if(isMoreThan(i->second,maxValue)){
            throw DBAppException("To be inserted value is higher than maximum value of column " + i->first);
        }
        if(colNameValue.count(table->getClusteringKey()) == 0){
            throw DBAppException("Primary Key must not be null in any inserted record");
        }
     }
      table->insertRecord(colNameValue);
      delete metadatamgr;
      delete diskinfomgr;
      std::cout << "Inserting the new record is done successfuly" << std::endl;
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






