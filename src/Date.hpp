#pragma once
# include <string>
class Date {
private:
    int year;
    int month;
    int day;

public:
    // Constructor(s) can be added as needed
    Date(std::string year, std::string month, std::string day);
    // Date must have a copy constructor
    // Operator overloading
    Date& operator=(const Date& date);
    bool operator>(const Date& date) const;
    bool operator<(const Date& date) const;

    // Utility functions
    void printDate() const;
    int getYear() const;
    int getMonth() const;
    int getDay() const;
};
