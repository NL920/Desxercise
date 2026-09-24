#ifndef TIME
#define TIME

#include <string>

class Time{
public:
    Time(int Hour, int Minute, int Second);

    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    std::string stringTime();

private:
    int hour;
    int minute;
    int second;
};

#endif