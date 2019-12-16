#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
//#include "final.h"
#include <unordered_map>
#include <mutex>
#include <condition_variable>
#include <ctime>
#include "simclient.hpp"
#include "broker.hpp"

using namespace std;

using TopicName = string;
using TopicValue = string;

class SimClient : public ClientOpsIF {
    protected:
        thread simth;
        Broker &broker;
        virtual void runSim() = 0;
    public:
        
        SimClient(Broker &b):broker(b){}
        ~SimClient(){}
        void start();
        virtual void recvMsg(const Message &){
        }
    // ...
};

/*
void SimClient::start()
// En pseudo C++
{
    simth = move(thread{&SimClient::runSim, this});
}
*/

// Ejemplo de un cliente Publisher
class SimPublisher : public SimClient {
    void runSim();
    Broker *b;
    public:
        SimPublisher(Broker &j);
        ~SimPublisher(){}
        bool connack_value;
        mutex m;
        condition_variable cond_var;
        bool ready;
        void recvMsg(const Message &m){
            switch ((int)m.getType()){
                case 1: // CONNACT
                {
                    ConnAckMsg *M = (ConnAckMsg *)&m;
                    recvConnack(M);
                    break;
                }
                case 2: // PUBLISH
                    break;
                default:
                    return; //ERROR -> DISCONNECT
            }
        }
        void recvConnack(ConnAckMsg *M){
            std::unique_lock<std::mutex> lock(m);
            switch ((int)(M->getStatusType())){
                case 0: // LOGIN_OK
                {
                    connack_value = true;
                    ready = true;
                    cond_var.notify_one();
                    break;
                }
                case 1: // LOGIN ERROR
                    connack_value = false;
                    ready = true;
                    cond_var.notify_one();
                    break;
            }
        }
    void Sense (string s){

    }
    // ...
};

SimPublisher::SimPublisher(Broker &j):SimClient(j){
    b = &j;
    ready = false;
    this->simth = thread(&SimPublisher::runSim, this);
    this->simth.join();
}

void SimPublisher::runSim()
{
    BrokerOpsIF *brops = broker.registerClient(this);
    brops->sendMsg(ConnectMsg("user", "pass")); // CONNECT
    // esperar por CONNACK sin errores
    std::unique_lock<std::mutex> lock(m);
    while(!connack_value){
        //cond_var.wait(lock); esto lo reemplace por lo siguiente:
        if(cond_var.wait_for(lock, std::chrono::seconds(4), [&](){return ready;})){
            break;
        }
        else{
            cout << "Loggin Error, no response of the broker" << endl;
            break;
        }
    }

    if (connack_value)
        cerr << "Connack recive -> OK" << endl;
    else
        cerr << "Connack recive -> Error" << endl; // DISCONNECT
    
    for (int i=0; i<5; ++i){
        std::this_thread::sleep_for (std::chrono::seconds(rand() % 4 + 1));

    }
    /*
    for( cierta cantidad de pasos ) {
        this_thread::sleep_for( un ratito random );
        PublishMsgfill m;
        m;
        brops->sendMsg(m); //PUBLISH
    }
    brops->sendMsg(DisconnectMsg{}); //DISCONNECT
    */
}
