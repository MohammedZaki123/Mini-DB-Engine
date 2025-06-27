# include "Date.hpp"
# include <vector>
# include <filesystem>
Date::Date(int year, int month, int day) 
:year(year), month(month) , day(day){
    // To be modified later
    // this->setYear(this->year);
    // this->setMonth(this->month);
    // this->setDay(this->day);
}
Date::Date(std::string dateStr){
    std::vector<std::string> result;
    std::stringstream ss(dateStr);
    std::string part;

    while (std::getline(ss, part, '-')) {
         result.push_back(part);
    }
   this->year = std::stoi(result[0]);
   this->month = std::stoi(result[1]);
   this->day = std::stoi(result[2]);
}

Date::Date(const Date& date){
    this->year = date.getYear();
    this->month = date.getMonth();
    this->day = date.getDay();
}
bool Date::operator==(const Date &date)
{
    if(this->year != date.getYear()){
        return false;
    }if(this->month != date.getMonth()){
        return false;
    }if(this->day != date.getDay()){
        return false;
    }
    return true;
}

bool Date::operator>(const Date &date) const
{
    if (this->year > date.year)
        return true;
    if (this->year < date.year)
        return false;

    // Years are equal
    if (this->month > date.month)
        return true;
    if (this->month < date.month)
        return false;

    // Months are also equal
    return this->day > date.day;
}

bool Date::operator<(const Date &date) const
{
     if (this->year < date.year)
        return true;
    if (this->year > date.year)
        return false;

    // Years are equal
    if (this->month < date.month)
        return true;
    if (this->month > date.month)
        return false;

    // Months are also equal
    return this->day < date.day;   
}

std::string Date::getDate() const
{
    std::string result = "";
    std::string y = std::to_string(year);
    std::string m = std::to_string(month); 
    std::string d = std::to_string(day);
    result.append(y + "-" + m + "-" + d);
    return result;
}

int Date::getYear() const
{
    return year;
}

int Date::getMonth() const
{
    return month;
}

int Date::getDay() const
{
    return day;
}

void Date::setYear(const int &year)
{
    this->year = year;
}

void Date::setMonth(const int &month)
{
    this->month = month;
}

void Date::setDay(const int &day)
{
    this->day = day;
}
