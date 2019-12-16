#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

#include <unordered_map>
#include <mutex>
#include <condition_variable>
#include <ctime>

using namespace std;

using TopicName = string;
using TopicValue = string;

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

// primer mensaje enviado por un cliente a un broker. Lleva un nombre de usuario y su clave.
class ConnectMsg : public Message { 
    private:
    string username;
    string password;
    public:
        ConnectMsg(string user, string pass):username(user), password(pass){
            Message::type = Message::Type::CONNECT;
        }
        Message *clone(){}
        string getUsername() const{
            return username;
        }
        string getPassword() const{
            return password;
        }
};

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
        usr_pass u_p = {"$", "$"};
        Client(ClientOpsIF *i):cif(i){}
        void sendMsg(const Message &m) {
            switch ((int)m.getType()){
                case 0: // CONNECT 
                {
                    ConnectMsg *M = (ConnectMsg *)&m;
                    if (u_p.username == "$" && u_p.password=="$"){
                        Register_User(M);
                        cif->recvMsg(ConnAckMsg(true));
                        }
                    else if (check_username(M))
                        cif->recvMsg(ConnAckMsg(true));
                    else
                        cif->recvMsg(ConnAckMsg(false));
                    break;
                }
                // case 1 is connact. It is not necessary
                case 2: // PUBLISH
                {

                    break;}
                case 3: // SUBSCRIBE
                    break; 
                case 4: // UNSUSCRIBE
                    break; 
                case 5: // DISCONNECT
                    break; 
            }
        //recvQueue.put(m.clone());
        }
        void Register_User(ConnectMsg *M){
            //u_p.username = M->username;
            //u_p.password = M->password;
            return;
        }
        bool check_username (ConnectMsg *M) const {
            return true;
            //return (u_p.username == M->username && u_p.password == M->password);
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
            unordered_map<ClientOpsIF *, Client *>::const_iterator got = clients.find (c);
            // if Client is not register, register it
            if ( got == clients.end() ){
                Client *Br = new Client(c);
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

struct Subscription {
        TopicName topic;
        Client *owner;
};

struct RetainedTopic {
    TopicName topic;
    TopicValue value;
    Client *owner;
};


/* Las tareas que realiza cada cliente deberían
ejecutarse en un thread propio. Cuando se crea que un objeto SimClient se recibe una referencia al Broker ,
que le permitirá ejecutar el método registerClient.*/

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
        cout<< "Connack recive -> OK" << endl;
    else
        cout << "Connack recive -> Error" << endl; // DISCONNECT
    
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


int main(void){
    Broker* broker = Broker::getInstance();
    SimPublisher b(*broker);
    return 0;
}