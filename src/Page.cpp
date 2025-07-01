#include "Page.hpp"
# include "Exception.hpp"
# include "Transformation.hpp"                                                                                                                                      
# include "DBApp.config"

// Used when creating a Page object for a page that exist in filesInfo disk file
Page::Page(std::string name, std::string pkType, std::string pkColName)
:name(name), manager(PageManager(name)) 
{
    std::vector <std::string> res = manager.loadPageInfo(pkColName);
    minPKValue = fromStr(pkType,res[0]);
    maxPKValue = fromStr(pkType,res[1]); 
    totalRecords = std::stoi(res[2]);
}


// Used when creating a page object for a page that does not exist in filesInfo disk file
Page::Page(std::string tableName, int noOfPages, std::any min, std::any max):
minPKValue(min), maxPKValue(max), totalRecords(0), 
name(tableName + std::to_string(noOfPages + 1) + ".csv"), manager(PageManager(name))
{
    // CSV File is not created yet
}

bool Page::isTarget(Record & record)
{
    std::any a = record.getVals().at(record.getClusteringKey());
    // if(isEqual(a,minPKValue) || isEqual(a,minPKValue)){
    //     throw DBAppException("Inserted primary key value already exist in the table");
    // }
    if(isLessThan(a,minPKValue)){
        return true;
    }
    if(isMoreThan(a,maxPKValue)){
        return totalRecords < maxRowPerPage;
    }
    // The Value is in between min and max. So it is in the correct page
    return true;
}

bool Page::isTarget(std::any keyVal)
{
    if(isLessThan(keyVal,minPKValue)){
        return false;
    }
    else if(isMoreThan(keyVal,maxPKValue)){
        return false;
    }
    return true;
}

// Record comparisons existence
void Page::insertRec(Record & newRecord, std::vector<std::string>& remRec)
{
    bool isInserted = false; 
    // storing result which will be written back to csv disk file of page
    std::vector<std::vector<std::string>> res;
    std::vector<std::vector<std::string>> fileLines = manager.readCSV();
    res.push_back(fileLines[0]);
    int i = 1;
    while(!isInserted && i < fileLines.size()){
        std::vector<std::pair<std::string,std::string>> values;
        for(int j = 0 ; j < fileLines[0].size(); j++){
            // matching column name to its corresponding value in each record
            values.push_back({fileLines[0][j],fileLines[i][j]});
        }
        // Record object is destroyed in every iteration
        Record record = Record(newRecord.getDatatypes(),values,newRecord.getClusteringKey());
        if(newRecord == record){
              throw DBAppException("Inserted primary key value already exist in the table");
        }else if(newRecord < record){
            // Adding record to the to be written to disk file of page
              res.push_back(newRecord.toString(fileLines[0]));
              isInserted = true;
              totalRecords++;
        }else{
            res.push_back(record.toString(fileLines[0]));
            i++;
        }
    }
    if(!isInserted){
        // new Record is the last record in the page
         // no remaining records for this page to delegate to another page
          res.push_back(newRecord.toString(fileLines[0]));
          isInserted = true;
          totalRecords++;
    }
    while(i < fileLines.size()){
        if(totalRecords > maxRowPerPage && i == fileLines.size() - 1){
            // the last record of will not be written back if 
            remRec = fileLines[i];
        }else{
            res.push_back(fileLines[i]);    
        }
        i++;
    }
    manager.writeCSV(res);
}


// No record comparison
void Page::shiftRec(std::vector<std::string> & record)
{
    // storing result which will be written back to csv disk file of page
    std::vector<std::vector<std::string>> res;
    std::vector<std::vector<std::string>> fileLines = manager.readCSV();
    res.push_back(fileLines[0]);
    res.push_back(record);
    totalRecords++;
    int i = 1;
    while(i < fileLines.size()){
        res.push_back(fileLines[i]);
        i++;
    }
    // Special case for the last record in the page
    if(totalRecords>maxRowPerPage){ 
       record = fileLines[fileLines.size() - 1];
       res.pop_back();
       totalRecords--;
    }else{
       record.clear();
    }
    manager.writeCSV(res);
}



// No record comparison: New Page Formation, this the first record of page to be inserted 
void Page::insertRec(std::vector<std::string> record, std::
vector<std::string> colNames)
{
    std::vector<std::vector<std::string>> res;
    manager.createFile(colNames);
    std::vector<std::vector<std::string>> fileLines = manager.readCSV();
    res.push_back(fileLines[0]);
    res.push_back(record);
    manager.writeCSV(res);
    totalRecords++;
}

bool Page::updateRec(std::any keyVal,std::unordered_map<std::string, std::any> newVals, std::unordered_map<std::string, std::string> types, std::string keyCol)
{
    std::vector<std::vector<std::string>> res;
    std::vector<std::vector<std::string>> fileLines = manager.readCSV();
    res.push_back(fileLines[0]);
    bool isUpdated = false;
    int i = 1;
    while(!isUpdated && i < fileLines.size()){
         std::vector<std::pair<std::string,std::string>> values;
        for(int j = 0 ; j < fileLines[0].size(); j++){
            // matching column name to its corresponding value in each record
            values.push_back({fileLines[0][j],fileLines[i][j]});
        }
        // Record object is destroyed in every iteration
        Record record = Record(types,values,keyCol);
        if(isEqual(record.getVals().at(record.getClusteringKey()),keyVal)){
            // alternative: this operation could be done inside record class and only an encapsulated version is presented in the page class
                record.setVals(newVals);
                isUpdated = true;
        }
        res.push_back(record.toString(fileLines[0]));
        i++;
    }

    // if a column does not exist as a key in vals attribute of record
    // then it has no value (set into null)
    while(i < fileLines.size()){
        res.push_back(fileLines[i]);
        i++;
    }
    manager.writeCSV(res);
    return isUpdated;
}

const std::vector<std::string> Page::toString(std::string tableName)
{
    std::vector<std::string> result;
    result.push_back(tableName);
    result.push_back("Table");
    result.push_back(name);
    result.push_back(manager.getPath());
    return result;
}
