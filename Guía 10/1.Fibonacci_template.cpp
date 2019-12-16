#include <iostream>
#include <complex>


template <class type_t = unsigned long int>
type_t Fibonacci(uint32_t index, type_t first_element = 0, type_t second_element = 1)
{
    if (index == 0) return 0;
    if (index == 1) return first_element;
    if (index == 2) return second_element;
    return Fibonacci(index-1, first_element, second_element) + Fibonacci(index-2, first_element, second_element);
}

int main(){
    using namespace std;
    complex<double> lala = 1;
    complex<double> null = 0;
    cout << Fibonacci(4,null,lala) << endl;

    cin.get();
}