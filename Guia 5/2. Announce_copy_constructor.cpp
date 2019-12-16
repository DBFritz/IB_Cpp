#include <iostream>

class Test
{
public:
    Test(){}
    Test(const Test& test)
    {
        std::cout << "Construí por copia!" << std::endl;
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
    Test myNewTest;
    std::cout << "Mandando un test..." << std::endl;
    recibe_Test(myNewTest);

    std::cout << "Recibiendo  un test..." << std::endl;
    myNewTest = retorna_Test();
    
    return 0;
}