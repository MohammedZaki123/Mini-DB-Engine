# include "FileManager.hpp"
# include <filesystem>
# include <fstream>
# include <iostream>
void MetaDataManager::createFile(){
    if(std::filesystem::exists(filePath)){
        return; 
    }
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not create file " << filePath << "\n";
        return;
    }

    std::vector<std::string> columnTitle = {"Table Name", "Column Name", "Column Type", "ClusteringKey", "IndexName","IndexType","min", "max"};

    for(int i = 0 ; i < columnTitle.size(); i++){
        file << columnTitle[i];
         if (i != columnTitle.size() - 1)
            file << ",";
    }

    file << "\n";
    file.close();
}

// void MetaDataManager::updateFile(std::vector<std::vector<std::string>> lines)
// {

// }

void DiskInfoManager::createFile(){
     if(std::filesystem::exists(filePath)){
        return;
    }

    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not create file " << filePath << "\n";
        return;
    }

    std::vector<std::string> columnTitle = {"Name", "type","FileName" ,"filePath"};

    for(int i = 0 ; i < columnTitle.size(); i++){
        file << columnTitle[i];
         if (i != columnTitle.size() - 1)
            file << ",";
    }

    file << "\n";
    file.close();
}

MetaDataManager::MetaDataManager(){
    this->filePath.append("metadata.csv");   
}

DiskInfoManager::DiskInfoManager(){
    this->filePath.append("files.csv");
}
std::vector<std::vector<std::string>> MetaDataManager::readCSV(std::string tableName) {
    std::ifstream file(this->filePath);
    std::vector<std::vector<std::string>> result;

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open metadata.csv");
    }

    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<std::string> row;
        std::string cell;

        // Split line by commas
        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        // Check if the first column matches tableName
        if (row[0] == tableName) {
            result.push_back(row);
        } else if (!result.empty()) {
            // We've already started collecting rows, and now we hit a different table name
            break;
        }
    }

    file.close();
    return result;
}

std::vector<std::vector<std::string>> DiskInfoManager::readCSV(std::string tableName){
    std::ifstream file(this->filePath);
    std::vector<std::vector<std::string>> result;

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open metadata.csv");
    }

    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<std::string> row;
        std::string cell;

        // Split line by commas
        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        // Check if the first column matches tableName
        if (row[0] == tableName) {
            result.push_back(row);
        } else if (!result.empty()) {
            // We've already started collecting rows, and now we hit a different table name
            break;
        }
    }

    file.close();
    return result;
}
void MetaDataManager::writeCSV(std::vector<std::vector<std::string>> lines){
    std::ifstream inFile(filePath);
    std::vector<std::string> existingLines;
    std::string line;

    while (std::getline(inFile, line)) {
        existingLines.push_back(line);
    }
    inFile.close();

    // Step 2: Trim trailing empty lines
    while (!existingLines.empty() && existingLines.back().empty()) {
        existingLines.pop_back();
    }

    // Step 3: Reopen in write mode to truncate and clean old trailing lines
    std::ofstream outFile(filePath, std::ios::trunc);
    for (const auto& l : existingLines) {
        outFile << l << '\n';
    }

    // Step 4: Append new rows


    for (const auto& row : lines) {
        for (size_t i = 0; i < row.size(); ++i) {
            outFile << row[i];
            if (i < row.size() - 1)
                outFile << ',';
        }
        outFile << '\n';
    }

    outFile.close();
}
void DiskInfoManager::writeCSV(std::vector<std::vector<std::string>> input){
    std::string line;
    std::ifstream file(this->filePath);
    int lastPagePos = 0;
    int rowNo = 0;
    std::vector<std::vector<std::string>> oldLines;
    std::vector<std::vector<std::string>> newLines;
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open metadata.csv");
    }
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<std::string> row;
        std::string cell;

        // Split line by commas
        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        if(row[0] == input[0][0]){
            lastPagePos = rowNo; 
        }
            oldLines.push_back(row);
            ++rowNo;
    }
    file.close();
    newLines.push_back(oldLines[0]);
    for(int i = 1 ; i < rowNo; i++){
        // In order to insert new Row in the right position
        // we should track the last page of tha table, and insert new Page after it  
        newLines.push_back(oldLines[i]);
        if(i == lastPagePos){
            newLines.push_back(input[0]);
        }
    }
    // The case if there is no tables created for the page
    if(lastPagePos == 0){
         newLines.push_back(input[0]);
    }

    // Step 3: Reopen in write mode to truncate and clean old trailing lines
    std::ofstream outFile(filePath, std::ios::trunc);

    // Step 4: Append new rows
    for (const auto& row : newLines) {
        for (size_t i = 0; i < row.size(); ++i) {
            outFile << row[i];
            if (i < row.size() - 1)
                outFile << ',';
        }
        outFile << '\n';
    }

    outFile.close();
}

// void DiskInfoManager::updateFile(std::vector<std::vector<std::string>> newLines)
// {
//     std::ifstream inFile(filePath);
//     std::vector<std::vector<std::string>> newData;

//     if (!inFile.is_open()) {
//         throw std::runtime_error("Failed to open file.");
//     }

//     std::string line;
//     int oldPagesIgnored = 0;
//     const std::string& firstPageName = newLines[0][2]; // FileName column

//     // Step 1: Read and reconstruct file contents
//     while (std::getline(inFile, line)) {
//         std::stringstream ss(line);
//         std::string cell;
//         std::vector<std::string> row;

//         while (std::getline(ss, cell, ',')) {
//             row.push_back(cell);
//         }

//         // Preserve header row
//         if (newData.empty()) {
//             newData.push_back(row);
//             continue;
//         }

//         // If this is the first line of the block to replace
//         if (row[2] == firstPageName) {

//             // Insert replacement block
//             for (auto& newRow : newLines) {
//                 newData.push_back(newRow);

//             }
//         }

//         // Continue skipping old rows from same FileName
//         else if (oldPagesIgnored < newLines.size()) {
//             oldPagesIgnored++;   
//         }else{
//         newData.push_back(row);
//         }
//     }

//     inFile.close();

//     // Step 2: Write updated data back
//     std::ofstream outFile("Files.csv", std::ios::trunc);
//     if (!outFile.is_open()) {
//         throw std::runtime_error("Failed to open Files.csv for writing.");
//     }

//     for (const auto& row : newData) {
//         for (size_t i = 0; i < row.size(); ++i) {
//             outFile << row[i];
//             if (i < row.size() - 1) outFile << ',';
//         }
//         outFile << '\n';
//     }

//     outFile.close();
// }

bool MetaDataManager::checkExistence(std::string tableName){
    std::ifstream file(this->filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open metadata.csv\n";
        return false;
    }

    std::string line;

    // Skip header row
    std::getline(file, line);  

    // Search data rows
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;

        if (std::getline(ss, cell, ',')) {
            if (cell == tableName) {
                return true;
            }
        }
    }
    file.close();

    return false;
}

PageManager::PageManager(std::string pageName)
{
    this->filePath.append(pageName);
}

std::vector<std::vector<std::string>> PageManager::readCSV()
{

    std::ifstream file(this->filePath);
    std::vector<std::vector<std::string>> result;

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open metadata.csv");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<std::string> row;
        std::string cell;

        // Split line by commas
        while (std::getline(ss, cell, ',')) {
            // storing only values not commas (delimeter)
            row.push_back(cell);
        }
        result.push_back(row);
    }
    file.close();
    return result;
}

void PageManager::writeCSV(std::vector<std::vector<std::string>> lines)
{
     std::ofstream outFile(filePath, std::ios::trunc);
    // Step 4: Write new version of rows 

    for (const auto& row : lines) {
        for (size_t i = 0; i < row.size(); ++i) {
            outFile << row[i];
            if (i < row.size() - 1)
                outFile << ',';
        }
        outFile << '\n';
    }
    outFile.close();
}

void PageManager::createFile(std::vector<std::string> columns)
{
     if(std::filesystem::exists(filePath)){
        return; 
    }
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not create file " << filePath << "\n";
        return;
    }

    for(int i = 0 ; i < columns.size(); i++){
        file << columns[i];
         if (i != columns.size() - 1)
            file << ",";
    }

    file << "\n";
    file.close();
}

std::vector<std::string> PageManager::loadPageInfo(std::string pkCol)
{
    int totalRecords = 0;
    std::vector<std::string> res;
    int pkColPos;
     std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        throw std::runtime_error("Failed to open file.");
    }
    
    std::string line;
    int targetIndex = -1;

    // Step 1: Read header row and find target column index
    if (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string cell;
        int index = 0;
        while (std::getline(ss, cell, ',')) {
            if (cell == pkCol) {
                targetIndex = index;
                break;
            }
            index++;
        }
    }
       std::vector<std::vector<std::string>> allRows;

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }
            allRows.push_back(row);
    }
    inFile.close();
    // works with every option
    // if there is only one record in the page
    // if there is only two records in the page 
    // if there is more than two records in the page
    res.push_back(allRows[0][targetIndex]);
    res.push_back(allRows[allRows.size() -1][targetIndex]);
    res.push_back(std::to_string(allRows.size()));
    return res;
}

const std::string PageManager::getPath()
{
    return filePath;
}
