#ifndef DATABASE_F
#define DATABASE_F

#include "Date.hpp"
#include "Time.hpp"
#include "Status.hpp"
#include "Training.hpp"

#include <sqlite3.h>

sqlite3* openDatabase(std::string name);

void createTrainingsTable(std::string database);

void addTrainingToDatabase(std::string nameDatabase, Training training);

void replaceStatusInDatabase(std::string database, std::string oldDate, std::string oldStartTime, Training newtraining);

void changeTrainingStatus(std::string database, Training& training, Status newStatus);//ref do oryginału!

Training getTrainingFromDatabase(std::string database, const std::string& name, const std::string& startTime);

#endif