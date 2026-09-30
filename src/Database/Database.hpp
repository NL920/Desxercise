#ifndef DATABASE_F
#define DATABASE_F

#include "Date.hpp"
#include "Time.hpp"
#include "Status.hpp"
#include "Training.hpp"

#include <sqlite3.h>

sqlite3* openDatabase(std::string name);

void createTrainingsTable();

void addTrainingToDatabase(std::string nameDatabase, Training training);

void replaceStatusInDatabase(std::string oldDate, std::string oldStartTime, Training newtraining);

void changeTrainingStatus(Training& training, Status newStatus);//ref do oryginału!

Training getTrainingFromDatabase(const std::string name, const std::string startTime);

#endif