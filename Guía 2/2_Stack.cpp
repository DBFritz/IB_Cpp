#include <iostream>
#include <list>

template <class T>
class Stack{
    std::list<T> list;

public:
    class Underflow { };
    class Overflow { };

    /// Constructor
    Stack() { }

    /// Destructor
    ~Stack()

    /// Agregar elementos
    void push(T toPush){
        list.push_front(toPush);
    }

    T pop(){
        T = list.pop_front()
    }
};
