#include <iostream>
#include <string>
//#include <chrono>
//#include <ctime>
#include <sqlite3.h>
#include <stdexcept>

enum class Status {
    Proposed,
    Accepted,
    Planned,
    Completed,
    Missed
};

class Date{
    int day;
    int month;
    int year;
public:
    Date(int Day, int Month, int Year)
        : day(Day), month(Month), year(Year)
    {
        if (day < 1 || day > 31)
            throw std::invalid_argument("Invalid day");

        if (month < 1 || month > 12)
            throw std::invalid_argument("Invalid month");

        if (year < 2026)
            throw std::invalid_argument("Invalid year");
}

    int getDay() const{
        return day;
    }

    int getMonth() const{
        return month;
    }

    int getYear() const{
        return year;
    }
};

class Time{
    int hour;
    int minute;
    int second;
public:
    Time(int Hour, int Minute, int Second)
    : hour(Hour), minute(Minute), second(Second)
    {
        if (hour < 0 || hour >= 24)
            throw std::invalid_argument("Invalid hour");

        if (minute < 0 || minute >= 60)
            throw std::invalid_argument("Invalid minute");

        if (second < 0 || second >= 60)
            throw std::invalid_argument("Invalid second");
}
    int getHour() const{
        return hour;
    }

    int getMinute() const{
        return minute;
    }

    int getSecond() const{
        return second;
    }
};

class Training{
        Date date;
        Time startTime; 
        Time endTime;
        std::string name;
        Status status; //lepiej klasa status czy klasyczny string
public://popraw konstruktor
    Training(Date Date_, Time StartTime, Time EndTime, std::string Name, Status Status){
        date = Date_;
        endTime = EndTime;
        startTime = StartTime;
        name = Name;
        status = Status;

    }


};

void sendToDatabase(){
    //tutaj dodaj notowanie treningu do bazy
}

int main()
{
    sqlite3* db = nullptr; //połączenie z bazą

    int result = sqlite3_open("trainings.db", &db);

    if (result != SQLITE_OK)
    {
        std::cerr << "Nie udalo sie otworzyc bazy: "
                  << sqlite3_errmsg(db) << '\n';

        sqlite3_close(db);
        return 1;
    }

    std::cout << "Baza danych zostala otwarta!\n";

    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS trainings (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            date DATE NOT NULL,
            StartTime TIME,
            EndTime TIME,
            name TEXT NOT NULL,
            status TEXT NOT NULL
        );
    )";

    char* errorMessage = nullptr;

    result = sqlite3_exec(db, sql, nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK)
    {
        std::cerr << "Blad tworzenia tabeli: "
                  << errorMessage << '\n';

        sqlite3_free(errorMessage);
        sqlite3_close(db);
        return 1;
    }

    std::cout << "Tabela users zostala utworzona!\n";

    sqlite3_close(db);

    return 0;
};

/*
int main(){
for(int i =0; i<3;i++){
    std::string trening;
    std::cout<<"What exercises did you do today?"<<std::endl;
    std::cin>>trening;
    {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);

        std::cout << "Trening: "<<trening<<" finished on day: "<<std::ctime(&time);

        
    }
}

return 0;
}
*/

/*mkdir build
cd build
cmake ..
cmake --build .
*/