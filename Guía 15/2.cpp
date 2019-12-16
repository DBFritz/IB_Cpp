#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>
#include <queue>
#include <chrono>
#include <string>

std::mutex mutex_light;
std::condition_variable cv_light;


void light(std::string colour, int ms)
{
    do{
        std::unique_lock<std::mutex> lck{mutex_light};
        cv_light.wait(lck);
        std::cout << colour << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds{ms});
        lck.unlock();
        cv_light.notify_one();
    }while(1);
}

int main(void)
{
    std::thread green{light, "VERDE", 1000}; 
    std::thread yellow{light, "ROJO", 1000}; 
    std::thread red{light, "VERDE", 1000}; 

    green.join();
    yellow.join();
    red.join();
    
    return 0;
}