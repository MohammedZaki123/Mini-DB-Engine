#include "Table.hpp"
# include "Record.hpp"
# include "Transformation.hpp"

Table::Table(std::vector<std::vector<std::string>> lines, FileManager * mgr): manager(mgr)
{
    this->name = lines[0][0];
    for(int i = 0; i < lines.size(); i++){
        std::any minValue = fromStr(lines[i][2],lines[i][6]);
        std::any maxValue = fromStr(lines[i][2],lines[i][7]);
        columnTypes.emplace(lines[i][1],lines[i][2]);
        columnMin.emplace(lines[i][1],minValue);
        columnMax.emplace(lines[i][1],maxValue);
        colNames.push_back(lines[i][1]);
        if(lines[i][3] == "True"){
            this->clusteringKey = lines[i][1];
        }
    }
}

void Table::insertRecord(const std::unordered_map<std::string, std::any> &values)
{

    Record record = Record(values,columnTypes,clusteringKey);
    std::vector<std::vector<std::string>> linesOfPages = manager->readCSV(name);
    // DiskInfoManager * mgr = dynamic_cast<DiskInfoManager*>(manager);
     std::vector<std::vector<std::string>> l;
    std::vector<Page> pages;
    Page * newPage;
    if(linesOfPages.empty()){
        newPage = new Page(name,0, values.at(clusteringKey), values.at(clusteringKey));
        // newPage object access PageManager to create a new csv file page
        newPage->insertRec(record.toString(colNames),colNames);
        std::vector<std::string>  pageInfo = newPage->toString(this->name);
        l.push_back(pageInfo);
        manager->writeCSV(l);
        delete newPage;
    }else{
    for(std::vector<std::string> line: linesOfPages){
        Page p = Page(line[2],columnTypes.at(clusteringKey),clusteringKey);
        pages.push_back(p);
    }
    int i = 0;
    while(i < pages.size()){
        if(pages[i].isTarget(record)){
            break;
        }
        i++;
    }   
    // record cannot be inserted in any page, no existing page will be affected
    if(i == pages.size()){
        // No space for newrecord in any page
         newPage = new Page(name,pages.size(), values.at(clusteringKey), values.at(clusteringKey));

        newPage->insertRec(record.toString(colNames),colNames);

        std::vector<std::string>  pageInfo = newPage->toString(this->name);
        l.push_back(pageInfo);
        manager->writeCSV(l);
        delete newPage;
        // newPage object access PageManager to create a new csv file page
    }else{
        std::vector<std::string> remainingRec;
        pages[i].insertRec(record,remainingRec);
        i++;
        while(!remainingRec.empty() && i < pages.size()){
            // case: to clear the result of insertRec function
            // in order not to influence later function calls results
            pages[i].shiftRec(remainingRec);
            i++;
        }
        // case when all pages are filled. So last record in the last page needs another page 
        if(!remainingRec.empty()){
            // No space for the last record in the last page
        newPage = new Page(name,pages.size(), values.at(clusteringKey), values.at(clusteringKey));

        newPage->insertRec(remainingRec,colNames);

        std::vector<std::string>  pageInfo = newPage->toString(this->name);
        l.push_back(pageInfo);
        manager->writeCSV(l);
        delete newPage;
        // newPage object access PageManager to create a new csv file page
        }

    }
}
    // updateFilesInfo(pages,targetPagePos,i);
}

bool Table::updateRecord(const std::unordered_map<std::string, std::any> &values,const std::string strClusteringKeyValue)
{
   bool isUpdated = false;
   std::vector<std::vector<std::string>> linesOfPages = manager->readCSV(name);
   if(linesOfPages.empty()){
    return isUpdated;
   }
   std::any keyValue = fromStr(columnTypes.at(clusteringKey),strClusteringKeyValue);
   std::vector<Page> pages;
   for(std::vector<std::string> line: linesOfPages){
        Page p = Page(line[2],columnTypes.at(clusteringKey),clusteringKey);
        pages.push_back(p);
    }
    int i = 0;
        while(i < pages.size()){
            if(pages[i].isTarget(keyValue))
            break;
            i++;
        }
    if(pages[i].updateRec(keyValue,values,columnTypes,clusteringKey)){
        isUpdated = true;
    }
    return isUpdated;
}
// void Table::updateFilesInfo(std::vector<Page>& pages, int first, int last)
// {
//     std::vector<std::vector<std::string>> lines;
//     for(int i = first ; i <= last; i++){
//         std::vector<std::string> line = pages[i].toString(name);
//         lines.push_back(line);
//     }
//     manager->writeCSV(lines);
// }

std::vector<std::unordered_map<std::string, std::any>> Table::retreiveResults(const std::vector<SQLTerm> &sqlTerms, const std::vector<std::string> &logicalOperators)
{
    std::vector<std::unordered_map<std::string, std::any>> res;
    std::vector<std::vector<std::string>> linesOfPages = manager->readCSV(name);
   if(linesOfPages.empty()){
    return res;
   }
   std::vector<Page> pages;
   for(std::vector<std::string> line: linesOfPages){
        Page p = Page(line[2],columnTypes.at(clusteringKey),clusteringKey);
        pages.push_back(p);
    }
    for(Page p: pages){
        // full table scan without the use of indices
        p.fetchRecords(columnTypes,sqlTerms,logicalOperators, res,clusteringKey);
    }
    return res;
}

// --- Getters ---
const std::string& Table::getName() const {
    return name;
}

const std::string& Table::getClusteringKey() const {
    return clusteringKey;
}

const std::unordered_map<std::string, std::string>& Table::getColumnTypes() const {
    return columnTypes;
}

const std::unordered_map<std::string, std::any>& Table::getColumnMin() const {
    return columnMin;
}

const std::unordered_map<std::string, std::any>& Table::getColumnMax() const {
    return columnMax;
}

const std::unordered_map<std::string, Index*>& Table::getIndexColumns() const {
    return indexColumns;
}

const std::vector<std::string> Table::getColNames()
{
    return colNames;
}

FileManager* Table::getFileManager() const {
    return manager;
}

// --- Setters ---
// void Table::setName(const std::string& newName) {
//     name = newName;
// }

// void Table::setClusteringKey(const std::string& key) {
//     clusteringKey = key;
// }

// void Table::setColumnTypes(const std::unordered_map<std::string, std::string>& types) {
//     columnTypes = types;
// }

// void Table::setColumnMin(const std::unordered_map<std::string, std::any>& minVals) {
//     columnMin = minVals;
// }

// void Table::setColumnMax(const std::unordered_map<std::string, std::any>& maxVals) {
//     columnMax = maxVals;
// }

// void Table::setIndexColumns(const std::unordered_map<std::string, Index*>& indices) {
//     indexColumns = indices;
// }

// void Table::setFileManager(FileManager* manager) {
//     mgr = manager;
// }
