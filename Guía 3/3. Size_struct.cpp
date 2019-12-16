#include <iostream>

struct Fecha_1{
    int day;
    int month;
    int year;
};

struct Fecha_2{
    int day;
    int month;
    int year;
    int next_day(){
        day++;
        return day;
    }
};

struct Fecha_3{
    int next_day(){
        return 24;
    }
};

int main()
{
    std::cout << "Con miembros:\t" << sizeof(Fecha_1) << std::endl
              << "Con miem. y func.:\t" << sizeof(Fecha_2) << std::endl
              << "Con funciones:\t" << sizeof(Fecha_3) << std::endl;
}