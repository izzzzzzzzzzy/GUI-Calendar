//
// Created by Sydney Maxwell Clements on 9/15/24.
//

#ifndef DATE_H
#define DATE_H

#include <iostream>
#include "Month.h"
#include "DayOfWeek.h"

class Date
{
private:
    int fDay;
    Month fMonth;
    int fYear;
    // TODO: Make Day of week automatically set
    DayOfWeek fDayOfWeek;
    bool fIsLeapYear{};

public:
    // Constructor
    Date();
    Date(int pDay, const string &pMonth, int pYear);
    Date(int pDay, Month pMonth, int pYear, DayOfWeek pDayOfWeek);
    Date(int pDay, const string &pMonth, int pYear, const string &pDayOfWeek);
    // Date(int pDay, Month pMonth, int pYear);

    // Getters
    int getDay() const;
    Month getMonth() const;
    int getYear() const;
    DayOfWeek getDayOfWeek() const;
    bool getIsLeapYear() const;

    // Setters
    void setDay(int pDay);
    void setMonth(Month pMonth);
    void setYear(int pYear);
    void setDayOfWeek(DayOfWeek pDayOfWeek);

    // Utility to manipulate day
    bool incrementDay();
    bool incrementMonth();
    bool decrementMonth();
    bool incrementYear();
    bool decrementYear();
    void multiIncrementDay(int pDayNumber);

    // utility functions:
    bool validateDate();
    bool checkLeapYear() const;
    bool checkLeapYear(int pUserInput) const;
    bool findDayOfWeek();
    static Month stringToMonth(const string &pMonth);
    static DayOfWeek stringToDayOfWeek(const string &pDayOfWeek);
    int dateToInt() const;
    int dateToInt(Date pInputDate) const;
    int monthToDaysInt(Month pInputMonth) const;
    // Utility to display date
    void displayDate() const;
    // DayOfWeek firstDayFromMonthAndYear(Month month, int year);
    static DayOfWeek firstDayFromMonthAndYear(Month month, int year);
    bool equals(Date other);
};

#endif // DATE_H
