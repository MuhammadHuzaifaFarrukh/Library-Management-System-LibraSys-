#pragma once
#include <string>

using namespace std;

// Simple date class to handle due dates
class Date
{
private:
    int day, month, year;

public:
    Date();
    Date(int d, int m, int y);
    static Date getCurrentDate();

    static Date calculateDueDate();

    string toString() const;

    static Date fromString(const string &dateStr);

    int getDaysUntil(const Date &other) const;
};