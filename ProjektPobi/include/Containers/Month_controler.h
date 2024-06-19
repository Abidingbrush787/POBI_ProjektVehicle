#ifndef MONTH_H
#define MONTH_H

#include <string>

enum class Month {
    Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
};

// Funkcja do zamiany numeru miesiąca na jego nazwę skróconą
std::string monthToString(int month);

// Funkcja do zamiany nazwy miesiąca na numer miesiąca
int stringToMonth(const std::string& month);

#endif // MONTH_H
