#include "Time.hpp"
#include <stdexcept>

    Time::Time(int Hour, int Minute, int Second)
    : hour(Hour), minute(Minute), second(Second)
    {
        if (hour < 0 || hour >= 24)
            throw std::invalid_argument("Invalid hour");

        if (minute < 0 || minute >= 60)
            throw std::invalid_argument("Invalid minute");

        if (second < 0 || second >= 60)
            throw std::invalid_argument("Invalid second");
}
    int Time::getHour() const{
        return hour;
    }

    int Time::getMinute() const{
        return minute;
    }

    int Time::getSecond() const{
        return second;
    }

    std::string Time::stringTime(){
        std::string StringTime = (hour < 10 ? "0" : "") + std::to_string(hour) + ":" + (minute < 10 ? "0" : "") + std::to_string(minute) + ":" + (second < 10 ? "0" : "") + std::to_string(second);
        return StringTime;
    }