//
// Created by Sydney Maxwell Clements on 9/15/24.
//
#include "Date.h"
using namespace std;
// TODO: (HALF DONE) Create full date verification (checking if February 31st is a date and so on)
// Constructor implementation
Date::Date() : Date(1, "January", 1960, "Friday") {}

Date::Date(int pDay, const string &pMonth, int pYear)
{
    fDay = pDay;
    fMonth = stringToMonth(pMonth);
    fYear = pYear;
    fIsLeapYear = checkLeapYear();
    fDayOfWeek = DayOfWeek::Sunday;
    findDayOfWeek();
}
Date::Date(int pDay, Month pMonth, int pYear, DayOfWeek pDayOfWeek)
    : fDay(pDay), fMonth(pMonth), fYear(pYear), fDayOfWeek(pDayOfWeek), fIsLeapYear(checkLeapYear())
{
}

Date::Date(int pDay, const string &pMonth, int pYear, const string &pDayOfWeek)
{
    fDay = pDay;
    fMonth = stringToMonth(pMonth);
    fYear = pYear;
    fDayOfWeek = stringToDayOfWeek(pDayOfWeek);
    fIsLeapYear = checkLeapYear();
}
// Getter implementations
int Date::getDay() const
{
    return fDay;
}

Month Date::getMonth() const
{
    return fMonth;
}

int Date::getYear() const
{
    return fYear;
}

DayOfWeek Date::getDayOfWeek() const
{
    return fDayOfWeek;
}
bool Date::getIsLeapYear() const
{
    return fIsLeapYear;
}

// Setter implementations
void Date::setDay(int pDay)
{
    fDay = pDay;
}

void Date::setMonth(Month pMonth)
{
    fMonth = pMonth;
}

void Date::setYear(int pYear)
{
    fYear = pYear;
}

void Date::setDayOfWeek(DayOfWeek pDayOfWeek)
{
    fDayOfWeek = pDayOfWeek;
}

// Increment functions
bool Date::incrementDay()
{
    // Array for days in each month
    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Determine the maximum day for the current month
    int maxDay = daysInMonth[static_cast<int>(fMonth) - 1];
    // Account for leap years
    if (fIsLeapYear && static_cast<int>(fMonth) == 2)
    {
        maxDay++;
    }

    fDay++;

    // Handle day overflow and month increment
    if (fDay > maxDay)
    {
        fDay = 1;         // Reset to the first day of the next month
        incrementMonth(); // Handle month increment and overflow
    }

    // Increment day of the week, wrap around after Saturday
    fDayOfWeek = static_cast<DayOfWeek>((static_cast<int>(fDayOfWeek) % 7) + 1);

    return true;
}

bool Date::incrementMonth()
{
    fMonth = static_cast<Month>(static_cast<int>(fMonth) + 1);

    // Handle month overflow and year increment
    if (fMonth > Month::December)
    {
        fMonth = Month::January;
        incrementYear(); // Increment the year if we overflow the month
    }
    findDayOfWeek();
    return true;
}
bool Date::decrementMonth()
{
    if(fMonth==Month::January){
        fYear--;
        fMonth = Month::December;

    } else{
        fMonth = static_cast<Month>(static_cast<int>(fMonth) - 1);
    }
    findDayOfWeek();
    return true;
}
bool Date::incrementYear()
{
    fYear++;
    fIsLeapYear = checkLeapYear();
    return true;
}
bool Date::decrementYear()
{
    fYear--;
    fIsLeapYear = checkLeapYear();
    return true;
}
void Date::multiIncrementDay(int pDayNumber)
{
    int i;
    for (i = 0; i < pDayNumber; i++)
    {
        incrementDay();
    }
}

bool Date::validateDate()
{
    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (fDay <= daysInMonth[(int)fMonth - 1] + ((int)fMonth == 2 && fIsLeapYear))
    {
        return true;
    }
    return false;
}
bool Date::checkLeapYear() const
{
    if (fYear % 400 == 0 || (fYear % 4 == 0 && fYear % 100 != 0))
    {
        return true;
    }
    return false;
}
bool Date::checkLeapYear(int pUserInput) const
{
    if (pUserInput % 400 == 0 || (pUserInput % 4 == 0 && pUserInput % 100 != 0))
    {
        return true;
    }
    return false;
}
bool Date::findDayOfWeek()
{
    // Declare the week as a collection of DayOfWeek objects
    static const DayOfWeek theWeek[] = {DayOfWeek::Sunday, DayOfWeek::Monday, DayOfWeek::Tuesday, DayOfWeek::Wednesday, DayOfWeek::Thursday, DayOfWeek::Friday, DayOfWeek::Saturday};

    // If the year is before 1960, throw an exception even though we can easily do before this
    if (this->fYear < 1960)
    {
        throw invalid_argument("Date before Jan 1st 1960");
    }
    else
    {
        // Start at 1960 where January 1st was a Friday
        int yearCurr = 1960;
        // Friday is index 5
        int currDayAsVectorIndex = 5;
        // Loop through each year from 1960 to fYear
        while (yearCurr < this->fYear)
        {
            if (!checkLeapYear(yearCurr))
            {
                // Isnt a leap year
                currDayAsVectorIndex = (currDayAsVectorIndex + 1) % 7;
            }
            else
            {
                // Is a leap year
                currDayAsVectorIndex = (currDayAsVectorIndex + 2) % 7;
            }
            yearCurr++;
        }
        // Now we are at January 1st of the target year
        // Calculate the difference between Jan 1st and the target date
        int diffOfDateDayAsInt = dateToInt() - 1;
        // Loop to adjust the day of the week by the number of days since Jan 1st
        for (int i = 0; i < diffOfDateDayAsInt; i++)
        {
            currDayAsVectorIndex = (currDayAsVectorIndex + 1) % 7;
        }
        // Set the correct day of the week
        setDayOfWeek(theWeek[currDayAsVectorIndex]);
        return true;
    }
}

// Takes an input string from a user, and converts it to an equal Month value and returns
Month Date::stringToMonth(const string &pMonth)
{
    if (pMonth == "january" || pMonth == "jan" || pMonth == "January" || pMonth == "Jan")
    {
        return Month::January;
    }
    else if (pMonth == "february" || pMonth == "feb" || pMonth == "February" || pMonth == "Feb")
    {
        return Month::February;
    }
    else if (pMonth == "march" || pMonth == "mar" || pMonth == "March" || pMonth == "Mar")
    {
        return Month::March;
    }
    else if (pMonth == "april" || pMonth == "apr" || pMonth == "April" || pMonth == "Apr")
    {
        return Month::April;
    }
    else if (pMonth == "may" || pMonth == "May")
    {
        return Month::May;
    }
    else if (pMonth == "june" || pMonth == "jun" || pMonth == "June" || pMonth == "Jun")
    {
        return Month::June;
    }
    else if (pMonth == "july" || pMonth == "jul" || pMonth == "July" || pMonth == "Jul")
    {
        return Month::July;
    }
    else if (pMonth == "august" || pMonth == "aug" || pMonth == "August" || pMonth == "Aug")
    {
        return Month::August;
    }
    else if (pMonth == "september" || pMonth == "sep" || pMonth == "September" || pMonth == "Sep")
    {
        return Month::September;
    }
    else if (pMonth == "october" || pMonth == "oct" || pMonth == "October" || pMonth == "Oct")
    {
        return Month::October;
    }
    else if (pMonth == "november" || pMonth == "nov" || pMonth == "November" || pMonth == "Nov")
    {
        return Month::November;
    }
    else if (pMonth == "december" || pMonth == "dec" || pMonth == "December" || pMonth == "Dec")
    {
        return Month::December;
    }
    else
    {
        throw invalid_argument("Month not found");
    }
}
DayOfWeek Date::stringToDayOfWeek(const string &pDayOfWeek)
{
    if (pDayOfWeek == "sunday" || pDayOfWeek == "sun" || pDayOfWeek == "Sunday" || pDayOfWeek == "Sun")
    {
        return DayOfWeek::Sunday;
    }
    else if (pDayOfWeek == "monday" || pDayOfWeek == "mon" || pDayOfWeek == "Monday" || pDayOfWeek == "Mon")
    {
        return DayOfWeek::Monday;
    }
    else if (pDayOfWeek == "tuesday" || pDayOfWeek == "tue" || pDayOfWeek == "Tuesday" || pDayOfWeek == "Tue")
    {
        return DayOfWeek::Tuesday;
    }
    else if (pDayOfWeek == "wednesday" || pDayOfWeek == "wed" || pDayOfWeek == "Wednesday" || pDayOfWeek == "Wed")
    {
        return DayOfWeek::Wednesday;
    }
    else if (pDayOfWeek == "thursday" || pDayOfWeek == "thu" || pDayOfWeek == "Thursday" || pDayOfWeek == "Thu")
    {
        return DayOfWeek::Thursday;
    }
    else if (pDayOfWeek == "friday" || pDayOfWeek == "fri" || pDayOfWeek == "Friday" || pDayOfWeek == "Fri")
    {
        return DayOfWeek::Friday;
    }
    else if (pDayOfWeek == "saturday" || pDayOfWeek == "sat" || pDayOfWeek == "Saturday" || pDayOfWeek == "Sat")
    {
        return DayOfWeek::Saturday;
    }
    else
    {
        throw invalid_argument("Date not found");
    }
}
int Date::dateToInt() const
{
    static const int cumulativeDayCount[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    // Adds the cumulative day count to the current day, to get the day of year as int.
    // The last part checks if it is a leap year and the month is BIGGER than 2, and if both are correct then it adds one to account for the leap day
    return cumulativeDayCount[(int)this->getMonth() - 1] + this->getDay() + (int)(fIsLeapYear && ((int)this->getMonth() > 2));
}
int Date::dateToInt(Date pInputDate) const
{
    static const int cumulativeDayCount[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    // Adds the cumulative day count to the current day, to get the day of year as int.
    // The last part checks if it is a leap year and the month is BIGGER than 2, and if both are correct then it adds one to account for the leap day
    return cumulativeDayCount[(int)pInputDate.getMonth() - 1] + pInputDate.getDay() + (int)(pInputDate.getIsLeapYear() && ((int)pInputDate.getMonth() > 2));
}
int Date::monthToDaysInt(Month pInputMonth) const
{
    static const int cumulativeDayCount[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    return cumulativeDayCount[(int)pInputMonth];
}

// Utility function to display the date
void Date::displayDate() const
{
    cout << "Today's date is " << dayOfWeekToString(fDayOfWeek) << " " << static_cast<int>(fMonth) << " / " << fDay << " / " << fYear << endl;
}

DayOfWeek Date::firstDayFromMonthAndYear(Month month, int year)
{
    Date reference = Date(1, monthToString(month), year);
    return reference.getDayOfWeek();
}
bool Date::equals(Date other){
    return (fDay == other.getDay()) && (fMonth == other.getMonth()) && (fYear == other.getYear());
}
