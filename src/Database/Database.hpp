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

#endif