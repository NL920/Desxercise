#include <iostream>
#include <stdexcept>
#include <string>
#include <sqlite3.h>

#include "Date.hpp"
#include "Time.hpp"
#include "Status.hpp"
#include "Training.hpp"
#include "Converters.hpp"

//do naprawienia, wskaźnik na bazę, gdzie umiescic funkcje, 
//zastąp kopiowanie referencją

sqlite3* openDatabase(std::string name){ //otwieranie bazy
    sqlite3* db = nullptr; //połączenie z bazą

    int result = sqlite3_open(name.c_str(), &db);

    if (result != SQLITE_OK)
        {
            std::cerr << "Nie udalo sie otworzyc bazy: "
                    << sqlite3_errmsg(db) << '\n';

            sqlite3_close(db);
            return nullptr;
        }

        std::cout << "Baza danych zostala otwarta!\n";
    return db;
}

void createTrainingsTable(){ //tworzenie tabeli jeżeli jej nie ma
    sqlite3* base = openDatabase("trainings.db");
    if (base == nullptr){
        return;
    }

    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS trainings (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            date DATE NOT NULL,
            startTime TIME,
            endTime TIME,
            name TEXT NOT NULL,
            status TEXT NOT NULL
        );
    )";

    char* errorMessage = nullptr;

    int result = sqlite3_exec(base, sql, nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK)
    {
        std::cerr << "Blad tworzenia tabeli: "
                  << errorMessage << '\n';

        sqlite3_free(errorMessage);
        sqlite3_close(base);
        return;
    }

    std::cout << "Tabela zostala utworzona!\n";
    sqlite3_close(base);

}


void addTrainingToDatabase(std::string nameDatabase, Training training){
    sqlite3 * base = openDatabase(nameDatabase);
    if (base == nullptr) {
        return;
    }

    const char* sql =
        "INSERT INTO trainings (date, startTime, endTime,name, status) VALUES (?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(base, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Błąd prepare: "
                  << sqlite3_errmsg(base) << std::endl;
        sqlite3_close(base);
        return;
    }

    std::string date=training.getDate();
    std::string startTime =  training.getTime(training.getstartTime());
    std::string endTime = training.getTime(training.getendTime());
    std::string name = training.getName(); 
    std::string status = training.getStatus();
    
    sqlite3_bind_text(stmt, 1, date.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, startTime.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, endTime.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, status.c_str(), -1, SQLITE_TRANSIENT); //przypilnuj żeby tu nie robił int
    

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Błąd INSERT: "
                  << sqlite3_errmsg(base) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(base);
    return;
}

void replaceStatusInDatabase(std::string oldDate, std::string oldStartTime, Training newtraining){
    sqlite3 * base = openDatabase("trainings.db");
    if (base == nullptr) {
        return;
    }

    const char* sql = "UPDATE trainings "
    "SET status = ? "
    "WHERE date = ? AND startTime = ?;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(base, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Błąd prepare: "
                  << sqlite3_errmsg(base) << std::endl;
        sqlite3_close(base);
        return;
    }

    std::string status = newtraining.getStatus();
    
    sqlite3_bind_text(stmt, 1, status.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, oldDate.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, oldStartTime.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Błąd INSERT: "
                  << sqlite3_errmsg(base) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(base);
    return;
}

void changeTrainingStatus(Training& training, Status newStatus){
    std::string oldDate = training.getDate();
    std::string oldStartTime = training.getTime(training.getstartTime());

    training.changeStatus(newStatus); //zmiana Statusu w obiekcie Trening
    replaceStatusInDatabase(oldDate, oldStartTime,training); //zmiana statusu w bazie
    
    std::cout<<"Status update finished"<<std::endl;
}

Training getTrainingFromDatabase(const std::string& date, const std::string& startTime){
    sqlite3 * base = openDatabase("trainings.db");
    if (base == nullptr) {
        throw std::runtime_error("Couldn't open database");
    }
    const char* sql = "SELECT  date, startTime, endTime, name, status" " FROM trainings "
    "WHERE date = ? AND startTime = ?;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(base, sql, -1, &stmt, nullptr) != SQLITE_OK) {
    std::string error = sqlite3_errmsg(base);
    sqlite3_close(base);

    throw std::runtime_error("Błąd prepare: " + error);
    }


    sqlite3_bind_text(stmt, 1, date.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, startTime.c_str(), -1, SQLITE_TRANSIENT);


    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string databaseDate =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

        std::string databaseStartTime =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

        std::string databaseEndTime =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        std::string databaseName =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

        std::string databaseStatus =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

        sqlite3_finalize(stmt);
        sqlite3_close(base);

        // zamiana string na Date, Time i Status - Converters.hpp
        Date trainingDate = stringToDate(databaseDate);
        Time trainingStartTime = stringToTime(databaseStartTime);
        Time trainingEndTime = stringToTime(databaseEndTime);
        Status trainingStatus = stringToStatus(databaseStatus);

        return Training(trainingDate,trainingStartTime,trainingEndTime,databaseName,trainingStatus);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(base);

    throw std::runtime_error("Nie znaleziono treningu");
}
