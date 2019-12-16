#include <iostream>

class Base_t{
public:
    int id;
};

class Derived_t: public Base_t{
public:
    int another;
};

void print_sizeof(Base_t &base)
{
    std::cout << sizeof(&base) << std::endl;
}

int main(){
    using namespace std;

    Base_t base;
    Derived_t derived;

    std::cout << sizeof(base) << std::endl;
    std::cout << sizeof(derived) << std::endl;

    print_sizeof(derived);

    cin.get();
    return 0;
}