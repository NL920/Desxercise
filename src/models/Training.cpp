#include "Training.hpp"
#include "Date.hpp"
#include "Time.hpp"

#include <iostream>

class Training{
         
public://popraw konstruktor
    Training(Date Date_, Time StartTime, Time EndTime, std::string Name, Status Status):
        date (Date_),endTime (EndTime),startTime (StartTime),name (Name),status(Status){}
};

void sendToDatabase(){
    //tutaj dodaj notowanie treningu do bazy
}