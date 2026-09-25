#include <iostream>
#include <string>
//#include <chrono>
//#include <ctime>
#include <sqlite3.h>
#include <stdexcept>

#include "Database.hpp"
#include "Training.hpp"
#include "Time.hpp"
#include "Date.hpp"
#include "Status.hpp"

int main(){
Time firststart = Time(10,41,0);
Time firstend = Time(11,52,0);
Date firstdate = Date(24,9,2026);
std::string firstname = "Basen";
Status firststatus = Status(Status::Missed);
Training firsttr = Training(firstdate, firststart, firstend, firstname, firststatus);

openDatabase("trainings.db");
createTrainingsTable();
//addTrainingToDatabase("trainings.db",firsttr);
changeTrainingStatus(firsttr, Status::Completed);

std::cout<<"Udało się"<<std::endl;

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

/*sqlite3 trainings.db
.tables
.schema trainings
.quit*/