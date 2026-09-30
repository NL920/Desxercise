#include <string>

#include "Date.hpp"
#include "Time.hpp"
#include "Status.hpp"

Date stringToDate(std::string& stringDate){
    int year = std::stoi(stringDate.substr(0, 4));
    int month = std::stoi(stringDate.substr(5, 2));
    int day = std::stoi(stringDate.substr(8, 2));

    return Date(day, month, year);
}

Time stringToTime(std::string& stringTime){
    int hour = std::stoi(stringTime.substr(0, 2));
    int minute = std::stoi(stringTime.substr(3, 2));
    int second = std::stoi(stringTime.substr(6, 2));
    return Time(hour, minute, second);
}
   
Status stringToStatus(std::string& stringStatus){
    if (stringStatus == "Proposed")
        return Status::Proposed;
    if (stringStatus == "Accepted")
        return Status::Accepted;
    if (stringStatus == "Planned")
        return Status::Planned;
    if (stringStatus == "Completed")
        return Status::Completed;
    if (stringStatus == "Missed")
        return Status::Missed;
    return Status::Unknown;
}