// #include <string>
// #include <fstream>
// #include <vector>
// #include <utility> // std::pair
// # include <unordered_map>
# include "DBApp.hpp"
// # include "SQLTerm.hpp"
// # include "iostream"
// # include "Date.hpp"

// void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<int>>> dataset){
//     // Make a CSV file with one or more columns of integer values
//     // Each column of data is represented by the pair <column name, column data>
//     //   as std::pair<std::string, std::vector<int>>
//     // The dataset is represented as a vector of these columns
//     // Note that all columns should be the same size
    
//     // Create an output filestream object
//     std::ofstream myFile(filename);
    
//     // Send column names to the stream
//     for(int j = 0; j < dataset.size(); ++j)
//     {
//         myFile << dataset.at(j).first;
//         if(j != dataset.size() - 1) myFile << ","; // No comma at end of line
//     }
//     myFile << "\n";
    
//     // Send data to the stream
//     for(int i = 0; i < dataset.at(0).second.size(); ++i)
//     {
//         for(int j = 0; j < dataset.size(); ++j)
//         {
//             myFile << dataset.at(j).second.at(i);
//             if(j != dataset.size() - 1) myFile << ","; // No comma at end of line
//         }
//         myFile << "\n";
//     }
    
//     // Close the file
//     myFile.close();
// }

// #include <string>
// #include <fstream>
// #include <vector>
// #include <utility> // std::pair
// #include <stdexcept> // std::runtime_error
// #include <sstream> // std::stringstream

// std::vector<std::pair<std::string, std::vector<int>>> read_csv(std::string filename){
//     // Reads a CSV file into a vector of <string, vector<int>> pairs where
//     // each pair represents <column name, column values>

//     // Create a vector of <string, int vector> pairs to store the result
//     std::vector<std::pair<std::string, std::vector<int>>> result;

//     // Create an input filestream
//     std::ifstream myFile(filename);

//     // Make sure the file is open
//     if(!myFile.is_open()) 
//     throw std::runtime_error("Could not open file");

//     // Helper vars
//     std::string line, colname;
//     int val;

//     // Read the column names
//     if(myFile.good())
//     {
//         // Extract the first line in the file
//         std::getline(myFile, line);

//         // Create a stringstream from line
//         std::stringstream ss(line);

//         // Extract each column name
//         while(std::getline(ss, colname, ',')){
            
//             // Initialize and add <colname, int vector> pairs to result
//             result.push_back({colname, std::vector<int> {}});
//         }
//     }

//     // Read data, line by line
//     while(std::getline(myFile, line))
//     {
//         // Create a stringstream of the current line
//         std::stringstream ss(line);
        
//         // Keep track of the current column index
//         int colIdx = 0;
        
//         // Extract each integer
//         while(ss >> val){
            
//             // Add the current integer to the 'colIdx' column's values vector
//             result.at(colIdx).second.push_back(val);
            
//             // If the next token is a comma, ignore it and move on
//             if(ss.peek() == ',') ss.ignore();
            
//             // Increment the column index
//             colIdx++;
//         }
//     }

//     // Close file
//     myFile.close();

//     return result;
// }

int main() {

    // Read three_cols.csv and ones.csv    
    DBApp dbApp;
    dbApp.init();
    // Define table schema (column name → data type)
    std::string strTableName = "Student";
    // std::unordered_map<std::string, std::string> htblColNameType;
    // htblColNameType["id"] = "Integer";
    // htblColNameType["name"] = "String";
    // htblColNameType["gpa"] = "Double";
    // htblColNameType["DateOfBirth"] = "Date";

    //  std::unordered_map<std::string, std::any> colNameMin;
    //  colNameMin["id"] = 0;
    //  colNameMin["name"] = std::string("A");
    //  colNameMin["gpa"] = 0.7;
    //  colNameMin["DateOfBirth"] = Date(2002,06,21);
    //  std::unordered_map<std::string, std::any> colNameMax;
    //  colNameMax["id"] = 10000000;   
    //  colNameMax["name"] = std::string("ZZZZZZZZZZZZZ");
    //  colNameMax["gpa"] = 4.0;
    //  colNameMax["DateOfBirth"] = Date(2025,06,21);
    // Create table and index
    // try{
    //     dbApp.createTable(strTableName, "id", htblColNameType,colNameMin,colNameMax);
    // }catch(DBAppException e){
    //     std::cout << e.what() << std::endl;
    // }
    // dbApp.createIndex(strTableName, {"gpa"});

    // Insert rows
    std::unordered_map<std::string, std::any> htblColNameValue;

    // htblColNameValue["id"] = 80;
    // htblColNameValue["name"] = std::string("Obama");
    // htblColNameValue["gpa"] = 0.8;
    // // htblColNameValue["DateOfBirth"] = Date("2019-10-11");
    // try{
    // dbApp.insertIntoTable(strTableName, htblColNameValue);
    // }catch(DBAppException e){
    //     std::cout << e.what() << std::endl;
    // }
    // htblColNameValue["id"] = 30;
    // std::string clusteringKeyValue = "80";
    // htblColNameValue["id"] = 80;
    // htblColNameValue["gpa"] = 2.2;
    // htblColNameValue["DateOfBirth"] = Date("2020-9-15");
    // try{
    //     dbApp.updateTable(strTableName,clusteringKeyValue,htblColNameValue);
    // }catch(DBAppException e){
    //     std::cout << e.what() << std::endl;
    // }

    

    // htblColNameValue.clear();
    // htblColNameValue["id"] = 453455;
    // htblColNameValue["name"] = std::string("Ahmed Noor");
    // htblColNameValue["gpa"] = 0.95;
    // dbApp.insertIntoTable(strTableName, htblColNameValue);

    // htblColNameValue.clear();
    // htblColNameValue["id"] = 5674567;
    // htblColNameValue["name"] = std::string("Dalia Noor");
    // htblColNameValue["gpa"] = 1.25;
    // dbApp.insertIntoTable(strTableName, htblColNameValue);

    // htblColNameValue.clear();
    // htblColNameValue["id"] = 23498;
    // htblColNameValue["name"] = std::string("John Noor");
    // htblColNameValue["gpa"] = 1.5;
    // dbApp.insertIntoTable(strTableName, htblColNameValue);

    // htblColNameValue.clear();
    // htblColNameValue["id"] = 78452;
    // htblColNameValue["name"] = std::string("Zaky Noor");
    // htblColNameValue["gpa"] = 0.88;
    // dbApp.insertIntoTable(strTableName, htblColNameValue);

    // // Build SELECT query
    // std::vector<SQLTerm> arrSQLTerms(1);

    // arrSQLTerms[0]._strTableName = "Student";
    // arrSQLTerms[0]._strColumnName = "DateOfBirth";
    // arrSQLTerms[0]._strOperator = "=";
    // arrSQLTerms[0]._objValue = Date("2002-6-21");

    // Assuming input meets SQL Operator Precendence
    // NOT > AND > XOR > OR    
    // std::vector<std::string> strarrOperators = {};

    // // // Execute SELECT
    // try{
    //     dbApp.selectFromTable(arrSQLTerms, strarrOperators);
    // }catch(DBAppException e){
    //     std::cout << e.what() << std::endl;
    // }

    // htblColNameValue["name"] = std::string("bruce wayne");
    // htblColNameValue["id"] = 200;
    htblColNameValue["gpa"] = 1.4; 
    try{
        dbApp.deleteFromTable(strTableName,htblColNameValue);
    }catch(DBAppException e){
         std::cout << e.what() << std::endl;
    }
    return 0;
}
