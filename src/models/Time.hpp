#ifndef TIME
#define TIME
class Time{
public:
    Time(int Hour, int Minute, int Second);

    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    std::string Time::stringTime();

private:
    int hour;
    int minute;
    int second;
};

#endif