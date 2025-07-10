#include "DBApp.hpp"
DBApp::DBApp()
{
    datatypes = {"Integer", "String", "Double", "Date"};
    logicalOperators = {"AND","OR","XOR"};
    comparisonOperators = {">",">=","<", "<=","!=","="};
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
    Decider dec;
    Transformer trans;
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
        if(!dec.isTypeCompatible(colNameMin[i->first], type)){
            throw DBAppException("The datatype of Min value of column " + i->first +  " is not compatible");
        }
        if(!dec.isTypeCompatible(colNameMax[i->first], type)){
            throw DBAppException("The datatype of Max value of column " + i->first +  " is not compatible");
        }
        // No datatype transformation is needed since both min and max value should now have the same datatype
        if(dec.isMoreThan(colNameMin[i->first], colNameMax[i->first])){
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
        std::string minStr = trans.toStr(colNameMin[i->first]);
        line.push_back(minStr);
        std::string maxStr = trans.toStr(colNameMax[i->first]);
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
    Table table = Table(fileOut,diskinfomgr);
    Decider dec;
    if(colNameValue.count(table.getClusteringKey()) == 0){
            throw DBAppException("Primary Key must not be null in any inserted record");
    }
     for(auto i = colNameValue.begin() ; i != colNameValue.end(); i++){
        std::string colName = i->first;
        // std::transform(colName.begin(),colName.end(),colName.begin(), ::tolower);       
        if(table.getColumnTypes().find(colName) == table.getColumnTypes().end()){
            throw DBAppException("Column " + colName + " does not exist in the table " + tableName);
        }
        std::string type = table.getColumnTypes().at(colName);
        if(!dec.isTypeCompatible(i->second,type)){
            throw DBAppException("The datatype of value of column " + i->first +  " is not compatible");
        }
        std::any minValue = table.getColumnMin().at(i->first);
        std::any maxValue = table.getColumnMax().at(i->first);
        if(dec.isLessThan(i->second,minValue)){
            throw DBAppException("To be inserted value is lower than minimum value of column " + i->first);
        }
        if(dec.isMoreThan(i->second,maxValue)){
            throw DBAppException("To be inserted value is higher than maximum value of column " + i->first);
        }
     }
      table.insertRecord(colNameValue);
      delete metadatamgr;
      delete diskinfomgr;
    //   Useful message for multithreading and concurrency
      std::cout << "One row affected" << std::endl;
}

void DBApp::updateTable(const std::string &tableName, const std::string strClusteringKeyValue , const std::unordered_map<std::string, std::any> &colNameValue)
{
    std::vector<std::vector<std::string>> fileOut = metadatamgr->readCSV(tableName);
    if(fileOut.empty()){
        throw DBAppException("Table " + tableName + " does not exist in the database");
    }
    Table  table = Table(fileOut,diskinfomgr);
    Decider dec;
    if(colNameValue.count(table.getClusteringKey())){
            throw DBAppException("Clustering Key column " + table.getClusteringKey() + " value cannot be altered");
    }
     for(auto i = colNameValue.begin() ; i != colNameValue.end(); i++){
        std::string colName = i->first;
        // std::transform(colName.begin(),colName.end(),colName.begin(), ::tolower);       
        if(table.getColumnTypes().find(colName) == table.getColumnTypes().end()){
            throw DBAppException("Column " + colName + " does not exist in the table " + tableName);
        }
        std::string type = table.getColumnTypes().at(colName);
        if(!dec.isTypeCompatible(i->second,type)){
            throw DBAppException("The datatype of value of column " + i->first +  " is not compatible");
        }
        std::any minValue = table.getColumnMin().at(i->first);
        std::any maxValue = table.getColumnMax().at(i->first);
        if(dec.isLessThan(i->second,minValue)){
            throw DBAppException("To be inserted value is lower than minimum value of column " + i->first);
        }
        if(dec.isMoreThan(i->second,maxValue)){
            throw DBAppException("To be inserted value is higher than maximum value of column " + i->first);
        }
     }
    //  Assuming that clustering key value input can be converted into its correct datatype
      bool isAffected = table.updateRecord(colNameValue,strClusteringKeyValue);
      delete metadatamgr;
      delete diskinfomgr;
      //   Useful message for multithreading and concurrency
      if(isAffected){
        std::cout << "One record is affected by the update" << std::endl;
      }else{
        std::cout << "No records affected by the update" << std::endl;
      }
}

void DBApp::deleteFromTable(const std::string &tableName, const std::unordered_map<std::string, std::any> &colNameValue)
{
     std::vector<std::vector<std::string>> fileOut = metadatamgr->readCSV(tableName);
    if(fileOut.empty()){
        throw DBAppException("Table " + tableName + " does not exist in the database");
    }
    Decider dec;
    Table  table = Table(fileOut,diskinfomgr);
      for(auto i = colNameValue.begin() ; i != colNameValue.end(); i++){
        std::string colName = i->first;
        // std::transform(colName.begin(),colName.end(),colName.begin(), ::tolower);       
        if(table.getColumnTypes().find(colName) == table.getColumnTypes().end()){
            throw DBAppException("Column " + colName + " does not exist in the table " + tableName);
        }
        std::string type = table.getColumnTypes().at(colName);
        if(!dec.isTypeCompatible(i->second,type)){
            throw DBAppException("The datatype of value of column " + i->first +  " is not compatible");
        }
    }
    int val = table.deleteRecords(colNameValue);
    if(val == 1){
        std::cout << val << " row is affected" << std::endl;
    }else{
        std::cout << val << " rows are affected" << std::endl;
    }
}

void DBApp::selectFromTable(const std::vector<SQLTerm> &sqlTerms, const std::vector<std::string> &Operators)
{
    std::vector<std::vector<std::string>> fileOut = metadatamgr->readCSV(sqlTerms[0]._strTableName);
     if(fileOut.empty()){
        throw DBAppException("Table " + sqlTerms[0]._strTableName + " does not exist in the database");
    }
    Decider dec;
    Table table = Table(fileOut,diskinfomgr);
    for(SQLTerm term: sqlTerms){
        if(!table.getColumnTypes().count(term._strColumnName)){
            throw DBAppException("column with the name " + term._strColumnName + " does not exist in the table " + term._strTableName);
        }
        if(!std::count(comparisonOperators.begin(),comparisonOperators.end(),term._strOperator)){
            throw DBAppException("operator " + term._strOperator + " is not identified as an operator");
        }
        if(!dec.isTypeCompatible(term._objValue,table.getColumnTypes().at(term._strColumnName))){
            throw DBAppException("input value type is not compatible with the column " + term._strColumnName);
        }
        if(dec.isLessThan(term._objValue, table.getColumnMin().at(term._strColumnName))){
            throw DBAppException("input value is less than min value of column " + term._strColumnName);
        }
        if(dec.isMoreThan(term._objValue,table.getColumnMax().at(term._strColumnName))){
            throw DBAppException("input value is more than max value of column " + term._strColumnName);
        }
    }
    for(std::string op: Operators){
       if(!std::count(logicalOperators.begin(),logicalOperators.end(),op)){
        throw DBAppException("Operator " + op + " is undefined behavior");
       }    
    }
    std::vector<std::unordered_map<std::string, std::any>> queryResult = table.retreiveResults(sqlTerms,Operators);
    printResults(queryResult);
    // return std::vector<std::unordered_map<std::string, std::any>>();
    delete diskinfomgr;
    delete metadatamgr;
}

// function is copied from AI agent (Not yet tested or debugged)
void DBApp::printResults(std::vector<std::unordered_map<std::string, std::any>> res){
    if (res.empty()) {
        std::cout << "No results found.\n";
        return;
    }
    Transformer trans; 
    // 1. Collect all column names (sorted to maintain consistency)
    std::vector<std::string> columns;
    std::set<std::string> colSet;

    for (const auto& row : res) {
        for (const auto& pair : row) {
            if (colSet.insert(pair.first).second) {
                columns.push_back(pair.first);
            }   
        }
    }

    // 2. Determine max width for each column
    std::unordered_map<std::string, size_t> colWidths;
    for (const auto& col : columns) {
        colWidths[col] = col.size(); // Start with header size
    }

    for (const auto& row : res) {
        for (const auto& col : columns) {
            auto it = row.find(col);
            if (it != row.end()) {
                std::string valStr = trans.toStr(it->second);
                colWidths[col] = std::max(colWidths[col], valStr.size());
            }
        }
    }

    // Helper lambda to print a border row
    auto printBorder = [&]() {
        std::cout << "+";
        for (const auto& col : columns) {
            std::cout << std::string(colWidths[col] + 2, '-') << "+";
        }
        std::cout << '\n';
    };

    // Helper lambda to print a row of values
    auto printRow = [&](const std::unordered_map<std::string, std::any>& row) {
        std::cout << "|";
        for (const auto& col : columns) {
            std::string val = row.count(col) ? trans.toStr(row.at(col)) : "";
            std::cout << " " << std::setw(colWidths[col]) << std::left << val << " |";
        }
        std::cout << '\n';
    };

    // 3. Print header
    printBorder();
    std::unordered_map<std::string, std::any> headerRow;
    for (const auto& col : columns) 
        headerRow[col] = col;
    printRow(headerRow);
    printBorder();

    // 4. Print all rows
    for (const auto& row : res) {
        printRow(row);
    }
    printBorder();
}
