#pragma once
# include <string>
# include <vector>
# include <filesystem>
class Date {
private:
    int year;
    int month;
    int day;
public:
    // Constructor(s) can be added as needed
    Date(int year, int month, int day);
    Date(std::string dateStr);
    // Date must have a copy constructor
    Date(const Date& date);
    // Operator overloading
    bool operator==(const Date& date);
    bool operator>(const Date& date) const;
    bool operator<(const Date& date) const;

    // Utility functions
    // getDate() is used to store date in csv file based on acceptable format
    std::string getDate() const;
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    void setYear(const int& year);
    void setMonth(const int& month);
    void setDay(const int& day);
};
