#include <iostream>

class Test
{
public:
    Test(){}
    Test(const Test& test, double gravity = 9.8)
    {
        std::cout << "Construí por copia!, utilice una gravedad de " << gravity << std::endl;
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
    recibe_Test(myNewTest);
}