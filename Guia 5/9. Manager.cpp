#include <iostream>


class Manager{
    int id ;
    Manager(int ID = 0) : id(ID) {
        std::cout << "Soy el Manager, y vengo a construirme" << std::endl;
    }
    Manager() : Manager(0) {}
public:
    static Manager *getInstance(int ID=0){
        return new Manager(ID);
    }
    int getID() { return id; }
};

int main()
{
    Manager myNewManager();

    Manager * manager = Manager::getInstance(5);
    std::cout << manager->getID() << std::endl;
}

// Al parecer sí me deja. Qué sé yo! Estoy re loco.