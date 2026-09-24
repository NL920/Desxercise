#include <iostream>
#include <string>

#include "Training.hpp"
#include "Date.hpp"
#include "Time.hpp"
#include "Database.hpp"


Training::Training(Date Date_, Time StartTime, Time EndTime, std::string Name, Status Status):
    date (Date_),startTime (StartTime),endTime (EndTime),name (Name),status(Status){}


Time Training::getstartTime(){
    return startTime;
}

Time Training::getendTime(){
    return endTime;
}

std::string Training::getDate(){
    std::string newDate = date.stringDate();
    return newDate;
}

std::string Training::getName(){
    return name;
}

std::string Training::getStatus(){
    return stringStatus(status);
}

std::string Training::getTime(Time time){
    std::string newTime = time.stringTime();
    return newTime;
}

void changeTrainingStatus(){}
