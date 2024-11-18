//
// Created by Sydney Maxwell Clements on 9/15/24.
//
#include "Calendar.h"

// Default constructor
Calendar::Calendar()
{
    today = Date(); // Use the default Date constructor
}

// Parameterized constructor
Calendar::Calendar(int pDay, Month pMonth, int pYear, DayOfWeek pDayOfWeek)
{
    today = Date(pDay, pMonth, pYear, pDayOfWeek); // Initialize with provided values
}
