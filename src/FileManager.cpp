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

void DiskInfoManager::createFile(){
     if(std::filesystem::exists(filePath)){
        return;
    }

    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not create file " << filePath << "\n";
        return;
    }

    std::vector<std::string> columnTitle = {"Name", "type", "filePath", "MinPKValue", "MaxPKValue", "Total Records"};

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
std::vector<std::vector<std::string>> MetaDataManager::readCSV(){
     std::vector<std::vector<std::string>> lines;

     return lines;
}

std::vector<std::vector<std::string>> DiskInfoManager::readCSV(){
    std::vector<std::vector<std::string>> lines;
    
     return lines;
}
void MetaDataManager::writeCSV(std::vector<std::vector<std::string>> lines){
    
}
void DiskInfoManager::writeCSV(std::vector<std::vector<std::string>> lines){

}

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

    return false;
}
