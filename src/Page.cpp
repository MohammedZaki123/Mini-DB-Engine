#include "Page.hpp"


// Used when creating a Page object for a page that exist in filesInfo disk file
Page::Page(std::string name, std::string pkType, std::string pkColName)
:name(name), manager(PageManager(name)) 
{
    Transformer trans;
    std::vector <std::string> res = manager.loadPageInfo(pkColName);
    minPKValue = trans.fromStr(pkType,res[0]);
    maxPKValue = trans.fromStr(pkType,res[1]); 
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
    Decider dec;
    std::any a = record.getVals().at(record.getClusteringKey());
    // if(isEqual(a,minPKValue) || isEqual(a,minPKValue)){
    //     throw DBAppException("Inserted primary key value already exist in the table");
    // }
    if(dec.isLessThan(a,minPKValue)){
        return true;
    }
    if(dec.isMoreThan(a,maxPKValue)){
        return totalRecords < maxRowPerPage;
    }
    // The Value is in between min and max. So it is in the correct page
    return true;
}

bool Page::isTarget(std::any keyVal)
{
    Decider dec;
    if(dec.isLessThan(keyVal,minPKValue)){
        return false;
    }
    else if(dec.isMoreThan(keyVal,maxPKValue)){
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
    Decider dec;
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
        if(dec.isEqual(record.getVals().at(record.getClusteringKey()),keyVal)){
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

void Page::fetchRecords(const std::unordered_map<std::string, std::string> types ,const std::vector<SQLTerm> &terms, const std::vector<std::string> operators, std::vector<std::unordered_map<std::string, std::any>> &tuples, std::string keyCol)
{
    std::vector<std::vector<std::string>> fileLines = manager.readCSV();
    int i = 1;
    Evaluator evaluator = Evaluator(terms,operators);
    while(i < fileLines.size()){
        std::vector<std::pair<std::string,std::string>> values;
        for(int j = 0 ; j < fileLines[0].size(); j++){
            // matching column name to its corresponding value in each record
            values.push_back({fileLines[0][j],fileLines[i][j]});
        }
        // Record object is destroyed in every iteration
        Record record = Record(types,values,keyCol);
        if(evaluator.formTheDecision(record)){
        // record is accepted within query constraints
            tuples.push_back(record.getVals());
        }
        i++;
    }
}

void Page::eraseRecs(const std::unordered_map<std::string, std::string> types , const std::unordered_map<std::string, std::any> deleteConditions, int& deletedRecs)
{
    Decider dec;
    std::vector<std::vector<std::string>> fileLines = manager.readCSV();
    finalRecs.push_back(fileLines[0]);
     // Read all records from page
    for (int i = 1; i < fileLines.size(); ++i) { // Skip header if present
        std::vector<std::pair<std::string,std::string>> values;
        for(int j = 0 ; j < fileLines[0].size(); j++){
            // matching column name to its corresponding value in each record
            values.push_back({fileLines[0][j],fileLines[i][j]});
        }
        // Record object is destroyed in every iteration
        Record record = Record(types,values);
        const auto& recordVals = record.getVals();

        bool shouldDelete = false;

        // Iterate over all delete condition keys
        for (const auto& [key, valueToDelete] : deleteConditions) {
            auto it = recordVals.find(key);
            if (it != recordVals.end() && dec.isEqual(it->second, valueToDelete)) {
                shouldDelete = true;
                break; // Early exit: one match is enough to delete
            }
        }

        if (shouldDelete) {
            ++deletedRecs;
        } else {
            currRecs.push(record.toString(fileLines[0]));
        }
    }

}

bool Page::fillGaps(Page &page)
{
    
    // Loop is only for all pages except last one
    while (!page.getCurrRecs().empty() && (this->totalRecords - this->currRecs.size() > 0)) {
        std::vector<std::string> pulledRecord = page.getCurrRecs().front();
        // page.currRecs.pop();
        page.popCurrRecs();
        this->currRecs.push(pulledRecord);
    }

    // All deleted records of the page are filled from subsequent pages
    // OR pages has no deleted records at all 
    return totalRecords - currRecs.size() == 0;
}

void Page::terminatePage()
{
    manager.deleteFile();
}

void Page::reWrite()
{
      while(!currRecs.empty()){
        std::vector<std::string> rec = currRecs.front();
        currRecs.pop();
        finalRecs.push_back(rec);
    }
    manager.writeCSV(finalRecs);
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

  std::queue<std::vector<std::string>> Page::getCurrRecs()
{
    return currRecs;
}

void Page::popCurrRecs()
{
    currRecs.pop();
}
