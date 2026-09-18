#ifndef DATE
#define DATE

class Date{
public:
    Date(int Day, int Month, int Year);

    int getDay() const;
    int getMonth() const;
    int getYear() const;  

private:
    int day;
    int month;
    int year;
};

#endif