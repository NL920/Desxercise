#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <sqlite3.h>

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
        CREATE TABLE IF NOT EXISTS users (
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
}
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