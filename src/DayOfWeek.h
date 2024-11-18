//
// Created by Sydney Maxwell Clements on 9/15/24.
//

#ifndef DAYOFWEEK_H
#define DAYOFWEEK_H

#include <string>

// Enum for days of the week
enum class DayOfWeek {
    Sunday = 1,
    Monday = 2,
    Tuesday = 3,
    Wednesday = 4,
    Thursday = 5,
    Friday = 6,
    Saturday = 7
};

// Function to convert DayOfWeek enum to a string
std::string dayOfWeekToString(DayOfWeek day);

// Overloaded operator== for comparing DayOfWeek with a string
bool operator==(DayOfWeek day, const std::string& dayString);

// Overloaded operator== for comparing a string with DayOfWeek
bool operator==(const std::string& dayString, DayOfWeek day);

#endif //M1OEP_DAYOFWEEK_H
