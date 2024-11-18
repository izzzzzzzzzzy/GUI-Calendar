#include "Month.h"
using namespace std;

// Utility function to convert Month enum to string using if statements
string monthToString(Month month) {
    if (month == Month::January) {
        return "January";
    } else if (month == Month::February) {
        return "February";
    } else if (month == Month::March) {
        return "March";
    } else if (month == Month::April) {
        return "April";
    } else if (month == Month::May) {
        return "May";
    } else if (month == Month::June) {
        return "June";
    } else if (month == Month::July) {
        return "July";
    } else if (month == Month::August) {
        return "August";
    } else if (month == Month::September) {
        return "September";
    } else if (month == Month::October) {
        return "October";
    } else if (month == Month::November) {
        return "November";
    } else if (month == Month::December) {
        return "December";
    } else {
        return "Unknown";
    }
}
// Overloaded == operator for comparing Month with string
bool operator==(Month month, const string& monthString) {
    return monthToString(month) == monthString;
}

// Overloaded == operator for comparing string with Month (symmetry)
bool operator==(const string& monthString, Month month) {
    return month == monthString; // Reuse the first overload
}
