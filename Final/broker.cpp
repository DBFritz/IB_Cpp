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
#include "broker.hpp"

using namespace std;

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

ConnectMsg::ConnectMsg(string user, string pass) : username(user), password(pass){
    Message::type = Message::Type::CONNECT;
}
ConnectMsg::Message *clone(){
    return (Message *)(new ConnectMsg(username, password)); // FIXME: Esto no me gusta para nada. FIXME: Liberar
}
ConnectMsg::string getUsername() const{
    return username;
}
ConnectMsg::string getPassword() const{
    return password;
}


// acknowledge de la conexión enviado del broker a los clientes
class ConnAckMsg : public Message {
    public:
        enum class Status { CONNECTION_OK, LOGIN_ERROR, /* OTHER_ERRORS... */ };
        ConnAckMsg(bool b){
            Message::type = Message::Type::CONNACK;
            if(b)
                status = Status::CONNECTION_OK;
            else
                status = Status::LOGIN_ERROR;
        }
        ConnAckMsg(ConnAckMsg::Status _status): status(_status) {} 
        Message *clone(void){
            return (Message *)(new ConnAckMsg(status)); // FIXME: Esto no me gusta para nada. FIXME: Liberar
        }

        Status getStatusType() const {
            return status;
        }
    private:
        Status status;
};

/*indica el tópico del mensaje, su valor y un flag que indica retención del mensaje. En nuestra
simplificación el tópico y el valor serán cadenas de caracteres. Es común que el tópico del mensaje
tenga la forma “aaaa/bbbb”.*/
class PublishMsg : public Message {
    private:
        TopicName topic;
        TopicValue value;
        bool retain;
    public:
        PublishMsg(TopicName n, TopicValue v, bool b):topic(n), value(v), retain(b){
            Message::type = Message::Type::PUBLISH;
        }
        TopicName getTopic() const{return topic;}
        TopicValue getValue() const {return value;}
        bool getRetain() const {return retain;}

};

/*indica que el cliente está interesado en recibir mensajes de un determinado tópico. En la
realidad el tópico puede tener * como wildcard para indicar un filtro de múltiples tópicos que cumplan
ese patrón.*/
class SubscribeMsg : public Message {
    /* ... */ 
};

// indica que el cliente no está más interesado en recibir mensajes de un determinado tópico.
class UnsubscribeMsg : public Message {
    /* ... */ 
};

//anuncio de desconexión de un cliente.
class DisconnectMsg : public Message {
    /* ... */ 
};


/* El Broker debería implementar un método BrokerOpsIFutilizarían los clientes para establecer la conexión.
*registerClient(ClientOpsIF *)  que utilizarían los clientes para establecer la conexión.

El Broker recibe una interface ClientOpsIF del cliente que utilizará para enviarle mensajes al cliente
(PublishMsg y ConAckMsg).*/

// Interface implementada por el cliente para recibir los tópicos subscriptos
class ClientOpsIF {
    public:
        virtual void recvMsg(const Message &) = 0;
};

// El cliente recibe del Broker una interface BrokerOpsIF que utiliza para enviar mensajes al Broker.
// Interface implementada por el Broker para enviarle mensajes
class BrokerOpsIF {
    public:
        BrokerOpsIF()=default;
        virtual void sendMsg(const Message &) = 0;
};

struct usr_pass{
    string username;
    string password;
};

class Client : BrokerOpsIF {
    private:
        thread th;
        ClientOpsIF *cif;
        //container<Subsciption *> subscriptions;
        //container<RetainedTopic *> topics;
        //cola<Message *> recvQueue;
    public:
        Client(ClientOpsIF *i):cif(i){}
        void sendMsg(const Message &m) {
            switch (m.getType()){
                case Message::Type::CONNECT:
                    cif->recvMsg(ConnAckMsg(ConnAckMsg::Status::CONNECTION_OK));
                    break;

                case Message::Type::PUBLISH:

                    break;
                case Message::Type::SUBSCRIBE:

                    break; 
                case Message::Type::UNSUBSCRIBE:

                    break; 
                case Message::Type::DISCONNECT:

                    break; 
                case Message::Type::CONNACK:
                    // I wasn't expecting this...
                    // this is embarrasing...
                    break;
            }
        //recvQueue.put(m.clone());
        }
        // ...
};

class Broker {
    private:
        unordered_map<ClientOpsIF *, Client *> clients; // caches para búsquedas eficientes
        //container<Subsciption *> subs_cache; // Múltiples subscripciones para un tópico
        //container<RetainedTopic *> topics_cache;
        static Broker* instance;
        Broker();
    public:
        static Broker* getInstance();
        BrokerOpsIF * registerClient(ClientOpsIF *c){
            unordered_map<ClientOpsIF *, Client *>::const_iterator got = clients.find(c);
            // if Client is not register, register it
            if ( got == clients.end() ){
                Client *Br = new Client(c); /// FIXME: Liberar
                clients.insert ( {c,Br} );
                return (BrokerOpsIF *) Br;
            } 
            else
                return (BrokerOpsIF *)got->second;
        }
        // ...
};

// Null, because instance will be initialized on demand.
Broker* Broker::instance = 0;

Broker* Broker::getInstance(){
    if (instance == 0){
        instance = new Broker();
    }
    return instance;
}

Broker::Broker(){};