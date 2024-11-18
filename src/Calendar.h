//
// Created by Sydney Maxwell Clements on 9/15/24.
//

#ifndef DEBUGGING_CALENDAR_H
#define DEBUGGING_CALENDAR_H

#include "Date.h"
#include "Month.h"
#include "DayOfWeek.h"

class Calendar
{
private:
    Date today;

public:
    // Default constructor
    Calendar();

    // Parameterized constructor
    Calendar(int pDay, Month pMonth, int pYear, DayOfWeek pDayOfWeek);

    // TODO: Additional member functions if needed (e.g., getters, setters, utility functions)
    // TODO: Graphical function to draw or represent calendar
};

#endif // DEBUGGING_CALENDAR_H
