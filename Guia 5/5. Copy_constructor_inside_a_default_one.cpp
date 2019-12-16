#include <iostream>

class Test
{
public:
    Test(){}
    Test(const Test& test){
        std::cout << "Construí un Test por copia!" << std::endl;
    }
};

class Test_container
{
public:
    Test test;
};

void recibe_Test_container(Test_container toGet){
}

int main()
{
    Test_container myNewTestContainer;
    recibe_Test_container(myNewTestContainer);
}