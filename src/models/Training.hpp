#ifndef TRAINING
#define TRAINING

#include "Date.hpp" 
#include "Time.hpp"
#include "Status.hpp"
#include <string>

class Training{
public:
    Training(Date Date_, Time StartTime, Time EndTime, std::string Name, Status Status);

    Time getstartTime();
    Time getendTime();
    std::string getDate();
    std::string getTime(Time time);
    std::string getName();
    std::string getStatus();

    void changeStatus(Status newstatus); //to do

private:
    Date date;
    Time startTime; 
    Time endTime;
    std::string name;
    Status status;
};

#endif