#include "DBApp.hpp"

DBApp::DBApp()
{
    
}

void DBApp::createTable(const std::string &tableName, const std::string &clusteringKeyColumn, const std::unordered_map<std::string, std::string> &colNameType, const std::unordered_map<std::string, std::any> &colNameMin, const std::unordered_map<std::string, std::any> &colNameMax)
{
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
