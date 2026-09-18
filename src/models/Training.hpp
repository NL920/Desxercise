#ifndef Training //czy to dobra nazwa
#define Training

#include "Date.hpp" //utworz
#include "Time.hpp"
#include "Status.hpp"
#include <string>

class Training{
public:
    Training();
    void sendToDatabase();
private:
    Date date;
    Time startTime; 
    Time endTime;
    std::string name;
    Status status;
};

#endif