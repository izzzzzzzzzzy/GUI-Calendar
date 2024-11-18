#include "DayOfWeek.h"
using namespace std;

// Utility function to convert DayOfWeek enum to string using if statements
string dayOfWeekToString(DayOfWeek day) {
    if (day == DayOfWeek::Sunday) {
        return "Sunday";
    } else if (day == DayOfWeek::Monday) {
        return "Monday";
    } else if (day == DayOfWeek::Tuesday) {
        return "Tuesday";
    } else if (day == DayOfWeek::Wednesday) {
        return "Wednesday";
    } else if (day == DayOfWeek::Thursday) {
        return "Thursday";
    } else if (day == DayOfWeek::Friday) {
        return "Friday";
    } else if (day == DayOfWeek::Saturday) {
        return "Saturday";
    } else {
        return "Unknown";
    }
}

// Overloaded == operator for comparing DayOfWeek with std::string
bool operator==(DayOfWeek day, const std::string& dayString) {
    return dayOfWeekToString(day) == dayString;
}

// Overloaded == operator for comparing string with DayOfWeek (symmetry)
bool operator==(const std::string& dayString, DayOfWeek day) {
    return day == dayString; // Reuse the first overload
}
