#ifndef _BROKER_HPP_
#define _BROKER_HPP_ 1.0

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <unordered_map>
#include <mutex>
#include <condition_variable>
#include <ctime>

using TopicName = std::string;
using TopicValue = std::string;

class Message {
    public:
        enum class Type { CONNECT, CONNACK, PUBLISH, SUBSCRIBE, UNSUBSCRIBE, DISCONNECT };
        Type getType() const{
            return type;
        }
        virtual Message *clone() = 0; // para evitar object splicing
    protected:
        Type type;
        // ...
};

class ConnectMsg : public Message { 
    private:
        string username;
        string password;
    public:
        ConnectMsg(string user, string pass);
        Message *clone();
        string getUsername();
        string getPassword();
};

    class ConnAckMsg;
    class PublishMsg;
    class SubscribeMsg;
    class UnsubscribeMsg;
    class DisconnectMsg;

class ClientOpsIF;

class BrokerOpsIF;
    class Client;

class Broker;

struct Subscription {
        TopicName topic;
        Client *owner;
};

struct RetainedTopic {
    TopicName topic;
    TopicValue value;
    Client *owner;
};

#endif