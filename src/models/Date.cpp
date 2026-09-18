#include "Date.hpp"
#include <stdexcept>


    Date::Date(int Day, int Month, int Year)
        : day(Day), month(Month), year(Year)
    {
        if (day < 1 || day > 31)
            throw std::invalid_argument("Invalid day");

        if (month < 1 || month > 12)
            throw std::invalid_argument("Invalid month");

        if (year < 2026)
            throw std::invalid_argument("Invalid year");
    }

    int Date::getDay() const{
        return day;
    }

    int Date::getMonth() const{
        return month;
    }

    int Date::getYear() const{
        return year;
    }
