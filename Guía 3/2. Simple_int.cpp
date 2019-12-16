#include <iostream>
class Simple{
    int val;
public:
    Simple(int value): val(value){
        std::cout << "Construyendo un Simple con el numero " << val << std::endl;
    }
    ~Simple(){
        std::cout << "Destruyendo un Simple con el numero " << val << std::endl;
    }
};

int main()
{
    Simple simple(3);
    goto pirulo;
    {
        Simple anotherSimple(4);  // Esto lo salta
    }
    pirulo:
    return 0;
}