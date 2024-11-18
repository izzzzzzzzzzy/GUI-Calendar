//
// Created by Sydney Maxwell Clements on 9/15/24.
//

#ifndef MONTH_H
#define MONTH_H
#include <string>
using namespace std;


// Enum for months of the year
enum class Month {
    January = 1,
    February = 2,
    March = 3,
    April = 4,
    May = 5,
    June = 6,
    July = 7,
    August = 8,
    September = 9,
    October = 10,
    November = 11,
    December = 12
};

// Function to convert Month enum to a string
string monthToString(Month month);

// Overloaded operator== for comparing Month with a string
bool operator==(Month month, const string& monthString);

// Overloaded operator== for comparing a string with Month
bool operator==(const string& monthString, Month month);

#endif //M1OEP_MONTH_H
