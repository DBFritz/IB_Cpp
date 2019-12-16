#include <iostream>
class Simple{
    public:
    Simple(){
        std::cout << "Construyendo un Simple" << std::endl;
    }
    ~Simple(){
        std::cout << "Destruyendo un Simple" << std::endl;
    }
};

int main()
{
    Simple simple;
    {
        Simple aSimpleinaScope;
    }

    Simple anotherSimple;


    return 0;
}