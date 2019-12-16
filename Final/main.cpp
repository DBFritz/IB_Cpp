#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <unordered_map>
#include <mutex>
#include <condition_variable>
#include <ctime>
#include "broker.hpp"
#include "simclient.hpp"

int main(void){
    Broker* broker = Broker::getInstance();
    SimPublisher b(*broker);
    return 0;
}