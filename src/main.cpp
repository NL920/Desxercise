#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

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


/*mkdir build
cd build
cmake ..
cmake --build .
*/