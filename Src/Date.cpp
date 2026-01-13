#include <chrono>
#include <sstream>
#include <string>
#include <ctime> // for time_t, tm, localtime, mktime, difftime
#include "Date.h"

using namespace std;

Date::Date() : day(0), month(0), year(0) {}

// May put checks here on days, months and years
Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

Date Date::getCurrentDate()
{
    // Here auto is chrono::time_point
    auto now = chrono::system_clock::now();
    // This gets data from the system clock ,can use high_resolution for getting time but it tells time in ticks rather than human-readable format
    // C++ uses chrono::time_point to store the time but due to this being highly sophisticated , we don't use it

    time_t now_c = chrono::system_clock::to_time_t(now);
    // This converts the time format into CTime Format as time manipulating functions can be done easily by this
    // time_t is a struct from C , which stores the time in C format
    // to_time_t( ) converts C++ time to C Format
    // from_time_t() converts C time to C++ Format

    tm *now_tm = localtime(&now_c);
    // localtime(Address of time_t Obj) , it breaks down the raw seconds since Epoch into month , date and years
    // You may use mktime(Address of time_t Obj)  , as it gives total seconds since Epoch from broken time , reverse of above
    // Epoch for older systems was : January 1, 1900, 00:00:00
    // Unix uses January 1, 1970, 00:00:00 as Epoch , might be in modern systems
    // Both localtime and mktime handle leap years and february correctly

    // Either create a new object like this , put all values and return its copy
    Date d;
    d.day = now_tm->tm_mday;
    d.month = now_tm->tm_mon + 1;
    d.year = now_tm->tm_year + 1900;
    // tm * keeps the time in its variables of tm_mday , tm_mon , tm_year etc
    // Access tm * by -> as it is a pointer

    return d;
}

Date Date::calculateDueDate()
{
    auto now = chrono::system_clock::now();
    // Add approximately one month (30 days)

    auto future = now + chrono::hours(24 * 30); // 30 Days and each day has 24 Hours
    // This is chrono::duration , you can write either unit like hours , minutes or
    // You can use it like a template by std::ratio and std::milli and other etc

    time_t future_c = chrono::system_clock::to_time_t(future);
    tm *future_tm = localtime(&future_c);
    return Date(future_tm->tm_mday, future_tm->tm_mon + 1, future_tm->tm_year + 1900);
    // Calls the paramterized constructor of the class and makes a copy of the Date object and returns it
}

string Date::toString() const
{
    return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
}

Date Date::fromString(const string &dateStr)
{
    stringstream ss(dateStr);
    int d, m, y;
    char delimiter;
    ss >> d >> delimiter >> m >> delimiter >> y;

    /*
    Date d1;
    d1.day = d;
    d1.month = m;
    d1.year = y;
    */

    return Date(d, m, y); // Calls the paramterized constructor of the class and makes a copy of the Date object and returns it
}

// We need to get the days remained
int Date::getDaysUntil(const Date &other) const
{
    tm tm1 = {0, 0, 0, day, month - 1, year - 1900};
    tm tm2 = {0, 0, 0, other.day, other.month - 1, other.year - 1900};
    // We assign using aggregate initializer to the tm struct template
    // month-1 refers to 0 -> January as mon+1 was done just for human readable format
    // Similarly for 1900

    time_t t1 = mktime(&tm1);
    // mktime(Address of time_t Obj) takes broken time and gives the original raw seconds since Epoch

    time_t t2 = mktime(&tm2);
    long long diff_seconds = difftime(t2, t1);
    // Find the difference between the seconds using the difftime function
    // While we could have performed t2-t1 subtraction as they are raw seconds
    // Using difftime() has advantages :
    // It handles the time zone and DST boundary issues
    // It ensures that return type is double always

    return diff_seconds / (60 * 60 * 24);
    // Converting seconds to days
    // 1 Day has 24 Hours , 1 Hour has 60 minutes and 1 minute has 60 seconds
}