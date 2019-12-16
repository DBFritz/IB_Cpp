#include <iostream>

class Test
{
public:
    Test(){}
    Test(const Test& test)
    {
        std::cout << "Construí por copia!" << std::endl;
    }
    Test(Test&& test)
    {
        std::cout << "Construí por moverme!" << std::endl;
    }
};

Test retorna_Test()
{
    Test toReturn;
    return toReturn;
}

void recibe_Test(Test toGet){
}

int main()
{
    
}