#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair
# include <unordered_map>
# include "DBApp.hpp"
# include "SQLTerm.hpp"
# include "iostream"
# include <chrono>
# include "Date.hpp"

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
    //  colNameMin["name"] = "A";
    //  colNameMin["gpa"] = 0.7;
    //  colNameMin["DateOfBirth"] = Date(2002,06,21);
    //  std::unordered_map<std::string, std::any> colNameMax;
    //  colNameMax["id"] = 10000000;   
    //  colNameMax["name"] = std::string("ZZZZZZZZZZZZZ");
    //  colNameMax["gpa"] = 0.67;
    //  colNameMax["DateOfBirth"] = Date(2002,07,21);
    // // Create table and index
    // try{
    //     dbApp.createTable(strTableName, "id", htblColNameType,colNameMin,colNameMax);
    // }catch(DBAppException e){
    //     std::cout << e.what() << std::endl;
    // }
    // // dbApp.createIndex(strTableName, {"gpa"});

    // Insert rows
    std::unordered_map<std::string, std::any> htblColNameValue;

    htblColNameValue["id"] = 2343432;
    htblColNameValue["name"] = std::string("Ahmed Noor");
    htblColNameValue["gpa"] = 0.95;
    dbApp.insertIntoTable(strTableName, htblColNameValue);

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
    // std::vector<SQLTerm> arrSQLTerms(2);
    // arrSQLTerms[0]._strTableName = "Student";
    // arrSQLTerms[0]._strColumnName = "name";
    // arrSQLTerms[0]._strOperator = "=";
    // arrSQLTerms[0]._objValue = std::string("John Noor");

    // arrSQLTerms[1]._strTableName = "Student";
    // arrSQLTerms[1]._strColumnName = "gpa";
    // arrSQLTerms[1]._strOperator = "=";
    // arrSQLTerms[1]._objValue = 1.5;

    // std::vector<std::string> strarrOperators = {"OR"};

    // // Execute SELECT
    // auto resultSet = dbApp.selectFromTable(arrSQLTerms, strarrOperators);

    // // Iterate and print results
    // for (const auto& row : resultSet) {
    //     std::cout << "Row:" << std::endl;
    //     for (const auto& [key, value] : row) {
    //         std::cout << "  " << key << ": ";
    //         if (value.type() == typeid(int)) std::cout << std::any_cast<int>(value);
    //         else if (value.type() == typeid(double)) std::cout << std::any_cast<double>(value);
    //         else if (value.type() == typeid(std::string)) std::cout << std::any_cast<std::string>(value);
    //         std::cout << std::endl;
    //     }
    // }

    return 0;
}


// int main() {
//     // Make three vectors, each of length 100 filled with 1s, 2s, and 3s
//     std::vector<int> vec1(100, 1);
//     std::vector<int> vec2(100, 2);
//     std::vector<int> vec3(100, 3);
    
//     // Wrap into a vector
//     std::vector<std::pair<std::string, std::vector<int>>> vals = {{"One", vec1}, {"Two", vec2}, {"Three", vec3}};
    
//     // Write the vector to CSV
//     write_csv("three_cols.csv", vals);
    
//     return 0;
// }
